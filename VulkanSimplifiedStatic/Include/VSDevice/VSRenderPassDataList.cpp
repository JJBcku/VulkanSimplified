#include "VSDeviceIpch.h"
#include "VSRenderPassDataList.h"

#include "../../DoNotInclude/VSDevice/VSRenderPassDataListInternal.h"

namespace VulkanSimplified
{
	RenderPassList::RenderPassList(VulkanSimplifiedInternal::RenderPassListInternal& ref) : _internal(ref)
	{
	}

	RenderPassList::~RenderPassList()
	{
	}

	IDObject<VulkanSimplifiedInternal::AutoCleanupRenderPass> RenderPassList::AddRenderPassWithoutResolveAttachments(
		const std::vector<IDObject<VulkanSimplifiedInternal::RenderPassAttachmentData>>& attachments, const std::vector<SubpassCreationDataWithoutResolving>& subpasses,
		const std::vector<IDObject<VulkanSimplifiedInternal::SubpassDependencyData>>& subpassDependencies, size_t addOnReserving)
	{
		return _internal.AddRenderPassWithoutResolveAttachments(attachments, subpasses, subpassDependencies, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::AutoCleanupRenderPass> RenderPassList::AddRenderPassWithResolveAttachments(
		const std::vector<IDObject<VulkanSimplifiedInternal::RenderPassAttachmentData>>& attachments, const std::vector<SubpassCreationDataWithResolving>& subpasses,
		const std::vector<IDObject<VulkanSimplifiedInternal::SubpassDependencyData>>& subpassDependencies, size_t addOnReserving)
	{
		return _internal.AddRenderPassWithResolveAttachments(attachments, subpasses, subpassDependencies, addOnReserving);
	}

}