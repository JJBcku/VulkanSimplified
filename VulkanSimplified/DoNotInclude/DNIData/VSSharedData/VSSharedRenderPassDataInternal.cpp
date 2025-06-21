#include "VSSharedNIpch.h"
#include "VSSharedRenderPassDataInternal.h"

#include "../../../Include/VSSharedData/VSSharedRenderPassDataListsCapacities.h"

#include "VSRenderPassAttachmentData.h"
#include "VSRenderPassAttachmentReference.h"
#include "VSRenderPassClearValues.h"

#include "VSSubpassDependencyData.h"

#include "../../../Include/VSCommon/VSAccessFlags.h"
#include "../../../Include/VSCommon/VSImageSampleFlags.h"
#include "../../../Include/VSCommon/VSImageLayoutFlags.h"
#include "../../../Include/VSCommon/VSRenderPassAttachmentOP.h"

#include "../VSCommon/VSDataFormatFlagsInternal.h"
#include "../VSCommon/VSPipelineStageFlagsInternal.h"

#include "../../../Include/VSSharedData/VSRenderPassClearValueID.h"

namespace VulkanSimplified
{
	SharedRenderPassDataListInternal::SharedRenderPassDataListInternal(const SharedRenderPassDataListsCapacities& initialCapacities) :
		_attachmentData(initialCapacities.sharedRenderPassAttachmentsInitialCapacity), _attachmentReferenceData(initialCapacities.sharedRenderPassReferencesInitialCapacity),
		_subpassDependencies(initialCapacities.sharedSubpassDependenciesInitialCapacity), _doubleClearValues(initialCapacities.doubleColorClearValueInitialCapacity),
		_int64ClearValues(initialCapacities.int64ColorClearValueInitialCapacity), _uint64ClearValues(initialCapacities.uint64ColorClearValueInitialCapacity),
		_floatClearValues(initialCapacities.floatColorClearValueInitialCapacity), _intClearValues(initialCapacities.intColorClearValueInitialCapacity),
		_uintClearValues(initialCapacities.uintColorClearValueInitialCapacity), _depthClearValues(initialCapacities.depthStencilColorClearValueInitialCapacity)
	{
	}

	SharedRenderPassDataListInternal::~SharedRenderPassDataListInternal()
	{
	}

	IDObject<RenderPassAttachmentData> SharedRenderPassDataListInternal::AddRenderPassAttachment(DataFormatSetIndependentID format,
		ImageSampleFlagBits samples, RenderPassAttachmentLoadOP loadOP, RenderPassAttachmentStoreOP storeOP,
		ImageLayoutFlags initialLayout, ImageLayoutFlags finalLayout, size_t addOnReserving)
	{
		RenderPassAttachmentData add;

		add.format = TranslateDataFormatToVkFormat(format);

		switch (samples)
		{
		case SAMPLE_64:
			add.samples = VK_SAMPLE_COUNT_64_BIT;
			break;
		case SAMPLE_32:
			add.samples = VK_SAMPLE_COUNT_32_BIT;
			break;
		case SAMPLE_16:
			add.samples = VK_SAMPLE_COUNT_16_BIT;
			break;
		case SAMPLE_8:
			add.samples = VK_SAMPLE_COUNT_8_BIT;
			break;
		case SAMPLE_4:
			add.samples = VK_SAMPLE_COUNT_4_BIT;
			break;
		case SAMPLE_2:
			add.samples = VK_SAMPLE_COUNT_2_BIT;
			break;
		case SAMPLE_1:
			add.samples = VK_SAMPLE_COUNT_1_BIT;
			break;
		default:
			throw std::runtime_error("SharedRenderPassDataListInternal::AddRenderPassAttachment Error: Program was given an erroneous sample count value!");
		}

		switch (loadOP)
		{
		case RenderPassAttachmentLoadOP::IGNORE:
			add.loadOP = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
			break;
		case RenderPassAttachmentLoadOP::CLEAR:
			add.loadOP = VK_ATTACHMENT_LOAD_OP_CLEAR;
			break;
		case RenderPassAttachmentLoadOP::LOAD:
			add.loadOP = VK_ATTACHMENT_LOAD_OP_LOAD;
			break;
		default:
			throw std::runtime_error("SharedRenderPassDataListInternal::AddRenderPassAttachment Error: Program was given an erroneous load operation value!");
		}

		switch (storeOP)
		{
		case RenderPassAttachmentStoreOP::IGNORE:
			add.storeOP = VK_ATTACHMENT_STORE_OP_DONT_CARE;
			break;
		case RenderPassAttachmentStoreOP::STORE:
			add.storeOP = VK_ATTACHMENT_STORE_OP_STORE;
			break;
		default:
			throw std::runtime_error("SharedRenderPassDataListInternal::AddRenderPassAttachment Error: Program was given an erroneous store operation value!");
		}

		switch (initialLayout)
		{
		case ImageLayoutFlags::PRESENT:
			add.initialLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
			break;
		case ImageLayoutFlags::TRANSFER_DESTINATION:
			add.initialLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
			break;
		case ImageLayoutFlags::TRANSFER_SOURCE:
			add.initialLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
			break;
		case ImageLayoutFlags::SHADER_READ_ONLY:
			add.initialLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			break;
		case ImageLayoutFlags::DEPTH_STENCIL_READ_ONLY:
			add.initialLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
			break;
		case ImageLayoutFlags::DEPTH_STENCIL_READ_WRITE:
			add.initialLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
			break;
		case ImageLayoutFlags::COLOR_ATTACHMENT:
			add.initialLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
			break;
		case ImageLayoutFlags::GENERAL:
			add.initialLayout = VK_IMAGE_LAYOUT_GENERAL;
			break;
		case ImageLayoutFlags::UNDEFINED:
			add.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			break;
		default:
			throw std::runtime_error("SharedRenderPassDataListInternal::AddRenderPassAttachment Error: Program was given an erroneous initial layout value!");
		}

		switch (finalLayout)
		{
		case ImageLayoutFlags::PRESENT:
			add.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
			break;
		case ImageLayoutFlags::TRANSFER_DESTINATION:
			add.finalLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
			break;
		case ImageLayoutFlags::TRANSFER_SOURCE:
			add.finalLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
			break;
		case ImageLayoutFlags::SHADER_READ_ONLY:
			add.finalLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			break;
		case ImageLayoutFlags::DEPTH_STENCIL_READ_ONLY:
			add.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
			break;
		case ImageLayoutFlags::DEPTH_STENCIL_READ_WRITE:
			add.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
			break;
		case ImageLayoutFlags::COLOR_ATTACHMENT:
			add.finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
			break;
		case ImageLayoutFlags::GENERAL:
			add.finalLayout = VK_IMAGE_LAYOUT_GENERAL;
			break;
		case ImageLayoutFlags::UNDEFINED:
			add.finalLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			break;
		default:
			throw std::runtime_error("SharedRenderPassDataListInternal::AddRenderPassAttachment Error: Program was given an erroneous final layout value!");
		}

		return _attachmentData.AddObject(std::move(add), addOnReserving);
	}

	IDObject<RenderPassAttachmentData> SharedRenderPassDataListInternal::AddUniqueRenderPassAttachment(DataFormatSetIndependentID format,
		ImageSampleFlagBits samples, RenderPassAttachmentLoadOP loadOP, RenderPassAttachmentStoreOP storeOP,
		ImageLayoutFlags initialLayout, ImageLayoutFlags finalLayout, size_t addOnReserving)
	{
		RenderPassAttachmentData add;

		add.format = TranslateDataFormatToVkFormat(format);

		switch (samples)
		{
		case SAMPLE_64:
			add.samples = VK_SAMPLE_COUNT_64_BIT;
			break;
		case SAMPLE_32:
			add.samples = VK_SAMPLE_COUNT_32_BIT;
			break;
		case SAMPLE_16:
			add.samples = VK_SAMPLE_COUNT_16_BIT;
			break;
		case SAMPLE_8:
			add.samples = VK_SAMPLE_COUNT_8_BIT;
			break;
		case SAMPLE_4:
			add.samples = VK_SAMPLE_COUNT_4_BIT;
			break;
		case SAMPLE_2:
			add.samples = VK_SAMPLE_COUNT_2_BIT;
			break;
		case SAMPLE_1:
			add.samples = VK_SAMPLE_COUNT_1_BIT;
			break;
		default:
			throw std::runtime_error("SharedRenderPassDataListInternal::AddUniqueRenderPassAttachment Error: Program was given an erroneous sample count value!");
		}

		switch (loadOP)
		{
		case RenderPassAttachmentLoadOP::IGNORE:
			add.loadOP = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
			break;
		case RenderPassAttachmentLoadOP::CLEAR:
			add.loadOP = VK_ATTACHMENT_LOAD_OP_CLEAR;
			break;
		case RenderPassAttachmentLoadOP::LOAD:
			add.loadOP = VK_ATTACHMENT_LOAD_OP_LOAD;
			break;
		default:
			throw std::runtime_error("SharedRenderPassDataListInternal::AddUniqueRenderPassAttachment Error: Program was given an erroneous load operation value!");
		}

		switch (storeOP)
		{
		case RenderPassAttachmentStoreOP::IGNORE:
			add.storeOP = VK_ATTACHMENT_STORE_OP_DONT_CARE;
			break;
		case RenderPassAttachmentStoreOP::STORE:
			add.storeOP = VK_ATTACHMENT_STORE_OP_STORE;
			break;
		default:
			throw std::runtime_error("SharedRenderPassDataListInternal::AddUniqueRenderPassAttachment Error: Program was given an erroneous store operation value!");
		}

		switch (initialLayout)
		{
		case ImageLayoutFlags::PRESENT:
			add.initialLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
			break;
		case ImageLayoutFlags::TRANSFER_DESTINATION:
			add.initialLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
			break;
		case ImageLayoutFlags::TRANSFER_SOURCE:
			add.initialLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
			break;
		case ImageLayoutFlags::SHADER_READ_ONLY:
			add.initialLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			break;
		case ImageLayoutFlags::DEPTH_STENCIL_READ_ONLY:
			add.initialLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
			break;
		case ImageLayoutFlags::DEPTH_STENCIL_READ_WRITE:
			add.initialLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
			break;
		case ImageLayoutFlags::COLOR_ATTACHMENT:
			add.initialLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
			break;
		case ImageLayoutFlags::GENERAL:
			add.initialLayout = VK_IMAGE_LAYOUT_GENERAL;
			break;
		case ImageLayoutFlags::UNDEFINED:
			add.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			break;
		default:
			throw std::runtime_error("SharedRenderPassDataListInternal::AddUniqueRenderPassAttachment Error: Program was given an erroneous initial layout value!");
		}

		switch (finalLayout)
		{
		case ImageLayoutFlags::PRESENT:
			add.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
			break;
		case ImageLayoutFlags::TRANSFER_DESTINATION:
			add.finalLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
			break;
		case ImageLayoutFlags::TRANSFER_SOURCE:
			add.finalLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
			break;
		case ImageLayoutFlags::SHADER_READ_ONLY:
			add.finalLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			break;
		case ImageLayoutFlags::DEPTH_STENCIL_READ_ONLY:
			add.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
			break;
		case ImageLayoutFlags::DEPTH_STENCIL_READ_WRITE:
			add.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
			break;
		case ImageLayoutFlags::COLOR_ATTACHMENT:
			add.finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
			break;
		case ImageLayoutFlags::GENERAL:
			add.finalLayout = VK_IMAGE_LAYOUT_GENERAL;
			break;
		case ImageLayoutFlags::UNDEFINED:
			add.finalLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			break;
		default:
			throw std::runtime_error("SharedRenderPassDataListInternal::AddUniqueRenderPassAttachment Error: Program was given an erroneous final layout value!");
		}

		return _attachmentData.AddUniqueObject(std::move(add), addOnReserving);
	}

	IDObject<RenderPassAttachmentReference> SharedRenderPassDataListInternal::AddRenderPassAttachmentReference(uint32_t attachmentIndex,
		ImageLayoutFlags subpassUsedAttachmentLayout, size_t addOnReserving)
	{
		RenderPassAttachmentReference add;
		add.attachmentIndex = attachmentIndex;

		switch (subpassUsedAttachmentLayout)
		{
		case ImageLayoutFlags::PRESENT:
			add.attachmentLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
			break;
		case ImageLayoutFlags::TRANSFER_DESTINATION:
			add.attachmentLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
			break;
		case ImageLayoutFlags::TRANSFER_SOURCE:
			add.attachmentLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
			break;
		case ImageLayoutFlags::SHADER_READ_ONLY:
			add.attachmentLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			break;
		case ImageLayoutFlags::DEPTH_STENCIL_READ_ONLY:
			add.attachmentLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
			break;
		case ImageLayoutFlags::DEPTH_STENCIL_READ_WRITE:
			add.attachmentLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
			break;
		case ImageLayoutFlags::COLOR_ATTACHMENT:
			add.attachmentLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
			break;
		case ImageLayoutFlags::GENERAL:
			add.attachmentLayout = VK_IMAGE_LAYOUT_GENERAL;
			break;
		case ImageLayoutFlags::UNDEFINED:
			add.attachmentLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			break;
		default:
			throw std::runtime_error("SharedRenderPassDataListInternal::AddRenderPassAttachment Error: Program was given an erroneous subpasses used attachment layout value!");
		}

		return _attachmentReferenceData.AddObject(std::move(add), addOnReserving);
	}

	IDObject<RenderPassAttachmentReference> SharedRenderPassDataListInternal::AddUniqueRenderPassAttachmentReference(uint32_t attachmentIndex,
		ImageLayoutFlags subpassUsedAttachmentLayout, size_t addOnReserving)
	{
		RenderPassAttachmentReference add;
		add.attachmentIndex = attachmentIndex;

		switch (subpassUsedAttachmentLayout)
		{
		case ImageLayoutFlags::PRESENT:
			add.attachmentLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
			break;
		case ImageLayoutFlags::TRANSFER_DESTINATION:
			add.attachmentLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
			break;
		case ImageLayoutFlags::TRANSFER_SOURCE:
			add.attachmentLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
			break;
		case ImageLayoutFlags::SHADER_READ_ONLY:
			add.attachmentLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			break;
		case ImageLayoutFlags::DEPTH_STENCIL_READ_ONLY:
			add.attachmentLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
			break;
		case ImageLayoutFlags::DEPTH_STENCIL_READ_WRITE:
			add.attachmentLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
			break;
		case ImageLayoutFlags::COLOR_ATTACHMENT:
			add.attachmentLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
			break;
		case ImageLayoutFlags::GENERAL:
			add.attachmentLayout = VK_IMAGE_LAYOUT_GENERAL;
			break;
		case ImageLayoutFlags::UNDEFINED:
			add.attachmentLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			break;
		default:
			throw std::runtime_error("SharedRenderPassDataListInternal::AddUniqueRenderPassAttachmentReference Error: Program was given an erroneous subpasses used attachment layout value!");
		}

		return _attachmentReferenceData.AddUniqueObject(std::move(add), addOnReserving);
	}

	IDObject<SubpassDependencyData> SharedRenderPassDataListInternal::AddSubpassDependency(uint32_t srcSubpass, uint32_t dstSubpass,
		PipelineStageFlags srcStageFlags, PipelineStageFlags dstStageFlags, AccessFlags srcAccessFlags,
		AccessFlags dstAccessFlags, size_t addOnReserving)
	{
		SubpassDependencyData add;

		add.srcSubpass = srcSubpass;
		add.dstSubpass = dstSubpass;

		add.srcStageFlags = TranslateStageFlags(srcStageFlags);
		add.dstStageFlags = TranslateStageFlags(dstStageFlags);

		add.srcAccessFlags = CompileAccessFlags(srcAccessFlags);
		add.dstAccessFlags = CompileAccessFlags(dstAccessFlags);

		return _subpassDependencies.AddObject(std::move(add), addOnReserving);
	}

	IDObject<SubpassDependencyData> SharedRenderPassDataListInternal::AddUniqueSubpassDependency(uint32_t srcSubpass, uint32_t dstSubpass,
		PipelineStageFlags srcStageFlags, PipelineStageFlags dstStageFlags, AccessFlags srcAccessFlags,
		AccessFlags dstAccessFlags, size_t addOnReserving)
	{
		SubpassDependencyData add;

		add.srcSubpass = srcSubpass;
		add.dstSubpass = dstSubpass;

		add.srcStageFlags = TranslateStageFlags(srcStageFlags);
		add.dstStageFlags = TranslateStageFlags(dstStageFlags);

		add.srcAccessFlags = CompileAccessFlags(srcAccessFlags);
		add.dstAccessFlags = CompileAccessFlags(dstAccessFlags);

		return _subpassDependencies.AddUniqueObject(std::move(add), addOnReserving);
	}

	IDObject<RenderPassDoubleColorClearValues> SharedRenderPassDataListInternal::AddDoubleColorClearValue(double r, double g, double b, double a, size_t addOnReserving)
	{
		RenderPassDoubleColorClearValues add{};

		add.r = r;
		add.g = g;
		add.b = b;
		add.a = a;

		return _doubleClearValues.AddObject(add, addOnReserving);
	}

	IDObject<RenderPassDoubleColorClearValues> SharedRenderPassDataListInternal::AddUniqueDoubleColorClearValue(double r, double g, double b, double a, size_t addOnReserving)
	{
		RenderPassDoubleColorClearValues add{};

		add.r = r;
		add.g = g;
		add.b = b;
		add.a = a;

		return _doubleClearValues.AddUniqueObject(add, addOnReserving);
	}

	IDObject<RenderPassInt64ColorClearValues> SharedRenderPassDataListInternal::AddInt64ColorClearValue(int64_t r, int64_t g, int64_t b, int64_t a, size_t addOnReserving)
	{
		RenderPassInt64ColorClearValues add{};

		add.r = r;
		add.g = g;
		add.b = b;
		add.a = a;

		return _int64ClearValues.AddObject(add, addOnReserving);
	}

	IDObject<RenderPassInt64ColorClearValues> SharedRenderPassDataListInternal::AddUniqueInt64ColorClearValue(int64_t r, int64_t g, int64_t b, int64_t a, size_t addOnReserving)
	{
		RenderPassInt64ColorClearValues add{};

		add.r = r;
		add.g = g;
		add.b = b;
		add.a = a;

		return _int64ClearValues.AddUniqueObject(add, addOnReserving);
	}

	IDObject<RenderPassUInt64ColorClearValues> SharedRenderPassDataListInternal::AddUInt64ColorClearValue(uint64_t r, uint64_t g, uint64_t b, uint64_t a, size_t addOnReserving)
	{
		RenderPassUInt64ColorClearValues add{};

		add.r = r;
		add.g = g;
		add.b = b;
		add.a = a;

		return _uint64ClearValues.AddObject(add, addOnReserving);
	}

	IDObject<RenderPassUInt64ColorClearValues> SharedRenderPassDataListInternal::AddUniqueUInt64ColorClearValue(uint64_t r, uint64_t g, uint64_t b, uint64_t a, size_t addOnReserving)
	{
		RenderPassUInt64ColorClearValues add{};

		add.r = r;
		add.g = g;
		add.b = b;
		add.a = a;

		return _uint64ClearValues.AddUniqueObject(add, addOnReserving);
	}

	IDObject<RenderPassFloatColorClearValues> SharedRenderPassDataListInternal::AddFloatColorClearValue(float r, float g, float b, float a, size_t addOnReserving)
	{
		RenderPassFloatColorClearValues add{};

		add.r = r;
		add.g = g;
		add.b = b;
		add.a = a;

		return _floatClearValues.AddObject(add, addOnReserving);
	}

	IDObject<RenderPassFloatColorClearValues> SharedRenderPassDataListInternal::AddUniqueFloatColorClearValue(float r, float g, float b, float a, size_t addOnReserving)
	{
		RenderPassFloatColorClearValues add{};

		add.r = r;
		add.g = g;
		add.b = b;
		add.a = a;

		return _floatClearValues.AddUniqueObject(add, addOnReserving);
	}

	IDObject<RenderPassIntColorClearValues> SharedRenderPassDataListInternal::AddIntColorClearValue(int32_t r, int32_t g, int32_t b, int32_t a, size_t addOnReserving)
	{
		RenderPassIntColorClearValues add{};

		add.r = r;
		add.g = g;
		add.b = b;
		add.a = a;

		return _intClearValues.AddObject(add, addOnReserving);
	}

	IDObject<RenderPassIntColorClearValues> SharedRenderPassDataListInternal::AddUniqueIntColorClearValue(int32_t r, int32_t g, int32_t b, int32_t a, size_t addOnReserving)
	{
		RenderPassIntColorClearValues add{};

		add.r = r;
		add.g = g;
		add.b = b;
		add.a = a;

		return _intClearValues.AddUniqueObject(add, addOnReserving);
	}

	IDObject<RenderPassUIntColorClearValues> SharedRenderPassDataListInternal::AddUIntColorClearValue(uint32_t r, uint32_t g, uint32_t b, uint32_t a, size_t addOnReserving)
	{
		RenderPassUIntColorClearValues add{};

		add.r = r;
		add.g = g;
		add.b = b;
		add.a = a;

		return _uintClearValues.AddObject(add, addOnReserving);
	}

	IDObject<RenderPassUIntColorClearValues> SharedRenderPassDataListInternal::AddUniqueUIntColorClearValue(uint32_t r, uint32_t g, uint32_t b, uint32_t a, size_t addOnReserving)
	{
		RenderPassUIntColorClearValues add{};

		add.r = r;
		add.g = g;
		add.b = b;
		add.a = a;

		return _uintClearValues.AddUniqueObject(add, addOnReserving);
	}

	IDObject<RenderPassDepthStencilClearValues> SharedRenderPassDataListInternal::AddDepthStencilClearValue(float depth, uint32_t stencil, size_t addOnReserving)
	{
		RenderPassDepthStencilClearValues add{};
		add.d = depth;
		add.s = stencil;

		return _depthClearValues.AddObject(add, addOnReserving);
	}

	IDObject<RenderPassDepthStencilClearValues> SharedRenderPassDataListInternal::AddUniqueDepthStencilClearValue(float depth, uint32_t stencil, size_t addOnReserving)
	{
		RenderPassDepthStencilClearValues add{};
		add.d = depth;
		add.s = stencil;

		return _depthClearValues.AddUniqueObject(add, addOnReserving);
	}

	std::vector<VkAttachmentDescription> SharedRenderPassDataListInternal::GetRenderPassAttachmentDescriptors(const std::vector<IDObject<RenderPassAttachmentData>> attachmentIDs) const
	{
		assert(!attachmentIDs.empty());

		std::vector<VkAttachmentDescription> ret;
		ret.reserve(attachmentIDs.size());

		auto attachmentData = _attachmentData.GetObjectList(attachmentIDs);

		for (auto& data : attachmentData)
		{
			VkAttachmentDescription add{};

			add.format = data.format;
			add.samples = data.samples;
			add.loadOp = data.loadOP;
			add.storeOp = data.storeOP;
			add.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
			add.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
			add.initialLayout = data.initialLayout;
			add.finalLayout = data.finalLayout;

			ret.push_back(add);
		}

		return ret;
	}

	std::vector<VkAttachmentReference> SharedRenderPassDataListInternal::GetRenderPassAttachmentReferences(const std::vector<std::optional<IDObject<RenderPassAttachmentReference>>>& referenceIDs) const
	{
		std::vector<VkAttachmentReference> ret;
		ret.reserve(referenceIDs.size());

		for (auto& ID : referenceIDs)
		{
			VkAttachmentReference add{};

			if (ID.has_value())
			{
				auto& reference = _attachmentReferenceData.GetConstObject(ID.value());

				add.attachment = reference.attachmentIndex;
				add.layout = reference.attachmentLayout;
			}
			else
			{
				add.attachment = VK_ATTACHMENT_UNUSED;
				add.layout = VK_IMAGE_LAYOUT_UNDEFINED;
			}

			ret.push_back(add);
		}

		return ret;
	}

	VkAttachmentReference SharedRenderPassDataListInternal::GetRenderPassAttachmentReference(const std::optional<IDObject<RenderPassAttachmentReference>>& referenceID) const
	{
		VkAttachmentReference ret{};

		if (referenceID.has_value())
		{
			auto& reference = _attachmentReferenceData.GetConstObject(referenceID.value());

			ret.attachment = reference.attachmentIndex;
			ret.layout = reference.attachmentLayout;
		}
		else
		{
			ret.attachment = VK_ATTACHMENT_UNUSED;
			ret.layout = VK_IMAGE_LAYOUT_UNDEFINED;
		}

		return ret;
	}

	std::vector<VkSubpassDependency> SharedRenderPassDataListInternal::GetSubpassDependencies(const std::vector<IDObject<SubpassDependencyData>>& dependencyIDs) const
	{
		std::vector<VkSubpassDependency> ret;
		ret.reserve(dependencyIDs.size());

		auto dependencyData = _subpassDependencies.GetObjectList(dependencyIDs);

		for (auto& data : dependencyData)
		{
			VkSubpassDependency add{};
			add.srcSubpass = data.srcSubpass;
			add.dstSubpass = data.dstSubpass;
			add.srcStageMask = data.srcStageFlags;
			add.dstStageMask = data.dstStageFlags;
			add.srcAccessMask = data.srcAccessFlags;
			add.dstAccessMask = data.dstAccessFlags;

			ret.push_back(add);
		}

		return ret;
	}

	std::pair<VkClearValue, std::optional<VkClearValue>> SharedRenderPassDataListInternal::GetClearValue(RenderPassClearValueID valueID) const
	{
		std::pair<VkClearValue, std::optional<VkClearValue>> ret;

		std::pair<VkClearValue, VkClearValue> data;

		switch (valueID.type)
		{
		case RenderPassClearValueIDType::COLOR_DOUBLE:
			data = GetDoubleColorClearValue(valueID.doubleColorID.ID);
			ret.first = data.first;
			ret.second = data.second;
			break;
		case RenderPassClearValueIDType::COLOR_INT64:
			data = GetInt64ColorClearValue(valueID.int64ColorID.ID);
			ret.first = data.first;
			ret.second = data.second;
			break;
		case RenderPassClearValueIDType::COLOR_UINT64:
			data = GetUInt64ColorClearValue(valueID.uint64ColorID.ID);
			ret.first = data.first;
			ret.second = data.second;
			break;
		case RenderPassClearValueIDType::COLOR_FLOAT:
			ret.first = GetFloatColorClearValue(valueID.floatColorID.ID);
			break;
		case RenderPassClearValueIDType::COLOR_INT:
			ret.first = GetIntColorClearValue(valueID.intColorID.ID);
			break;
		case RenderPassClearValueIDType::COLOR_UINT:
			ret.first = GetUIntColorClearValue(valueID.uintColorID.ID);
			break;
		case RenderPassClearValueIDType::DEPTH_STENCIL:
			ret.first = GetDepthStencilClearValue(valueID.depthStencilID.ID);
			break;
		default:
			throw std::runtime_error("SharedRenderPassDataListInternal::GetClearValue Error: Program was given an erroneous type of value's id!");
		}

		return ret;
	}

	std::pair<VkClearValue, VkClearValue> SharedRenderPassDataListInternal::GetDoubleColorClearValue(IDObject<RenderPassDoubleColorClearValues> valueID) const
	{
		std::pair<VkClearValue, VkClearValue> ret;

		auto& data = _doubleClearValues.GetConstObject(valueID);

		std::memcpy(&ret.first.color, &data.r, sizeof(double) << 1);
		std::memcpy(&ret.second.color, &data.b, sizeof(double) << 1);

		return ret;
	}

	std::pair<VkClearValue, VkClearValue> SharedRenderPassDataListInternal::GetInt64ColorClearValue(IDObject<RenderPassInt64ColorClearValues> valueID) const
	{
		std::pair<VkClearValue, VkClearValue> ret;

		auto& data = _int64ClearValues.GetConstObject(valueID);

		std::memcpy(&ret.first.color, &data.r, sizeof(int64_t) << 1);
		std::memcpy(&ret.second.color, &data.b, sizeof(int64_t) << 1);

		return ret;
	}

	std::pair<VkClearValue, VkClearValue> SharedRenderPassDataListInternal::GetUInt64ColorClearValue(IDObject<RenderPassUInt64ColorClearValues> valueID) const
	{
		std::pair<VkClearValue, VkClearValue> ret;

		auto& data = _uint64ClearValues.GetConstObject(valueID);

		std::memcpy(&ret.first.color, &data.r, sizeof(uint64_t) << 1);
		std::memcpy(&ret.second.color, &data.b, sizeof(uint64_t) << 1);

		return ret;
	}

	VkClearValue SharedRenderPassDataListInternal::GetFloatColorClearValue(IDObject<RenderPassFloatColorClearValues> valueID) const
	{
		VkClearValue ret{};

		auto& data = _floatClearValues.GetConstObject(valueID);

		ret.color.float32[0] = data.r;
		ret.color.float32[1] = data.g;
		ret.color.float32[2] = data.b;
		ret.color.float32[3] = data.a;

		return ret;
	}

	VkClearValue SharedRenderPassDataListInternal::GetIntColorClearValue(IDObject<RenderPassIntColorClearValues> valueID) const
	{
		VkClearValue ret{};

		auto& data = _intClearValues.GetConstObject(valueID);

		ret.color.int32[0] = data.r;
		ret.color.int32[1] = data.g;
		ret.color.int32[2] = data.b;
		ret.color.int32[3] = data.a;

		return ret;
	}

	VkClearValue SharedRenderPassDataListInternal::GetUIntColorClearValue(IDObject<RenderPassUIntColorClearValues> valueID) const
	{
		VkClearValue ret{};

		auto& data = _uintClearValues.GetConstObject(valueID);

		ret.color.uint32[0] = data.r;
		ret.color.uint32[1] = data.g;
		ret.color.uint32[2] = data.b;
		ret.color.uint32[3] = data.a;

		return ret;
	}

	VkClearValue SharedRenderPassDataListInternal::GetDepthStencilClearValue(IDObject<RenderPassDepthStencilClearValues> valueID) const
	{
		VkClearValue ret{};

		auto& data = _depthClearValues.GetConstObject(valueID);

		ret.depthStencil.depth = data.d;
		ret.depthStencil.stencil = data.s;

		return ret;
	}

	VkAccessFlags SharedRenderPassDataListInternal::CompileAccessFlags(AccessFlags accessFlags)
	{
		VkAccessFlags ret = 0;

		if ((accessFlags & ACCESS_INDIRECT_COMMAND_READ) == ACCESS_INDIRECT_COMMAND_READ)
			ret |= VK_ACCESS_INDIRECT_COMMAND_READ_BIT;

		if ((accessFlags & ACCESS_INDEX_READ) == ACCESS_INDEX_READ)
			ret |= VK_ACCESS_INDEX_READ_BIT;

		if ((accessFlags & ACCESS_VERTEX_ATTRIBUTE_READ) == ACCESS_VERTEX_ATTRIBUTE_READ)
			ret |= VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT;

		if ((accessFlags & ACCESS_UNIFORM_READ) == ACCESS_UNIFORM_READ)
			ret |= VK_ACCESS_UNIFORM_READ_BIT;

		if ((accessFlags & ACCESS_INPUT_ATTACHMENT_READ) == ACCESS_INPUT_ATTACHMENT_READ)
			ret |= VK_ACCESS_INPUT_ATTACHMENT_READ_BIT;

		if ((accessFlags & ACCESS_SHADER_READ) == ACCESS_SHADER_READ)
			ret |= VK_ACCESS_SHADER_READ_BIT;

		if ((accessFlags & ACCESS_SHADER_WRITE) == ACCESS_SHADER_WRITE)
			ret |= VK_ACCESS_SHADER_WRITE_BIT;

		if ((accessFlags & ACCESS_COLOR_ATTACHMENT_READ) == ACCESS_COLOR_ATTACHMENT_READ)
			ret |= VK_ACCESS_COLOR_ATTACHMENT_READ_BIT;

		if ((accessFlags & ACCESS_COLOR_ATTACHMENT_WRITE) == ACCESS_COLOR_ATTACHMENT_WRITE)
			ret |= VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

		if ((accessFlags & ACCESS_DEPTH_STENCIL_READ) == ACCESS_DEPTH_STENCIL_READ)
			ret |= VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT;

		if ((accessFlags & ACCESS_DEPTH_STENCIL_WRITE) == ACCESS_DEPTH_STENCIL_WRITE)
			ret |= VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

		if ((accessFlags & ACCESS_TRANSFER_READ) == ACCESS_TRANSFER_READ)
			ret |= VK_ACCESS_TRANSFER_READ_BIT;

		if ((accessFlags & ACCESS_TRANSFER_WRITE) == ACCESS_TRANSFER_WRITE)
			ret |= VK_ACCESS_TRANSFER_WRITE_BIT;

		if ((accessFlags & ACCESS_HOST_READ) == ACCESS_HOST_READ)
			ret |= VK_ACCESS_HOST_READ_BIT;

		if ((accessFlags & ACCESS_HOST_WRITE) == ACCESS_HOST_WRITE)
			ret |= VK_ACCESS_HOST_WRITE_BIT;

		if ((accessFlags & ACCESS_MEMORY_READ) == ACCESS_MEMORY_READ)
			ret |= VK_ACCESS_MEMORY_READ_BIT;

		if ((accessFlags & ACCESS_MEMORY_WRITE) == ACCESS_MEMORY_WRITE)
			ret |= VK_ACCESS_MEMORY_WRITE_BIT;

		return ret;
	}

}