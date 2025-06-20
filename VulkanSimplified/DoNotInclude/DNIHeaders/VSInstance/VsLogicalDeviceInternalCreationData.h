#pragma once

#include "../../../Include/VSInstance/VSDeviceVulkan10FeatureFlagsDef.h"
#include "../../../Include/VSInstance/VSDeviceExtensionPacksList.h"

#include <stdint.h>
#include <vector>

#include <vulkan/vulkan_core.h>

namespace VulkanSimplified
{
	struct LogicalDeviceInternalCreationData
	{
		std::vector<VkDeviceQueueCreateInfo> queueInfos;

		uint32_t apiVersion;
		uint32_t padding;

		VkPhysicalDeviceFeatures features;
		std::vector<const char*> enabledExtensionsList;

		DeviceVulkan10FeatureFlags vulkan10EnabledFeatures;
		DeviceExtensionPacksList requestedExtensionPacks;

		LogicalDeviceInternalCreationData();
	};
}
