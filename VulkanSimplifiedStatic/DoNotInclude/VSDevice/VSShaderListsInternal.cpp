#include "VSDeviceNIpch.h"
#include "VSShaderListsInternal.h"

#include "../../Include/VSDevice/VSShaderListsInitialCapacitiesList.h"
#include "../../Include/VSDevice/VSArbitraryShaderID.h"

#include "VSAutoCleanupFragmentShaderModule.h"
#include "VSAutoCleanupVertexShaderModule.h"

namespace VulkanSimplifiedInternal
{
	ShaderListsInternal::ShaderListsInternal(VkDevice device, const VulkanSimplified::ShaderListsInitialCapacitiesList& initialCapacities) : _device(device),
		_fragmentShaders(initialCapacities.fragmentShadersListInitialCapacity), _vertexShaders(initialCapacities.vertexShadersListInitialCapacity)
	{
	}

	ShaderListsInternal::~ShaderListsInternal()
	{
	}

	IDObject<AutoCleanupFragmentShaderModule> ShaderListsInternal::CreateFragmentShaderModule(const char& data, size_t dataSize, size_t addOnReservation)
	{
		if (dataSize == 0)
			throw std::runtime_error("ShaderListsInternal::CreateFragmentShaderModule Error: Program tried to create an empty shader!");

		if (dataSize % 4 != 0)
			throw std::runtime_error("ShaderListsInternal::CreateFragmentShaderModule Error: Program tried to use code with size that is not an integer multiple of four!");

		VkShaderModuleCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = dataSize;
		createInfo.pCode = reinterpret_cast<const std::uint32_t*>(&data);

		VkShaderModule add = VK_NULL_HANDLE;

		if (vkCreateShaderModule(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
			throw std::runtime_error("ShaderListsInternal::CreateFragmentShaderModule Error: Program failed to create shader module!");

		return _fragmentShaders.AddObject(AutoCleanupFragmentShaderModule(_device, add), addOnReservation);
	}

	IDObject<AutoCleanupVertexShaderModule> ShaderListsInternal::CreateVertexShaderModule(const char& data, size_t dataSize, size_t addOnReservation)
	{
		if (dataSize == 0)
			throw std::runtime_error("ShaderListsInternal::CreateVertexShaderModule Error: Program tried to create an empty shader!");

		if (dataSize % 4 != 0)
			throw std::runtime_error("ShaderListsInternal::CreateVertexShaderModule Error: Program tried to use code with size that is not an integer multiple of four!");

		VkShaderModuleCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = dataSize;
		createInfo.pCode = reinterpret_cast<const std::uint32_t*>(&data);

		VkShaderModule add = VK_NULL_HANDLE;

		if (vkCreateShaderModule(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
			throw std::runtime_error("ShaderListsInternal::CreateVertexShaderModule Error: Program failed to create shader module!");

		return _vertexShaders.AddObject(AutoCleanupVertexShaderModule(_device, add), addOnReservation);
	}

	VkShaderModule ShaderListsInternal::GetShaderModule(VulkanSimplified::ArbitraryShaderID shaderID) const
	{
		VkShaderModule ret = VK_NULL_HANDLE;

		switch (shaderID.type)
		{
		case VulkanSimplified::SHADER_TYPE_FRAGMENT:
			ret = GetFragmentShader(shaderID.fragmentShader.fragmentShaderID);
			break;
		case VulkanSimplified::SHADER_TYPE_VERTEX:
			ret = GetVertexShader(shaderID.vertexShader.vertexShaderID);
			break;
		default:
			throw std::runtime_error("ShaderListsInternal::GetShaderModule Error: Program was given an erroneous shader id type!");
		}

		return ret;
	}

	VkShaderModule ShaderListsInternal::GetFragmentShader(IDObject<AutoCleanupFragmentShaderModule> shaderID) const
	{
		return _fragmentShaders.GetConstObject(shaderID).GetShaderModule();
	}

	VkShaderModule ShaderListsInternal::GetVertexShader(IDObject<AutoCleanupVertexShaderModule> shaderID) const
	{
		return _vertexShaders.GetConstObject(shaderID).GetShaderModule();
	}

}