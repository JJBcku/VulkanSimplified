#pragma once

#include "VSWindowListInitialCapacities.h"
#include "VSShaderListsInitialCapacitiesList.h"
#include "VSDescriptorListsInitialCapacities.h"
#include "VSRenderPassListInitialCapacities.h"

namespace VulkanSimplified
{
	struct DeviceInitialCapacitiesList
	{
		WindowListInitialCapacities windowList;
		ShaderListsInitialCapacitiesList shaderLists;
		DescriptorListsInitialCapacities descriptorLists;
		RenderPassDataListsInitialCapacities renderPassLists;

		DeviceInitialCapacitiesList() = default;
	};
}
