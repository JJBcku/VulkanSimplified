#pragma once

#include <CustomLists/UnsortedIDVector.h>

#include "../../../Include/VSCommon/VSAccessFlagsDef.h"
#include "../../../Include/VSCommon/VSImageSampleFlagsDef.h"
#include "../../../Include/VSCommon/VSImageLayoutFlagsDef.h"
#include "../../../Include/VSCommon/VSPipelineStageFlagsDef.h"
#include "../../../Include/VSCommon/VSRenderPassAttachmentOPDef.h"

#include <vector>
#include <utility>
#include <stdint.h>

union VkClearValue;
struct VkAttachmentDescription;
struct VkAttachmentReference;
struct VkSubpassDependency;

typedef uint32_t VkAccessFlags;

namespace VulkanSimplified
{
	struct SharedRenderPassDataListsCapacities;
	struct DataFormatSetIndependentID;

	enum ImageSampleFlagBits : ImageSampleFlags;

	union RenderPassClearValueID;
}

namespace VulkanSimplifiedInternal
{
	struct RenderPassAttachmentData;
	struct RenderPassAttachmentReference;
	struct SubpassDependencyData;

	struct RenderPassDoubleColorClearValues;
	struct RenderPassInt64ColorClearValues;
	struct RenderPassUInt64ColorClearValues;

	struct RenderPassFloatColorClearValues;
	struct RenderPassIntColorClearValues;
	struct RenderPassUIntColorClearValues;

	struct RenderPassDepthStencilClearValues;

	class SharedRenderPassDataListInternal
	{
	public:
		SharedRenderPassDataListInternal(const VulkanSimplified::SharedRenderPassDataListsCapacities& initialCapacities);
		~SharedRenderPassDataListInternal();

		IDObject<RenderPassAttachmentData> AddRenderPassAttachment(VulkanSimplified::DataFormatSetIndependentID format, VulkanSimplified::ImageSampleFlagBits samples,
			VulkanSimplified::RenderPassAttachmentLoadOP loadOP, VulkanSimplified::RenderPassAttachmentStoreOP storeOP, VulkanSimplified::ImageLayoutFlags initialLayout,
			VulkanSimplified::ImageLayoutFlags finalLayout, size_t addOnReserving);
		IDObject<RenderPassAttachmentData> AddUniqueRenderPassAttachment(VulkanSimplified::DataFormatSetIndependentID format, VulkanSimplified::ImageSampleFlagBits samples,
			VulkanSimplified::RenderPassAttachmentLoadOP loadOP, VulkanSimplified::RenderPassAttachmentStoreOP storeOP, VulkanSimplified::ImageLayoutFlags initialLayout,
			VulkanSimplified::ImageLayoutFlags finalLayout, size_t addOnReserving);

		IDObject<RenderPassAttachmentReference> AddRenderPassAttachmentReference(uint32_t attachmentIndex, VulkanSimplified::ImageLayoutFlags subpassUsedAttachmentLayout,
			size_t addOnReserving);
		IDObject<RenderPassAttachmentReference> AddUniqueRenderPassAttachmentReference(uint32_t attachmentIndex, VulkanSimplified::ImageLayoutFlags subpassUsedAttachmentLayout,
			size_t addOnReserving);

		IDObject<SubpassDependencyData> AddSubpassDependency(uint32_t srcSubpass, uint32_t dstSubpass, VulkanSimplified::PipelineStageFlags srcStageFlags,
			VulkanSimplified::PipelineStageFlags dstStageFlags, VulkanSimplified::AccessFlags srcAccessFlags, VulkanSimplified::AccessFlags dstAccessFlags, size_t addOnReserving);
		IDObject<SubpassDependencyData> AddUniqueSubpassDependency(uint32_t srcSubpass, uint32_t dstSubpass, VulkanSimplified::PipelineStageFlags srcStageFlags,
			VulkanSimplified::PipelineStageFlags dstStageFlags, VulkanSimplified::AccessFlags srcAccessFlags, VulkanSimplified::AccessFlags dstAccessFlags, size_t addOnReserving);

		IDObject<RenderPassDoubleColorClearValues> AddDoubleColorClearValue(double r, double g, double b, double a, size_t addOnReserving);
		IDObject<RenderPassDoubleColorClearValues> AddUniqueDoubleColorClearValue(double r, double g, double b, double a, size_t addOnReserving);
		IDObject<RenderPassInt64ColorClearValues> AddInt64ColorClearValue(int64_t r, int64_t g, int64_t b, int64_t a, size_t addOnReserving);
		IDObject<RenderPassInt64ColorClearValues> AddUniqueInt64ColorClearValue(int64_t r, int64_t g, int64_t b, int64_t a, size_t addOnReserving);
		IDObject<RenderPassUInt64ColorClearValues> AddUInt64ColorClearValue(uint64_t r, uint64_t g, uint64_t b, uint64_t a, size_t addOnReserving);
		IDObject<RenderPassUInt64ColorClearValues> AddUniqueUInt64ColorClearValue(uint64_t r, uint64_t g, uint64_t b, uint64_t a, size_t addOnReserving);

		IDObject<RenderPassFloatColorClearValues> AddFloatColorClearValue(float r, float g, float b, float a, size_t addOnReserving);
		IDObject<RenderPassFloatColorClearValues> AddUniqueFloatColorClearValue(float r, float g, float b, float a, size_t addOnReserving);
		IDObject<RenderPassIntColorClearValues> AddIntColorClearValue(int32_t r, int32_t g, int32_t b, int32_t a, size_t addOnReserving);
		IDObject<RenderPassIntColorClearValues> AddUniqueIntColorClearValue(int32_t r, int32_t g, int32_t b, int32_t a, size_t addOnReserving);
		IDObject<RenderPassUIntColorClearValues> AddUIntColorClearValue(uint32_t r, uint32_t g, uint32_t b, uint32_t a, size_t addOnReserving);
		IDObject<RenderPassUIntColorClearValues> AddUniqueUIntColorClearValue(uint32_t r, uint32_t g, uint32_t b, uint32_t a, size_t addOnReserving);

		IDObject<RenderPassDepthStencilClearValues> AddDepthStencilClearValue(float depth, uint32_t stencil, size_t addOnReserving);
		IDObject<RenderPassDepthStencilClearValues> AddUniqueDepthStencilClearValue(float depth, uint32_t stencil, size_t addOnReserving);

		std::vector<VkAttachmentDescription> GetRenderPassAttachmentDescriptors(const std::vector<IDObject<RenderPassAttachmentData>> attachmentIDs) const;

		std::vector<VkAttachmentReference> GetRenderPassAttachmentReferences(const std::vector<std::optional<IDObject<RenderPassAttachmentReference>>>& referenceIDs) const;
		VkAttachmentReference GetRenderPassAttachmentReference(const std::optional<IDObject<RenderPassAttachmentReference>>& referenceID) const;

		std::vector<VkSubpassDependency> GetSubpassDependencies(const std::vector<IDObject<SubpassDependencyData>>& dependencyIDs) const;

		std::pair<VkClearValue, std::optional<VkClearValue>> GetClearValue(VulkanSimplified::RenderPassClearValueID valueID) const;

	private:
		UnsortedIDVector<RenderPassAttachmentData> _attachmentData;
		UnsortedIDVector<RenderPassAttachmentReference> _attachmentReferenceData;
		UnsortedIDVector<SubpassDependencyData> _subpassDependencies;

		UnsortedIDVector<RenderPassDoubleColorClearValues> _doubleClearValues;
		UnsortedIDVector<RenderPassInt64ColorClearValues> _int64ClearValues;
		UnsortedIDVector<RenderPassUInt64ColorClearValues> _uint64ClearValues;

		UnsortedIDVector<RenderPassFloatColorClearValues> _floatClearValues;
		UnsortedIDVector<RenderPassIntColorClearValues> _intClearValues;
		UnsortedIDVector<RenderPassUIntColorClearValues> _uintClearValues;

		UnsortedIDVector<RenderPassDepthStencilClearValues> _depthClearValues;

		std::pair<VkClearValue, VkClearValue> GetDoubleColorClearValue(IDObject<RenderPassDoubleColorClearValues> valueID) const;
		std::pair<VkClearValue, VkClearValue> GetInt64ColorClearValue(IDObject<RenderPassInt64ColorClearValues> valueID) const;
		std::pair<VkClearValue, VkClearValue> GetUInt64ColorClearValue(IDObject<RenderPassUInt64ColorClearValues> valueID) const;

		VkClearValue GetFloatColorClearValue(IDObject<RenderPassFloatColorClearValues> valueID) const;
		VkClearValue GetIntColorClearValue(IDObject<RenderPassIntColorClearValues> valueID) const;
		VkClearValue GetUIntColorClearValue(IDObject<RenderPassUIntColorClearValues> valueID) const;

		VkClearValue GetDepthStencilClearValue(IDObject<RenderPassDepthStencilClearValues> valueID) const;

		VkAccessFlags CompileAccessFlags(VulkanSimplified::AccessFlags accessFlags);
	};
}