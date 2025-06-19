#include "VSInstanceNIpch.h"
#include "../../DNIHeaders/VSInstance/VsLogicalDeviceInternalCreationData.h"

namespace VulkanSimplifiedInternal
{
	LogicalDeviceInternalCreationData::LogicalDeviceInternalCreationData()
	{
		apiVersion = 0;
		padding = 0;

		features = {};

		vulkan10EnabledFeatures = 0;
	}
}