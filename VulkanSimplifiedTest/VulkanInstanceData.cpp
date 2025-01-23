#include "pch.h"
#include "VulkanInstanceData.h"

VulkanInstanceData::VulkanInstanceData()
{
	physicalDevicesIndex = std::numeric_limits<size_t>::max();

	graphicsQueueIndex = std::numeric_limits<size_t>::max();
	graphicsQueueFamily = std::numeric_limits<size_t>::max();
	presentingQueueIndex = std::numeric_limits<size_t>::max();
	presentingQueueFamily = std::numeric_limits<size_t>::max();
}
