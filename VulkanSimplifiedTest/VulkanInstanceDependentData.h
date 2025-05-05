#pragma once

#include <VSDataFormatFlags.h>

struct VulkanInstanceDependentData
{
	size_t physicalDevicesIndex;

	VulkanSimplified::DataFormatSetIndependentID supportedFormat;
	uint32_t minSwapchainImageAmount;
	uint32_t maxSwapchainImageAmount;

	size_t graphicsQueueIndex;
	uint32_t graphicsQueueFamily;
	uint32_t padding;
	std::optional<size_t> transferOnlyQueueIndex;
	std::optional<uint32_t> transferOnlyQueueFamily;
	std::optional<size_t> presentingQueueIndex;
	std::optional<uint32_t> presentingQueueFamily;

	VulkanInstanceDependentData();
};