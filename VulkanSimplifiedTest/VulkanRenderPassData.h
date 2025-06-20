#pragma once

#include <CustomLists/IDObject.h>
#include <VSSharedRenderPassDataListDef.h>
#include <VSRenderPassDataListDef.h>
#include <VSRenderPassClearValueID.h>

struct VulkanRenderPassData
{
	std::vector<IDObject<VulkanSimplified::RenderPassAttachmentData>> renderPassAttachments;
	IDObject<VulkanSimplified::RenderPassAttachmentReference> colorAttachmentReference;
	IDObject<VulkanSimplified::RenderPassAttachmentReference> depthAttachmentReference;
	IDObject<VulkanSimplified::RenderPassAttachmentReference> resolveAttachmentReference;
	IDObject<VulkanSimplified::SubpassDependencyData> subpassDependency;

	std::vector<std::optional<VulkanSimplified::RenderPassClearValueID>> clearValues;

	IDObject<VulkanSimplified::AutoCleanupRenderPass> renderPass;

	VulkanRenderPassData() = default;
};