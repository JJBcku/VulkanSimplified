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
		ImageUsageFlags usageFlags, const std::vector<size_t>& queuesUsingImage, bool preInitialized, size_t initialImageViewListCapacity, size_t addOnReserving)
	{
		return _internal.AddColorRenderTargetImage(width, height, format, usageFlags, queuesUsingImage, preInitialized, initialImageViewListCapacity, addOnReserving);
	}

	bool ImageDataLists::RemoveColorRenderTargetImage(IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> imageID, bool throwOnIDNotFound)
	{
		return _internal.RemoveColorRenderTargetImage(imageID, throwOnIDNotFound);
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

	void ImageDataLists::BindColorRenderTargetImage(IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> imageID, MemoryAllocationFullID allocationID,
		size_t addOnReserving)
	{
		_internal.BindColorRenderTargetImage(imageID, allocationID, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::AutoCleanupImageView> ImageDataLists::AddColorRenderTargetImageView(IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> imageID,
		size_t addOnReserving)
	{
		return _internal.AddColorRenderTargetImageView(imageID, addOnReserving);
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