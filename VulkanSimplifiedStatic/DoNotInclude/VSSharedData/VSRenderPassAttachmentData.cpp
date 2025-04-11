#include "VSSharedNIpch.h"
#include "VSRenderPassAttachmentData.h"

namespace VulkanSimplifiedInternal
{
	RenderPassAttachmentData::RenderPassAttachmentData()
	{
		format = VK_FORMAT_MAX_ENUM;;
		samples = VK_SAMPLE_COUNT_FLAG_BITS_MAX_ENUM;
		loadOP = VK_ATTACHMENT_LOAD_OP_MAX_ENUM;
		storeOP = VK_ATTACHMENT_STORE_OP_MAX_ENUM;
		initialLayout = VK_IMAGE_LAYOUT_MAX_ENUM;
		finalLayout = VK_IMAGE_LAYOUT_MAX_ENUM;
	}
}