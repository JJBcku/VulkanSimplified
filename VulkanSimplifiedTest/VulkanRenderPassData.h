#pragma once

#include <CustomLists/IDObject.h>
#include <VSSharedRenderPassDataList.h>

struct VulkanRenderPassData
{
	std::vector<IDObject<VulkanSimplifiedInternal::RenderPassAttachmentData>> renderPassAttachments;
	IDObject<VulkanSimplifiedInternal::RenderPassAttachmentReference> colorAttachmentReference;
	IDObject<VulkanSimplifiedInternal::SubpassDependencyData> subpassDependency;

	VulkanRenderPassData() = default;
};