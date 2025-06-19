#include "VSDeviceNIpch.h"
#include "../../DNIHeaders/VSDevice/VSAutoCleanupResolveRenderTargetImage.h"

namespace VulkanSimplifiedInternal
{
	AutoCleanupResolveRenderTargetImage::AutoCleanupResolveRenderTargetImage(VkDevice device, VkImage image, uint32_t width, uint32_t height, VkFormat format,
		size_t imageViewsInitialCapacity) : AutoCleanupImage(device, image, width, height, 1, 1, format, VK_SAMPLE_COUNT_1_BIT, imageViewsInitialCapacity)
	{
	}

	AutoCleanupResolveRenderTargetImage::~AutoCleanupResolveRenderTargetImage()
	{
	}

	IDObject<AutoCleanupImageView> AutoCleanupResolveRenderTargetImage::AddImageView(size_t addOnReserving)
	{
		VkImageSubresourceRange range{};
		range.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		range.baseMipLevel = 0;
		range.levelCount = 1;
		range.baseArrayLayer = 0;
		range.layerCount = 1;

		return AutoCleanupImage::AddImageView({}, range, VK_IMAGE_VIEW_TYPE_2D, addOnReserving);
	}

}