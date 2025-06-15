#pragma once

#include "CustomLists/UnsortedIDVector.h"

#include "../../Include/VSCommon/VSImageUsageFlagsDef.h"
#include "../../Include/VSCommon/VSMemorySuballocationFullID.h"
#include "../../Include/VSCommon/VSMemorySizeDef.h"

#include "../../Include/VSDevice/VSMultitypeImagesIDDef.h"

#include "../../Include/VSDevice/VSImageDataListsDef.h"

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

	class ImageDataListsInternal
	{
	public:
		ImageDataListsInternal(const DeviceCoreInternal& deviceCore, const RenderPassListInternal& renderPassData, MemoryObjectsListInternal& memoryList, VkDevice device,
			const VulkanSimplified::ImageDataListsInitialCapacities& initialCapacities);
		~ImageDataListsInternal();

		ImageDataListsInternal& operator=(const ImageDataListsInternal&) noexcept = delete;

		IDObject<AutoCleanupColorRenderTargetImage> AddColorRenderTargetImage(uint32_t width, uint32_t height, VulkanSimplified::DataFormatSetIndependentID format,
			const std::vector<size_t>& queuesUsingImage, bool preInitialized, size_t initialImageViewListCapacity, size_t addOnReserving);
		IDObject<AutoCleanup2DTexture> Add2DTextureImage(uint32_t width, uint32_t height, uint32_t mipLevel, VulkanSimplified::DataFormatSetIndependentID format,
			const std::vector<size_t>& queuesUsingImage, bool preInitialized, size_t initialImageViewListCapacity, size_t addOnReserving);

		bool RemoveColorRenderTargetImage(IDObject<AutoCleanupColorRenderTargetImage> imageID, bool throwOnIDNotFound);
		bool Remove2DTextureImage(IDObject<AutoCleanup2DTexture> imageID, bool throwOnIDNotFound);

		AutoCleanupColorRenderTargetImage& GetColorRenderTargetImageInternal(IDObject<AutoCleanupColorRenderTargetImage> imageID);
		const AutoCleanupColorRenderTargetImage& GetColorRenderTargetImageInternal(IDObject<AutoCleanupColorRenderTargetImage> imageID) const;

		AutoCleanup2DTexture& Get2DTextureImageInternal(IDObject<AutoCleanup2DTexture> imageID);
		const AutoCleanup2DTexture& Get2DTextureImageInternal(IDObject<AutoCleanup2DTexture> imageID) const;

		VkImage GetColorRenderTargetImage(IDObject<AutoCleanupColorRenderTargetImage> imageID) const;
		VkImageView GetColorRenderTargetImageView(IDObject<AutoCleanupColorRenderTargetImage> imageID, IDObject<AutoCleanupImageView> viewID) const;

		VkImage Get2DTextureImage(IDObject<AutoCleanup2DTexture> imageID) const;
		VkImageView Get2DTextureImageImageView(IDObject<AutoCleanup2DTexture> imageID, IDObject<AutoCleanupImageView> viewID) const;

		uint32_t GetColorRenderTargetImagesWidth(IDObject<AutoCleanupColorRenderTargetImage> imageID) const;
		uint32_t GetColorRenderTargetImagesHeight(IDObject<AutoCleanupColorRenderTargetImage> imageID) const;

		uint32_t GetColorRenderTargetImagesMemoryTypeMask(IDObject<AutoCleanupColorRenderTargetImage> imageID) const;
		VulkanSimplified::MemorySize GetColorRenderTargetImagesSize(IDObject<AutoCleanupColorRenderTargetImage> imageID) const;
		VulkanSimplified::MemorySize GetColorRenderTargetImagesRequiredAligment(IDObject<AutoCleanupColorRenderTargetImage> imageID) const;

		uint32_t Get2DTextureImagesWidth(IDObject<AutoCleanup2DTexture> imageID) const;
		uint32_t Get2DTextureImagesHeight(IDObject<AutoCleanup2DTexture> imageID) const;

		uint32_t Get2DTextureImagesMemoryTypeMask(IDObject<AutoCleanup2DTexture> imageID) const;
		VulkanSimplified::MemorySize Get2DTextureImagesSize(IDObject<AutoCleanup2DTexture> imageID) const;
		VulkanSimplified::MemorySize Get2DTextureImagesRequiredAligment(IDObject<AutoCleanup2DTexture> imageID) const;

		void BindColorRenderTargetImage(IDObject<AutoCleanupColorRenderTargetImage> imageID, VulkanSimplified::MemoryAllocationFullID allocationID, size_t addOnReserving);
		void Bind2DTextureImage(IDObject<AutoCleanup2DTexture> imageID, VulkanSimplified::MemoryAllocationFullID allocationID, size_t addOnReserving);

		IDObject<AutoCleanupImageView> AddColorRenderTargetImageView(IDObject<AutoCleanupColorRenderTargetImage> imageID, size_t addOnReserving);

		IDObject<AutoCleanupImageView> Add2DTextureImageFullView(IDObject<AutoCleanup2DTexture> imageID, size_t addOnReserving);
		IDObject<AutoCleanupImageView> Add2DTextureImageSingleMipmapView(IDObject<AutoCleanup2DTexture> imageID, uint32_t mipmap, size_t addOnReserving);
		IDObject<AutoCleanupImageView> Add2DTextureImageRemainingMipmapsView(IDObject<AutoCleanup2DTexture> imageID, uint32_t startingMipmap, size_t addOnReserving);
		IDObject<AutoCleanupImageView> Add2DTextureImageSelectedMipmapsView(IDObject<AutoCleanup2DTexture> imageID, uint32_t startingMipmap, uint32_t mipmapCount,
			size_t addOnReserving);

		IDObject<AutoCleanupFramebuffer> AddFramebuffer(IDObject<AutoCleanupRenderPass> renderPass,
			const std::vector<std::pair<VulkanSimplified::MultitypeImagesID, IDObject<AutoCleanupImageView>>>& attachmentsList, uint32_t width, uint32_t height,
			uint32_t layers, size_t addOnReserving);
		IDObject<AutoCleanupSampler> AddSampler(bool magFilterLinear, bool minFilterLinear, bool mipmapLinear, bool addressXMirrored, bool addressYMirrored, bool addressZMirrored,
			float mipmapBias, float maxAnisotropy, float minLod, const std::optional<float>& maxLod, size_t addOnReserving);

		bool RemoveFramebuffer(IDObject<AutoCleanupFramebuffer> framebufferID, bool throwOnIDNotFound);
		bool RemoveSampler(IDObject<AutoCleanupSampler> samplerID, bool throwOnIDNotFound);

		VkFramebuffer GetFramebuffer(IDObject<AutoCleanupFramebuffer> framebufferID) const;
		VkSampler GetSampler(IDObject<AutoCleanupSampler> samplerID) const;
		std::vector<VkSampler> GetSamplerList(std::vector<IDObject<AutoCleanupSampler>> samplerIDs) const;

	private:
		const DeviceCoreInternal& _deviceCore;
		const RenderPassListInternal& _renderPassData;
		MemoryObjectsListInternal& _memoryList;
		VkDevice _device;

		UnsortedIDVector<AutoCleanupColorRenderTargetImage> _colorRenderTargetList;
		UnsortedIDVector<AutoCleanup2DTexture> _2dTexturesList;

		UnsortedIDVector<AutoCleanupFramebuffer> _framebufferList;
		UnsortedIDVector<AutoCleanupSampler> _samplerList;
	};
}