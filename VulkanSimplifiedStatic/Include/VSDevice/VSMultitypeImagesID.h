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
	};

	union MultitypeImagesID
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

		MultitypeImagesID();
		MultitypeImagesID(const IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage>& ID);
		MultitypeImagesID(const IDObject<VulkanSimplifiedInternal::AutoCleanupDepthStencilRenderTargetImage>& ID);
	};
}