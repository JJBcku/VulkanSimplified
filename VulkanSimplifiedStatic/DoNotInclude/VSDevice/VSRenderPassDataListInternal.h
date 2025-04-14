#pragma once

#include <CustomLists/UnsortedIDVector.h>

namespace VulkanSimplified
{
	struct RenderPassDataListsInitialCapacities;

	struct SubpassCreationDataWithoutResolving;
	struct SubpassCreationDataWithResolving;
}

namespace VulkanSimplifiedInternal
{
	class SharedRenderPassDataListInternal;

	class AutoCleanupRenderPass;

	struct RenderPassAttachmentData;
	struct SubpassDependencyData;

	class RenderPassListInternal
	{
	public:
		RenderPassListInternal(const SharedRenderPassDataListInternal& sharedRenderPassData, VkDevice device,
			const VulkanSimplified::RenderPassDataListsInitialCapacities& initialCapacities);
		~RenderPassListInternal();

		IDObject<AutoCleanupRenderPass> AddRenderPassWithoutResolveAttachments(const std::vector<IDObject<RenderPassAttachmentData>>& attachments,
			const std::vector<VulkanSimplified::SubpassCreationDataWithoutResolving>& subpasses, const std::vector<IDObject<SubpassDependencyData>>& subpassDependencies,
			size_t addOnReserve);

		IDObject<AutoCleanupRenderPass> AddRenderPassWithResolveAttachments(const std::vector<IDObject<RenderPassAttachmentData>>& attachments,
			const std::vector<VulkanSimplified::SubpassCreationDataWithResolving>& subpasses, const std::vector<IDObject<SubpassDependencyData>>& subpassDependencies,
			size_t addOnReserve);

		VkRenderPass GetRenderPass(IDObject<AutoCleanupRenderPass> renderPassID) const;

	private:
		const SharedRenderPassDataListInternal& _sharedRenderPassData;

		VkDevice _device;

		UnsortedIDVector<AutoCleanupRenderPass> _renderPassList;
	};
}