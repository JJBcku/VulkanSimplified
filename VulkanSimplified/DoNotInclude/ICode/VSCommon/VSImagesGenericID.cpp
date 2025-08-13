#include "VSCommonIpch.h"
#include "../../../Include/VSCommon/VSImagesGenericID.h"

namespace VulkanSimplified
{
	ImagesGenericID::ImagesGenericID()
	{
		type = ImagesIDType::UNKNOWN;
	}

	ImagesGenericID::ImagesGenericID(IDObject<AutoCleanupColorRenderTargetImage> ID)
	{
		colorRenderTarget.type = ImagesIDType::COLOR_RENDER_TARGET;
		colorRenderTarget.ID = ID;
	}

	ImagesGenericID::ImagesGenericID(IDObject<AutoCleanup2DTexture> ID)
	{
		texture2D.type = ImagesIDType::TEXTURE_2D;
		texture2D.ID = ID;

		texture2D.baseMipLevel = 0;
		texture2D.mipLevelCount = {};
	}

	ImagesGenericID::ImagesGenericID(IDObject<AutoCleanup2DArrayTexture> ID)
	{
		textureArray2D.type = ImagesIDType::TEXTURE_2D_ARRAY;
		textureArray2D.ID = ID;

		textureArray2D.baseMipLevel = 0;
		textureArray2D.mipLevelCount = {};

		textureArray2D.baseArrayLayer = 0;
		textureArray2D.arrayLayersCount = {};
	}
}