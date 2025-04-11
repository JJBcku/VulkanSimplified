#pragma once

namespace VulkanSimplifiedInternal
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