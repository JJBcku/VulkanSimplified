#include "VSDeviceDNIpch.h"
#include "VSAutoCleanup2DTexture.h"

#include "VSAutoCleanupImageView.h"

namespace VulkanSimplified
{
	AutoCleanup2DTexture::AutoCleanup2DTexture(VkDevice device, VkImage image, uint32_t width, uint32_t height, uint32_t mipmapLevels, VkFormat format,
		size_t imageViewsInitialCapacity) : AutoCleanupImage(device, image, width, height, 1, mipmapLevels, format, VK_SAMPLE_COUNT_1_BIT, imageViewsInitialCapacity)
	{
	}

	AutoCleanup2DTexture::~AutoCleanup2DTexture()
	{
	}

	IDObject<AutoCleanupImageView> AutoCleanup2DTexture::AddFullImageView(size_t addOnReserving)
	{
		VkImageSubresourceRange range{};
		range.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		range.baseMipLevel = 0;
		range.levelCount = GetMipmapLevels();
		range.baseArrayLayer = 0;
		range.layerCount = 1;

		return AutoCleanupImage::AddImageView({}, range, VK_IMAGE_VIEW_TYPE_2D, addOnReserving);
	}

	IDObject<AutoCleanupImageView> AutoCleanup2DTexture::AddSelectedMipmapsImageView(uint32_t startingMipmap, std::optional<uint32_t> mipmapCount, size_t addOnReserving)
	{
		uint32_t mipmapAmount = GetMipmapLevels();

		if (startingMipmap >= mipmapAmount)
			throw std::runtime_error("AutoCleanup2DTexture::AddSelectedMipmapsImageView Error: Program tried to use non-existent starting mipmap!");

		if (mipmapAmount - startingMipmap < mipmapCount)
			throw std::runtime_error("AutoCleanup2DTexture::AddSelectedMipmapsImageView Error: Program tried to use more mipmaps than is available!");

		VkImageSubresourceRange range{};
		range.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		range.baseMipLevel = startingMipmap;
		if (mipmapCount.has_value())
			range.levelCount = mipmapCount.value();
		else
			range.levelCount = VK_REMAINING_MIP_LEVELS;
		range.baseArrayLayer = 0;
		range.layerCount = 1;

		return AutoCleanupImage::AddImageView({}, range, VK_IMAGE_VIEW_TYPE_2D, addOnReserving);
	}

}