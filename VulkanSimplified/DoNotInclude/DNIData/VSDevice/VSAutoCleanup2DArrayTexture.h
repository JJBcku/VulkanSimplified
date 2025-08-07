#pragma once

#include "VSAutoCleanupImage.h"

#include <optional>

namespace VulkanSimplified
{
	class AutoCleanup2DArrayTexture : public AutoCleanupImage
	{
	public:
		AutoCleanup2DArrayTexture(VkDevice device, VkImage image, uint32_t width, uint32_t height, uint32_t arrayLayers, uint32_t mipmapLevels, VkFormat format,
			size_t imageViewsInitialCapacity);
		~AutoCleanup2DArrayTexture();

		AutoCleanup2DArrayTexture(const AutoCleanup2DArrayTexture& rhs) noexcept = delete;
		AutoCleanup2DArrayTexture(AutoCleanup2DArrayTexture&& rhs) noexcept = default;

		AutoCleanup2DArrayTexture& operator=(const AutoCleanup2DArrayTexture& rhs) noexcept = delete;
		AutoCleanup2DArrayTexture& operator=(AutoCleanup2DArrayTexture&& rhs) noexcept = default;

		IDObject<AutoCleanupImageView> AddFullImageView(size_t addOnReserving);
		IDObject<AutoCleanupImageView> AddSelectedLayersAndMipmapsImageView(uint32_t startingMipmap, std::optional<uint32_t> usedMipmapCount, uint32_t startingLayer,
			std::optional<uint32_t> usedLayerCount, size_t addOnReserving);
	};
}