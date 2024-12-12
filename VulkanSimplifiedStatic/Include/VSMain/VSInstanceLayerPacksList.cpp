#include "VSMainIpch.h"
#include "VSInstanceLayerPacksList.h"

#include <memory>

namespace VulkanSimplified
{
	InstanceLayerPacksList::InstanceLayerPacksList()
	{
		debugUtils = false;
		std::memset(padding, false, sizeof(padding));
	}
}
