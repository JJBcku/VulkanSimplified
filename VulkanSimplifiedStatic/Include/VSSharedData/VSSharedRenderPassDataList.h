#pragma once

#include <CustomLists\IDObjectDef.h>

#include "../../Include/VSCommon/VSAccessFlagsDef.h"
#include "../../Include/VSCommon/VSImageSampleFlagsDef.h"
#include "../../Include/VSCommon/VSImageLayoutFlagsDef.h"
#include "../../Include/VSCommon/VSPipelineStageFlagsDef.h"
#include "../../Include/VSCommon/VSRenderPassAttachmentOPDef.h"

#include "VSSharedRenderPassDataListDef.h"

namespace VulkanSimplifiedInternal
{
	class SharedRenderPassDataListInternal;
}

namespace VulkanSimplified
{
	struct SharedRenderPassDataListsCapacities;
	struct DataFormatSetIndependentID;

	enum ImageSampleFlagBits : ImageSampleFlags;

	union RenderPassClearValueID;

	constexpr uint32_t externalSubpass = std::numeric_limits<uint32_t>::max();

	class SharedRenderPassDataList
	{
	public:
		SharedRenderPassDataList(VulkanSimplifiedInternal::SharedRenderPassDataListInternal& ref);
		~SharedRenderPassDataList();

		IDObject<VulkanSimplifiedInternal::RenderPassAttachmentData> AddRenderPassAttachment(DataFormatSetIndependentID format, ImageSampleFlagBits samples,
			RenderPassAttachmentLoadOP loadOP, RenderPassAttachmentStoreOP storeOP, ImageLayoutFlags initialLayout,
			ImageLayoutFlags finalLayout, size_t addOnReserving = 0);
		IDObject<VulkanSimplifiedInternal::RenderPassAttachmentData> AddUniqueRenderPassAttachment(DataFormatSetIndependentID format, ImageSampleFlagBits samples,
			RenderPassAttachmentLoadOP loadOP, RenderPassAttachmentStoreOP storeOP, ImageLayoutFlags initialLayout,
			ImageLayoutFlags finalLayout, size_t addOnReserving = 0);

		IDObject<VulkanSimplifiedInternal::RenderPassAttachmentReference> AddRenderPassAttachmentReference(uint32_t attachmentIndex, ImageLayoutFlags subpassUsedAttachmentLayout,
			size_t addOnReserving = 0);
		IDObject<VulkanSimplifiedInternal::RenderPassAttachmentReference> AddUniqueRenderPassAttachmentReference(uint32_t attachmentIndex, ImageLayoutFlags subpassUsedAttachmentLayout,
			size_t addOnReserving = 0);

		IDObject<VulkanSimplifiedInternal::SubpassDependencyData> AddSubpassDependency(uint32_t srcSubpass, uint32_t dstSubpass, PipelineStageFlags srcStageFlags,
			PipelineStageFlags dstStageFlags, AccessFlags srcAccessFlags, AccessFlags dstAccessFlags, size_t addOnReserving = 0);
		IDObject<VulkanSimplifiedInternal::SubpassDependencyData> AddUniqueSubpassDependency(uint32_t srcSubpass, uint32_t dstSubpass, PipelineStageFlags srcStageFlags,
			PipelineStageFlags dstStageFlags, AccessFlags srcAccessFlags, AccessFlags dstAccessFlags, size_t addOnReserving = 0);

		IDObject<VulkanSimplifiedInternal::RenderPassDoubleColorClearValues> AddDoubleColorClearValue(double r, double g, double b, double a, size_t addOnReserving = 0);
		IDObject<VulkanSimplifiedInternal::RenderPassDoubleColorClearValues> AddUniqueDoubleColorClearValue(double r, double g, double b, double a, size_t addOnReserving = 0);
		IDObject<VulkanSimplifiedInternal::RenderPassInt64ColorClearValues> AddInt64ColorClearValue(int64_t r, int64_t g, int64_t b, int64_t a, size_t addOnReserving = 0);
		IDObject<VulkanSimplifiedInternal::RenderPassInt64ColorClearValues> AddUniqueInt64ColorClearValue(int64_t r, int64_t g, int64_t b, int64_t a, size_t addOnReserving = 0);
		IDObject<VulkanSimplifiedInternal::RenderPassUInt64ColorClearValues> AddUInt64ColorClearValue(uint64_t r, uint64_t g, uint64_t b, uint64_t a, size_t addOnReserving = 0);
		IDObject<VulkanSimplifiedInternal::RenderPassUInt64ColorClearValues> AddUniqueUInt64ColorClearValue(uint64_t r, uint64_t g, uint64_t b, uint64_t a, size_t addOnReserving = 0);

		IDObject<VulkanSimplifiedInternal::RenderPassFloatColorClearValues> AddFloatColorClearValue(float r, float g, float b, float a, size_t addOnReserving = 0);
		IDObject<VulkanSimplifiedInternal::RenderPassFloatColorClearValues> AddUniqueFloatColorClearValue(float r, float g, float b, float a, size_t addOnReserving = 0);
		IDObject<VulkanSimplifiedInternal::RenderPassIntColorClearValues> AddIntColorClearValue(int32_t r, int32_t g, int32_t b, int32_t a, size_t addOnReserving = 0);
		IDObject<VulkanSimplifiedInternal::RenderPassIntColorClearValues> AddUniqueIntColorClearValue(int32_t r, int32_t g, int32_t b, int32_t a, size_t addOnReserving = 0);
		IDObject<VulkanSimplifiedInternal::RenderPassUIntColorClearValues> AddUIntColorClearValue(uint32_t r, uint32_t g, uint32_t b, uint32_t a, size_t addOnReserving = 0);
		IDObject<VulkanSimplifiedInternal::RenderPassUIntColorClearValues> AddUniqueUIntColorClearValue(uint32_t r, uint32_t g, uint32_t b, uint32_t a, size_t addOnReserving = 0);

		IDObject<VulkanSimplifiedInternal::RenderPassDepthStencilClearValues> AddDepthStencilClearValue(float depth, uint32_t stencil, size_t addOnReserving = 0);
		IDObject<VulkanSimplifiedInternal::RenderPassDepthStencilClearValues> AddUniqueDepthStencilClearValue(float depth, uint32_t stencil, size_t addOnReserving = 0);

	private:
		VulkanSimplifiedInternal::SharedRenderPassDataListInternal& _internal;
	};
}