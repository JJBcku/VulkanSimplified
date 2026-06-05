#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSMultitypeImagesID.h"

namespace VulkanSimplified
{
	RenderTargetImagesID::RenderTargetImagesID() noexcept
	{
		type = ImageIDType::UNKNOWN;
	}

	RenderTargetImagesID::RenderTargetImagesID(const IDObject<AutoCleanupColorRenderTargetImage>& ID) noexcept : colorRenderTarget(ID)
	{
	}

	RenderTargetImagesID::RenderTargetImagesID(const IDObject<AutoCleanupDepthStencilRenderTargetImage>& ID) noexcept : depthStencilRenderTarget(ID)
	{
	}

	RenderTargetImagesID::RenderTargetImagesID(const IDObject<AutoCleanupResolveRenderTargetImage>& ID) noexcept : resolveRenderTarget(ID)
	{
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

	RenderTargetImagesID::ColorRenderTargetID::ColorRenderTargetID(const IDObject<AutoCleanupColorRenderTargetImage>& ID) noexcept : ID(ID)
	{
		type = ImageIDType::COLOR_RENDER_TARGET;
	}

	RenderTargetImagesID::DepthStencilRenderTargetID::DepthStencilRenderTargetID(const IDObject<AutoCleanupDepthStencilRenderTargetImage>& ID) noexcept : ID(ID)
	{
		type = ImageIDType::DEPTH_STENCIL_RENDER_TARGET;
	}

	RenderTargetImagesID::ResolveRenderTargetID::ResolveRenderTargetID(const IDObject<AutoCleanupResolveRenderTargetImage>& ID) noexcept : ID(ID)
	{
		type = ImageIDType::RESOLVE_RENDER_TARGET;
	}

}
