#include "VSCommonIpch.h"
#include "../../../Include/VSCommon/VSImagesGenericID.h"

namespace VulkanSimplified
{
	ImagesGenericID::ImagesGenericID() noexcept
	{
		type = ImagesIDType::UNKNOWN;
	}

	ImagesGenericID::ImagesGenericID(IDObject<AutoCleanupColorRenderTargetImage> ID) noexcept
	{
		colorRenderTarget.type = ImagesIDType::COLOR_RENDER_TARGET;
		colorRenderTarget.ID = ID;
	}

	ImagesGenericID::ImagesGenericID(IDObject<AutoCleanup2DTexture> ID) noexcept
	{
		texture2D.type = ImagesIDType::TEXTURE_2D;
		texture2D.ID = ID;

		texture2D.baseMipLevel = 0;
		texture2D.mipLevelCount = {};
	}

	ImagesGenericID::ImagesGenericID(IDObject<AutoCleanup2DArrayTexture> ID) noexcept
	{
		textureArray2D.type = ImagesIDType::TEXTURE_2D_ARRAY;
		textureArray2D.ID = ID;

		textureArray2D.baseMipLevel = 0;
		textureArray2D.mipLevelCount = {};

		textureArray2D.baseArrayLayer = 0;
		textureArray2D.arrayLayersCount = {};
	}

	ImagesGenericID::ImagesGenericID(const ImagesGenericID& rhs) noexcept
	{
		std::memcpy(this, &rhs, sizeof(ImagesGenericID));
	}

	ImagesGenericID::ImagesGenericID(ImagesGenericID&& rhs) noexcept
	{
		std::memcpy(this, &rhs, sizeof(ImagesGenericID));
		rhs.type = ImagesIDType::UNKNOWN;
	}

	ImagesGenericID::~ImagesGenericID()
	{
	}

	ImagesGenericID& ImagesGenericID::operator=(const ImagesGenericID& rhs) noexcept
	{
		std::memcpy(this, &rhs, sizeof(ImagesGenericID));
		return *this;
	}

	ImagesGenericID& ImagesGenericID::operator=(ImagesGenericID&& rhs) noexcept
	{
		std::memcpy(this, &rhs, sizeof(ImagesGenericID));
		rhs.type = ImagesIDType::UNKNOWN;
		return *this;
	}

}