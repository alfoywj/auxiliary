//
// Created by redbean on 22. 7. 30.
//

#include "VkBundle.h"

VkBundle::VkBundle(VkDevice vkDevice, VkQueue vkQueue, uint32_t queueIndex,  VkPhysicalDevice vkPhysicalDevice) : mVkDevice(vkDevice), mVkQueue(vkQueue), mQueueIndex(queueIndex), mVkPhysicalDevice(vkPhysicalDevice){
    vkGetPhysicalDeviceMemoryProperties(mVkPhysicalDevice, &mVkPhysicalDeviceMemoryProperties);
}

VkBool32 VkBundle::AllocateMemoryTypeFromProperties(uint32_t typeBits, VkMemoryPropertyFlags requirements_mask, uint32_t *typeIndex) {
    // Search memtypes to find first index with those properties
    for (uint32_t i = 0; i < VK_MAX_MEMORY_TYPES; i++) {
        if ((typeBits & 1) == 1) {
            // Type is available, does it match user properties?
            if ((mVkPhysicalDeviceMemoryProperties.memoryTypes[i].propertyFlags & requirements_mask) == requirements_mask) {
                *typeIndex = i;
                return VK_TRUE;
            }
        }
        typeBits >>= 1;
    }
    return VK_FALSE;
}