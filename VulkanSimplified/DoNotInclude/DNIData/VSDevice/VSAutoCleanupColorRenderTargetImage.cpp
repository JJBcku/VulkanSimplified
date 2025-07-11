#include "VSDeviceDNIpch.h"
#include "VSAutoCleanupColorRenderTargetImage.h"

namespace VulkanSimplified
{
	AutoCleanupColorRenderTargetImage::AutoCleanupColorRenderTargetImage(VkDevice device, VkImage image, uint32_t width, uint32_t height, VkFormat format,
		VkSampleCountFlagBits sampleCount, size_t imageViewsInitialCapacity) : AutoCleanupImage(device, image, width, height, 1, 1, format, sampleCount, imageViewsInitialCapacity)
	{
	}

	AutoCleanupColorRenderTargetImage::~AutoCleanupColorRenderTargetImage()
	{
	}

	IDObject<AutoCleanupImageView> AutoCleanupColorRenderTargetImage::AddImageView(size_t addOnReserving)
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