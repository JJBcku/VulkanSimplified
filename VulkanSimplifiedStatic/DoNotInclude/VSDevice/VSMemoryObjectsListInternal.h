#pragma once

#include "VSHeapInternalData.h"
#include "VSMemoryTypeInternalData.h"

#include "../../Include/VSCommon/VSMemorySuballocationFullID.h"
#include "../../Include/VSCommon/VSMemoryTypePropertiesDef.h"
#include "../../Include/VSCommon/VSMemorySizeDef.h"

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
			const std::vector<VulkanSimplified::MemoryTypeProperties>& acceptableMemoryTypesProperties, uint32_t memoryTypeMask, size_t addOnReserving);

		std::optional<VulkanSimplified::MemoryAllocationFullID> TryToAllocateMemory(size_t memorySize, size_t initialSuballocationsReserved,
			const std::vector<VulkanSimplified::MemoryTypeProperties>& acceptableMemoryTypesProperties, uint32_t memoryTypeMask, size_t addOnReserving);

		VkDeviceMemory GetMemory(VulkanSimplified::MemoryAllocationFullID allocationID) const;

		bool FreeMemory(VulkanSimplified::MemoryAllocationFullID memoryID, bool throwOnIDNotFound, bool throwOnSuballocationsNotEmpty);

		size_t BindImage(VulkanSimplified::MemoryAllocationFullID allocationID, VkImage image, VulkanSimplified::MemorySize size, VulkanSimplified::MemorySize aligment,
			size_t addOnReserving);
		size_t BindBuffer(VulkanSimplified::MemoryAllocationFullID allocationID, VkBuffer buffer, VulkanSimplified::MemorySize size, VulkanSimplified::MemorySize aligment,
			size_t addOnReserving);

		bool RemoveSuballocation(VulkanSimplified::MemorySuballocationFullID allocationID, bool throwOnNotFound);

		void WriteToMemory(VulkanSimplified::MemorySuballocationFullID suballocationID, VulkanSimplified::MemorySize writeOffset, const unsigned char& writeData,
			VulkanSimplified::MemorySize writeSize);

		bool IsMemoryMapped(VulkanSimplified::MemoryAllocationFullID allocationID) const;

	private:
		size_t heapCount;
		std::array<HeapInternalData, 16> memoryHeapData;

		size_t typeCount;
		std::array<std::optional<MemoryTypeInternalData>, 32> memoryTypeData;
	};
}