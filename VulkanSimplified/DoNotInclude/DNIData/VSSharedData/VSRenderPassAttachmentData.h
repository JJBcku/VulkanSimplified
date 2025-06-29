#pragma once

#include <vulkan/vulkan_core.h>
#include <compare>

namespace VulkanSimplified
{
	struct RenderPassAttachmentData
	{
		VkFormat format;
		VkSampleCountFlagBits samples;
		VkAttachmentLoadOp loadOP;
		VkAttachmentStoreOp storeOP;
		VkImageLayout initialLayout;
		VkImageLayout finalLayout;

		RenderPassAttachmentData();

		bool operator==(const RenderPassAttachmentData&) const noexcept = default;
		std::strong_ordering operator<=>(const RenderPassAttachmentData&) const noexcept = default;
	};
}