#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSArbitraryShaderID.h"

namespace VulkanSimplified
{
	ArbitraryShaderID::ArbitraryShaderID()
	{
		type = static_cast<ShaderTypeFlagBit>(0);
	}

	ArbitraryShaderID::ArbitraryShaderID(IDObject<AutoCleanupFragmentShaderModule> fragmentShaderID)
	{
		type = SHADER_TYPE_FRAGMENT;
		fragmentShader.fragmentShaderID = fragmentShaderID;
	}

	ArbitraryShaderID::ArbitraryShaderID(IDObject<AutoCleanupVertexShaderModule> vertexShaderID)
	{
		type = SHADER_TYPE_VERTEX;
		vertexShader.vertexShaderID = vertexShaderID;
	}
}