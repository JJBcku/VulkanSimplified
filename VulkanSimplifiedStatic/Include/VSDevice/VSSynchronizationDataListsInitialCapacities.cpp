#include "VSDeviceIpch.h"
#include "VSSynchronizationDataListsInitialCapacities.h"

namespace VulkanSimplified
{
	SynchronizationDataListsInitialCapacities::SynchronizationDataListsInitialCapacities()
	{
		fenceListInitialCapacity = 0;
		semaphoreListInitialCapacity = 0;
	}

	SynchronizationDataListsInitialCapacities::~SynchronizationDataListsInitialCapacities()
	{
	}

}