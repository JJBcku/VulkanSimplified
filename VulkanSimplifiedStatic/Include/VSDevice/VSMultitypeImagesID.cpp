#include "VSDeviceIpch.h"
#include "VSMultitypeImagesID.h"

namespace VulkanSimplified
{
	RenderTargetImagesID::RenderTargetImagesID()
	{
		type = ImageIDType::UNKNOWN;
	}

	RenderTargetImagesID::RenderTargetImagesID(const IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage>& ID)
	{
		colorRenderTarget.type = ImageIDType::COLOR_RENDER_TARGET;
		colorRenderTarget.ID = ID;
	}

	RenderTargetImagesID::RenderTargetImagesID(const IDObject<VulkanSimplifiedInternal::AutoCleanupDepthStencilRenderTargetImage>& ID)
	{
		depthStencilRenderTarget.type = ImageIDType::DEPTH_STENCIL_RENDER_TARGET;
		depthStencilRenderTarget.ID = ID;
	}

	RenderTargetImagesID::RenderTargetImagesID(const IDObject<VulkanSimplifiedInternal::AutoCleanupResolveRenderTargetImage>& ID)
	{
		resolveRenderTarget.type = ImageIDType::RESOLVE_RENDER_TARGET;
		resolveRenderTarget.ID = ID;
	}
}
