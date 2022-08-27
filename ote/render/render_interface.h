#pragma once

#include "ote/ote_defines.h"
#include <vulkan/vulkan_core.h>
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
void create_render_mesh(VkDevice vkDevice, ote_data_mesh* pDataMesh, render_mesh* pRenderMesh);
#ifdef __cplusplus
}
#endif