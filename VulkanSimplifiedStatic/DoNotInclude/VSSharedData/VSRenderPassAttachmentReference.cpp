#include "VSSharedNIpch.h"
#include "VSRenderPassAttachmentReference.h"

namespace VulkanSimplifiedInternal
{
	RenderPassAttachmentReference::RenderPassAttachmentReference()
	{
		attachmentIndex = std::numeric_limits<uint32_t>::max();
		attachmentLayout = VK_IMAGE_LAYOUT_MAX_ENUM;
	}
}