#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSShaderLists.h"

#include <CustomLists/IDObject.h>

#include "../../../DoNotInclude/DNIHeaders/VSDevice/VSShaderListsInternal.h"

#include "../../../DoNotInclude/DNIHeaders/VSDevice/VSAutoCleanupFragmentShaderModule.h"
#include "../../../DoNotInclude/DNIHeaders/VSDevice/VSAutoCleanupVertexShaderModule.h"

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