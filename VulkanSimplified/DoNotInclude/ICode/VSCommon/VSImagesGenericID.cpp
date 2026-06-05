#include "VSCommonIpch.h"
#include "../../../Include/VSCommon/VSImagesGenericID.h"

namespace VulkanSimplified
{
	ImagesGenericID::ImagesGenericID() noexcept
	{
		type = ImagesIDType::UNKNOWN;
	}

	ImagesGenericID::ImagesGenericID(const IDObject<AutoCleanupColorRenderTargetImage>& ID) noexcept : colorRenderTarget(ID)
	{
	}

	ImagesGenericID::ImagesGenericID(const IDObject<AutoCleanup2DTexture>& ID) noexcept : texture2D(ID)
	{
	}

	ImagesGenericID::ImagesGenericID(const IDObject<AutoCleanup2DArrayTexture>& ID) noexcept : textureArray2D(ID)
	{
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

	ImagesGenericID::ImagesColorRenderTargetID::ImagesColorRenderTargetID(const IDObject<AutoCleanupColorRenderTargetImage>& ID) noexcept : ID(ID)
	{
		type = ImagesIDType::COLOR_RENDER_TARGET;
	}

	ImagesGenericID::ImagesTexture2DID::ImagesTexture2DID(const IDObject<AutoCleanup2DTexture>& ID) noexcept : ID(ID)
	{
		type = ImagesIDType::TEXTURE_2D;

		baseMipLevel = 0;
		mipLevelPadding = 0;
		mipLevelCount = {};
	}

	ImagesGenericID::ImagesTexture2DArrayID::ImagesTexture2DArrayID(const IDObject<AutoCleanup2DArrayTexture>& ID) noexcept : ID(ID)
	{
		type = ImagesIDType::TEXTURE_2D_ARRAY;

		baseMipLevel = 0;
		mipLevelCount = {};

		baseArrayLayer = 0;
		arrayLayersCount = {};
	}

}