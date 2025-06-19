#include "VSSharedIpch.h"
#include "../../../Include/VSSharedData/VSSharedRenderPassDataList.h"

#include "../../../DoNotInclude/DNIHeaders/VSSharedData/VSSharedRenderPassDataInternal.h"

#include "../../../Include/VSCommon/VSAccessFlags.h"
#include "../../../Include/VSCommon/VSImageSampleFlags.h"
#include "../../../Include/VSCommon/VSImageLayoutFlags.h"
#include "../../../Include/VSCommon/VSRenderPassAttachmentOP.h"

#include "../../../DoNotInclude/DNIHeaders/VSCommon/VSDataFormatFlagsInternal.h"
#include "../../../DoNotInclude/DNIHeaders/VSCommon/VSPipelineStageFlagsInternal.h"

#include "../../../Include/VSSharedData/VSRenderPassClearValueID.h"

namespace VulkanSimplified
{
	SharedRenderPassDataList::SharedRenderPassDataList(VulkanSimplifiedInternal::SharedRenderPassDataListInternal& ref) : _internal(ref)
	{
	}

	SharedRenderPassDataList::~SharedRenderPassDataList()
	{
	}

	IDObject<VulkanSimplifiedInternal::RenderPassAttachmentData> SharedRenderPassDataList::AddRenderPassAttachment(DataFormatSetIndependentID format, ImageSampleFlagBits samples,
		RenderPassAttachmentLoadOP loadOP, RenderPassAttachmentStoreOP storeOP, ImageLayoutFlags initialLayout, ImageLayoutFlags finalLayout, size_t addOnReserving)
	{
		return _internal.AddRenderPassAttachment(format, samples, loadOP, storeOP, initialLayout, finalLayout, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::RenderPassAttachmentData> SharedRenderPassDataList::AddUniqueRenderPassAttachment(DataFormatSetIndependentID format,
		ImageSampleFlagBits samples, RenderPassAttachmentLoadOP loadOP, RenderPassAttachmentStoreOP storeOP, ImageLayoutFlags initialLayout, ImageLayoutFlags finalLayout,
		size_t addOnReserving)
	{
		return _internal.AddUniqueRenderPassAttachment(format, samples, loadOP, storeOP, initialLayout, finalLayout, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::RenderPassAttachmentReference> SharedRenderPassDataList::AddRenderPassAttachmentReference(uint32_t attachmentIndex,
		ImageLayoutFlags subpassUsedAttachmentLayout, size_t addOnReserving)
	{
		return _internal.AddRenderPassAttachmentReference(attachmentIndex, subpassUsedAttachmentLayout, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::RenderPassAttachmentReference> SharedRenderPassDataList::AddUniqueRenderPassAttachmentReference(uint32_t attachmentIndex,
		ImageLayoutFlags subpassUsedAttachmentLayout, size_t addOnReserving)
	{
		return _internal.AddUniqueRenderPassAttachmentReference(attachmentIndex, subpassUsedAttachmentLayout, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::SubpassDependencyData> SharedRenderPassDataList::AddSubpassDependency(uint32_t srcSubpass, uint32_t dstSubpass,
		PipelineStageFlags srcStageFlags, PipelineStageFlags dstStageFlags, AccessFlags srcAccessFlags, AccessFlags dstAccessFlags, size_t addOnReserving)
	{
		return _internal.AddSubpassDependency(srcSubpass, dstSubpass, srcStageFlags, dstStageFlags, srcAccessFlags, dstAccessFlags, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::SubpassDependencyData> SharedRenderPassDataList::AddUniqueSubpassDependency(uint32_t srcSubpass, uint32_t dstSubpass,
		PipelineStageFlags srcStageFlags, PipelineStageFlags dstStageFlags, AccessFlags srcAccessFlags, AccessFlags dstAccessFlags, size_t addOnReserving)
	{
		return _internal.AddUniqueSubpassDependency(srcSubpass, dstSubpass, srcStageFlags, dstStageFlags, srcAccessFlags, dstAccessFlags, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::RenderPassDoubleColorClearValues> SharedRenderPassDataList::AddDoubleColorClearValue(double r, double g, double b, double a,
		size_t addOnReserving)
	{
		return _internal.AddDoubleColorClearValue(r, g, b, a, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::RenderPassDoubleColorClearValues> SharedRenderPassDataList::AddUniqueDoubleColorClearValue(double r, double g, double b, double a,
		size_t addOnReserving)
	{
		return _internal.AddUniqueDoubleColorClearValue(r, g, b, a, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::RenderPassInt64ColorClearValues> SharedRenderPassDataList::AddInt64ColorClearValue(int64_t r, int64_t g, int64_t b, int64_t a,
		size_t addOnReserving)
	{
		return _internal.AddInt64ColorClearValue(r, g, b, a, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::RenderPassInt64ColorClearValues> SharedRenderPassDataList::AddUniqueInt64ColorClearValue(int64_t r, int64_t g, int64_t b, int64_t a,
		size_t addOnReserving)
	{
		return _internal.AddUniqueInt64ColorClearValue(r, g, b, a, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::RenderPassUInt64ColorClearValues> SharedRenderPassDataList::AddUInt64ColorClearValue(uint64_t r, uint64_t g, uint64_t b, uint64_t a,
		size_t addOnReserving)
	{
		return _internal.AddUInt64ColorClearValue(r, g, b, a, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::RenderPassUInt64ColorClearValues> SharedRenderPassDataList::AddUniqueUInt64ColorClearValue(uint64_t r, uint64_t g, uint64_t b, uint64_t a,
		size_t addOnReserving)
	{
		return _internal.AddUniqueUInt64ColorClearValue(r, g, b, a, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::RenderPassFloatColorClearValues> SharedRenderPassDataList::AddFloatColorClearValue(float r, float g, float b, float a, size_t addOnReserving)
	{
		return _internal.AddFloatColorClearValue(r, g, b, a, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::RenderPassFloatColorClearValues> SharedRenderPassDataList::AddUniqueFloatColorClearValue(float r, float g, float b, float a,
		size_t addOnReserving)
	{
		return _internal.AddUniqueFloatColorClearValue(r, g, b, a, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::RenderPassIntColorClearValues> SharedRenderPassDataList::AddIntColorClearValue(int32_t r, int32_t g, int32_t b, int32_t a, size_t addOnReserving)
	{
		return _internal.AddIntColorClearValue(r, g, b, a, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::RenderPassIntColorClearValues> SharedRenderPassDataList::AddUniqueIntColorClearValue(int32_t r, int32_t g, int32_t b, int32_t a, size_t addOnReserving)
	{
		return _internal.AddUniqueIntColorClearValue(r, g, b, a, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::RenderPassUIntColorClearValues> SharedRenderPassDataList::AddUIntColorClearValue(uint32_t r, uint32_t g, uint32_t b, uint32_t a,
		size_t addOnReserving)
	{
		return _internal.AddUIntColorClearValue(r, g, b, a, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::RenderPassUIntColorClearValues> SharedRenderPassDataList::AddUniqueUIntColorClearValue(uint32_t r, uint32_t g, uint32_t b, uint32_t a,
		size_t addOnReserving)
	{
		return _internal.AddUniqueUIntColorClearValue(r, g, b, a, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::RenderPassDepthStencilClearValues> SharedRenderPassDataList::AddDepthStencilClearValue(float depth, uint32_t stencil, size_t addOnReserving)
	{
		return _internal.AddDepthStencilClearValue(depth, stencil, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::RenderPassDepthStencilClearValues> SharedRenderPassDataList::AddUniqueDepthStencilClearValue(float depth, uint32_t stencil, size_t addOnReserving)
	{
		return _internal.AddUniqueDepthStencilClearValue(depth, stencil, addOnReserving);
	}

}