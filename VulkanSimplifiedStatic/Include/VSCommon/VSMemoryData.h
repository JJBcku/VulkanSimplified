#pragma once

namespace VulkanSimplified
{
	typedef uint64_t MemoryTypeProperties;

	enum MemoryTypePropertyFlags : MemoryTypeProperties
	{
		DEVICE_LOCAL = 0x1,
		HOST_VISIBLE = 0x2,
		HOST_COHERENT = 0x4,
		HOST_CACHED = 0x8,
		LAZYLY_ALLOCATED = 0x10,
		PROTECTED = 0x20,
	};

	struct MemoryTypeData
	{
		size_t memoryIndex;
		MemoryTypeProperties properties;

		MemoryTypeData();
	};

	typedef std::uint64_t MemoryHeapProperties;

	enum MemoryHeapPropertyFlags : MemoryHeapProperties
	{
		DEVICE_LOCAL_HEAP = 0x1,
		MULTI_INSTANCE_HEAP = 0X2,
	};

	typedef std::uint64_t MemorySize;

	struct MemoryHeapData
	{
		MemorySize size;
		MemoryHeapProperties properties;

		size_t memoryTypeAmount;
		std::array<MemoryTypeData, VK_MAX_MEMORY_TYPES> memoryTypes;

		MemoryHeapData();
	};

	struct MemoryDataList
	{
		size_t heapAmount;
		std::array<MemoryHeapData, VK_MAX_MEMORY_HEAPS> memoryHeaps;

		MemoryDataList();
	};
}