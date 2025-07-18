#pragma once
#include <vulkan/vulkan_core.h>
#include <stdint.h>
#include <compare>

namespace VulkanSimplified
{
	struct RenderPassAttachmentReference
	{
		uint32_t attachmentIndex;
		VkImageLayout attachmentLayout;

		RenderPassAttachmentReference();

		bool operator==(const RenderPassAttachmentReference&) const noexcept = default;
		std::strong_ordering operator<=>(const RenderPassAttachmentReference&) const noexcept = default;
	};
}