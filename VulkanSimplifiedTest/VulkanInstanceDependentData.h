#pragma once

struct VulkanInstanceDependentData
{
	size_t physicalDevicesIndex;

	size_t graphicsQueueIndex;
	size_t graphicsQueueFamily;
	std::optional<size_t> transferOnlyQueueIndex;
	std::optional<size_t> transferOnlyQueueFamily;
	size_t presentingQueueIndex;
	size_t presentingQueueFamily;

	VulkanInstanceDependentData();
};