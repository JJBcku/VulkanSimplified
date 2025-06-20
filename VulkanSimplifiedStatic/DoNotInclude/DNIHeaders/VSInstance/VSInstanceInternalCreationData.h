#pragma once

#include "../../../Include/VSMain/VSInstanceExtensionPacksList.h"
#include "../../../Include/VSMain/VSInstanceLayerPacksList.h"
#include "../../../Include/VSCommon/VSVersionData.h"

#include <string>
#include <stdint.h>
#include <vector>

namespace VulkanSimplifiedInternal
{
	struct InstanceInternalCreationData
	{
		std::string appName;
		std::string appVariantName;
		VulkanSimplified::VersionData appVersion;
		std::string engineName;
		VulkanSimplified::VersionData engineVersion;
		std::vector<const char*> requestedExtensions;
		std::vector<const char*> requestedLayers;

		VulkanSimplified::VersionData usedVulkanApiVersion;
		VulkanSimplified::InstanceExtensionPacksList enabledExtensionPacksList;
		VulkanSimplified::InstanceLayerPacksList enabledLayerPacksList;

		InstanceInternalCreationData();
	};
}
