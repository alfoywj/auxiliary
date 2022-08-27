//
// Created by redbean on 22. 8. 25.
//
#include <cstring>
#include "render_interface.h"

#include "shaders/mesh.frag.h"
#include "shaders/mesh.vert.h"

void createBuffer(VkBundle *vk, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties,
                  render_buffer *pRenderBuffer) {
    pRenderBuffer->size = size;
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    VK_CHECK(vkCreateBuffer(vk->mVkDevice, &bufferInfo, nullptr, &pRenderBuffer->buffer));

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(vk->mVkDevice, pRenderBuffer->buffer, &memRequirements);

    pRenderBuffer->alignment = memRequirements.alignment;

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = 0;

    vk->AllocateMemoryTypeFromProperties(memRequirements.memoryTypeBits,
                                         properties,
                                         &allocInfo.memoryTypeIndex);

    VK_CHECK(vkAllocateMemory(vk->mVkDevice, &allocInfo, nullptr, &pRenderBuffer->memory));

    pRenderBuffer->allocation_size = allocInfo.allocationSize;

    VK_CHECK(vkBindBufferMemory(vk->mVkDevice, pRenderBuffer->buffer, pRenderBuffer->memory, 0));
}

void create_render_mesh(VkBundle *vkBundle, ote_data_mesh *pDataMesh, render_mesh *pRenderMesh) {

    {
        createBuffer(vkBundle, pDataMesh->vertex_count * pDataMesh->stride * sizeof(float),

                     VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                     VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                     &pRenderMesh->vertexBuffer);
    }
    {
        createBuffer(vkBundle, pDataMesh->index_count * sizeof(uint32_t),
                     VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
                     VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                     &pRenderMesh->indexBuffer);
    }
}

void update_render_mesh(VkBundle *vkBundle, ote_data_mesh *pDataMesh, render_mesh *pRenderMesh) {
    {
        void *data{};
        vkMapMemory(vkBundle->mVkDevice, pRenderMesh->vertexBuffer.memory, 0, pRenderMesh->vertexBuffer.size, 0, &data);

        memcpy(data, pDataMesh->vertices, (size_t) pRenderMesh->vertexBuffer.size);
        vkUnmapMemory(vkBundle->mVkDevice, pRenderMesh->vertexBuffer.memory);
    }
    {
        void *data{};
        vkMapMemory(vkBundle->mVkDevice, pRenderMesh->indexBuffer.memory, 0, pRenderMesh->indexBuffer.size, 0, &data);

        memcpy(data, pDataMesh->indices, (size_t) pRenderMesh->indexBuffer.size);
        vkUnmapMemory(vkBundle->mVkDevice, pRenderMesh->indexBuffer.memory);
    }
}

void shader_load(VkDevice vkDevice, const uint32_t *code, size_t size, VkShaderModule *out_module) {
    VkShaderModuleCreateInfo info = {
            .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
            .codeSize = size,
            .pCode = code,
    };

    VkShaderModule module;
    VK_CHECK(vkCreateShaderModule(vkDevice, &info, NULL, &module));
    *out_module = module;
}

//https://github.com/KhronosGroup/Vulkan-Guide/blob/master/chapters/vertex_input_data_processing.adoc
void load_mesh_shader(VkBundle *vkBundle, render_shader *mesh_shader) {
    shader_load(vkBundle->mVkDevice, shaders_mesh_vert, sizeof(shaders_mesh_vert), &mesh_shader->vertShader);
    shader_load(vkBundle->mVkDevice, shaders_mesh_frag, sizeof(shaders_mesh_frag), &mesh_shader->fragShader);
    mesh_shader->vertexInputBindingDescription.push_back({
                                                                 0,                          // binding
                                                                 sizeof(float) * 4,             // stride
                                                                 VK_VERTEX_INPUT_RATE_VERTEX // inputRate
                                                         });
    mesh_shader->vertexInputAttributeDescription.push_back(
            {
                    0,
                    0,
                    VK_FORMAT_R32G32B32A32_SFLOAT,
                    0
            });
}

void load_mesh_pipeline(VkBundle *vkBundle, render_pipeline *mesh_pipeline, render_shader* pRenderShader, VkRenderPass* pRenderPass) {
    const VkDescriptorSetLayoutCreateInfo descriptor_layout = {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
            .pNext = NULL,
            .bindingCount = 0,
            .pBindings = VK_NULL_HANDLE,
    };

    VK_CHECK(vkCreateDescriptorSetLayout(vkBundle->mVkDevice, &descriptor_layout, NULL, &mesh_pipeline->descriptorSetLayout));

    const VkPipelineLayoutCreateInfo pPipelineLayoutCreateInfo = {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
            .pNext = NULL,
            .setLayoutCount = 1,
            .pSetLayouts = &mesh_pipeline->descriptorSetLayout,
    };

    VK_CHECK(vkCreatePipelineLayout(vkBundle->mVkDevice, &pPipelineLayoutCreateInfo, NULL, &mesh_pipeline->pipelineLayout));


    VkGraphicsPipelineCreateInfo graphicsPipelineCreateInfo{VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO};

    VkPipelineVertexInputStateCreateInfo vi{VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO};
    vi.vertexBindingDescriptionCount = pRenderShader->vertexInputBindingDescription.size();
    vi.pVertexBindingDescriptions = pRenderShader->vertexInputBindingDescription.data();
    vi.vertexAttributeDescriptionCount = pRenderShader->vertexInputAttributeDescription.size();
    vi.pVertexAttributeDescriptions = pRenderShader->vertexInputAttributeDescription.data();


    VkPipelineInputAssemblyStateCreateInfo ia{VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO};
    ia.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

    VkPipelineRasterizationStateCreateInfo rs{VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO};
    rs.polygonMode = VK_POLYGON_MODE_LINE;
    rs.cullMode = VK_CULL_MODE_NONE;
    rs.frontFace = VK_FRONT_FACE_CLOCKWISE;
    rs.depthClampEnable = VK_FALSE;
    rs.rasterizerDiscardEnable = VK_FALSE;
    rs.depthBiasEnable = VK_FALSE;
    rs.lineWidth = 1.0f;

    VkPipelineColorBlendAttachmentState cba;
    cba.colorWriteMask = 0xf;
    cba.blendEnable = VK_FALSE;

    VkPipelineColorBlendStateCreateInfo cb{VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO};
    cb.attachmentCount = 1;
    cb.pAttachments = &cba;


    VkPipelineDepthStencilStateCreateInfo ds{VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO};
    ds.depthTestEnable = VK_TRUE;
    ds.depthWriteEnable = VK_TRUE;
    ds.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
    ds.depthBoundsTestEnable = VK_FALSE;
    ds.back.failOp = VK_STENCIL_OP_KEEP;
    ds.back.passOp = VK_STENCIL_OP_KEEP;
    ds.back.compareOp = VK_COMPARE_OP_ALWAYS;
    ds.stencilTestEnable = VK_FALSE;
    ds.front = ds.back;

    VkDynamicState dynamicStateEnables[2] {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};
    VkPipelineDynamicStateCreateInfo dynamicState{VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO};
    dynamicState.dynamicStateCount = 2;
    dynamicState.pDynamicStates = dynamicStateEnables;

    VkPipelineViewportStateCreateInfo vp{VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO};
    vp.viewportCount = 1;
    vp.scissorCount = 1;

    VkPipelineMultisampleStateCreateInfo ms{VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO};
    ms.pSampleMask = NULL;
    ms.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

    VkPipelineShaderStageCreateInfo shaderStages[2];
    memset(&shaderStages, 0, 2 * sizeof(VkPipelineShaderStageCreateInfo));

    shaderStages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
    shaderStages[0].module = pRenderShader->vertShader;
    shaderStages[0].pName = "main";

    shaderStages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    shaderStages[1].module = pRenderShader->fragShader;
    shaderStages[1].pName = "main";

    graphicsPipelineCreateInfo.layout = mesh_pipeline->pipelineLayout;
    graphicsPipelineCreateInfo.pVertexInputState = &vi;
    graphicsPipelineCreateInfo.pInputAssemblyState = &ia;
    graphicsPipelineCreateInfo.pRasterizationState = &rs;
    graphicsPipelineCreateInfo.pColorBlendState = &cb;
    graphicsPipelineCreateInfo.pMultisampleState = &ms;
    graphicsPipelineCreateInfo.pViewportState = &vp;
    graphicsPipelineCreateInfo.pDepthStencilState = &ds;
    graphicsPipelineCreateInfo.stageCount = 2;
    graphicsPipelineCreateInfo.pStages = shaderStages;
    graphicsPipelineCreateInfo.renderPass = *pRenderPass;
    graphicsPipelineCreateInfo.pDynamicState = &dynamicState;

    VK_CHECK(vkCreateGraphicsPipelines(vkBundle->mVkDevice,
                                       VK_NULL_HANDLE,
                                       1,
                                       &graphicsPipelineCreateInfo,
                                       NULL,
                                       &mesh_pipeline->pipeline));
}

