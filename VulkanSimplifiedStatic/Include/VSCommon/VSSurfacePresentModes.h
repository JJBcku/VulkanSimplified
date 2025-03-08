#pragma once

namespace VulkanSimplified
{
	typedef uint64_t SurfacePresentModes;

	enum SurfacePresentModeBits : SurfacePresentModes
	{
		PRESENT_MODE_IMMEDIATE = 0x1,
		PRESENT_MODE_MAILBOX = 0x2,
		PRESENT_MODE_FIFO_STRICT = 0x4,
		PRESENT_MODE_FIFO_RELAXED = 0x8,
	};
}