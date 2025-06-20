#pragma once

#include "../../../Include/VSCommon/VSMemorySizeDef.h"

typedef struct VkDevice_T* VkDevice;
typedef struct VkDeviceMemory_T* VkDeviceMemory;
typedef struct VkImage_T* VkImage;
typedef struct VkBuffer_T* VkBuffer;

#include <vector>
#include <utility>

namespace VulkanSimplified
{
	struct SuballocationInternalData;

	class MemoryAllocationData
	{
	public:
		MemoryAllocationData(VkDevice device, VkDeviceMemory memory, MemorySize totalSize, size_t reservedSuballocations, bool mapMemory);
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

		size_t BindImage(VkImage image, MemorySize size, MemorySize aligment, size_t addOnReserving);
		size_t BindBuffer(VkBuffer buffer, MemorySize size, MemorySize aligment, size_t addOnReserving);

		bool RemoveSuballocation(MemorySize beggining, bool throwOnNotFound);

		void WriteToMemory(MemorySize suballocationBeggining, MemorySize writeOffset, const unsigned char& writeData,
			MemorySize writeSize);

		bool IsMemoryBound() const;

	private:
		VkDevice _device;
		VkDeviceMemory _memory;

		unsigned char* _data;

		MemorySize _totalSize;
		MemorySize _usedSize;
		std::vector<SuballocationInternalData> _suballocationData;

		void CheckSuballocationVectorSize(size_t addOnReserving);
		std::pair<size_t, size_t> FindMemoryAdressAndVectorIndexForSuballocation(size_t size, size_t aligment);
	};
}