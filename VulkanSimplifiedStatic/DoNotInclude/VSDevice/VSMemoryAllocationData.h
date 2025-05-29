#pragma once

#include "../../Include/VSCommon/VSMemorySizeDef.h"
#include "VSSuballocationInternalData.h"

namespace VulkanSimplifiedInternal
{
	class MemoryAllocationData
	{
	public:
		MemoryAllocationData(VkDevice device, VkDeviceMemory memory, VulkanSimplified::MemorySize totalSize, size_t reservedSuballocations, bool mapMemory);
		~MemoryAllocationData();

		MemoryAllocationData(const MemoryAllocationData&) noexcept = delete;
		MemoryAllocationData(MemoryAllocationData&& rhs) noexcept;

		MemoryAllocationData& operator=(const MemoryAllocationData&) noexcept = delete;
		MemoryAllocationData& operator=(MemoryAllocationData&& rhs) noexcept;

		VkDeviceMemory GetMemory() const;

		size_t GetTotalSize() const;
		size_t GetFreeSize() const;

		bool SuballocationListEmpty() const;
		size_t SuballocationListSize() const;

		size_t BindImage(VkImage image, VulkanSimplified::MemorySize size, VulkanSimplified::MemorySize aligment, size_t addOnReserving);
		size_t BindBuffer(VkBuffer buffer, VulkanSimplified::MemorySize size, VulkanSimplified::MemorySize aligment, size_t addOnReserving);

		bool RemoveSuballocation(VulkanSimplified::MemorySize beggining, bool throwOnNotFound);

		void WriteToMemory(VulkanSimplified::MemorySize suballocationBeggining, VulkanSimplified::MemorySize writeOffset, const unsigned char& writeData,
			VulkanSimplified::MemorySize writeSize);

		bool IsMemoryBound() const;

	private:
		VkDevice _device;
		VkDeviceMemory _memory;

		unsigned char* _data;

		VulkanSimplified::MemorySize _totalSize;
		VulkanSimplified::MemorySize _usedSize;
		std::vector<SuballocationInternalData> _suballocationData;

		void CheckSuballocationVectorSize(size_t addOnReserving);
		std::pair<size_t, size_t> FindMemoryAdressAndVectorIndexForSuballocation(size_t size, size_t aligment);
	};
}