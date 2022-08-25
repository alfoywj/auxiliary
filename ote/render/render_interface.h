#pragma once

#include "dbm/dbm_defines.h"
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

#ifdef __cplusplus
}
#endif