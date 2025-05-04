#pragma once

#include <CustomLists\IDObjectDef.h>

namespace VulkanSimplifiedInternal
{
	struct RenderPassAttachmentReference;
}

namespace VulkanSimplified
{
	typedef std::optional<IDObject<VulkanSimplifiedInternal::RenderPassAttachmentReference>> AttachmentReference;
}