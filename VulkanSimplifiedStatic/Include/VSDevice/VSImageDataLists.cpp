#include "VSDeviceIpch.h"
#include "VSImageDataLists.h"

#include "../../DoNotInclude/VSDevice/VSImageDataListsInternal.h"

#include "../../Include/VSCommon/VSDataFormatFlags.h"
#include "../../Include/VSCommon/VSImageUsageFlags.h"

namespace VulkanSimplified
{
	ImageDataLists::ImageDataLists(VulkanSimplifiedInternal::ImageDataListsInternal& ref) : _internal(ref)
	{
	}

	ImageDataLists::~ImageDataLists()
	{
	}

	IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> ImageDataLists::AddColorRenderTargetImage(uint32_t width, uint32_t height, DataFormatSetIndependentID format,
		const std::vector<size_t>& queuesUsingImage, bool preInitialized, size_t initialImageViewListCapacity, size_t addOnReserving)
	{
		return _internal.AddColorRenderTargetImage(width, height, format, queuesUsingImage, preInitialized, initialImageViewListCapacity, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::AutoCleanup2DTexture> ImageDataLists::Add2DTextureImage(uint32_t width, uint32_t height, uint32_t mipLevel, DataFormatSetIndependentID format, const std::vector<size_t>& queuesUsingImage, bool preInitialized, size_t initialImageViewListCapacity, size_t addOnReserving)
	{
		return _internal.Add2DTextureImage(width, height, mipLevel, format, queuesUsingImage, preInitialized, initialImageViewListCapacity, addOnReserving);
	}

	bool ImageDataLists::RemoveColorRenderTargetImage(IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> imageID, bool throwOnIDNotFound)
	{
		return _internal.RemoveColorRenderTargetImage(imageID, throwOnIDNotFound);
	}

	bool ImageDataLists::Remove2DTextureImage(IDObject<VulkanSimplifiedInternal::AutoCleanup2DTexture> imageID, bool throwOnIDNotFound)
	{
		return _internal.Remove2DTextureImage(imageID, throwOnIDNotFound);
	}

	uint32_t ImageDataLists::GetColorRenderTargetImagesWidth(IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> imageID) const
	{
		return _internal.GetColorRenderTargetImagesWidth(imageID);
	}

	uint32_t ImageDataLists::GetColorRenderTargetImagesHeight(IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> imageID) const
	{
		return _internal.GetColorRenderTargetImagesHeight(imageID);
	}

	uint32_t ImageDataLists::GetColorRenderTargetImagesMemoryTypeMask(IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> imageID) const
	{
		return _internal.GetColorRenderTargetImagesMemoryTypeMask(imageID);
	}

	uint64_t ImageDataLists::GetColorRenderTargetImagesSize(IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> imageID) const
	{
		return _internal.GetColorRenderTargetImagesSize(imageID);
	}

	uint64_t ImageDataLists::GetColorRenderTargetImagesRequiredAligment(IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> imageID) const
	{
		return _internal.GetColorRenderTargetImagesRequiredAligment(imageID);
	}

	uint32_t ImageDataLists::Get2DTextureImagesWidth(IDObject<VulkanSimplifiedInternal::AutoCleanup2DTexture> imageID) const
	{
		return _internal.Get2DTextureImagesWidth(imageID);
	}

	uint32_t ImageDataLists::Get2DTextureImagesHeight(IDObject<VulkanSimplifiedInternal::AutoCleanup2DTexture> imageID) const
	{
		return _internal.Get2DTextureImagesHeight(imageID);
	}

	uint32_t ImageDataLists::Get2DTextureImagesMemoryTypeMask(IDObject<VulkanSimplifiedInternal::AutoCleanup2DTexture> imageID) const
	{
		return _internal.Get2DTextureImagesMemoryTypeMask(imageID);
	}

	VulkanSimplified::MemorySize ImageDataLists::Get2DTextureImagesSize(IDObject<VulkanSimplifiedInternal::AutoCleanup2DTexture> imageID) const
	{
		return _internal.Get2DTextureImagesSize(imageID);
	}

	VulkanSimplified::MemorySize ImageDataLists::Get2DTextureImagesRequiredAligment(IDObject<VulkanSimplifiedInternal::AutoCleanup2DTexture> imageID) const
	{
		return _internal.Get2DTextureImagesRequiredAligment(imageID);
	}

	void ImageDataLists::BindColorRenderTargetImage(IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> imageID, MemoryAllocationFullID allocationID,
		size_t addOnReserving)
	{
		_internal.BindColorRenderTargetImage(imageID, allocationID, addOnReserving);
	}

	void ImageDataLists::Bind2DTextureImage(IDObject<VulkanSimplifiedInternal::AutoCleanup2DTexture> imageID, MemoryAllocationFullID allocationID, size_t addOnReserving)
	{
		_internal.Bind2DTextureImage(imageID, allocationID, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::AutoCleanupImageView> ImageDataLists::AddColorRenderTargetImageView(IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> imageID,
		size_t addOnReserving)
	{
		return _internal.AddColorRenderTargetImageView(imageID, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::AutoCleanupImageView> ImageDataLists::Add2DTextureImageFullView(IDObject<VulkanSimplifiedInternal::AutoCleanup2DTexture> imageID,
		size_t addOnReserving)
	{
		return _internal.Add2DTextureImageFullView(imageID, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::AutoCleanupImageView> ImageDataLists::Add2DTextureImageSingleMipmapView(IDObject<VulkanSimplifiedInternal::AutoCleanup2DTexture> imageID,
		uint32_t mipmap, size_t addOnReserving)
	{
		return _internal.Add2DTextureImageSingleMipmapView(imageID, mipmap, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::AutoCleanupImageView> ImageDataLists::Add2DTextureImageRemainingMipmapsView(IDObject<VulkanSimplifiedInternal::AutoCleanup2DTexture> imageID,
		uint32_t startingMipmap, size_t addOnReserving)
	{
		return _internal.Add2DTextureImageRemainingMipmapsView(imageID, startingMipmap, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::AutoCleanupImageView> ImageDataLists::Add2DTextureImageSelectedMipmapsView(IDObject<VulkanSimplifiedInternal::AutoCleanup2DTexture> imageID,
		uint32_t startingMipmap, uint32_t mipmapCount, size_t addOnReserving)
	{
		return _internal.Add2DTextureImageSelectedMipmapsView(imageID, startingMipmap, mipmapCount, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::AutoCleanupFramebuffer> ImageDataLists::AddFramebuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupRenderPass> renderPass,
		const std::vector<std::pair<MultitypeImagesID, IDObject<VulkanSimplifiedInternal::AutoCleanupImageView>>>& attachmentsList, uint32_t width, uint32_t height, uint32_t layers,
		size_t addOnReserving)
	{
		return _internal.AddFramebuffer(renderPass, attachmentsList, width, height, layers, addOnReserving);
	}

	bool ImageDataLists::RemoveFramebuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupFramebuffer> framebufferID, bool throwOnIDNotFound)
	{
		return _internal.RemoveFramebuffer(framebufferID, throwOnIDNotFound);
	}

}