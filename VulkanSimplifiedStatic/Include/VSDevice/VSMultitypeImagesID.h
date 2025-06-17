#pragma once

#include <CustomLists/IDObject.h>

#include "VSImageDataListsDef.h"

namespace VulkanSimplified
{
	enum class ImageIDType : uint64_t
	{
		UNKNOWN = 0,
		COLOR_RENDER_TARGET = 1,
		DEPTH_STENCIL_RENDER_TARGET = 2,
		RESOLVE_RENDER_TARGET = 4,
	};

	union RenderTargetImagesID
	{
		ImageIDType type;

		struct
		{
			ImageIDType type;
			IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> ID;
		} colorRenderTarget;

		struct
		{
			ImageIDType type;
			IDObject<VulkanSimplifiedInternal::AutoCleanupDepthStencilRenderTargetImage> ID;
		} depthStencilRenderTarget;

		struct
		{
			ImageIDType type;
			IDObject<VulkanSimplifiedInternal::AutoCleanupResolveRenderTargetImage> ID;
		} resolveRenderTarget;

		RenderTargetImagesID();
		RenderTargetImagesID(const IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage>& ID);
		RenderTargetImagesID(const IDObject<VulkanSimplifiedInternal::AutoCleanupDepthStencilRenderTargetImage>& ID);
		RenderTargetImagesID(const IDObject<VulkanSimplifiedInternal::AutoCleanupResolveRenderTargetImage>& ID);
	};
}