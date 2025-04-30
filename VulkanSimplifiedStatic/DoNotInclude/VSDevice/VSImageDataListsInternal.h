#pragma once

#include "CustomLists/UnsortedIDVector.h"

#include "../../Include/VSCommon/VSImageUsageFlagsDef.h"
#include "../../Include/VSCommon/VSMemorySuballocationFullID.h"

namespace VulkanSimplified
{
	struct DataFormatSetIndependentID;
	struct ImageDataListsInitialCapacities;
}

namespace VulkanSimplifiedInternal
{
	class DeviceCoreInternal;
	class RenderPassListInternal;
	class MemoryObjectsListInternal;

	class AutoCleanupImageView;
	class AutoCleanupColorRenderTargetImage;

	class ImageDataListsInternal
	{
	public:
		ImageDataListsInternal(const DeviceCoreInternal& deviceCore, const RenderPassListInternal& renderPassData, MemoryObjectsListInternal& memoryList, VkDevice device,
			const VulkanSimplified::ImageDataListsInitialCapacities& initialCapacities);
		~ImageDataListsInternal();

		ImageDataListsInternal& operator=(const ImageDataListsInternal&) noexcept = delete;

		IDObject<AutoCleanupColorRenderTargetImage> AddColorRenderTargetImage(uint32_t width, uint32_t height, VulkanSimplified::DataFormatSetIndependentID format,
			VulkanSimplified::ImageUsageFlags usageFlags, const std::vector<size_t>& queuesUsingImage, bool preInitialized, size_t initialImageViewListCapacity, size_t addOnReserving);

		bool RemoveColorRenderTargetImage(IDObject<AutoCleanupColorRenderTargetImage> imageID, bool throwOnIDNotFound);

		VkImage GetImage(IDObject<AutoCleanupColorRenderTargetImage> imageID) const;
		VkImageView GetImageView(IDObject<AutoCleanupColorRenderTargetImage> imageID, IDObject<AutoCleanupImageView> viewID) const;

		uint32_t GetColorRenderTargetImageWidth(IDObject<AutoCleanupColorRenderTargetImage> imageID) const;
		uint32_t GetColorRenderTargetImageHeight(IDObject<AutoCleanupColorRenderTargetImage> imageID) const;

		uint32_t GetColorRenderTargetImageMemoryTypeMask(IDObject<AutoCleanupColorRenderTargetImage> imageID) const;
		uint64_t GetColorRenderTargetImageSize(IDObject<AutoCleanupColorRenderTargetImage> imageID) const;
		uint64_t GetColorRenderTargetImageRequiredAligment(IDObject<AutoCleanupColorRenderTargetImage> imageID) const;

		void BindColorRenderTargetImage(IDObject<AutoCleanupColorRenderTargetImage> imageID, VulkanSimplified::MemoryAllocationFullID allocationID, size_t addOnReserving);

		IDObject<AutoCleanupImageView> AddColorRenderTargetImageView(IDObject<AutoCleanupColorRenderTargetImage> imageID, size_t addOnReserving);

	private:
		const DeviceCoreInternal& _deviceCore;
		const RenderPassListInternal& _renderPassData;
		MemoryObjectsListInternal& _memoryList;
		VkDevice _device;

		UnsortedIDVector<AutoCleanupColorRenderTargetImage> _colorRenderTargets;
	};
}