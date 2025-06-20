#include "VSInstanceNIpch.h"
#include "../../DNIHeaders/VSInstance/VSInstanceInternalCreationData.h"

namespace VulkanSimplifiedInternal
{
	InstanceInternalCreationData::InstanceInternalCreationData() : appName("Unknown"), appVariantName(), appVersion(), engineName("Unknown"), engineVersion(),
		requestedExtensions(), requestedLayers(), usedVulkanApiVersion(), enabledExtensionPacksList(), enabledLayerPacksList()
	{
	}
}
