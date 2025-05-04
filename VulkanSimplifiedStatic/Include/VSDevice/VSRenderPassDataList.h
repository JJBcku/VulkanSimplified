#pragma once

#include <CustomLists\IDObjectDef.h>

namespace VulkanSimplifiedInternal
{
	class RenderPassListInternal;
	class AutoCleanupRenderPass;

	struct RenderPassAttachmentData;
	struct SubpassDependencyData;
}

namespace VulkanSimplified
{
	struct SubpassCreationDataWithoutResolving;
	struct SubpassCreationDataWithResolving;

	class RenderPassList
	{
	public:
		RenderPassList(VulkanSimplifiedInternal::RenderPassListInternal& ref);
		~RenderPassList();

		IDObject<VulkanSimplifiedInternal::AutoCleanupRenderPass> AddRenderPassWithoutResolveAttachments(
			const std::vector<IDObject<VulkanSimplifiedInternal::RenderPassAttachmentData>>& attachments, const std::vector<SubpassCreationDataWithoutResolving>& subpasses,
			const std::vector<IDObject<VulkanSimplifiedInternal::SubpassDependencyData>>& subpassDependencies, size_t addOnReserve = 0);

		IDObject<VulkanSimplifiedInternal::AutoCleanupRenderPass> AddRenderPassWithResolveAttachments(
			const std::vector<IDObject<VulkanSimplifiedInternal::RenderPassAttachmentData>>& attachments, const std::vector<SubpassCreationDataWithResolving>& subpasses,
			const std::vector<IDObject<VulkanSimplifiedInternal::SubpassDependencyData>>& subpassDependencies, size_t addOnReserve = 0);

	private:
		VulkanSimplifiedInternal::RenderPassListInternal& _internal;
	};
}