#pragma once

namespace VulkanSimplified
{
	struct DataBufferListsInitialCapacities
	{
		size_t vertexBufferListInitialCapacity;
		size_t stagingBufferListInitialCapacity;
		size_t indexBufferListInitialCapacity;

		DataBufferListsInitialCapacities();
	};
}