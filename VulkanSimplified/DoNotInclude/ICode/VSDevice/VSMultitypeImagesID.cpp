#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSMultitypeImagesID.h"

namespace VulkanSimplified
{
	RenderTargetImagesID::RenderTargetImagesID() noexcept
	{
		type = ImageIDType::UNKNOWN;
	}

	RenderTargetImagesID::RenderTargetImagesID(const IDObject<AutoCleanupColorRenderTargetImage>& ID) noexcept
	{
		colorRenderTarget.type = ImageIDType::COLOR_RENDER_TARGET;
		colorRenderTarget.ID = ID;
	}

	RenderTargetImagesID::RenderTargetImagesID(const IDObject<AutoCleanupDepthStencilRenderTargetImage>& ID) noexcept
	{
		depthStencilRenderTarget.type = ImageIDType::DEPTH_STENCIL_RENDER_TARGET;
		depthStencilRenderTarget.ID = ID;
	}

	RenderTargetImagesID::RenderTargetImagesID(const IDObject<AutoCleanupResolveRenderTargetImage>& ID) noexcept
	{
		resolveRenderTarget.type = ImageIDType::RESOLVE_RENDER_TARGET;
		resolveRenderTarget.ID = ID;
	}

	RenderTargetImagesID::RenderTargetImagesID(const RenderTargetImagesID& rhs) noexcept
	{
		std::memcpy(this, &rhs, sizeof(RenderTargetImagesID));
	}

	RenderTargetImagesID::~RenderTargetImagesID()
	{
	}

	RenderTargetImagesID& RenderTargetImagesID::operator=(const RenderTargetImagesID& rhs) noexcept
	{
		std::memcpy(this, &rhs, sizeof(RenderTargetImagesID));

		return *this;
	}
}
