#pragma once

#include <CustomLists/IDObject.h>
#include <VSSharedRenderPassDataListDef.h>
#include <VSRenderPassDataListDef.h>
#include <VSRenderPassClearValueID.h>

struct VulkanRenderPassData
{
	std::vector<IDObject<VulkanSimplifiedInternal::RenderPassAttachmentData>> renderPassAttachments;
	IDObject<VulkanSimplifiedInternal::RenderPassAttachmentReference> colorAttachmentReference;
	IDObject<VulkanSimplifiedInternal::RenderPassAttachmentReference> depthAttachmentReference;
	IDObject<VulkanSimplifiedInternal::RenderPassAttachmentReference> resolveAttachmentReference;
	IDObject<VulkanSimplifiedInternal::SubpassDependencyData> subpassDependency;

	std::vector<std::optional<VulkanSimplified::RenderPassClearValueID>> clearValues;

	IDObject<VulkanSimplifiedInternal::AutoCleanupRenderPass> renderPass;

	VulkanRenderPassData() = default;
};