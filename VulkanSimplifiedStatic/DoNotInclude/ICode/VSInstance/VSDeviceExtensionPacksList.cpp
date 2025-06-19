#include "VSInstanceIpch.h"
#include "../../../Include/VSInstance/VSDeviceExtensionPacksList.h"

namespace VulkanSimplified
{
	DeviceExtensionPacksList::DeviceExtensionPacksList()
	{
		swapchainBase = false;
		std::memset(padding, false, sizeof(padding));
	}
}