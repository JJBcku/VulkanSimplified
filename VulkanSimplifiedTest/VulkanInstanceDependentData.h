#pragma once

#include <VSDataFormatFlags.h>

struct VulkanInstanceDependentData
{
	size_t physicalDevicesIndex;

	VulkanSimplified::DataFormatSetIndependentID supportedFormat;
	uint32_t minSwapchainImageAmount;
	uint32_t maxSwapchainImageAmount;

	size_t graphicsQueueIndex;
	size_t graphicsQueueFamily;
	std::optional<size_t> transferOnlyQueueIndex;
	std::optional<size_t> transferOnlyQueueFamily;
	size_t presentingQueueIndex;
	size_t presentingQueueFamily;

	VulkanInstanceDependentData();
};