#include "pch.h"
#include "VulkanInstanceDependentData.h"

VulkanInstanceDependentData::VulkanInstanceDependentData()
{
	physicalDevicesIndex = std::numeric_limits<size_t>::max();

	minSwapchainImageAmount = 0;
	maxSwapchainImageAmount = 0;

	graphicsQueueIndex = std::numeric_limits<size_t>::max();
	graphicsQueueFamily = std::numeric_limits<size_t>::max();
	presentingQueueIndex = std::numeric_limits<size_t>::max();
	presentingQueueFamily = std::numeric_limits<size_t>::max();
}
