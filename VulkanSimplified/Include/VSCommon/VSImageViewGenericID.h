#pragma once

#include "../VSDevice/VSImageDataListsDef.h"

#include <CustomLists/IDObject.h>

namespace VulkanSimplified
{
	enum class ImageViewIDType
	{
		NONE = 0,
		COLOR = 1,
		DEPTH_STENCIL = 2,
		TEXTURE_2D = 4,
		ARRAY_TEXTURE_2D = 8,
	};

	union ImageViewGenericID
	{
		ImageViewIDType IDType;

		struct
		{
			ImageViewIDType IDType;
			IDObject<AutoCleanupColorRenderTargetImage> imageID;
			IDObject<AutoCleanupImageView> viewID;
		} colorViewID;

		struct
		{
			ImageViewIDType IDType;
			IDObject<AutoCleanupDepthStencilRenderTargetImage> imageID;
			IDObject<AutoCleanupImageView> viewID;
		} depthStencilViewID;

		struct
		{
			ImageViewIDType IDType;
			IDObject<AutoCleanup2DTexture> imageID;
			IDObject<AutoCleanupImageView> viewID;
		} texture2DViewID;

		struct
		{
			ImageViewIDType IDType;
			IDObject<AutoCleanup2DArrayTexture> imageID;
			IDObject<AutoCleanupImageView> viewID;
		} texture2DArrayViewID;

		ImageViewGenericID();
		ImageViewGenericID(IDObject<AutoCleanupColorRenderTargetImage> imageID, IDObject<AutoCleanupImageView> viewID);
		ImageViewGenericID(IDObject<AutoCleanupDepthStencilRenderTargetImage> imageID, IDObject<AutoCleanupImageView> viewID);
		ImageViewGenericID(IDObject<AutoCleanup2DTexture> imageID, IDObject<AutoCleanupImageView> viewID);
		ImageViewGenericID(IDObject<AutoCleanup2DArrayTexture> imageID, IDObject<AutoCleanupImageView> viewID);
	};
}