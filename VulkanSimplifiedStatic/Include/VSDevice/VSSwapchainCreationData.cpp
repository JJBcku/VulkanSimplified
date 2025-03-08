#include "VSDeviceIpch.h"
#include "VSSwapchainCreationData.h"

namespace VulkanSimplified
{
	SwapchainCreationData::SwapchainCreationData()
	{
		surfacePresentMode = static_cast<SurfacePresentModeBits>(0);

		imageAmount = 0;
		padding = 0;
	}
}