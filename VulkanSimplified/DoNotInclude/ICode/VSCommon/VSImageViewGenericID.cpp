#include "VsCommonIpch.h"
#include "../../../Include/VSCommon/VSImageViewGenericID.h"

namespace VulkanSimplified
{
	ImageViewGenericID::ImageViewGenericID()
	{
		IDType = ImageViewIDType::NONE;
	}

	ImageViewGenericID::ImageViewGenericID(IDObject<AutoCleanupColorRenderTargetImage> imageID, IDObject<AutoCleanupImageView> viewID)
	{
		colorViewID.IDType = ImageViewIDType::COLOR;
		colorViewID.imageID = imageID;
		colorViewID.viewID = viewID;
	}

	ImageViewGenericID::ImageViewGenericID(IDObject<AutoCleanupDepthStencilRenderTargetImage> imageID, IDObject<AutoCleanupImageView> viewID)
	{
		depthStencilViewID.IDType = ImageViewIDType::DEPTH_STENCIL;
		depthStencilViewID.imageID = imageID;
		depthStencilViewID.viewID = viewID;
	}

	ImageViewGenericID::ImageViewGenericID(IDObject<AutoCleanup2DTexture> imageID, IDObject<AutoCleanupImageView> viewID)
	{
		texture2DViewID.IDType = ImageViewIDType::TEXTURE_2D;
		texture2DViewID.imageID = imageID;
		texture2DViewID.viewID = viewID;
	}

	ImageViewGenericID::ImageViewGenericID(IDObject<AutoCleanup2DArrayTexture> imageID, IDObject<AutoCleanupImageView> viewID)
	{
		texture2DArrayViewID.IDType = ImageViewIDType::ARRAY_TEXTURE_2D;
		texture2DArrayViewID.imageID = imageID;
		texture2DArrayViewID.viewID = viewID;
	}
}
