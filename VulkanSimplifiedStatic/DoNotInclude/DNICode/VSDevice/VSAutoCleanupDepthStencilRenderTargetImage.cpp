#include "VSDeviceNIpch.h"
#include "../../DNIHeaders/VSDevice/VSAutoCleanupDepthStencilRenderTargetImage.h"

namespace VulkanSimplifiedInternal
{
	AutoCleanupDepthStencilRenderTargetImage::AutoCleanupDepthStencilRenderTargetImage(VkDevice device, VkImage image, uint32_t width, uint32_t height, VkFormat format,
		VkSampleCountFlagBits sampleCount, size_t imageViewsInitialCapacity) : AutoCleanupImage(device, image, width, height, 1, 1, format, sampleCount, imageViewsInitialCapacity)
	{
	}

	AutoCleanupDepthStencilRenderTargetImage::~AutoCleanupDepthStencilRenderTargetImage()
	{
	}

	IDObject<AutoCleanupImageView> AutoCleanupDepthStencilRenderTargetImage::AddImageView(size_t addOnReserving)
	{
		VkImageSubresourceRange range{};
		range.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;
		range.baseMipLevel = 0;
		range.levelCount = 1;
		range.baseArrayLayer = 0;
		range.layerCount = 1;

		return AutoCleanupImage::AddImageView({}, range, VK_IMAGE_VIEW_TYPE_2D, addOnReserving);
	}

}