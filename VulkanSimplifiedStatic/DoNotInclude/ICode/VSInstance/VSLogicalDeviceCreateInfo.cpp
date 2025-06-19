#include "VSInstanceIpch.h"
#include "../../../Include/VSInstance/VSLogicalDeviceCreateInfo.h"

namespace VulkanSimplified
{

	QueueCreationData::QueueCreationData()
	{
		queuesFamily = std::numeric_limits<decltype(queuesFamily)>::max();
		padding = 0;
	}

	LogicalDeviceCreationData::LogicalDeviceCreationData()
	{
		physicalGPUIndex = std::numeric_limits<size_t>::max();

		vulkan10EnabledFeatures = 0;
	}

}