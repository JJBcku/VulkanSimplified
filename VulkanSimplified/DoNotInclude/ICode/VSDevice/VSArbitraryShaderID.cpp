#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSArbitraryShaderID.h"

namespace VulkanSimplified
{
	ArbitraryShaderID::ArbitraryShaderID() noexcept
	{
		type = static_cast<ShaderTypeFlagBit>(0);
	}

	ArbitraryShaderID::ArbitraryShaderID(IDObject<AutoCleanupFragmentShaderModule> fragmentShaderID) noexcept
	{
		type = SHADER_TYPE_FRAGMENT;
		fragmentShader.fragmentShaderID = fragmentShaderID;
	}

	ArbitraryShaderID::ArbitraryShaderID(IDObject<AutoCleanupVertexShaderModule> vertexShaderID) noexcept
	{
		type = SHADER_TYPE_VERTEX;
		vertexShader.vertexShaderID = vertexShaderID;
	}

	ArbitraryShaderID::ArbitraryShaderID(const ArbitraryShaderID& rhs) noexcept
	{
		std::memcpy(this, &rhs, sizeof(ArbitraryShaderID));
	}

	ArbitraryShaderID::ArbitraryShaderID(ArbitraryShaderID&& rhs) noexcept
	{
		std::memcpy(this, &rhs, sizeof(ArbitraryShaderID));
		rhs.type = static_cast<ShaderTypeFlagBit>(0);
	}

	ArbitraryShaderID::~ArbitraryShaderID()
	{
	}

	ArbitraryShaderID& ArbitraryShaderID::operator=(const ArbitraryShaderID& rhs) noexcept
	{
		std::memcpy(this, &rhs, sizeof(ArbitraryShaderID));
		return *this;
	}

	ArbitraryShaderID& ArbitraryShaderID::operator=(ArbitraryShaderID&& rhs) noexcept
	{
		std::memcpy(this, &rhs, sizeof(ArbitraryShaderID));
		rhs.type = static_cast<ShaderTypeFlagBit>(0);
		return *this;
	}

}