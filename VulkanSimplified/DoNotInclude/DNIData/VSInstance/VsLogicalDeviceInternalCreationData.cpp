#include "VSInstanceDNIpch.h"
#include "VSLogicalDeviceInternalCreationData.h"

namespace VulkanSimplified
{
	LogicalDeviceInternalCreationData::LogicalDeviceInternalCreationData()
	{
		apiVersion = 0;
		padding = 0;

		features = {};

		vulkan10EnabledFeatures = 0;
	}
}