#pragma once

#include "VSAutoCleanupImage.h"

namespace VulkanSimplifiedInternal
{
	class AutoCleanup2DTexture : public AutoCleanupImage
	{
	public:
		AutoCleanup2DTexture(VkDevice device, VkImage image, uint32_t width, uint32_t height, uint32_t mipmapLevels, VkFormat format, VkImageLayout layout,
			size_t imageViewsInitialCapacity);
		~AutoCleanup2DTexture();

		AutoCleanup2DTexture(const AutoCleanup2DTexture& rhs) noexcept = delete;
		AutoCleanup2DTexture(AutoCleanup2DTexture&& rhs) noexcept = default;

		AutoCleanup2DTexture& operator=(const AutoCleanup2DTexture& rhs) noexcept = delete;
		AutoCleanup2DTexture& operator=(AutoCleanup2DTexture& rhs) noexcept = default;

		IDObject<AutoCleanupImageView> AddFullImageView(size_t addOnReserving);
		IDObject<AutoCleanupImageView> AddSingleMipmapImageView(uint32_t mipmap, size_t addOnReserving);
		IDObject<AutoCleanupImageView> AddRemainingMipmapsImageView(uint32_t startingMipmap, size_t addOnReserving);
		IDObject<AutoCleanupImageView> AddSelectedMipmapsImageView(uint32_t startingMipmap, uint32_t mipmapCount, size_t addOnReserving);
	};
}