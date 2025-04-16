#include "VSDeviceIpch.h"
#include "VSArbitraryShaderID.h"

namespace VulkanSimplified
{
	ArbitraryShaderID::ArbitraryShaderID()
	{
		type = static_cast<ShaderTypeFlagBit>(0);
	}

	ArbitraryShaderID::ArbitraryShaderID(IDObject<VulkanSimplifiedInternal::AutoCleanupFragmentShaderModule> fragmentShaderID)
	{
		type = SHADER_TYPE_FRAGMENT;
		fragmentShader.fragmentShaderID = fragmentShaderID;
	}

	ArbitraryShaderID::ArbitraryShaderID(IDObject<VulkanSimplifiedInternal::AutoCleanupVertexShaderModule> vertexShaderID)
	{
		type = SHADER_TYPE_VERTEX;
		vertexShader.vertexShaderID = vertexShaderID;
	}
}