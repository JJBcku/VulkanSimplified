#pragma once

namespace VulkanSimplified
{
	enum class RenderPassAttachmentLoadOP : uint64_t
	{
		LOAD = 0x1,
		CLEAR = 0x2,
		IGNORE = 0x3,
	};

	enum class RenderPassAttachmentStoreOP : uint64_t
	{
		STORE = 0x1,
		IGNORE = 0x2,
	};
}