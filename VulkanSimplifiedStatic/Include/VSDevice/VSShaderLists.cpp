#include "VSDeviceIpch.h"
#include "VSShaderLists.h"

#include <CustomLists/IDObject.h>

#include "../../DoNotInclude/VSDevice/VSShaderListsInternal.h"

#include "../../DoNotInclude/VSDevice/VSAutoCleanupFragmentShaderModule.h"
#include "../../DoNotInclude/VSDevice/VSAutoCleanupVertexShaderModule.h"

namespace VulkanSimplified
{
	ShaderLists::ShaderLists(VulkanSimplifiedInternal::ShaderListsInternal& ref) : _internal(ref)
	{
	}

	ShaderLists::~ShaderLists()
	{
	}

	IDObject<VulkanSimplifiedInternal::AutoCleanupFragmentShaderModule> ShaderLists::CreateFragmentShaderModule(const char& data, size_t dataSize, size_t addOnReservation)
	{
		return _internal.CreateFragmentShaderModule(data, dataSize, addOnReservation);
	}

	IDObject<VulkanSimplifiedInternal::AutoCleanupVertexShaderModule> ShaderLists::CreateVertexShaderModule(const char& data, size_t dataSize, size_t addOnReservation)
	{
		return _internal.CreateVertexShaderModule(data, dataSize, addOnReservation);
	}

}