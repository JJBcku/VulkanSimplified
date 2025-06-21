#include "VSDeviceDNIpch.h"
#include "VSHeapInternalData.h"

namespace VulkanSimplified
{
	HeapInternalData::HeapInternalData()
	{
		heapSize = 0;
		usedSize = 0;
		properties = std::numeric_limits<MemoryHeapProperties>::max();
	}

	MemorySize HeapInternalData::GetFreeSize() const
	{
		assert(heapSize >= usedSize);

		return heapSize - usedSize;
	}
}