#pragma once

#include "../../Include/VSCommon/VSImageUsageFlagsDef.h"
#include "../../Include/VSCommon/VSMemorySuballocationFullID.h"

#include "VSImageDataListsDef.h"

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

		uint32_t GetColorRenderTargetImageWidth(IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> imageID) const;
		uint32_t GetColorRenderTargetImageHeight(IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> imageID) const;

		uint32_t GetColorRenderTargetImageMemoryTypeMask(IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> imageID) const;
		uint64_t GetColorRenderTargetImageSize(IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> imageID) const;
		uint64_t GetColorRenderTargetImageRequiredAligment(IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> imageID) const;

		void BindColorRenderTargetImage(IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> imageID, MemoryAllocationFullID allocationID,
			size_t addOnReserving = 0);

		IDObject<VulkanSimplifiedInternal::AutoCleanupImageView> AddColorRenderTargetImageView(IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> imageID,
			size_t addOnReserving = 0);

	private:
		VulkanSimplifiedInternal::ImageDataListsInternal& _internal;
	};
}