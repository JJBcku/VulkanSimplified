#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSRenderPassDataList.h"

#include "../../../DoNotInclude/DNIData/VSDevice/VSRenderPassDataListInternal.h"

namespace VulkanSimplified
{
	RenderPassList::RenderPassList(RenderPassListInternal& ref) : _internal(ref)
	{
	}

	RenderPassList::~RenderPassList()
	{
	}

	IDObject<AutoCleanupRenderPass> RenderPassList::AddRenderPassWithoutResolveAttachments(
		const std::vector<IDObject<RenderPassAttachmentData>>& attachments, const std::vector<SubpassCreationDataWithoutResolving>& subpasses,
		const std::vector<IDObject<SubpassDependencyData>>& subpassDependencies, size_t addOnReserving)
	{
		return _internal.AddRenderPassWithoutResolveAttachments(attachments, subpasses, subpassDependencies, addOnReserving);
	}

	IDObject<AutoCleanupRenderPass> RenderPassList::AddRenderPassWithResolveAttachments(
		const std::vector<IDObject<RenderPassAttachmentData>>& attachments, const std::vector<SubpassCreationDataWithResolving>& subpasses,
		const std::vector<IDObject<SubpassDependencyData>>& subpassDependencies, size_t addOnReserving)
	{
		return _internal.AddRenderPassWithResolveAttachments(attachments, subpasses, subpassDependencies, addOnReserving);
	}

}