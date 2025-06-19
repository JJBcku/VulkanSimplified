#include "VSDeviceNIpch.h"
#include "../../DNIHeaders/VSDevice/VSMemoryObjectsListInternal.h"

#include "../../../Include/VSCommon/VSMemoryDataList.h"

#include "../../../Include/VSDevice/VSMemoryObjectsListInitialCapacities.h"

namespace VulkanSimplifiedInternal
{
	MemoryObjectsListInternal::MemoryObjectsListInternal(VkDevice device, const VulkanSimplified::MemoryDataList& memoryHeapList,
		const VulkanSimplified::MemoryObjectsListInitialCapacities& initialCapacities)
	{
		heapCount = memoryHeapList.heapAmount;

		for (size_t i = 0; i < heapCount; ++i)
		{
			memoryHeapData[i].heapSize = memoryHeapList.memoryHeaps[i].size;
			memoryHeapData[i].properties = memoryHeapList.memoryHeaps[i].properties;
		}

		typeCount = 0;

		for (size_t i = 0; i < heapCount; i++)
		{
			for (size_t j = 0; j < memoryHeapList.memoryHeaps[i].memoryTypeAmount; j++)
			{
				memoryTypeData[typeCount++].emplace(device, static_cast<uint32_t>(i), memoryHeapList.memoryHeaps[i].memoryTypes[j],
					initialCapacities.initialCapacities[memoryHeapList.memoryHeaps[i].memoryTypes[j].memoryIndex]);
			}
		}
	}

	MemoryObjectsListInternal::~MemoryObjectsListInternal()
	{
	}

	VulkanSimplified::MemoryAllocationFullID MemoryObjectsListInternal::AllocateMemory(size_t memorySize, size_t initialSuballocationsReserved,
		const std::vector<VulkanSimplified::MemoryTypeProperties>& acceptableMemoryTypesProperties, uint32_t memoryTypeMask, size_t addOnReserving)
	{
		std::optional<VulkanSimplified::MemoryAllocationFullID> ret;
		assert(memorySize > 0);
		assert(memoryTypeMask > 0);
		assert(!acceptableMemoryTypesProperties.empty());

		for (size_t i = 0; i < acceptableMemoryTypesProperties.size(); ++i)
		{
			for (size_t j = 0; j < typeCount; ++j)
			{
				if (acceptableMemoryTypesProperties[i] != memoryTypeData[j].value().GetProperties())
					continue;

				uint32_t memoryBit = 1U << memoryTypeData[j].value().GetTypeIndex();

				if ((memoryTypeMask & memoryBit) != memoryBit)
					continue;

				size_t heapIndex = memoryTypeData[j].value().GetHeapIndex();

				if (memoryHeapData[heapIndex].GetFreeSize() < memorySize)
					continue;

				ret.emplace(memoryTypeData[j].value().AddMemoryAllocation(memorySize, initialSuballocationsReserved, addOnReserving), j);

				memoryHeapData[heapIndex].usedSize += memorySize;

				if (ret.has_value())
					return ret.value();
			}
		}

		throw std::runtime_error("MemoryObjectsListInternal::AddMemoryAllocation Error: Program failed to allocate memory!");
	}

	std::optional<VulkanSimplified::MemoryAllocationFullID> MemoryObjectsListInternal::TryToAllocateMemory(size_t memorySize, size_t initialSuballocationsReserved,
		const std::vector<VulkanSimplified::MemoryTypeProperties>& acceptableMemoryTypesProperties, uint32_t memoryTypeMask, size_t addOnReserving)
	{
		std::optional<VulkanSimplified::MemoryAllocationFullID> ret;

		assert(memorySize > 0);
		assert(memoryTypeMask > 0);
		assert(!acceptableMemoryTypesProperties.empty());

		for (size_t i = 0; i < acceptableMemoryTypesProperties.size(); ++i)
		{
			for (size_t j = 0; j < typeCount; ++j)
			{
				if (acceptableMemoryTypesProperties[i] != memoryTypeData[j].value().GetProperties())
					continue;

				uint32_t memoryBit = 1U << memoryTypeData[j].value().GetTypeIndex();

				if ((memoryTypeMask & memoryBit) != memoryBit)
					continue;

				size_t heapIndex = memoryTypeData[j].value().GetHeapIndex();

				if (memoryHeapData[heapIndex].GetFreeSize() < memorySize)
					continue;

				ret.emplace(memoryTypeData[j].value().AddMemoryAllocation(memorySize, initialSuballocationsReserved, addOnReserving), j);
				memoryHeapData[heapIndex].usedSize += memorySize;

				if (ret.has_value())
					break;
			}

			if (ret.has_value())
				break;
		}

		return ret;
	}

	VkDeviceMemory MemoryObjectsListInternal::GetMemory(VulkanSimplified::MemoryAllocationFullID allocationID) const
	{
		if (allocationID.second >= typeCount)
			throw std::runtime_error("MemoryObjectsListInternal::GetMemory Error: Program tried to access a non-existent memory type!");

		return memoryTypeData[allocationID.second].value().GetMemory(allocationID.first);
	}

	size_t MemoryObjectsListInternal::BindImage(VulkanSimplified::MemoryAllocationFullID allocationID, VkImage image, VulkanSimplified::MemorySize size,
		VulkanSimplified::MemorySize aligment, size_t addOnReserving)
	{
		if (allocationID.second >= typeCount)
			throw std::runtime_error("MemoryObjectsListInternal::BindImage Error: Program tried to access a non-existent memory type!");

		return memoryTypeData[allocationID.second].value().BindImage(allocationID.first, image, size, aligment, addOnReserving);
	}

	size_t MemoryObjectsListInternal::BindBuffer(VulkanSimplified::MemoryAllocationFullID allocationID, VkBuffer buffer, VulkanSimplified::MemorySize size, VulkanSimplified::MemorySize aligment, size_t addOnReserving)
	{
		if (allocationID.second >= typeCount)
			throw std::runtime_error("MemoryObjectsListInternal::BindBuffer Error: Program tried to access a non-existent memory type!");

		return memoryTypeData[allocationID.second].value().BindBuffer(allocationID.first, buffer, size, aligment, addOnReserving);
	}

	bool MemoryObjectsListInternal::RemoveSuballocation(VulkanSimplified::MemorySuballocationFullID allocationID, bool throwOnNotFound)
	{
		if (allocationID.first.second >= typeCount)
			throw std::runtime_error("MemoryObjectsListInternal::RemoveSuballocation Error: Program tried to access a non-existent memory type!");

		return memoryTypeData[allocationID.first.second].value().RemoveSuballocation(allocationID.first.first, allocationID.second, throwOnNotFound);
	}

	void MemoryObjectsListInternal::WriteToMemory(VulkanSimplified::MemorySuballocationFullID suballocationID, VulkanSimplified::MemorySize writeOffset,
		const unsigned char& writeData, VulkanSimplified::MemorySize writeSize)
	{
		memoryTypeData[suballocationID.first.second].value().WriteToMemory(suballocationID, writeOffset, writeData, writeSize);
	}

	bool MemoryObjectsListInternal::IsMemoryMapped(VulkanSimplified::MemoryAllocationFullID allocationID) const
	{
		return memoryTypeData[allocationID.second].value().IsMemoryMapped();
	}

	bool MemoryObjectsListInternal::FreeMemory(VulkanSimplified::MemoryAllocationFullID memoryID, bool throwOnIDNotFound, bool throwOnSuballocationsNotEmpty)
	{
		if (memoryID.second >= typeCount)
			throw std::runtime_error("MemoryObjectsListInternal::FreeMemory Error: Program tried to access a non-existent memory type!");

		auto& memType = memoryTypeData[memoryID.second];
		assert(memType.has_value());

		bool ret = memType.value().CheckForAllocationsExistence(memoryID.first);

		if (!ret && throwOnIDNotFound)
			throw std::runtime_error("MemoryObjectsListInternal::FreeMemory Error: Program tried to free non-existent memory allocation!");

		if (ret)
		{
			auto& memHeap = memoryHeapData[memType.value().GetHeapIndex()];
			size_t memorySize = memType.value().GetMemoryAllocationsSize(memoryID.first);
			assert(memHeap.usedSize >= memorySize);
			memHeap.usedSize -= memorySize;
			ret = memType.value().FreeMemory(memoryID.first, throwOnIDNotFound, throwOnSuballocationsNotEmpty);
		}

		return ret;
	}
}