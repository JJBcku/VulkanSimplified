#pragma once

#include <VSDataFormatFlags.h>
#include <VSImageSampleFlags.h>

struct VulkanInstanceDependentData
{
	size_t physicalDevicesIndex;

	VulkanSimplified::DataFormatSetIndependentID supportedColorFormat;
	VulkanSimplified::DataFormatSetIndependentID supportedDepthFormat;
	uint32_t minSwapchainImageAmount;
	uint32_t maxSwapchainImageAmount;

	VulkanSimplified::ImageSampleFlagBits maxSamples;
	std::optional<uint32_t> sampleShadingRate;

	size_t graphicsQueueIndex;
	uint32_t graphicsQueueFamily;
	float maxAnisotropy;
	std::optional<size_t> transferOnlyQueueIndex;
	std::optional<uint32_t> transferOnlyQueueFamily;
	std::optional<size_t> presentingQueueIndex;
	std::optional<uint32_t> presentingQueueFamily;

	VulkanInstanceDependentData();
};