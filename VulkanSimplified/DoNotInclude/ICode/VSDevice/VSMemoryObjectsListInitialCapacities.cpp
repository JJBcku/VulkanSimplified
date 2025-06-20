#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSMemoryObjectsListInitialCapacities.h"

namespace VulkanSimplified
{
	MemoryObjectsListInitialCapacities::MemoryObjectsListInitialCapacities()
	{
		std::memset(initialCapacities.data(), 0, initialCapacities.size() * sizeof(initialCapacities[0]));
	}

	MemoryObjectsListInitialCapacities::~MemoryObjectsListInitialCapacities()
	{
	}
}