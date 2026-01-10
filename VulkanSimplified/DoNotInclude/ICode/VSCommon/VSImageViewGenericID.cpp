#include "VsCommonIpch.h"
#include "../../../Include/VSCommon/VSImageViewGenericID.h"

namespace VulkanSimplified
{
	ImageViewGenericID::ImageViewGenericID() noexcept
	{
		IDType = ImageViewIDType::NONE;
	}

	ImageViewGenericID::ImageViewGenericID(IDObject<AutoCleanupColorRenderTargetImage> imageID, IDObject<AutoCleanupImageView> viewID) noexcept
	{
		colorViewID.IDType = ImageViewIDType::COLOR;
		colorViewID.imageID = imageID;
		colorViewID.viewID = viewID;
	}

	ImageViewGenericID::ImageViewGenericID(IDObject<AutoCleanupDepthStencilRenderTargetImage> imageID, IDObject<AutoCleanupImageView> viewID) noexcept
	{
		depthStencilViewID.IDType = ImageViewIDType::DEPTH_STENCIL;
		depthStencilViewID.imageID = imageID;
		depthStencilViewID.viewID = viewID;
	}

	ImageViewGenericID::ImageViewGenericID(IDObject<AutoCleanup2DTexture> imageID, IDObject<AutoCleanupImageView> viewID) noexcept
	{
		texture2DViewID.IDType = ImageViewIDType::TEXTURE_2D;
		texture2DViewID.imageID = imageID;
		texture2DViewID.viewID = viewID;
	}

	ImageViewGenericID::ImageViewGenericID(IDObject<AutoCleanup2DArrayTexture> imageID, IDObject<AutoCleanupImageView> viewID) noexcept
	{
		texture2DArrayViewID.IDType = ImageViewIDType::ARRAY_TEXTURE_2D;
		texture2DArrayViewID.imageID = imageID;
		texture2DArrayViewID.viewID = viewID;
	}

	ImageViewGenericID::ImageViewGenericID(const ImageViewGenericID& rhs) noexcept
	{
		std::memcpy(this, &rhs, sizeof(ImageViewGenericID));
	}

	ImageViewGenericID::ImageViewGenericID(ImageViewGenericID&& rhs) noexcept
	{
		std::memcpy(this, &rhs, sizeof(ImageViewGenericID));
		rhs.IDType = ImageViewIDType::NONE;
	}

	ImageViewGenericID::~ImageViewGenericID()
	{
	}

	ImageViewGenericID& ImageViewGenericID::operator=(const ImageViewGenericID& rhs) noexcept
	{
		std::memcpy(this, &rhs, sizeof(ImageViewGenericID));
		return *this;
	}

	ImageViewGenericID& ImageViewGenericID::operator=(ImageViewGenericID&& rhs) noexcept
	{
		std::memcpy(this, &rhs, sizeof(ImageViewGenericID));
		rhs.IDType = ImageViewIDType::NONE;
		return *this;
	}

}
