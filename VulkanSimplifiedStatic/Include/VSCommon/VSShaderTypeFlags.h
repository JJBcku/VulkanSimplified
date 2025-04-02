#pragma once

namespace VulkanSimplified
{
	typedef uint64_t ShaderTypeFlags;

	enum ShaderTypeFlagBit : ShaderTypeFlags
	{
		SHADER_TYPE_FRAGMENT = 0x1,
		SHADER_TYPE_VERTEX = 0x2,
	};
}