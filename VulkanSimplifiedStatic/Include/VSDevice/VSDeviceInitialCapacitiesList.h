#pragma once

#include "VSWindowListInitialCapacities.h"
#include "VSShaderListsInitialCapacitiesList.h"
#include "VSDescriptorListsInitialCapacities.h"
#include "VSRenderPassListInitialCapacities.h"
#include "VSPipelineDataListsInitialCapacities.h"
#include "VSMemoryObjectsListInitialCapacities.h"
#include "VSImageDataListsInitialCapacities.h"

namespace VulkanSimplified
{
	struct DeviceInitialCapacitiesList
	{
		WindowListInitialCapacities windowList;
		ShaderListsInitialCapacitiesList shaderLists;
		DescriptorListsInitialCapacities descriptorLists;
		RenderPassDataListsInitialCapacities renderPassLists;
		PipelineDataListsInitialCapacities pipelineDataLists;
		MemoryObjectsListInitialCapacities memoryObjectsList;
		ImageDataListsInitialCapacities imageLists;

		DeviceInitialCapacitiesList() = default;
	};
}
