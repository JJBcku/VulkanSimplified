#pragma once

#include "VSSharedPipelineDataListsCapacities.h"

namespace VulkanSimplified
{
	struct SharedDataListsCapacities
	{
		SharedPipelineDataListsCapacities pipelineLists;

		SharedDataListsCapacities() = default;
	};
}