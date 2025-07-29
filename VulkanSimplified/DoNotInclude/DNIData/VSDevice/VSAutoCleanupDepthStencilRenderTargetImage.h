#pragma once

#include "VSAutoCleanupImage.h"

#include <Miscellaneous/Bool64Def.h>

namespace VulkanSimplified
{
	class AutoCleanupDepthStencilRenderTargetImage : public AutoCleanupImage
	{
	public:
		AutoCleanupDepthStencilRenderTargetImage(VkDevice device, VkImage image, uint32_t width, uint32_t height, VkFormat format, VkSampleCountFlagBits sampleCount,
			Misc::Bool64Values depthElement, Misc::Bool64Values stencilElement, size_t imageViewsInitialCapacity);
		~AutoCleanupDepthStencilRenderTargetImage();

		AutoCleanupDepthStencilRenderTargetImage(const AutoCleanupDepthStencilRenderTargetImage& rhs) noexcept = delete;
		AutoCleanupDepthStencilRenderTargetImage(AutoCleanupDepthStencilRenderTargetImage&& rhs) noexcept = default;

		AutoCleanupDepthStencilRenderTargetImage& operator=(const AutoCleanupDepthStencilRenderTargetImage& rhs) noexcept = delete;
		AutoCleanupDepthStencilRenderTargetImage& operator=(AutoCleanupDepthStencilRenderTargetImage&& rhs) noexcept = default;

		IDObject<AutoCleanupImageView> AddImageView(size_t addOnReserving);

		private:
			Misc::Bool64 _depthElement;
			Misc::Bool64 _stencilElement;
	};
}