#pragma once

#include "../../Include/VSMain/VSInstanceExtensionPacksList.h"
#include "../../Include/VSMain/VSInstanceLayerPacksList.h"

#include <string>
#include <stdint.h>
#include <vector>

namespace VulkanSimplifiedInternal
{
	struct InstanceInternalCreationData
	{
		std::string appName;
		uint32_t appVersion;
		uint32_t padding;
		std::string engineName;
		uint32_t engineVersion;
		uint32_t usedVulkanApiVersion;
		std::vector<const char*> requestedExtensions;
		std::vector<const char*> requestedLayers;

		VulkanSimplified::InstanceExtensionPacksList enabledExtensionPacksList;
		VulkanSimplified::InstanceLayerPacksList enabledLayerPacksList;

		InstanceInternalCreationData();
	};
}
