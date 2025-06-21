#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSShaderLists.h"

#include <CustomLists/IDObject.h>

#include "../../../DoNotInclude/DNIData/VSDevice/VSShaderListsInternal.h"

#include "../../../DoNotInclude/DNIData/VSDevice/VSAutoCleanupFragmentShaderModule.h"
#include "../../../DoNotInclude/DNIData/VSDevice/VSAutoCleanupVertexShaderModule.h"

namespace VulkanSimplified
{
	ShaderLists::ShaderLists(ShaderListsInternal& ref) : _internal(ref)
	{
	}

	ShaderLists::~ShaderLists()
	{
	}

	IDObject<AutoCleanupFragmentShaderModule> ShaderLists::CreateFragmentShaderModule(const char& data, size_t dataSize, size_t addOnReservation)
	{
		return _internal.CreateFragmentShaderModule(data, dataSize, addOnReservation);
	}

	IDObject<AutoCleanupVertexShaderModule> ShaderLists::CreateVertexShaderModule(const char& data, size_t dataSize, size_t addOnReservation)
	{
		return _internal.CreateVertexShaderModule(data, dataSize, addOnReservation);
	}

}