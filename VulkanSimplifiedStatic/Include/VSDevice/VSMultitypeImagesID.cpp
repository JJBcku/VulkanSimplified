#include "VSDeviceIpch.h"
#include "VSMultitypeImagesID.h"

namespace VulkanSimplified
{
	MultitypeImagesID::MultitypeImagesID()
	{
		type = ImageIDType::UNKNOWN;
	}

	MultitypeImagesID::MultitypeImagesID(const IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage>& ID)
	{
		colorRenderTarget.type = ImageIDType::COLOR_RENDER_TARGET;
		colorRenderTarget.ID = ID;
	}

	MultitypeImagesID::MultitypeImagesID(const IDObject<VulkanSimplifiedInternal::AutoCleanupDepthStencilRenderTargetImage>& ID)
	{
		depthStencilRenderTarget.type = ImageIDType::DEPTH_STENCIL_RENDER_TARGET;
		depthStencilRenderTarget.ID = ID;
	}
}
