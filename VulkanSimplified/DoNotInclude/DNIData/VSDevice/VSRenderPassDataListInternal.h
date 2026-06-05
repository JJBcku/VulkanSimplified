#pragma once

#include <CustomLists/UnsortedIDVector.h>

#include <vector>

typedef struct VkDevice_T* VkDevice;
typedef struct VkRenderPass_T* VkRenderPass;

namespace VulkanSimplified
{
	struct RenderPassDataListsInitialCapacities;

	struct SubpassCreationDataWithoutResolving;
	struct SubpassCreationDataWithResolving;
}

namespace VulkanSimplified
{
	class SharedRenderPassDataListsInternal;

	class AutoCleanupRenderPass;

	struct RenderPassAttachmentData;
	struct SubpassDependencyData;

	class RenderPassListInternal
	{
	public:
		RenderPassListInternal(const SharedRenderPassDataListsInternal& sharedRenderPassData, VkDevice device,
			const RenderPassDataListsInitialCapacities& initialCapacities);
		~RenderPassListInternal();

		RenderPassListInternal(const RenderPassListInternal&) noexcept = delete;

		RenderPassListInternal& operator=(const RenderPassListInternal&) noexcept = delete;

		IDObject<AutoCleanupRenderPass> AddRenderPassWithoutResolveAttachments(const std::vector<IDObject<RenderPassAttachmentData>>& attachments,
			const std::vector<SubpassCreationDataWithoutResolving>& subpasses, const std::vector<IDObject<SubpassDependencyData>>& subpassDependencies,
			size_t addOnReserving);

		IDObject<AutoCleanupRenderPass> AddRenderPassWithResolveAttachments(const std::vector<IDObject<RenderPassAttachmentData>>& attachments,
			const std::vector<SubpassCreationDataWithResolving>& subpasses, const std::vector<IDObject<SubpassDependencyData>>& subpassDependencies,
			size_t addOnReserving);

		VkRenderPass GetRenderPass(IDObject<AutoCleanupRenderPass> renderPassID) const;

	private:
		const SharedRenderPassDataListsInternal& _sharedRenderPassData;

		VkDevice _device;

		UnsortedIDVector<AutoCleanupRenderPass> _renderPassList;
	};
}