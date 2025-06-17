#pragma once

#include "VSAutoCleanupImage.h"

namespace VulkanSimplifiedInternal
{
	class AutoCleanupResolveRenderTargetImage : public AutoCleanupImage
	{
	public:
		AutoCleanupResolveRenderTargetImage(VkDevice device, VkImage image, uint32_t width, uint32_t height, VkFormat format, size_t imageViewsInitialCapacity);
		~AutoCleanupResolveRenderTargetImage();

		AutoCleanupResolveRenderTargetImage(const AutoCleanupResolveRenderTargetImage& rhs) noexcept = delete;
		AutoCleanupResolveRenderTargetImage(AutoCleanupResolveRenderTargetImage&& rhs) noexcept = default;

		AutoCleanupResolveRenderTargetImage& operator=(const AutoCleanupResolveRenderTargetImage& rhs) noexcept = delete;
		AutoCleanupResolveRenderTargetImage& operator=(AutoCleanupResolveRenderTargetImage&& rhs) noexcept = default;

		IDObject<AutoCleanupImageView> AddImageView(size_t addOnReserving);
	};
}
