#include "VSMainIpch.h"
#include "../../../Include/VSMain/VSInstanceLayerPacksList.h"

namespace VulkanSimplified
{
	InstanceLayerPacksList::InstanceLayerPacksList()
	{
		debugUtils = false;
		std::memset(padding, false, sizeof(padding));
	}
}
