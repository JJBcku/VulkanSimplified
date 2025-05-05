#include "pch.h"
#include "VulkanInstanceDependentData.h"

VulkanInstanceDependentData::VulkanInstanceDependentData()
{
	physicalDevicesIndex = std::numeric_limits<size_t>::max();

	minSwapchainImageAmount = 0;
	maxSwapchainImageAmount = 0;

	graphicsQueueIndex = std::numeric_limits<size_t>::max();
	graphicsQueueFamily = std::numeric_limits<uint32_t>::max();
	padding = 0;
}
