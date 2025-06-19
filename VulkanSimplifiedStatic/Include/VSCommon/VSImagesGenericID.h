#pragma once

#include <CustomLists/IDObject.h>

#include "../VSDevice/VSImageDataListsDef.h"

#include <optional>
#include <stdint.h>

namespace VulkanSimplified
{
	enum class ImagesIDType : uint64_t
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

			uint32_t baseMipLevel;
			std::optional<uint32_t> mipLevelCount;
		} texture2DID;

		ImagesGenericID();
		ImagesGenericID(IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> ID);
		ImagesGenericID(IDObject<VulkanSimplifiedInternal::AutoCleanup2DTexture> ID);
	};
}