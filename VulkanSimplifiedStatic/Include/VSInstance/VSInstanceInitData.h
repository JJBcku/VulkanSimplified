#pragma once

#include "../VSMain/VSInstanceExtensionPacksList.h"
#include "../VSMain/VSInstanceLayerPacksList.h"
#include "../VSCommon/VSVersionData.h"

namespace VulkanSimplified
{
	struct InstanceInitData
	{
		VersionData usedVulkanApiVersion;
		InstanceExtensionPacksList enabledExtensionPacks;
		InstanceLayerPacksList enabledLayerPacks;

		InstanceInitData() = default;
	};
}