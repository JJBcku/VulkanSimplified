#include "VSDeviceIpch.h"
#include "VSMemoryObjectsListInitialCapacities.h"

namespace VulkanSimplified
{
	MemoryObjectsListInitialCapacities::MemoryObjectsListInitialCapacities()
	{
		for (size_t i = 0; i < initialCapacities.size(); ++i)
		{
			initialCapacities[i] = 0;
		}
	}

	MemoryObjectsListInitialCapacities::~MemoryObjectsListInitialCapacities()
	{
	}
}