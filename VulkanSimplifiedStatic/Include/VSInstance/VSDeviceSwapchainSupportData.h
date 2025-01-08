#pragma once

#include "../VSCommon/VSImageUsageFlags.h"
#include "../VSCommon/VSDataFormatFlags.h"

namespace VulkanSimplified
{
	struct SurfaceSupportedColorspaceFormatsLists
	{
		DataFormatFullSetList srgbNonlinearColorspace;

		SurfaceSupportedColorspaceFormatsLists();
	};

	typedef uint64_t SurfacePresentModes;

	enum SurfacePresentModeBits : SurfacePresentModes
	{
		PRESENT_MODE_IMMEDIATE = 0x1,
		PRESENT_MODE_MAILBOX = 0x2,
		PRESENT_MODE_FIFO_STRICT = 0x4,
		PRESENT_MODE_FIFO_RELAXED = 0x8,
	};

	struct SurfaceSupportData
	{
		uint32_t minWidth;
		uint32_t minHeight;

		uint32_t maxWidth;
		uint32_t maxHeight;

		uint32_t minImageCount;
		uint32_t maxImageCount;

		ImageUsageFlags surfaceUsageFlags;
		SurfacePresentModes surfacePresentModes;
		SurfaceSupportedColorspaceFormatsLists surfaceSupportedSwapchainFormats;

		SurfaceSupportData();
	};
}
