#include "VSInstanceDNIpch.h"
#include "VSInstanceInternalCreationData.h"

namespace VulkanSimplified
{
	InstanceInternalCreationData::InstanceInternalCreationData() : appName("Unknown"), appVariantName(), appVersion(), engineName("Unknown"), engineVersion(),
		requestedExtensions(), requestedLayers(), usedVulkanApiVersion(), enabledExtensionPacksList(), enabledLayerPacksList()
	{
	}
}
