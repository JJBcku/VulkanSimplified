#pragma once

#include "CustomLists/UnsortedIDVector.h"

#include "../../Include/VSCommon/VSImageUsageFlagsDef.h"
#include "../../Include/VSCommon/VSMemorySuballocationFullID.h"
#include "../../Include/VSCommon/VSMemorySizeDef.h"

#include "../../Include/VSDevice/VSMultitypeImagesIDDef.h"

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

	class AutoCleanupRenderPass;

	class AutoCleanupImageView;
	class AutoCleanupColorRenderTargetImage;
	class AutoCleanupFramebuffer;

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

		AutoCleanupColorRenderTargetImage& GetColorRenderTargetImageInternal(IDObject<AutoCleanupColorRenderTargetImage> imageID);
		const  AutoCleanupColorRenderTargetImage& GetColorRenderTargetImageInternal(IDObject<AutoCleanupColorRenderTargetImage> imageID) const;

		VkImage GetColorRenderTargetImage(IDObject<AutoCleanupColorRenderTargetImage> imageID) const;
		VkImageView GetColorRenderTargetImageView(IDObject<AutoCleanupColorRenderTargetImage> imageID, IDObject<AutoCleanupImageView> viewID) const;

		uint32_t GetColorRenderTargetImagesWidth(IDObject<AutoCleanupColorRenderTargetImage> imageID) const;
		uint32_t GetColorRenderTargetImagesHeight(IDObject<AutoCleanupColorRenderTargetImage> imageID) const;

		uint32_t GetColorRenderTargetImagesMemoryTypeMask(IDObject<AutoCleanupColorRenderTargetImage> imageID) const;
		VulkanSimplified::MemorySize GetColorRenderTargetImagesSize(IDObject<AutoCleanupColorRenderTargetImage> imageID) const;
		VulkanSimplified::MemorySize GetColorRenderTargetImagesRequiredAligment(IDObject<AutoCleanupColorRenderTargetImage> imageID) const;

		void BindColorRenderTargetImage(IDObject<AutoCleanupColorRenderTargetImage> imageID, VulkanSimplified::MemoryAllocationFullID allocationID, size_t addOnReserving);

		IDObject<AutoCleanupImageView> AddColorRenderTargetImageView(IDObject<AutoCleanupColorRenderTargetImage> imageID, size_t addOnReserving);

		IDObject<AutoCleanupFramebuffer> AddFramebuffer(IDObject<AutoCleanupRenderPass> renderPass,
			const std::vector<std::pair<VulkanSimplified::MultitypeImagesID, IDObject<AutoCleanupImageView>>>& attachmentsList, uint32_t width, uint32_t height,
			uint32_t layers, size_t addOnReserving);

		bool RemoveFramebuffer(IDObject<AutoCleanupFramebuffer> framebufferID, bool throwOnIDNotFound);

		VkFramebuffer GetFramebuffer(IDObject<AutoCleanupFramebuffer> framebufferID) const;

	private:
		const DeviceCoreInternal& _deviceCore;
		const RenderPassListInternal& _renderPassData;
		MemoryObjectsListInternal& _memoryList;
		VkDevice _device;

		UnsortedIDVector<AutoCleanupColorRenderTargetImage> _colorRenderTargetList;

		UnsortedIDVector<AutoCleanupFramebuffer> _framebufferList;
	};
}