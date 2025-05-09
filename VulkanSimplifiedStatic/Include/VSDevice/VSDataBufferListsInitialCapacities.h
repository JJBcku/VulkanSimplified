#pragma once

namespace VulkanSimplified
{
	struct DataBufferListsInitialCapacities
	{
		size_t vertexBufferListInitialCapacity;
		size_t stagingBufferListInitialCapacity;

		DataBufferListsInitialCapacities();
	};
}