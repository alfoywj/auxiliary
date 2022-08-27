#pragma once

#include "ote/ote_defines.h"
#include "VkBundle.h"
#ifdef __cplusplus
extern "C" {
#endif

struct render_buffer {
    //! Backing memory.
    VkDeviceMemory memory;

    //! Buffer.
    VkBuffer buffer;

    //! Size requested for the buffer.
    VkDeviceSize size;

    //! Size of the memory allocation.
    VkDeviceSize allocation_size;

    //! Alignment of the buffer.
    VkDeviceSize alignment;

    void *mapped;
};

struct render_mesh {
    render_buffer vertexBuffer;
    render_buffer indexBuffer;
};

struct render_shader {
    VkShaderModule vertShader;
    VkShaderModule fragShader;
    std::vector<VkVertexInputBindingDescription> vertexInputBindingDescription;
    std::vector<VkVertexInputAttributeDescription> vertexInputAttributeDescription;
};

struct render_pipeline {
    VkDescriptorSetLayout descriptorSetLayout;
    VkPipelineLayout pipelineLayout;
    VkPipeline pipeline;
};

void load_mesh_shader(VkBundle* vkBundle, render_shader* mesh_shader);
void load_mesh_pipeline(VkBundle *vkBundle, render_pipeline *mesh_pipeline, render_shader* pRenderShader, VkRenderPass* pRenderPass);
void create_render_mesh(VkBundle* vkBundle, ote_data_mesh* pDataMesh, render_mesh* pRenderMesh);
void update_render_mesh(VkBundle *vkBundle, ote_data_mesh *pDataMesh, render_mesh *pRenderMesh);
#ifdef __cplusplus
}
#endif