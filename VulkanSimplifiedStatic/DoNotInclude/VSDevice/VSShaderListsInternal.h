#pragma once

#include <CustomLists/UnsortedIDVector.h>

typedef struct VkDevice_T* VkDevice;
typedef struct VkShaderModule_T* VkShaderModule;

namespace VulkanSimplified
{
	struct ShaderListsInitialCapacitiesList;
	union ArbitraryShaderID;
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

		VkShaderModule GetShaderModule(VulkanSimplified::ArbitraryShaderID shaderID) const;

	private:
		VkDevice _device;

		UnsortedIDVector<AutoCleanupFragmentShaderModule> _fragmentShaders;
		UnsortedIDVector<AutoCleanupVertexShaderModule> _vertexShaders;

		VkShaderModule GetFragmentShader(IDObject<AutoCleanupFragmentShaderModule> shaderID) const;
		VkShaderModule GetVertexShader(IDObject<AutoCleanupVertexShaderModule> shaderID) const;
	};
}