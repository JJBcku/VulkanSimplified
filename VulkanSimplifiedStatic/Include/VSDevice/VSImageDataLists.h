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
			const std::vector<size_t>& queuesUsingImage, bool preInitialized, size_t initialImageViewListCapacity, size_t addOnReserving = 0);
		IDObject<VulkanSimplifiedInternal::AutoCleanup2DTexture> Add2DTextureImage(uint32_t width, uint32_t height, uint32_t mipLevel, DataFormatSetIndependentID format,
			const std::vector<size_t>& queuesUsingImage, bool preInitialized, size_t initialImageViewListCapacity, size_t addOnReserving = 0);

		bool RemoveColorRenderTargetImage(IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> imageID, bool throwOnIDNotFound);
		bool Remove2DTextureImage(IDObject<VulkanSimplifiedInternal::AutoCleanup2DTexture> imageID, bool throwOnIDNotFound);

		uint32_t GetColorRenderTargetImagesWidth(IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> imageID) const;
		uint32_t GetColorRenderTargetImagesHeight(IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> imageID) const;

		uint32_t GetColorRenderTargetImagesMemoryTypeMask(IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> imageID) const;
		VulkanSimplified::MemorySize GetColorRenderTargetImagesSize(IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> imageID) const;
		VulkanSimplified::MemorySize GetColorRenderTargetImagesRequiredAligment(IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> imageID) const;

		uint32_t Get2DTextureImagesWidth(IDObject<VulkanSimplifiedInternal::AutoCleanup2DTexture> imageID) const;
		uint32_t Get2DTextureImagesHeight(IDObject<VulkanSimplifiedInternal::AutoCleanup2DTexture> imageID) const;

		uint32_t Get2DTextureImagesMemoryTypeMask(IDObject<VulkanSimplifiedInternal::AutoCleanup2DTexture> imageID) const;
		VulkanSimplified::MemorySize Get2DTextureImagesSize(IDObject<VulkanSimplifiedInternal::AutoCleanup2DTexture> imageID) const;
		VulkanSimplified::MemorySize Get2DTextureImagesRequiredAligment(IDObject<VulkanSimplifiedInternal::AutoCleanup2DTexture> imageID) const;

		void BindColorRenderTargetImage(IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> imageID, MemoryAllocationFullID allocationID,
			size_t addOnReserving = 0);
		void Bind2DTextureImage(IDObject<VulkanSimplifiedInternal::AutoCleanup2DTexture> imageID, MemoryAllocationFullID allocationID, size_t addOnReserving = 0);

		IDObject<VulkanSimplifiedInternal::AutoCleanupImageView> AddColorRenderTargetImageView(IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> imageID,
			size_t addOnReserving = 0);

		IDObject<VulkanSimplifiedInternal::AutoCleanupImageView> Add2DTextureImageFullView(IDObject<VulkanSimplifiedInternal::AutoCleanup2DTexture> imageID, size_t addOnReserving = 0);
		IDObject<VulkanSimplifiedInternal::AutoCleanupImageView> Add2DTextureImageSingleMipmapView(IDObject<VulkanSimplifiedInternal::AutoCleanup2DTexture> imageID, uint32_t mipmap,
			size_t addOnReserving = 0);
		IDObject<VulkanSimplifiedInternal::AutoCleanupImageView> Add2DTextureImageRemainingMipmapsView(IDObject<VulkanSimplifiedInternal::AutoCleanup2DTexture> imageID,
			uint32_t startingMipmap, size_t addOnReserving = 0);
		IDObject<VulkanSimplifiedInternal::AutoCleanupImageView> Add2DTextureImageSelectedMipmapsView(IDObject<VulkanSimplifiedInternal::AutoCleanup2DTexture> imageID,
			uint32_t startingMipmap, uint32_t mipmapCount, size_t addOnReserving = 0);

		IDObject<VulkanSimplifiedInternal::AutoCleanupFramebuffer> AddFramebuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupRenderPass> renderPass,
			const std::vector<std::pair<MultitypeImagesID, IDObject<VulkanSimplifiedInternal::AutoCleanupImageView>>>& attachmentsList, uint32_t width, uint32_t height,
			uint32_t layers, size_t addOnReserving = 0);
		IDObject<VulkanSimplifiedInternal::AutoCleanupSampler> AddSampler(bool magFilterLinear, bool minFilterLinear, bool mipmapLinear, bool addressXMirrored, bool addressYMirrored,
			bool addressZMirrored, float mipmapBias, float maxAnisotropy, float minLod, std::optional<float> maxLod, size_t addOnReserving = 0);

		bool RemoveFramebuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupFramebuffer> framebufferID, bool throwOnIDNotFound = true);
		bool RemoveSampler(IDObject<VulkanSimplifiedInternal::AutoCleanupSampler> samplerID, bool throwOnIDNotFound = false);

	private:
		VulkanSimplifiedInternal::ImageDataListsInternal& _internal;
	};
}