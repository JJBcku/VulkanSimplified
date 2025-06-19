#include "VSInstanceNIpch.h"
#include "../../DNIHeaders/VSInstance/VSInstanceInternalCreationData.h"

namespace VulkanSimplifiedInternal
{
	InstanceInternalCreationData::InstanceInternalCreationData()
	{
		appName = "Unknown";
		appVersion = 0;
		padding = 0;
		engineName = "Unknown";
		engineVersion = 0;
		usedVulkanApiVersion = 0;
	}
}
