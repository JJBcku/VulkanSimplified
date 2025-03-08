#pragma once

#include "../VSCommon/VSSurfacePresentModes.h"
#include "../VSCommon/VSDataFormatFlags.h"

namespace VulkanSimplified
{
	struct SwapchainCreationData
	{
		SurfacePresentModeBits surfacePresentMode;
		DataFormatSetIndependentID format;

		std::uint32_t imageAmount;
		std::uint32_t padding;

		std::vector<size_t> queuesUsingSwapchain;

		SwapchainCreationData();
	};
}
