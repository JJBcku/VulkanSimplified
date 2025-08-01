#pragma once

#include "VSAutoCleanupImage.h"

namespace VulkanSimplified
{
	class AutoCleanupColorRenderTargetImage : public AutoCleanupImage
	{
	public:
		AutoCleanupColorRenderTargetImage(VkDevice device, VkImage image, uint32_t width, uint32_t height, VkFormat format, VkSampleCountFlagBits sampleCount,
			size_t imageViewsInitialCapacity);
		~AutoCleanupColorRenderTargetImage();

		AutoCleanupColorRenderTargetImage(const AutoCleanupColorRenderTargetImage& rhs) noexcept = delete;
		AutoCleanupColorRenderTargetImage(AutoCleanupColorRenderTargetImage&& rhs) noexcept = default;

		AutoCleanupColorRenderTargetImage& operator=(const AutoCleanupColorRenderTargetImage& rhs) noexcept = delete;
		AutoCleanupColorRenderTargetImage& operator=(AutoCleanupColorRenderTargetImage&& rhs) noexcept = default;

		IDObject<AutoCleanupImageView> AddImageView(size_t addOnReserving);
	};
}