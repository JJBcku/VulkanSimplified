#pragma once

#include <CustomLists\IDObjectDef.h>

namespace VulkanSimplifiedInternal
{
	class ShaderListsInternal;
	class AutoCleanupFragmentShaderModule;
	class AutoCleanupVertexShaderModule;
}

namespace VulkanSimplified
{
	class ShaderLists
	{
	public:
		ShaderLists(VulkanSimplifiedInternal::ShaderListsInternal& ref);
		~ShaderLists();

		IDObject<VulkanSimplifiedInternal::AutoCleanupFragmentShaderModule> CreateFragmentShaderModule(const char& data, size_t dataSize, size_t addOnReservation = 0);
		IDObject<VulkanSimplifiedInternal::AutoCleanupVertexShaderModule> CreateVertexShaderModule(const char& data, size_t dataSize, size_t addOnReservation = 0);

	private:
		VulkanSimplifiedInternal::ShaderListsInternal& _internal;
	};
}