#include "VSMainIpch.h"
#include "../../../Include/VSMain/VSInstanceExtensionPacksList.h"

namespace VulkanSimplified
{
	InstanceExtensionPacksList::InstanceExtensionPacksList()
	{
		sdlRequiredExtensions = false;
		debugUtils = false;
		std::memset(padding, false, sizeof(padding));
	}
}
