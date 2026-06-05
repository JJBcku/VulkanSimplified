#include "VsCommonIpch.h"
#include "../../../Include/VSCommon/VSImageViewGenericID.h"

namespace VulkanSimplified
{
	ImageViewGenericID::ImageViewGenericID() noexcept
	{
		IDType = ImageViewIDType::NONE;
	}

	ImageViewGenericID::ImageViewGenericID(const IDObject<AutoCleanupColorRenderTargetImage>& imageID, const IDObject<AutoCleanupImageView>& viewID) noexcept :
		colorViewID(imageID, viewID)
	{
	}

	ImageViewGenericID::ImageViewGenericID(const IDObject<AutoCleanupDepthStencilRenderTargetImage>& imageID, const IDObject<AutoCleanupImageView>& viewID) noexcept :
		depthStencilViewID(imageID, viewID)
	{
	}

	ImageViewGenericID::ImageViewGenericID(const IDObject<AutoCleanup2DTexture>& imageID, const IDObject<AutoCleanupImageView>& viewID) noexcept : texture2DViewID(imageID, viewID)
	{
	}

	ImageViewGenericID::ImageViewGenericID(const IDObject<AutoCleanup2DArrayTexture>& imageID, const IDObject<AutoCleanupImageView>& viewID) noexcept :
		texture2DArrayViewID(imageID, viewID)
	{
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

	ImageViewGenericID::ImageColorViewID::ImageColorViewID(const IDObject<AutoCleanupColorRenderTargetImage>& imageID, const IDObject<AutoCleanupImageView>& viewID) noexcept :
		imageID(imageID), viewID(viewID)
	{
		IDType = ImageViewIDType::COLOR;
	}

	ImageViewGenericID::ImageDepthStencilViewID::ImageDepthStencilViewID(const IDObject<AutoCleanupDepthStencilRenderTargetImage>& imageID,
		const IDObject<AutoCleanupImageView>& viewID) noexcept : imageID(imageID), viewID(viewID)
	{
		IDType = ImageViewIDType::DEPTH_STENCIL;
	}

	ImageViewGenericID::Texture2DViewID::Texture2DViewID(const IDObject<AutoCleanup2DTexture>& imageID, const IDObject<AutoCleanupImageView>& viewID) noexcept :
		imageID(imageID), viewID(viewID)
	{
		IDType = ImageViewIDType::TEXTURE_2D;
	}

	ImageViewGenericID::Texture2DArrayViewID::Texture2DArrayViewID(const IDObject<AutoCleanup2DArrayTexture>& imageID, const IDObject<AutoCleanupImageView>& viewID) noexcept :
		imageID(imageID), viewID(viewID)
	{
		IDType = ImageViewIDType::ARRAY_TEXTURE_2D;
	}

}
