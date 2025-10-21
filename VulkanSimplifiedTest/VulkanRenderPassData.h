#pragma once

#include <CustomLists/IDObject.h>
#include <VSSharedRenderPassDataListsDef.h>
#include <VSRenderPassDataListDef.h>
#include <VSRenderPassClearValueID.h>

struct VulkanRenderPassData
{
	std::vector<IDObject<VS::RenderPassAttachmentData>> renderPassAttachments;
	IDObject<VS::RenderPassAttachmentReference> colorAttachmentReference;
	IDObject<VS::RenderPassAttachmentReference> depthAttachmentReference;
	IDObject<VS::RenderPassAttachmentReference> resolveAttachmentReference;
	IDObject<VS::SubpassDependencyData> subpassDependency;

	std::vector<std::optional<VS::RenderPassClearValueID>> clearValues;

	IDObject<VS::AutoCleanupRenderPass> renderPass;

	VulkanRenderPassData() = default;
};