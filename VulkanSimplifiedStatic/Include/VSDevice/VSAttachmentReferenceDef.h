#pragma once

template<class T>
class IDObject;

namespace VulkanSimplifiedInternal
{
	struct RenderPassAttachmentReference;
}

namespace VulkanSimplified
{
	typedef std::optional<IDObject<VulkanSimplifiedInternal::RenderPassAttachmentReference>> AttachmentReference;
}