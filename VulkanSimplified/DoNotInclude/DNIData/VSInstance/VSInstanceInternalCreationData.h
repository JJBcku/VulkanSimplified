#pragma once

#include "../../../Include/VSMain/VSInstanceExtensionPacksList.h"
#include "../../../Include/VSMain/VSInstanceLayerPacksList.h"
#include "../../../Include/VSCommon/VSVersionData.h"

#include <string>
#include <stdint.h>
#include <vector>

namespace VulkanSimplified
{
	struct InstanceInternalCreationData
	{
		std::string appName;
		std::string appVariantName;
		VersionData appVersion;
		std::string engineName;
		VersionData engineVersion;
		std::vector<const char*> requestedExtensions;
		std::vector<const char*> requestedLayers;

		VersionData usedVulkanApiVersion;
		InstanceExtensionPacksList enabledExtensionPacksList;
		InstanceLayerPacksList enabledLayerPacksList;

		InstanceInternalCreationData();
	};
}
