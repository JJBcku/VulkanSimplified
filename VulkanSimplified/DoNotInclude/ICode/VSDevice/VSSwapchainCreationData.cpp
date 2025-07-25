#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSSwapchainCreationData.h"

namespace VulkanSimplified
{
	SwapchainCreationData::SwapchainCreationData()
	{
		compositeAlphaMode = static_cast<CompositeAlphaFlagBits>(0);
		surfaceTranformMode = static_cast<SurfaceTransformFlagBits>(0);
		surfacePresentMode = static_cast<SurfacePresentModeBits>(0);

		imageAmount = 0;
		padding = 0;
	}
}