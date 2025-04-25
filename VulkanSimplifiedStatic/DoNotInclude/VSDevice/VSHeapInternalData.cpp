#include "VSDeviceNIpch.h"
#include "VSHeapInternalData.h"

namespace VulkanSimplifiedInternal
{
	HeapInternalData::HeapInternalData()
	{
		heapSize = 0;
		usedSize = 0;
		properties = std::numeric_limits<VulkanSimplified::MemoryHeapProperties>::max();
	}

	VulkanSimplified::MemorySize HeapInternalData::GetFreeSize() const
	{
		assert(heapSize >= usedSize);

		return heapSize - usedSize;
	}
}