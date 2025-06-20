#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSMultitypeImagesID.h"

namespace VulkanSimplified
{
	RenderTargetImagesID::RenderTargetImagesID()
	{
		type = ImageIDType::UNKNOWN;
	}

	RenderTargetImagesID::RenderTargetImagesID(const IDObject<AutoCleanupColorRenderTargetImage>& ID)
	{
		colorRenderTarget.type = ImageIDType::COLOR_RENDER_TARGET;
		colorRenderTarget.ID = ID;
	}

	RenderTargetImagesID::RenderTargetImagesID(const IDObject<AutoCleanupDepthStencilRenderTargetImage>& ID)
	{
		depthStencilRenderTarget.type = ImageIDType::DEPTH_STENCIL_RENDER_TARGET;
		depthStencilRenderTarget.ID = ID;
	}

	RenderTargetImagesID::RenderTargetImagesID(const IDObject<AutoCleanupResolveRenderTargetImage>& ID)
	{
		resolveRenderTarget.type = ImageIDType::RESOLVE_RENDER_TARGET;
		resolveRenderTarget.ID = ID;
	}
}
