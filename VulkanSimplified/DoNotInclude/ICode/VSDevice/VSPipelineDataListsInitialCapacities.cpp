#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSPipelineDataListsInitialCapacities.h"

namespace VulkanSimplified
{
	PipelineDataListsInitialCapacities::PipelineDataListsInitialCapacities()
	{
		pipelineCacheListInitialCapacity = 0;

		pipelineLayoutListInitialCapacity = 0;
		graphicsPipelineListInitialCapacity = 0;
	}
}