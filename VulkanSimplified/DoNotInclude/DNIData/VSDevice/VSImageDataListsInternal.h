#pragma once

#include "CustomLists/UnsortedIDVector.h"

#include "../../../Include/VSCommon/VSImageUsageFlagsDef.h"
#include "../../../Include/VSCommon/VSImageSampleFlagsDef.h"
#include "../../../Include/VSCommon/VSMemorySuballocationFullID.h"
#include "../../../Include/VSCommon/VSMemorySizeDef.h"

#include "../../../Include/VSDevice/VSMultitypeImagesIDDef.h"

#include "../../../Include/VSDevice/VSImageDataListsDef.h"

#include <Miscellaneous/Bool64Def.h>

#include <vulkan/vulkan_core.h>
#include <stdint.h>
#include <vector>
#include <optional>

typedef struct VkDevice_T* VkDevice;
typedef struct VkImage_T* VkImage;
typedef struct VkImageView_T* VkImageView;
typedef struct VkFramebuffer_T* VkFramebuffer;
typedef struct VkSampler_T* VkSampler;

namespace VulkanSimplified
{
	struct DataFormatSetIndependentID;
	struct ImageDataListsInitialCapacities;
}

namespace VulkanSimplified
{
	class DeviceCoreInternal;
	class RenderPassListInternal;
	class MemoryObjectsListInternal;

	class AutoCleanupRenderPass;

	class ImageDataListsInternal
	{
	public:
		ImageDataListsInternal(const DeviceCoreInternal& deviceCore, const RenderPassListInternal& renderPassData, MemoryObjectsListInternal& memoryList, VkDevice device,
			const ImageDataListsInitialCapacities& initialCapacities);
		~ImageDataListsInternal();

		ImageDataListsInternal& operator=(const ImageDataListsInternal&) noexcept = delete;

		IDObject<AutoCleanupColorRenderTargetImage> AddColorRenderTargetImage(uint32_t width, uint32_t height, DataFormatSetIndependentID format,
			ImageSampleFlagBits imageSamples, const std::vector<size_t>& queuesUsingImage, bool preInitialized, bool transient, size_t initialImageViewListCapacity,
			size_t addOnReserving);
		IDObject<AutoCleanupDepthStencilRenderTargetImage> AddDepthStencilRenderTargetImage(uint32_t width, uint32_t height, DataFormatSetIndependentID format,
			ImageSampleFlagBits imageSamples, const std::vector<size_t>& queuesUsingImage, bool preInitialized, bool transient, size_t initialImageViewListCapacity,
			size_t addOnReserving);
		IDObject<AutoCleanupResolveRenderTargetImage> AddResolveRenderTargetImage(uint32_t width, uint32_t height, DataFormatSetIndependentID format,
			const std::vector<size_t>& queuesUsingImage, bool preInitialized, bool transient, size_t initialImageViewListCapacity, size_t addOnReserving);

		IDObject<AutoCleanup2DTexture> Add2DTextureImage(uint32_t width, uint32_t height, uint32_t mipLevel, DataFormatSetIndependentID format,
			const std::vector<size_t>& queuesUsingImage, bool preInitialized, size_t initialImageViewListCapacity, size_t addOnReserving);
		IDObject<AutoCleanup2DArrayTexture> Add2DArrayTextureImage(uint32_t width, uint32_t height, uint32_t layerCount, uint32_t mipLevel, DataFormatSetIndependentID format,
			const std::vector<size_t>& queuesUsingImage, bool preInitialized, size_t initialImageViewListCapacity, size_t addOnReserving);

		bool RemoveColorRenderTargetImage(IDObject<AutoCleanupColorRenderTargetImage> imageID, bool throwOnIDNotFound);
		bool RemoveDepthStencilRenderTargetImage(IDObject<AutoCleanupDepthStencilRenderTargetImage> imageID, bool throwOnIDNotFound);
		bool RemoveResolveRenderTargetImage(IDObject<AutoCleanupResolveRenderTargetImage> imageID, bool throwOnIDNotFound);

		bool Remove2DTextureImage(IDObject<AutoCleanup2DTexture> imageID, bool throwOnIDNotFound);
		bool Remove2DArrayTextureImage(IDObject<AutoCleanup2DArrayTexture> imageID, bool throwOnIDNotFound);

		AutoCleanupColorRenderTargetImage& GetColorRenderTargetImageInternal(IDObject<AutoCleanupColorRenderTargetImage> imageID);
		const AutoCleanupColorRenderTargetImage& GetColorRenderTargetImageInternal(IDObject<AutoCleanupColorRenderTargetImage> imageID) const;

		AutoCleanupDepthStencilRenderTargetImage& GetDepthStencilRenderTargetImageInternal(IDObject<AutoCleanupDepthStencilRenderTargetImage> imageID);
		const AutoCleanupDepthStencilRenderTargetImage& GetDepthStencilRenderTargetImageInternal(IDObject<AutoCleanupDepthStencilRenderTargetImage> imageID) const;

		AutoCleanupResolveRenderTargetImage& GetResolveRenderTargetImageInternal(IDObject<AutoCleanupResolveRenderTargetImage> imageID);
		const AutoCleanupResolveRenderTargetImage& GetResolveRenderTargetImageInternal(IDObject<AutoCleanupResolveRenderTargetImage> imageID) const;

		AutoCleanup2DTexture& Get2DTextureImageInternal(IDObject<AutoCleanup2DTexture> imageID);
		const AutoCleanup2DTexture& Get2DTextureImageInternal(IDObject<AutoCleanup2DTexture> imageID) const;

		AutoCleanup2DArrayTexture& Get2DArrayTextureImageInternal(IDObject<AutoCleanup2DArrayTexture> imageID);
		const AutoCleanup2DArrayTexture& Get2DArrayTextureImageInternal(IDObject<AutoCleanup2DArrayTexture> imageID) const;

		VkImage GetColorRenderTargetImage(IDObject<AutoCleanupColorRenderTargetImage> imageID) const;
		VkImageView GetColorRenderTargetImageView(IDObject<AutoCleanupColorRenderTargetImage> imageID, IDObject<AutoCleanupImageView> viewID) const;

		VkImage GetDepthStencilRenderTargetImage(IDObject<AutoCleanupDepthStencilRenderTargetImage> imageID) const;
		VkImageView GetDepthStencilRenderTargetImageView(IDObject<AutoCleanupDepthStencilRenderTargetImage> imageID, IDObject<AutoCleanupImageView> viewID) const;

		VkImage GetResolveRenderTargetImage(IDObject<AutoCleanupResolveRenderTargetImage> imageID) const;
		VkImageView GetResolveRenderTargetImageView(IDObject<AutoCleanupResolveRenderTargetImage> imageID, IDObject<AutoCleanupImageView> viewID) const;

		VkImage Get2DTextureImage(IDObject<AutoCleanup2DTexture> imageID) const;
		VkImageView Get2DTextureImageView(IDObject<AutoCleanup2DTexture> imageID, IDObject<AutoCleanupImageView> viewID) const;

		VkImage Get2DArrayTextureImage(IDObject<AutoCleanup2DArrayTexture> imageID) const;
		VkImageView Get2DArrayTextureImageView(IDObject<AutoCleanup2DArrayTexture> imageID, IDObject<AutoCleanupImageView> viewID) const;

		uint32_t GetColorRenderTargetImagesWidth(IDObject<AutoCleanupColorRenderTargetImage> imageID) const;
		uint32_t GetColorRenderTargetImagesHeight(IDObject<AutoCleanupColorRenderTargetImage> imageID) const;

		uint32_t GetColorRenderTargetImagesMemoryTypeMask(IDObject<AutoCleanupColorRenderTargetImage> imageID) const;
		MemorySize GetColorRenderTargetImagesSize(IDObject<AutoCleanupColorRenderTargetImage> imageID) const;
		MemorySize GetColorRenderTargetImagesRequiredAligment(IDObject<AutoCleanupColorRenderTargetImage> imageID) const;

		uint32_t GetDepthStencilRenderTargetImagesWidth(IDObject<AutoCleanupDepthStencilRenderTargetImage> imageID) const;
		uint32_t GetDepthStencilRenderTargetImagesHeight(IDObject<AutoCleanupDepthStencilRenderTargetImage> imageID) const;

		uint32_t GetDepthStencilRenderTargetImagesMemoryTypeMask(IDObject<AutoCleanupDepthStencilRenderTargetImage> imageID) const;
		MemorySize GetDepthStencilRenderTargetImagesSize(IDObject<AutoCleanupDepthStencilRenderTargetImage> imageID) const;
		MemorySize GetDepthStencilRenderTargetImagesRequiredAligment(IDObject<AutoCleanupDepthStencilRenderTargetImage> imageID) const;

		VkSampleCountFlagBits GetDepthStencilRenderTargetSampleCount(IDObject<AutoCleanupDepthStencilRenderTargetImage> imageID) const;

		uint32_t GetResolveRenderTargetImagesWidth(IDObject<AutoCleanupResolveRenderTargetImage> imageID) const;
		uint32_t GetResolveRenderTargetImagesHeight(IDObject<AutoCleanupResolveRenderTargetImage> imageID) const;

		uint32_t GetResolveRenderTargetImagesMemoryTypeMask(IDObject<AutoCleanupResolveRenderTargetImage> imageID) const;
		MemorySize GetResolveRenderTargetImagesSize(IDObject<AutoCleanupResolveRenderTargetImage> imageID) const;
		MemorySize GetResolveRenderTargetImagesRequiredAligment(IDObject<AutoCleanupResolveRenderTargetImage> imageID) const;

		uint32_t Get2DTextureImagesWidth(IDObject<AutoCleanup2DTexture> imageID) const;
		uint32_t Get2DTextureImagesHeight(IDObject<AutoCleanup2DTexture> imageID) const;

		uint32_t Get2DTextureImagesMemoryTypeMask(IDObject<AutoCleanup2DTexture> imageID) const;
		MemorySize Get2DTextureImagesSize(IDObject<AutoCleanup2DTexture> imageID) const;
		MemorySize Get2DTextureImagesRequiredAligment(IDObject<AutoCleanup2DTexture> imageID) const;

		uint32_t Get2DArrayTextureImagesWidth(IDObject<AutoCleanup2DArrayTexture> imageID) const;
		uint32_t Get2DArrayTextureImagesHeight(IDObject<AutoCleanup2DArrayTexture> imageID) const;

		uint32_t Get2DArrayTextureImagesMemoryTypeMask(IDObject<AutoCleanup2DArrayTexture> imageID) const;
		MemorySize Get2DArrayTextureImagesSize(IDObject<AutoCleanup2DArrayTexture> imageID) const;
		MemorySize Get2DArrayTextureImagesRequiredAligment(IDObject<AutoCleanup2DArrayTexture> imageID) const;

		void BindColorRenderTargetImage(IDObject<AutoCleanupColorRenderTargetImage> imageID, MemoryAllocationFullID allocationID, size_t addOnReserving);
		void BindDepthStencilRenderTargetImage(IDObject<AutoCleanupDepthStencilRenderTargetImage> imageID, MemoryAllocationFullID allocationID, size_t addOnReserving);
		void BindResolveRenderTargetImage(IDObject<AutoCleanupResolveRenderTargetImage> imageID, MemoryAllocationFullID allocationID, size_t addOnReserving);

		void Bind2DTextureImage(IDObject<AutoCleanup2DTexture> imageID, MemoryAllocationFullID allocationID, size_t addOnReserving);
		void Bind2DArrayTextureImage(IDObject<AutoCleanup2DArrayTexture> imageID, MemoryAllocationFullID allocationID, size_t addOnReserving);

		IDObject<AutoCleanupImageView> AddColorRenderTargetImageView(IDObject<AutoCleanupColorRenderTargetImage> imageID, size_t addOnReserving);
		IDObject<AutoCleanupImageView> AddDepthStencilRenderTargetImageView(IDObject<AutoCleanupDepthStencilRenderTargetImage> imageID, size_t addOnReserving);
		IDObject<AutoCleanupImageView> AddResolveRenderTargetImageView(IDObject<AutoCleanupResolveRenderTargetImage> imageID, size_t addOnReserving);

		IDObject<AutoCleanupImageView> Add2DTextureImageFullView(IDObject<AutoCleanup2DTexture> imageID, size_t addOnReserving);
		IDObject<AutoCleanupImageView> Add2DTextureImageSelectedMipmapsView(IDObject<AutoCleanup2DTexture> imageID, uint32_t startingMipmap, std::optional<uint32_t> mipmapCount,
			size_t addOnReserving);

		IDObject<AutoCleanupImageView> Add2DArrayTextureImageFullView(IDObject<AutoCleanup2DArrayTexture> imageID, size_t addOnReserving);
		IDObject<AutoCleanupImageView> Add2DArrayTextureImageSelectedLayersAndMipmapsImageView(IDObject<AutoCleanup2DArrayTexture> imageID,
			uint32_t startingMipmap, std::optional<uint32_t> usedMipmapCount, uint32_t startingLayer, std::optional<uint32_t> usedLayerCount, size_t addOnReserving);

		IDObject<AutoCleanupFramebuffer> AddFramebuffer(IDObject<AutoCleanupRenderPass> renderPass,
			const std::vector<std::pair<RenderTargetImagesID, IDObject<AutoCleanupImageView>>>& attachmentsList, uint32_t width, uint32_t height,
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
		UnsortedIDVector<AutoCleanupDepthStencilRenderTargetImage> _depthStencilRenderTargetList;
		UnsortedIDVector<AutoCleanupResolveRenderTargetImage> _resolveRenderTargetList;
		UnsortedIDVector<AutoCleanup2DTexture> _2dTexturesList;
		UnsortedIDVector<AutoCleanup2DArrayTexture> _2dArrayTexturesList;

		UnsortedIDVector<AutoCleanupFramebuffer> _framebufferList;
		UnsortedIDVector<AutoCleanupSampler> _samplerList;

		Misc::Bool64Values FormatHasDepthANDStencilComponents(DataFormatSetIndependentID format) const;
		Misc::Bool64Values FormatHasDepthORStencilComponents(DataFormatSetIndependentID format) const;
		Misc::Bool64Values FormatHasDepthComponent(DataFormatSetIndependentID format) const;
		Misc::Bool64Values FormatHasStencilComponent(DataFormatSetIndependentID format) const;
	};
}