#pragma once

#include <CustomLists/UnsortedIDVector.h>

namespace VulkanSimplified
{
	struct ShaderListsInitialCapacitiesList;
}

namespace VulkanSimplifiedInternal
{
	class AutoCleanupFragmentShaderModule;
	class AutoCleanupVertexShaderModule;

	class ShaderListsInternal
	{
	public:
		ShaderListsInternal(VkDevice device, const VulkanSimplified::ShaderListsInitialCapacitiesList& initialCapacities);
		~ShaderListsInternal();

		IDObject<AutoCleanupFragmentShaderModule> CreateFragmentShaderModule(const char& data, size_t dataSize, size_t addOnReservation);
		IDObject<AutoCleanupVertexShaderModule> CreateVertexShaderModule(const char& data, size_t dataSize, size_t addOnReservation);

	private:
		VkDevice _device;

		UnsortedIDVector<AutoCleanupFragmentShaderModule> _fragmentShaders;
		UnsortedIDVector<AutoCleanupVertexShaderModule> _vertexShaders;
	};
}