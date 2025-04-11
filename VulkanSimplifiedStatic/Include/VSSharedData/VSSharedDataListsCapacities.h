#pragma once

#include "VSSharedPipelineDataListsCapacities.h"
#include "VSSharedDescriptorDataListCapacities.h"

namespace VulkanSimplified
{
	struct SharedDataListsCapacities
	{
		SharedDescriptorDataListCapacities descriptorLists;
		SharedPipelineDataListsCapacities pipelineLists;

		SharedDataListsCapacities() = default;
	};
}