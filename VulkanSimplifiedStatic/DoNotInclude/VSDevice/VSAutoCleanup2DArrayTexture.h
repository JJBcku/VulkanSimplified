#pragma once

#include "VSAutoCleanupImage.h"

namespace VulkanSimplifiedInternal
{
	class AutoCleanup2DArrayTexture : public AutoCleanupImage
	{
	public:
		AutoCleanup2DArrayTexture(VkDevice device, VkImage image, uint32_t width, uint32_t height, uint32_t arrayLayers, uint32_t mipmapLevels, VkFormat format, VkImageLayout layout,
			size_t imageViewsInitialCapacity);
		~AutoCleanup2DArrayTexture();

		AutoCleanup2DArrayTexture(const AutoCleanup2DArrayTexture& rhs) noexcept = delete;
		AutoCleanup2DArrayTexture(AutoCleanup2DArrayTexture&& rhs) noexcept = default;

		AutoCleanup2DArrayTexture& operator=(const AutoCleanup2DArrayTexture& rhs) noexcept = delete;
		AutoCleanup2DArrayTexture& operator=(AutoCleanup2DArrayTexture&& rhs) noexcept = default;

		IDObject<AutoCleanupImageView> AddFullImageView(size_t addOnReserving);
		IDObject<AutoCleanupImageView> AddSelectedLayersImageView(uint32_t startingLayer, uint32_t usedLayerCount, size_t addOnReserving);
		IDObject<AutoCleanupImageView> AddSelectedMipmapsImageView(uint32_t startingMipmap, uint32_t usedMipmapCount, size_t addOnReserving);
		IDObject<AutoCleanupImageView> AddSelectedLayersAndMipmapsImageView(uint32_t startingMipmap, uint32_t usedMipmapCount, uint32_t startingLayer, uint32_t usedLayerCount,
			size_t addOnReserving);

		IDObject<AutoCleanupImageView> AddSingleLayerImageView(uint32_t arrayLayer, size_t addOnReserving);
		IDObject<AutoCleanupImageView> AddSingleLayerSelectMipmapsImageView(uint32_t arrayLayer, uint32_t startingMipmap, uint32_t usedMipmapCount, size_t addOnReserving);

		IDObject<AutoCleanupImageView> AddSingleMipmapImageView(uint32_t mipmapLevel, size_t addOnReserving);
		IDObject<AutoCleanupImageView> AddSingleMipmapSelectLayerImageView(uint32_t mipmapLevel, uint32_t startingLayer, uint32_t usedLayerCount, size_t addOnReserving);

		IDObject<AutoCleanupImageView> AddSingleMipmapAndLayerImageView(uint32_t mipmapLevel, uint32_t arrayLayer, size_t addOnReserving);

		IDObject<AutoCleanupImageView> AddRemainingLayersImageView(uint32_t startingLayer, size_t addOnReserving);
		IDObject<AutoCleanupImageView> AddRemainingLayersSelectMipmapsImageView(uint32_t startingLayer, uint32_t startingMipmap, uint32_t usedMipmapCount, size_t addOnReserving);
		IDObject<AutoCleanupImageView> AddRemainingLayersSingleMipmapImageView(uint32_t startingLayer, uint32_t mipmapLevel, size_t addOnReserving);

		IDObject<AutoCleanupImageView> AddRemainingMipmapsImageView(uint32_t startingMipmap, size_t addOnReserving);
		IDObject<AutoCleanupImageView> AddRemainingMipmapsSelectLayersImageView(uint32_t startingMipmap, uint32_t startingLayer, uint32_t usedLayerCount, size_t addOnReserving);
		IDObject<AutoCleanupImageView> AddRemainingMipmapsSingleLayerImageView(uint32_t startingMipmap, uint32_t arrayLayer, size_t addOnReserving);

		IDObject<AutoCleanupImageView> AddRemainingMipmapsAndLayersImageView(uint32_t startingMipmap, uint32_t startingLayer, size_t addOnReserving);
	};
}