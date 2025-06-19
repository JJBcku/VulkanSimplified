#pragma once

#include <CustomLists/IDObject.h>

#include <optional>

namespace VulkanSimplifiedInternal
{
	struct RenderPassAttachmentReference;
}

namespace VulkanSimplified
{
	typedef std::optional<IDObject<VulkanSimplifiedInternal::RenderPassAttachmentReference>> AttachmentReference;
}