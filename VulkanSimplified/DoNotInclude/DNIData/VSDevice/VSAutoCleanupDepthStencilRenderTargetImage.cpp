#include "VSDeviceDNIpch.h"
#include "VSAutoCleanupDepthStencilRenderTargetImage.h"

#include <Miscellaneous/Bool64.h>

namespace VulkanSimplified
{
	AutoCleanupDepthStencilRenderTargetImage::AutoCleanupDepthStencilRenderTargetImage(VkDevice device, VkImage image, uint32_t width, uint32_t height, VkFormat format,
		VkSampleCountFlagBits sampleCount, Misc::Bool64Values depthElement, Misc::Bool64Values stencilElement, size_t imageViewsInitialCapacity) :
		AutoCleanupImage(device, image, width, height, 1, 1, format, sampleCount, imageViewsInitialCapacity)
	{
		_depthElement = depthElement;
		_stencilElement = stencilElement;
	}

	AutoCleanupDepthStencilRenderTargetImage::~AutoCleanupDepthStencilRenderTargetImage()
	{
	}

	IDObject<AutoCleanupImageView> AutoCleanupDepthStencilRenderTargetImage::AddImageView(size_t addOnReserving)
	{
		VkImageSubresourceRange range{};
		range.aspectMask = 0;
		if (_depthElement == Misc::BOOL64_TRUE)
			range.aspectMask |= VK_IMAGE_ASPECT_DEPTH_BIT;

		if (_stencilElement == Misc::BOOL64_TRUE)
			range.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;

		range.baseMipLevel = 0;
		range.levelCount = 1;
		range.baseArrayLayer = 0;
		range.layerCount = 1;

		return AutoCleanupImage::AddImageView({}, range, VK_IMAGE_VIEW_TYPE_2D, addOnReserving);
	}

}