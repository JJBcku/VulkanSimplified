#include "VSCommonIpch.h"
#include "VSImagesGenericID.h"

namespace VulkanSimplified
{
	ImagesGenericID::ImagesGenericID()
	{
		type = ImagesIDType::UNKNOWN;
	}

	ImagesGenericID::ImagesGenericID(IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage> ID)
	{
		colorRenderTargetID.type = ImagesIDType::COLOR_RENDER_TARGET;
		colorRenderTargetID.ID = ID;
	}

	ImagesGenericID::ImagesGenericID(IDObject<VulkanSimplifiedInternal::AutoCleanup2DTexture> ID)
	{
		texture2DID.type = ImagesIDType::TEXTURE_2D;
		texture2DID.ID = ID;

		texture2DID.baseMipLevel = 0;
		texture2DID.mipLevelCount = {};
	}
}