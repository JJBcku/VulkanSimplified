#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSDataBufferListsInitialCapacities.h"

namespace VulkanSimplified
{
	DataBufferListsInitialCapacities::DataBufferListsInitialCapacities()
	{
		vertexBufferListInitialCapacity = 0;
		stagingBufferListInitialCapacity = 0;
		indexBufferListInitialCapacity = 0;
		uniformBufferListInitialCapacity = 0;
	}
}