#pragma once

#include "../../Include/VSInstance/VSDeviceVulkan10Features.h"
#include "../../Include/VSInstance/VSDeviceExtensionPacksList.h"

namespace VulkanSimplifiedInternal
{
	struct LogicalDeviceInternalCreationData
	{
		std::vector<VkDeviceQueueCreateInfo> queueInfos;

		std::uint32_t apiVersion;
		std::uint32_t padding;

		VkPhysicalDeviceFeatures features;
		std::vector<const char*> enabledExtensionsList;

		VulkanSimplified::DeviceVulkan10FeatureFlags vulkan10EnabledFeatures;
		VulkanSimplified::DeviceExtensionPacksList requestedExtensionPacks;

		LogicalDeviceInternalCreationData();
	};
}
