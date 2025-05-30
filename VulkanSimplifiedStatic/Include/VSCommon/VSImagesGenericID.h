#pragma once

#include <CustomLists/IDObject.h>

#include "../VSDevice/VSImageDataListsDef.h"

namespace VulkanSimplified
{
	enum class ImagesIDType
	{
		UNKNOWN = 0,
		COLOR_RENDER_TARGET = 1,
		TEXTURE_2D = 2,
	};

	union ImagesGenericID
	{
		ImagesIDType type;

		struct
		{
			ImagesIDType type;
			IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> ID;
		} colorRenderTargetID;

		struct
		{
			ImagesIDType type;
			IDObject<VulkanSimplifiedInternal::AutoCleanup2DTexture> ID;
		} texture2DID;

		ImagesGenericID();
		ImagesGenericID(IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> ID);
		ImagesGenericID(IDObject<VulkanSimplifiedInternal::AutoCleanup2DTexture> ID);
	};
}