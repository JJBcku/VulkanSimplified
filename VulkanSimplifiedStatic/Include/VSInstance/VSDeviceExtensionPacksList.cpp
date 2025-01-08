#include "VSInstanceIpch.h"
#include "VSDeviceExtensionPacksList.h"

namespace VulkanSimplified
{
	DeviceExtensionPacksList::DeviceExtensionPacksList()
	{
		swapchainBase = false;
		std::memset(padding, false, sizeof(padding));
	}
}