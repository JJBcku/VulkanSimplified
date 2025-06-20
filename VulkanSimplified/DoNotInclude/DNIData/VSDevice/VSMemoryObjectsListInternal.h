#pragma once

#include "VSHeapInternalData.h"
#include "VSMemoryTypeInternalData.h"

#include "../../../Include/VSCommon/VSMemorySuballocationFullID.h"
#include "../../../Include/VSCommon/VSMemoryTypePropertiesDef.h"
#include "../../../Include/VSCommon/VSMemorySizeDef.h"

#include <vector>
#include <array>
#include <optional>
#include <stdint.h>

typedef struct VkDevice_T* VkDevice;
typedef struct VkDeviceMemory_T* VkDeviceMemory;
typedef struct VkImage_T* VkImage;
typedef struct VkBuffer_T* VkBuffer;

namespace VulkanSimplified
{
	struct MemoryObjectsListInitialCapacities;
	struct MemoryDataList;
}

namespace VulkanSimplified
{
	class MemoryObjectsListInternal
	{
	public:
		MemoryObjectsListInternal(VkDevice device, const MemoryDataList& memoryHeapList, const MemoryObjectsListInitialCapacities& initialCapacities);
		~MemoryObjectsListInternal();

		MemoryObjectsListInternal(const MemoryObjectsListInternal&) noexcept = delete;
		MemoryObjectsListInternal(MemoryObjectsListInternal&&) noexcept = delete;

		MemoryObjectsListInternal& operator=(const MemoryObjectsListInternal&) noexcept = delete;
		MemoryObjectsListInternal& operator=(MemoryObjectsListInternal&&) noexcept = delete;

		MemoryAllocationFullID AllocateMemory(size_t memorySize, size_t initialSuballocationsReserved,
			const std::vector<MemoryTypeProperties>& acceptableMemoryTypesProperties, uint32_t memoryTypeMask, size_t addOnReserving);

		std::optional<MemoryAllocationFullID> TryToAllocateMemory(size_t memorySize, size_t initialSuballocationsReserved,
			const std::vector<MemoryTypeProperties>& acceptableMemoryTypesProperties, uint32_t memoryTypeMask, size_t addOnReserving);

		VkDeviceMemory GetMemory(MemoryAllocationFullID allocationID) const;

		bool FreeMemory(MemoryAllocationFullID memoryID, bool throwOnIDNotFound, bool throwOnSuballocationsNotEmpty);

		size_t BindImage(MemoryAllocationFullID allocationID, VkImage image, MemorySize size, MemorySize aligment,
			size_t addOnReserving);
		size_t BindBuffer(MemoryAllocationFullID allocationID, VkBuffer buffer, MemorySize size, MemorySize aligment,
			size_t addOnReserving);

		bool RemoveSuballocation(MemorySuballocationFullID allocationID, bool throwOnNotFound);

		void WriteToMemory(MemorySuballocationFullID suballocationID, MemorySize writeOffset, const unsigned char& writeData,
			MemorySize writeSize);

		bool IsMemoryMapped(MemoryAllocationFullID allocationID) const;

	private:
		size_t heapCount;
		std::array<HeapInternalData, 16> memoryHeapData;

		size_t typeCount;
		std::array<std::optional<MemoryTypeInternalData>, 32> memoryTypeData;
	};
}