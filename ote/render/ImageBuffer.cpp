//
// Created by redbean on 22. 7. 30.
//

#include "ImageBuffer.h"

void ImageBuffer::CreateAllocBind(VkBundle *vkBundle, const VkImageCreateInfo *pCreateInfo) {
    mVkFormat = pCreateInfo->format;
    mExtent = pCreateInfo->extent;

    VK_CHECK(vkCreateImage(vkBundle->mVkDevice, pCreateInfo, nullptr, &mVkImage));

    VkMemoryRequirements memReqs;
    vkGetImageMemoryRequirements(vkBundle->mVkDevice, mVkImage, &memReqs);
    mAllocationSize = memReqs.size;

    VkMemoryAllocateInfo vkMemoryAllocateInfo = {
            .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
            .pNext = VK_NULL_HANDLE,
            .allocationSize = mAllocationSize,
            .memoryTypeIndex = 0,
    };

    vkBundle->AllocateMemoryTypeFromProperties(memReqs.memoryTypeBits,
                                                VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                                                &vkMemoryAllocateInfo.memoryTypeIndex);
    VK_CHECK(vkAllocateMemory(vkBundle->mVkDevice, &vkMemoryAllocateInfo, nullptr, &mVkDeviceMemory));
    VK_CHECK(vkBindImageMemory(vkBundle->mVkDevice, mVkImage, mVkDeviceMemory, 0));
}
