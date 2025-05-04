#pragma once

#include <CustomLists/IDObject.h>

#include "VSImageDataListsDef.h"

namespace VulkanSimplified
{
	enum class ImageIDType : uint64_t
	{
		UNKNOWN = 0,
		COLOR_RENDER_TARGET = 1,
	};

	union MultitypeImagesID
	{
		ImageIDType type;
		struct
		{
			ImageIDType type;
			IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> ID;
		} colorRenderTarget;

		MultitypeImagesID();
		MultitypeImagesID(const IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage>& ID);
	};
}