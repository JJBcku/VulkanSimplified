#include "VSDeviceNIpch.h"
#include "VSAutoCleanup2DArrayTexture.h"

namespace VulkanSimplifiedInternal
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

	IDObject<AutoCleanupImageView> AutoCleanup2DArrayTexture::AddSelectedLayersImageView(uint32_t startingLayer, uint32_t usedLayerCount, size_t addOnReserving)
	{
		uint32_t layerAmount = GetDepth();

		if (startingLayer >= layerAmount)
			throw std::runtime_error("AutoCleanup2DArrayTexture::AddSelectedLayersImageView Error: Program tried to use non-existent starting arrayLayer!");

		if (layerAmount - startingLayer < usedLayerCount)
			throw std::runtime_error("AutoCleanup2DArrayTexture::AddSelectedLayersImageView Error: Program tried to use more layers than is available!");

		VkImageSubresourceRange range{};
		range.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		range.baseMipLevel = 0;
		range.levelCount = GetMipmapLevels();
		range.baseArrayLayer = startingLayer;
		range.layerCount = usedLayerCount;

		return AutoCleanupImage::AddImageView({}, range, VK_IMAGE_VIEW_TYPE_2D_ARRAY, addOnReserving);
	}

	IDObject<AutoCleanupImageView> AutoCleanup2DArrayTexture::AddSelectedMipmapsImageView(uint32_t startingMipmap, uint32_t usedMipmapCount, size_t addOnReserving)
	{
		uint32_t mipmapAmount = GetMipmapLevels();

		if (startingMipmap >= mipmapAmount)
			throw std::runtime_error("AutoCleanup2DArrayTexture::AddSelectedMipmapsImageView Error: Program tried to use non-existent starting mipmapLevel!");

		if (mipmapAmount - startingMipmap < usedMipmapCount)
			throw std::runtime_error("AutoCleanup2DArrayTexture::AddSelectedMipmapsImageView Error: Program tried to use more mipmaps than is available!");

		VkImageSubresourceRange range{};
		range.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		range.baseMipLevel = startingMipmap;
		range.levelCount = usedMipmapCount;
		range.baseArrayLayer = 0;
		range.layerCount = GetDepth();

		return AutoCleanupImage::AddImageView({}, range, VK_IMAGE_VIEW_TYPE_2D_ARRAY, addOnReserving);
	}

	IDObject<AutoCleanupImageView> AutoCleanup2DArrayTexture::AddSelectedLayersAndMipmapsImageView(uint32_t startingMipmap, uint32_t usedMipmapCount,
		uint32_t startingLayer, uint32_t usedLayerCount, size_t addOnReserving)
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
		range.levelCount = usedMipmapCount;
		range.baseArrayLayer = startingLayer;
		range.layerCount = usedLayerCount;

		return AutoCleanupImage::AddImageView({}, range, VK_IMAGE_VIEW_TYPE_2D_ARRAY, addOnReserving);
	}

	IDObject<AutoCleanupImageView> AutoCleanup2DArrayTexture::AddSingleLayerImageView(uint32_t arrayLayer, size_t addOnReserving)
	{
		if (arrayLayer >= GetDepth())
			throw std::runtime_error("AutoCleanup2DArrayTexture::AddSelectedLayersAndMipmapsImageView Error: Program tried to use non-existent arrayLayer!");

		VkImageSubresourceRange range{};
		range.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		range.baseMipLevel = 0;
		range.levelCount = GetMipmapLevels();
		range.baseArrayLayer = arrayLayer;
		range.layerCount = 1;

		return AutoCleanupImage::AddImageView({}, range, VK_IMAGE_VIEW_TYPE_2D, addOnReserving);
	}

	IDObject<AutoCleanupImageView> AutoCleanup2DArrayTexture::AddSingleLayerSelectMipmapsImageView(uint32_t arrayLayer, uint32_t startingMipmap, uint32_t usedMipmapCount,
		size_t addOnReserving)
	{
		if (arrayLayer >= GetDepth())
			throw std::runtime_error("AutoCleanup2DArrayTexture::AddSingleLayerSelectMipmapsImageView Error: Program tried to use non-existent arrayLayer!");

		uint32_t mipmapAmount = GetMipmapLevels();

		if (startingMipmap >= mipmapAmount)
			throw std::runtime_error("AutoCleanup2DArrayTexture::AddSingleLayerSelectMipmapsImageView Error: Program tried to use non-existent starting mipmapLevel!");

		if (mipmapAmount - startingMipmap < usedMipmapCount)
			throw std::runtime_error("AutoCleanup2DArrayTexture::AddSingleLayerSelectMipmapsImageView Error: Program tried to use more mipmaps than is available!");

		VkImageSubresourceRange range{};
		range.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		range.baseMipLevel = startingMipmap;
		range.levelCount = usedMipmapCount;
		range.baseArrayLayer = arrayLayer;
		range.layerCount = 1;

		return AutoCleanupImage::AddImageView({}, range, VK_IMAGE_VIEW_TYPE_2D, addOnReserving);
	}

	IDObject<AutoCleanupImageView> AutoCleanup2DArrayTexture::AddSingleMipmapImageView(uint32_t mipmapLevel, size_t addOnReserving)
	{
		if (mipmapLevel >= GetMipmapLevels())
			throw std::runtime_error("AutoCleanup2DArrayTexture::AddSingleMipmapImageView Error: Program tried to use non-existent mipmapLevel!");

		VkImageSubresourceRange range{};
		range.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		range.baseMipLevel = mipmapLevel;
		range.levelCount = 1;
		range.baseArrayLayer = 0;
		range.layerCount = GetDepth();

		return AutoCleanupImage::AddImageView({}, range, VK_IMAGE_VIEW_TYPE_2D_ARRAY, addOnReserving);
	}

	IDObject<AutoCleanupImageView> AutoCleanup2DArrayTexture::AddSingleMipmapSelectLayerImageView(uint32_t mipmapLevel, uint32_t startingLayer, uint32_t usedLayerCount,
		size_t addOnReserving)
	{
		if (mipmapLevel >= GetMipmapLevels())
			throw std::runtime_error("AutoCleanup2DArrayTexture::AddSingleMipmapSelectLayerImageView Error: Program tried to use non-existent mipmapLevel!");

		uint32_t layerAmount = GetDepth();

		if (startingLayer >= layerAmount)
			throw std::runtime_error("AutoCleanup2DArrayTexture::AddSingleMipmapSelectLayerImageView Error: Program tried to use non-existent starting arrayLayer!");

		if (layerAmount - startingLayer < usedLayerCount)
			throw std::runtime_error("AutoCleanup2DArrayTexture::AddSingleMipmapSelectLayerImageView Error: Program tried to use more layers than is available!");

		VkImageSubresourceRange range{};
		range.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		range.baseMipLevel = mipmapLevel;
		range.levelCount = 1;
		range.baseArrayLayer = startingLayer;
		range.layerCount = usedLayerCount;

		return AutoCleanupImage::AddImageView({}, range, VK_IMAGE_VIEW_TYPE_2D_ARRAY, addOnReserving);
	}

	IDObject<AutoCleanupImageView> AutoCleanup2DArrayTexture::AddSingleMipmapAndLayerImageView(uint32_t mipmapLevel, uint32_t arrayLayer, size_t addOnReserving)
	{
		if (mipmapLevel >= GetMipmapLevels())
			throw std::runtime_error("AutoCleanup2DArrayTexture::AddSingleMipmapAndLayerImageView Error: Program tried to use non-existent mipmapLevel!");

		uint32_t layerAmount = GetDepth();

		if (arrayLayer >= layerAmount)
			throw std::runtime_error("AutoCleanup2DArrayTexture::AddSingleMipmapAndLayerImageView Error: Program tried to use non-existent arrayLayer!");

		VkImageSubresourceRange range{};
		range.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		range.baseMipLevel = mipmapLevel;
		range.levelCount = 1;
		range.baseArrayLayer = arrayLayer;
		range.layerCount = 1;

		return AutoCleanupImage::AddImageView({}, range, VK_IMAGE_VIEW_TYPE_2D, addOnReserving);
	}

	IDObject<AutoCleanupImageView> AutoCleanup2DArrayTexture::AddRemainingLayersImageView(uint32_t startingLayer, size_t addOnReserving)
	{
		if (startingLayer >= GetDepth())
			throw std::runtime_error("AutoCleanup2DArrayTexture::AddRemainingLayersImageView Error: Program tried to use non-existent starting arrayLayer!");

		VkImageSubresourceRange range{};
		range.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		range.baseMipLevel = 0;
		range.levelCount = GetMipmapLevels();
		range.baseArrayLayer = startingLayer;
		range.layerCount = VK_REMAINING_ARRAY_LAYERS;

		return AutoCleanupImage::AddImageView({}, range, VK_IMAGE_VIEW_TYPE_2D_ARRAY, addOnReserving);
	}

	IDObject<AutoCleanupImageView> AutoCleanup2DArrayTexture::AddRemainingLayersSelectMipmapsImageView(uint32_t startingLayer, uint32_t startingMipmap, uint32_t usedMipmapCount,
		size_t addOnReserving)
	{
		uint32_t mipmapAmount = GetMipmapLevels();

		if (startingMipmap >= mipmapAmount)
			throw std::runtime_error("AutoCleanup2DArrayTexture::AddRemainingLayersSelectMipmapsImageView Error: Program tried to use non-existent starting mipmapLevel!");

		if (mipmapAmount - startingMipmap < usedMipmapCount)
			throw std::runtime_error("AutoCleanup2DArrayTexture::AddRemainingLayersSelectMipmapsImageView Error: Program tried to use more mipmaps than is available!");

		if (startingLayer >= GetDepth())
			throw std::runtime_error("AutoCleanup2DArrayTexture::AddRemainingLayersSelectMipmapsImageView Error: Program tried to use non-existent starting arrayLayer!");

		VkImageSubresourceRange range{};
		range.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		range.baseMipLevel = startingMipmap;
		range.levelCount = usedMipmapCount;
		range.baseArrayLayer = startingLayer;
		range.layerCount = VK_REMAINING_ARRAY_LAYERS;

		return AutoCleanupImage::AddImageView({}, range, VK_IMAGE_VIEW_TYPE_2D_ARRAY, addOnReserving);
	}

	IDObject<AutoCleanupImageView> AutoCleanup2DArrayTexture::AddRemainingLayersSingleMipmapImageView(uint32_t startingLayer, uint32_t mipmapLevel, size_t addOnReserving)
	{
		if (mipmapLevel >= GetMipmapLevels())
			throw std::runtime_error("AutoCleanup2DArrayTexture::AddRemainingLayersSelectMipmapsImageView Error: Program tried to use non-existent starting mipmapLevel!");

		if (startingLayer >= GetDepth())
			throw std::runtime_error("AutoCleanup2DArrayTexture::AddRemainingLayersSelectMipmapsImageView Error: Program tried to use non-existent starting arrayLayer!");

		VkImageSubresourceRange range{};
		range.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		range.baseMipLevel = mipmapLevel;
		range.levelCount = 1;
		range.baseArrayLayer = startingLayer;
		range.layerCount = VK_REMAINING_ARRAY_LAYERS;

		return AutoCleanupImage::AddImageView({}, range, VK_IMAGE_VIEW_TYPE_2D_ARRAY, addOnReserving);
	}

	IDObject<AutoCleanupImageView> AutoCleanup2DArrayTexture::AddRemainingMipmapsImageView(uint32_t startingMipmap, size_t addOnReserving)
	{
		if (startingMipmap >= GetMipmapLevels())
			throw std::runtime_error("AutoCleanup2DArrayTexture::AddRemainingMipmapsImageView Error: Program tried to use non-existent starting mipmapLevel!");

		VkImageSubresourceRange range{};
		range.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		range.baseMipLevel = startingMipmap;
		range.levelCount = VK_REMAINING_MIP_LEVELS;
		range.baseArrayLayer = 0;
		range.layerCount = GetDepth();

		return AutoCleanupImage::AddImageView({}, range, VK_IMAGE_VIEW_TYPE_2D_ARRAY, addOnReserving);
	}

	IDObject<AutoCleanupImageView> AutoCleanup2DArrayTexture::AddRemainingMipmapsSelectLayersImageView(uint32_t startingMipmap, uint32_t startingLayer, uint32_t usedLayerCount,
		size_t addOnReserving)
	{
		if (startingMipmap >= GetMipmapLevels())
			throw std::runtime_error("AutoCleanup2DArrayTexture::AddRemainingMipmapsSelectLayersImageView Error: Program tried to use non-existent starting mipmapLevel!");

		uint32_t layerAmount = GetDepth();

		if (startingLayer >= layerAmount)
			throw std::runtime_error("AutoCleanup2DArrayTexture::AddRemainingMipmapsSelectLayersImageView Error: Program tried to use non-existent starting arrayLayer!");

		if (layerAmount - startingLayer < usedLayerCount)
			throw std::runtime_error("AutoCleanup2DArrayTexture::AddRemainingMipmapsSelectLayersImageView Error: Program tried to use more layers than is available!");

		VkImageSubresourceRange range{};
		range.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		range.baseMipLevel = startingMipmap;
		range.levelCount = VK_REMAINING_MIP_LEVELS;
		range.baseArrayLayer = startingLayer;
		range.layerCount = usedLayerCount;

		return AutoCleanupImage::AddImageView({}, range, VK_IMAGE_VIEW_TYPE_2D_ARRAY, addOnReserving);
	}

	IDObject<AutoCleanupImageView> AutoCleanup2DArrayTexture::AddRemainingMipmapsSingleLayerImageView(uint32_t startingMipmap, uint32_t arrayLayer, size_t addOnReserving)
	{
		if (startingMipmap >= GetMipmapLevels())
			throw std::runtime_error("AutoCleanup2DArrayTexture::AddRemainingMipmapsSingleLayerImageView Error: Program tried to use non-existent starting mipmapLevel!");

		if (arrayLayer >= GetDepth())
			throw std::runtime_error("AutoCleanup2DArrayTexture::AddRemainingMipmapsSingleLayerImageView Error: Program tried to use non-existent starting arrayLayer!");

		VkImageSubresourceRange range{};
		range.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		range.baseMipLevel = startingMipmap;
		range.levelCount = VK_REMAINING_MIP_LEVELS;
		range.baseArrayLayer = arrayLayer;
		range.layerCount = 1;

		return AutoCleanupImage::AddImageView({}, range, VK_IMAGE_VIEW_TYPE_2D, addOnReserving);
	}

	IDObject<AutoCleanupImageView> AutoCleanup2DArrayTexture::AddRemainingMipmapsAndLayersImageView(uint32_t startingMipmap, uint32_t startingLayer, size_t addOnReserving)
	{
		if (startingMipmap >= GetMipmapLevels())
			throw std::runtime_error("AutoCleanup2DArrayTexture::AddRemainingMipmapsAndLayersImageView Error: Program tried to use non-existent starting mipmapLevel!");

		uint32_t layerAmount = GetDepth();

		if (startingLayer >= layerAmount)
			throw std::runtime_error("AutoCleanup2DArrayTexture::AddRemainingMipmapsAndLayersImageView Error: Program tried to use non-existent starting arrayLayer!");

		VkImageSubresourceRange range{};
		range.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		range.baseMipLevel = startingMipmap;
		range.levelCount = VK_REMAINING_MIP_LEVELS;
		range.baseArrayLayer = startingLayer;
		range.layerCount = VK_REMAINING_ARRAY_LAYERS;

		return AutoCleanupImage::AddImageView({}, range, VK_IMAGE_VIEW_TYPE_2D_ARRAY, addOnReserving);
	}

}
