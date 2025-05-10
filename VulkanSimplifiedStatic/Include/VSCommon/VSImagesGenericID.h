#pragma once

#include <CustomLists/IDObject.h>

#include "../VSDevice/VSImageDataListsDef.h"

namespace VulkanSimplified
{
	enum class ImagesIDType
	{
		UNKNOWN = 0,
		COLOR_RENDER_TARGET = 1,
	};

	union ImagesGenericID
	{
		ImagesIDType type;

		struct
		{
			ImagesIDType type;
			IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> ID;
		} colorRenderTargetID;

		ImagesGenericID();
		ImagesGenericID(IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> ID);
	};
}