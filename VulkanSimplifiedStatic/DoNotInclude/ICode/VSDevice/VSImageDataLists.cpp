#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSImageDataLists.h"

#include "../../../DoNotInclude/DNIHeaders/VSDevice/VSImageDataListsInternal.h"

#include "../../../Include/VSCommon/VSDataFormatFlags.h"
#include "../../../Include/VSCommon/VSImageUsageFlags.h"

namespace VulkanSimplified
{
	ImageDataLists::ImageDataLists(ImageDataListsInternal& ref) : _internal(ref)
	{
	}

	ImageDataLists::~ImageDataLists()
	{
	}

	IDObject<AutoCleanupColorRenderTargetImage> ImageDataLists::AddColorRenderTargetImage(uint32_t width, uint32_t height, DataFormatSetIndependentID format,
		ImageSampleFlagBits imageSamples, const std::vector<size_t>& queuesUsingImage, bool preInitialized, size_t initialImageViewListCapacity, size_t addOnReserving)
	{
		return _internal.AddColorRenderTargetImage(width, height, format, imageSamples, queuesUsingImage, preInitialized, initialImageViewListCapacity, addOnReserving);
	}

	IDObject<AutoCleanupDepthStencilRenderTargetImage> ImageDataLists::AddDepthStencilRenderTargetImage(uint32_t width, uint32_t height,
		DataFormatSetIndependentID format, ImageSampleFlagBits imageSamples, const std::vector<size_t>& queuesUsingImage,
		bool preInitialized, size_t initialImageViewListCapacity, size_t addOnReserving)
	{
		return _internal.AddDepthStencilRenderTargetImage(width, height, format, imageSamples, queuesUsingImage, preInitialized, initialImageViewListCapacity, addOnReserving);
	}

	IDObject<AutoCleanupResolveRenderTargetImage> ImageDataLists::AddResolveRenderTargetImage(uint32_t width, uint32_t height,
		DataFormatSetIndependentID format, const std::vector<size_t>& queuesUsingImage, bool preInitialized, size_t initialImageViewListCapacity, size_t addOnReserving)
	{
		return _internal.AddResolveRenderTargetImage(width, height, format, queuesUsingImage, preInitialized, initialImageViewListCapacity, addOnReserving);
	}

	IDObject<AutoCleanup2DTexture> ImageDataLists::Add2DTextureImage(uint32_t width, uint32_t height, uint32_t mipLevel, DataFormatSetIndependentID format, const std::vector<size_t>& queuesUsingImage, bool preInitialized, size_t initialImageViewListCapacity, size_t addOnReserving)
	{
		return _internal.Add2DTextureImage(width, height, mipLevel, format, queuesUsingImage, preInitialized, initialImageViewListCapacity, addOnReserving);
	}

	bool ImageDataLists::RemoveColorRenderTargetImage(IDObject<AutoCleanupColorRenderTargetImage> imageID, bool throwOnIDNotFound)
	{
		return _internal.RemoveColorRenderTargetImage(imageID, throwOnIDNotFound);
	}

	bool ImageDataLists::RemoveDepthStencilRenderTargetImage(IDObject<AutoCleanupDepthStencilRenderTargetImage> imageID, bool throwOnIDNotFound)
	{
		return _internal.RemoveDepthStencilRenderTargetImage(imageID, throwOnIDNotFound);
	}

	bool ImageDataLists::RemoveResolveRenderTargetImage(IDObject<AutoCleanupResolveRenderTargetImage> imageID, bool throwOnIDNotFound)
	{
		return _internal.RemoveResolveRenderTargetImage(imageID, throwOnIDNotFound);
	}

	bool ImageDataLists::Remove2DTextureImage(IDObject<AutoCleanup2DTexture> imageID, bool throwOnIDNotFound)
	{
		return _internal.Remove2DTextureImage(imageID, throwOnIDNotFound);
	}

	uint32_t ImageDataLists::GetColorRenderTargetImagesWidth(IDObject<AutoCleanupColorRenderTargetImage> imageID) const
	{
		return _internal.GetColorRenderTargetImagesWidth(imageID);
	}

	uint32_t ImageDataLists::GetColorRenderTargetImagesHeight(IDObject<AutoCleanupColorRenderTargetImage> imageID) const
	{
		return _internal.GetColorRenderTargetImagesHeight(imageID);
	}

	uint32_t ImageDataLists::GetColorRenderTargetImagesMemoryTypeMask(IDObject<AutoCleanupColorRenderTargetImage> imageID) const
	{
		return _internal.GetColorRenderTargetImagesMemoryTypeMask(imageID);
	}

	uint64_t ImageDataLists::GetColorRenderTargetImagesSize(IDObject<AutoCleanupColorRenderTargetImage> imageID) const
	{
		return _internal.GetColorRenderTargetImagesSize(imageID);
	}

	uint64_t ImageDataLists::GetColorRenderTargetImagesRequiredAligment(IDObject<AutoCleanupColorRenderTargetImage> imageID) const
	{
		return _internal.GetColorRenderTargetImagesRequiredAligment(imageID);
	}

	uint32_t ImageDataLists::GetDepthStencilRenderTargetImagesWidth(IDObject<AutoCleanupDepthStencilRenderTargetImage> imageID) const
	{
		return _internal.GetDepthStencilRenderTargetImagesWidth(imageID);
	}

	uint32_t ImageDataLists::GetDepthStencilRenderTargetImagesHeight(IDObject<AutoCleanupDepthStencilRenderTargetImage> imageID) const
	{
		return _internal.GetDepthStencilRenderTargetImagesHeight(imageID);
	}

	uint32_t ImageDataLists::GetDepthStencilRenderTargetImagesMemoryTypeMask(IDObject<AutoCleanupDepthStencilRenderTargetImage> imageID) const
	{
		return _internal.GetDepthStencilRenderTargetImagesMemoryTypeMask(imageID);
	}

	MemorySize ImageDataLists::GetDepthStencilRenderTargetImagesSize(IDObject<AutoCleanupDepthStencilRenderTargetImage> imageID) const
	{
		return _internal.GetDepthStencilRenderTargetImagesSize(imageID);
	}

	MemorySize ImageDataLists::GetDepthStencilRenderTargetImagesRequiredAligment(IDObject<AutoCleanupDepthStencilRenderTargetImage> imageID) const
	{
		return _internal.GetDepthStencilRenderTargetImagesRequiredAligment(imageID);
	}

	uint32_t ImageDataLists::GetResolveRenderTargetImagesWidth(IDObject<AutoCleanupResolveRenderTargetImage> imageID) const
	{
		return _internal.GetResolveRenderTargetImagesWidth(imageID);
	}

	uint32_t ImageDataLists::GetResolveRenderTargetImagesHeight(IDObject<AutoCleanupResolveRenderTargetImage> imageID) const
	{
		return _internal.GetResolveRenderTargetImagesHeight(imageID);
	}

	uint32_t ImageDataLists::GetResolveRenderTargetImagesMemoryTypeMask(IDObject<AutoCleanupResolveRenderTargetImage> imageID) const
	{
		return _internal.GetResolveRenderTargetImagesMemoryTypeMask(imageID);
	}

	MemorySize ImageDataLists::GetResolveRenderTargetImagesSize(IDObject<AutoCleanupResolveRenderTargetImage> imageID) const
	{
		return _internal.GetResolveRenderTargetImagesSize(imageID);
	}

	MemorySize ImageDataLists::GetResolveRenderTargetImagesRequiredAligment(IDObject<AutoCleanupResolveRenderTargetImage> imageID) const
	{
		return _internal.GetResolveRenderTargetImagesRequiredAligment(imageID);
	}

	uint32_t ImageDataLists::Get2DTextureImagesWidth(IDObject<AutoCleanup2DTexture> imageID) const
	{
		return _internal.Get2DTextureImagesWidth(imageID);
	}

	uint32_t ImageDataLists::Get2DTextureImagesHeight(IDObject<AutoCleanup2DTexture> imageID) const
	{
		return _internal.Get2DTextureImagesHeight(imageID);
	}

	uint32_t ImageDataLists::Get2DTextureImagesMemoryTypeMask(IDObject<AutoCleanup2DTexture> imageID) const
	{
		return _internal.Get2DTextureImagesMemoryTypeMask(imageID);
	}

	MemorySize ImageDataLists::Get2DTextureImagesSize(IDObject<AutoCleanup2DTexture> imageID) const
	{
		return _internal.Get2DTextureImagesSize(imageID);
	}

	MemorySize ImageDataLists::Get2DTextureImagesRequiredAligment(IDObject<AutoCleanup2DTexture> imageID) const
	{
		return _internal.Get2DTextureImagesRequiredAligment(imageID);
	}

	void ImageDataLists::BindColorRenderTargetImage(IDObject<AutoCleanupColorRenderTargetImage> imageID, MemoryAllocationFullID allocationID,
		size_t addOnReserving)
	{
		_internal.BindColorRenderTargetImage(imageID, allocationID, addOnReserving);
	}

	void ImageDataLists::BindDepthStencilRenderTargetImage(IDObject<AutoCleanupDepthStencilRenderTargetImage> imageID,
		MemoryAllocationFullID allocationID, size_t addOnReserving)
	{
		_internal.BindDepthStencilRenderTargetImage(imageID, allocationID, addOnReserving);
	}

	void ImageDataLists::BindResolveRenderTargetImage(IDObject<AutoCleanupResolveRenderTargetImage> imageID, MemoryAllocationFullID allocationID,
		size_t addOnReserving)
	{
		_internal.BindResolveRenderTargetImage(imageID, allocationID, addOnReserving);
	}

	void ImageDataLists::Bind2DTextureImage(IDObject<AutoCleanup2DTexture> imageID, MemoryAllocationFullID allocationID, size_t addOnReserving)
	{
		_internal.Bind2DTextureImage(imageID, allocationID, addOnReserving);
	}

	IDObject<AutoCleanupImageView> ImageDataLists::AddColorRenderTargetImageView(IDObject<AutoCleanupColorRenderTargetImage> imageID,
		size_t addOnReserving)
	{
		return _internal.AddColorRenderTargetImageView(imageID, addOnReserving);
	}

	IDObject<AutoCleanupImageView> ImageDataLists::AddDepthStencilRenderTargetImageView(
		IDObject<AutoCleanupDepthStencilRenderTargetImage> imageID, size_t addOnReserving)
	{
		return _internal.AddDepthStencilRenderTargetImageView(imageID, addOnReserving);
	}

	IDObject<AutoCleanupImageView> ImageDataLists::AddResolveRenderTargetImageView(
		IDObject<AutoCleanupResolveRenderTargetImage> imageID, size_t addOnReserving)
	{
		return _internal.AddResolveRenderTargetImageView(imageID, addOnReserving);
	}

	IDObject<AutoCleanupImageView> ImageDataLists::Add2DTextureImageFullView(IDObject<AutoCleanup2DTexture> imageID,
		size_t addOnReserving)
	{
		return _internal.Add2DTextureImageFullView(imageID, addOnReserving);
	}

	IDObject<AutoCleanupImageView> ImageDataLists::Add2DTextureImageSingleMipmapView(IDObject<AutoCleanup2DTexture> imageID,
		uint32_t mipmap, size_t addOnReserving)
	{
		return _internal.Add2DTextureImageSingleMipmapView(imageID, mipmap, addOnReserving);
	}

	IDObject<AutoCleanupImageView> ImageDataLists::Add2DTextureImageRemainingMipmapsView(IDObject<AutoCleanup2DTexture> imageID,
		uint32_t startingMipmap, size_t addOnReserving)
	{
		return _internal.Add2DTextureImageRemainingMipmapsView(imageID, startingMipmap, addOnReserving);
	}

	IDObject<AutoCleanupImageView> ImageDataLists::Add2DTextureImageSelectedMipmapsView(IDObject<AutoCleanup2DTexture> imageID,
		uint32_t startingMipmap, uint32_t mipmapCount, size_t addOnReserving)
	{
		return _internal.Add2DTextureImageSelectedMipmapsView(imageID, startingMipmap, mipmapCount, addOnReserving);
	}

	IDObject<AutoCleanupFramebuffer> ImageDataLists::AddFramebuffer(IDObject<AutoCleanupRenderPass> renderPass,
		const std::vector<std::pair<RenderTargetImagesID, IDObject<AutoCleanupImageView>>>& attachmentsList, uint32_t width, uint32_t height, uint32_t layers,
		size_t addOnReserving)
	{
		return _internal.AddFramebuffer(renderPass, attachmentsList, width, height, layers, addOnReserving);
	}

	IDObject<AutoCleanupSampler> ImageDataLists::AddSampler(bool magFilterLinear, bool minFilterLinear, bool mipmapLinear, bool addressXMirrored,
		bool addressYMirrored, bool addressZMirrored, float mipmapBias, float maxAnisotropy, float minLod, std::optional<float> maxLod, size_t addOnReserving)
	{
		return _internal.AddSampler(magFilterLinear, minFilterLinear, mipmapLinear, addressXMirrored, addressYMirrored, addressZMirrored, mipmapBias, maxAnisotropy,
			minLod, maxLod, addOnReserving);
	}

	bool ImageDataLists::RemoveFramebuffer(IDObject<AutoCleanupFramebuffer> framebufferID, bool throwOnIDNotFound)
	{
		return _internal.RemoveFramebuffer(framebufferID, throwOnIDNotFound);
	}

	bool ImageDataLists::RemoveSampler(IDObject<AutoCleanupSampler> samplerID, bool throwOnIDNotFound)
	{
		return _internal.RemoveSampler(samplerID, throwOnIDNotFound);
	}

}