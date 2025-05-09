#pragma once

#include "../VSCommon/VSImageUsageFlagsDef.h"
#include "../VSCommon/VSMemorySuballocationFullID.h"
#include "../VSCommon/VSMemorySizeDef.h"

#include "VSImageDataListsDef.h"
#include "VSRenderPassDataListDef.h"
#include "VSMultitypeImagesIDDef.h"

namespace VulkanSimplifiedInternal
{
	class ImageDataListsInternal;
}

namespace VulkanSimplified
{
	struct DataFormatSetIndependentID;

	class ImageDataLists
	{
	public:
		ImageDataLists(VulkanSimplifiedInternal::ImageDataListsInternal& ref);
		~ImageDataLists();

		IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> AddColorRenderTargetImage(uint32_t width, uint32_t height, DataFormatSetIndependentID format,
			ImageUsageFlags usageFlags, const std::vector<size_t>& queuesUsingImage, bool preInitialized, size_t initialImageViewListCapacity, size_t addOnReserving = 0);

		bool RemoveColorRenderTargetImage(IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> imageID, bool throwOnIDNotFound);

		uint32_t GetColorRenderTargetImagesWidth(IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> imageID) const;
		uint32_t GetColorRenderTargetImagesHeight(IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> imageID) const;

		uint32_t GetColorRenderTargetImagesMemoryTypeMask(IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> imageID) const;
		VulkanSimplified::MemorySize GetColorRenderTargetImagesSize(IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> imageID) const;
		VulkanSimplified::MemorySize GetColorRenderTargetImagesRequiredAligment(IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> imageID) const;

		void BindColorRenderTargetImage(IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> imageID, MemoryAllocationFullID allocationID,
			size_t addOnReserving = 0);

		IDObject<VulkanSimplifiedInternal::AutoCleanupImageView> AddColorRenderTargetImageView(IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> imageID,
			size_t addOnReserving = 0);

		IDObject<VulkanSimplifiedInternal::AutoCleanupFramebuffer> AddFramebuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupRenderPass> renderPass,
			const std::vector<std::pair<MultitypeImagesID, IDObject<VulkanSimplifiedInternal::AutoCleanupImageView>>>& attachmentsList, uint32_t width, uint32_t height,
			uint32_t layers, size_t addOnReserving = 0);

		bool RemoveFramebuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupFramebuffer> framebufferID, bool throwOnIDNotFound = true);

	private:
		VulkanSimplifiedInternal::ImageDataListsInternal& _internal;
	};
}