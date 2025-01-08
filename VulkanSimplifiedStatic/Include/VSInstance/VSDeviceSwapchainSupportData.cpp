#include "VSInstanceIpch.h"
#include "VSDeviceSwapchainSupportData.h"

namespace VulkanSimplified
{

	SurfaceSupportedColorspaceFormatsLists::SurfaceSupportedColorspaceFormatsLists()
	{
	}

	SurfaceSupportData::SurfaceSupportData()
	{
		minWidth = std::numeric_limits<uint32_t>::max();
		minHeight = std::numeric_limits<uint32_t>::max();

		maxWidth = 0;
		maxHeight = 0;

		minImageCount = 0;
		maxImageCount = 0;

		surfaceUsageFlags = 0;
		surfacePresentModes = 0;
	}

}