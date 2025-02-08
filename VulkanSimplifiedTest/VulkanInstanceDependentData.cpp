#include "pch.h"
#include "VulkanInstanceDependentData.h"

VulkanInstanceDependentData::VulkanInstanceDependentData()
{
	physicalDevicesIndex = std::numeric_limits<size_t>::max();

	graphicsQueueIndex = std::numeric_limits<size_t>::max();
	graphicsQueueFamily = std::numeric_limits<size_t>::max();
	presentingQueueIndex = std::numeric_limits<size_t>::max();
	presentingQueueFamily = std::numeric_limits<size_t>::max();
}
