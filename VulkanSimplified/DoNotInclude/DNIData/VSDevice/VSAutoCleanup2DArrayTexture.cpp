#include "VSDeviceDNIpch.h"
#include "VSAutoCleanup2DArrayTexture.h"

namespace VulkanSimplified
{
	AutoCleanup2DArrayTexture::AutoCleanup2DArrayTexture(VkDevice device, VkImage image, uint32_t width, uint32_t height, uint32_t arrayLayers, uint32_t mipmapLevels, VkFormat format,
		size_t imageViewsInitialCapacity) : AutoCleanupImage(device, image, width, height, arrayLayers, mipmapLevels, format, VK_SAMPLE_COUNT_1_BIT, imageViewsInitialCapacity)
	{
	}

	AutoCleanup2DArrayTexture::~AutoCleanup2DArrayTexture()
	{
	}

	IDObject<AutoCleanupImageView> AutoCleanup2DArrayTexture::AddFullImageView(size_t addOnReserving)
	{
		VkImageSubresourceRange range{};
		range.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		range.baseMipLevel = 0;
		range.levelCount = GetMipmapLevels();
		range.baseArrayLayer = 0;
		range.layerCount = GetDepth();

		return AutoCleanupImage::AddImageView({}, range, VK_IMAGE_VIEW_TYPE_2D_ARRAY, addOnReserving);
	}

	IDObject<AutoCleanupImageView> AutoCleanup2DArrayTexture::AddSelectedLayersAndMipmapsImageView(uint32_t startingMipmap, std::optional<uint32_t> usedMipmapCount,
		uint32_t startingLayer, std::optional<uint32_t> usedLayerCount, size_t addOnReserving)
	{
		uint32_t mipmapAmount = GetMipmapLevels();

		if (startingMipmap >= mipmapAmount)
			throw std::runtime_error("AutoCleanup2DArrayTexture::AddSelectedLayersAndMipmapsImageView Error: Program tried to use non-existent starting mipmapLevel!");

		if (mipmapAmount - startingMipmap < usedMipmapCount)
			throw std::runtime_error("AutoCleanup2DArrayTexture::AddSelectedLayersAndMipmapsImageView Error: Program tried to use more mipmaps than is available!");

		uint32_t layerAmount = GetDepth();

		if (startingLayer >= layerAmount)
			throw std::runtime_error("AutoCleanup2DArrayTexture::AddSelectedLayersAndMipmapsImageView Error: Program tried to use non-existent starting arrayLayer!");

		if (layerAmount - startingLayer < usedLayerCount)
			throw std::runtime_error("AutoCleanup2DArrayTexture::AddSelectedLayersAndMipmapsImageView Error: Program tried to use more layers than is available!");

		VkImageSubresourceRange range{};
		range.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		range.baseMipLevel = startingMipmap;
		if (usedMipmapCount.has_value())
			range.levelCount = usedMipmapCount.value();
		else
			range.levelCount = VK_REMAINING_MIP_LEVELS;
		range.baseArrayLayer = startingLayer;
		if (usedLayerCount.has_value())
			range.layerCount = usedLayerCount.value();
		else
			range.layerCount = VK_REMAINING_ARRAY_LAYERS;

		return AutoCleanupImage::AddImageView({}, range, VK_IMAGE_VIEW_TYPE_2D_ARRAY, addOnReserving);
	}

}
