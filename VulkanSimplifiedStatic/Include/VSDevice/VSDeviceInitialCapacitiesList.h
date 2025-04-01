#pragma once

#include "VSDeviceWindowListInitialCapacities.h"
#include "VSShaderListsInitialCapacitiesList.h"

namespace VulkanSimplified
{
	struct DeviceInitialCapacitiesList
	{
		WindowListInitialCapacities windowList;
		ShaderListsInitialCapacitiesList shaderLists;

		DeviceInitialCapacitiesList() = default;
	};
}
