#pragma once

#include "VSAutoCleanupImage.h"

namespace VulkanSimplified
{
	class AutoCleanupDepthStencilRenderTargetImage : public AutoCleanupImage
	{
	public:
		AutoCleanupDepthStencilRenderTargetImage(VkDevice device, VkImage image, uint32_t width, uint32_t height, VkFormat format, VkSampleCountFlagBits sampleCount,
			size_t imageViewsInitialCapacity);
		~AutoCleanupDepthStencilRenderTargetImage();

		AutoCleanupDepthStencilRenderTargetImage(const AutoCleanupDepthStencilRenderTargetImage& rhs) noexcept = delete;
		AutoCleanupDepthStencilRenderTargetImage(AutoCleanupDepthStencilRenderTargetImage&& rhs) noexcept = default;

		AutoCleanupDepthStencilRenderTargetImage& operator=(const AutoCleanupDepthStencilRenderTargetImage& rhs) noexcept = delete;
		AutoCleanupDepthStencilRenderTargetImage& operator=(AutoCleanupDepthStencilRenderTargetImage&& rhs) noexcept = default;

		IDObject<AutoCleanupImageView> AddImageView(size_t addOnReserving);
	};
}