#include "VSDeviceIpch.h"
#include "VSMemoryObjectsListInitialCapacities.h"

#include <memory>

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