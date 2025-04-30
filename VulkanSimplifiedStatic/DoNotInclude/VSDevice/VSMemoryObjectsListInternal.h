#pragma once

#include "VSHeapInternalData.h"
#include "VSMemoryTypeInternalData.h"

#include "../../Include/VSCommon/VSMemorySuballocationFullID.h"
#include "../../Include/VSCommon/VSMemoryTypePropertiesDef.h"

namespace VulkanSimplified
{
	struct MemoryObjectsListInitialCapacities;
	struct MemoryDataList;
}

namespace VulkanSimplifiedInternal
{
	class MemoryObjectsListInternal
	{
	public:
		MemoryObjectsListInternal(VkDevice device, const VulkanSimplified::MemoryDataList& memoryHeapList, const VulkanSimplified::MemoryObjectsListInitialCapacities& initialCapacities);
		~MemoryObjectsListInternal();

		MemoryObjectsListInternal(const MemoryObjectsListInternal&) noexcept = delete;
		MemoryObjectsListInternal(MemoryObjectsListInternal&&) noexcept = delete;

		MemoryObjectsListInternal& operator=(const MemoryObjectsListInternal&) noexcept = delete;
		MemoryObjectsListInternal& operator=(MemoryObjectsListInternal&&) noexcept = delete;

		VulkanSimplified::MemoryAllocationFullID AllocateMemory(size_t memorySize, size_t initialSuballocationsReserved,
			const std::vector<VulkanSimplified::MemoryTypeProperties>& acceptableMemoryTypesProperties, std::uint32_t memoryTypeMask, size_t addOnReserve);

		std::optional<VulkanSimplified::MemoryAllocationFullID> TryToAllocateMemory(size_t memorySize, size_t initialSuballocationsReserved,
			const std::vector<VulkanSimplified::MemoryTypeProperties>& acceptableMemoryTypesProperties, std::uint32_t memoryTypeMask, size_t addOnReserve);

		bool FreeMemory(std::pair<IDObject<MemoryAllocationData>, size_t> memoryID, bool throwOnNotFound);

		size_t BindImage(VulkanSimplified::MemoryAllocationFullID allocationID, VkImage image, size_t size, size_t aligment, size_t addOnReserve);

		bool RemoveSuballocation(VulkanSimplified::MemorySuballocationFullID allocationID, bool throwOnNotFound);

	private:
		size_t heapCount;
		std::array<HeapInternalData, 16> memoryHeapData;

		size_t typeCount;
		std::array<std::optional<MemoryTypeInternalData>, 32> memoryTypeData;
	};
}