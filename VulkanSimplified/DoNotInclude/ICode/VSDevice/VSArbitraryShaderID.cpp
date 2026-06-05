#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSArbitraryShaderID.h"

namespace VulkanSimplified
{
	ArbitraryShaderID::ArbitraryShaderID() noexcept
	{
		type = static_cast<ShaderTypeFlagBit>(0);
	}

	ArbitraryShaderID::ArbitraryShaderID(const IDObject<AutoCleanupFragmentShaderModule>& fragmentShaderID) noexcept : fragmentShader(fragmentShaderID)
	{
	}

	ArbitraryShaderID::ArbitraryShaderID(const IDObject<AutoCleanupVertexShaderModule>& vertexShaderID) noexcept : vertexShader(vertexShaderID)
	{
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

	ArbitraryShaderID::FragmentShaderID::FragmentShaderID(const IDObject<AutoCleanupFragmentShaderModule>& fragmentShaderID) noexcept : fragmentShaderID(fragmentShaderID)
	{
		type = SHADER_TYPE_FRAGMENT;
	}

	ArbitraryShaderID::VertexShaderID::VertexShaderID(const IDObject<AutoCleanupVertexShaderModule>& vertexShaderID) noexcept : vertexShaderID(vertexShaderID)
	{
		type = SHADER_TYPE_VERTEX;
	}

}