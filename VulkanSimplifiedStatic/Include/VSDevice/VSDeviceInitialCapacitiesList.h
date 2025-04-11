#pragma once

#include "VSDeviceWindowListInitialCapacities.h"
#include "VSShaderListsInitialCapacitiesList.h"
#include "VSDescriptorListsInitialCapacities.h"

namespace VulkanSimplified
{
	struct DeviceInitialCapacitiesList
	{
		WindowListInitialCapacities windowList;
		ShaderListsInitialCapacitiesList shaderLists;
		DescriptorListsInitialCapacities descriptorLists;

		DeviceInitialCapacitiesList() = default;
	};
}
