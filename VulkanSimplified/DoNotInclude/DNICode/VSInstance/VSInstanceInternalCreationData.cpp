#include "VSInstanceNIpch.h"
#include "../../DNIHeaders/VSInstance/VSInstanceInternalCreationData.h"

namespace VulkanSimplified
{
	InstanceInternalCreationData::InstanceInternalCreationData() : appName("Unknown"), appVariantName(), appVersion(), engineName("Unknown"), engineVersion(),
		requestedExtensions(), requestedLayers(), usedVulkanApiVersion(), enabledExtensionPacksList(), enabledLayerPacksList()
	{
	}
}
