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
}