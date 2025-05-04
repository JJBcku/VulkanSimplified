#pragma once

#include <CustomLists/IDObject.h>

#include "../VSCommon/VSShaderTypeFlags.h"

namespace VulkanSimplifiedInternal
{
	class AutoCleanupFragmentShaderModule;
	class AutoCleanupVertexShaderModule;
}

namespace VulkanSimplified
{
	union ArbitraryShaderID
	{
	public:
		ShaderTypeFlagBit type;

		struct
		{
			ShaderTypeFlagBit type;
			IDObject<VulkanSimplifiedInternal::AutoCleanupFragmentShaderModule> fragmentShaderID;
		} fragmentShader;

		struct
		{
			ShaderTypeFlagBit type;
			IDObject<VulkanSimplifiedInternal::AutoCleanupVertexShaderModule> vertexShaderID;
		} vertexShader;

		ArbitraryShaderID();
		ArbitraryShaderID(IDObject<VulkanSimplifiedInternal::AutoCleanupFragmentShaderModule> fragmentShaderID);
		ArbitraryShaderID(IDObject<VulkanSimplifiedInternal::AutoCleanupVertexShaderModule> vertexShaderID);
	};
}