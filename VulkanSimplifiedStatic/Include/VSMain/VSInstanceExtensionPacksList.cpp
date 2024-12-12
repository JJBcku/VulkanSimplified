#include "VSMainIpch.h"
#include "VSInstanceExtensionPacksList.h"

#include <memory>

namespace VulkanSimplified
{
	InstanceExtensionPacksList::InstanceExtensionPacksList()
	{
		sdlRequiredExtensions = false;
		debugUtils = false;
		std::memset(padding, false, sizeof(padding));
	}
}
