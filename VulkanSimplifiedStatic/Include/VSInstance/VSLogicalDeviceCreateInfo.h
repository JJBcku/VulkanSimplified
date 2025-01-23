#pragma once

#include "VSDeviceVulkan10Features.h"
#include "VSDeviceExtensionPacksList.h"

namespace VulkanSimplified
{
	struct QueueCreationData
	{
		std::uint32_t queuesFamily;
		std::uint32_t padding;
		std::vector<uint16_t> queuesPriorities;

		QueueCreationData();
	};

	struct LogicalDeviceCreationData
	{
		size_t physicalGPUIndex;
		std::vector<QueueCreationData> queuesCreationInfo;

		DeviceVulkan10FeatureFlags vulkan10EnabledFeatures;
		DeviceExtensionPacksList requestedExtensionPacks;

		LogicalDeviceCreationData();
	};
}