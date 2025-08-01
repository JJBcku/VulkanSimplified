#include "VSDeviceDNIpch.h"
#include "VSMemoryTypeInternalData.h"

#include "../../../Include/VSCommon/VSMemoryTypeProperties.h"

namespace VulkanSimplified
{
	MemoryTypeInternalData::MemoryTypeInternalData(VkDevice device, uint32_t heapIndex, const MemoryTypeData& memoryData,
		size_t reservedAllocation) : _device(device), _heapIndex(heapIndex), _typeIndex(memoryData.memoryIndex), _properties(memoryData.properties),
		_allocationsList(reservedAllocation)
	{
	}

	MemoryTypeInternalData::~MemoryTypeInternalData()
	{
	}

	MemoryTypeInternalData::MemoryTypeInternalData(MemoryTypeInternalData&& rhs) noexcept : _device(rhs._device), _heapIndex(rhs._heapIndex), _typeIndex(rhs._typeIndex),
		_properties(rhs._properties), _allocationsList(std::move(rhs._allocationsList))
	{
		rhs._device = VK_NULL_HANDLE;
		rhs._heapIndex = std::numeric_limits<uint32_t>::max();
		rhs._typeIndex = std::numeric_limits<uint32_t>::max();
		rhs._properties = std::numeric_limits<MemoryTypeProperties>::max();
	}

	MemoryTypeInternalData& MemoryTypeInternalData::operator=(MemoryTypeInternalData&& rhs) noexcept
	{
		_device = rhs._device;
		_heapIndex = rhs._heapIndex;
		_typeIndex = rhs._typeIndex;
		_properties = rhs._properties;
		_allocationsList = std::move(rhs._allocationsList);

		rhs._device = VK_NULL_HANDLE;
		rhs._heapIndex = std::numeric_limits<uint32_t>::max();
		rhs._typeIndex = std::numeric_limits<uint32_t>::max();
		rhs._properties = std::numeric_limits<MemoryTypeProperties>::max();
		return *this;
	}

	IDObject<MemoryAllocationData> MemoryTypeInternalData::AddMemoryAllocation(size_t dataSize, size_t initialSuballocationsReserved, size_t addOnReserving)
	{
		assert(dataSize > 0);

		VkMemoryAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize = dataSize;
		allocInfo.memoryTypeIndex = _typeIndex;

		VkDeviceMemory allocation = VK_NULL_HANDLE;

		if (vkAllocateMemory(_device, &allocInfo, nullptr, &allocation) != VK_SUCCESS)
			throw std::runtime_error("MemoryTypeInternalData::AddMemoryAllocation Error: Program failed to allocate memory!");

		bool mapMemory = IsMemoryMapped();

		return _allocationsList.AddObject(MemoryAllocationData(_device, allocation, dataSize, initialSuballocationsReserved, mapMemory), addOnReserving);
	}

	VkDeviceMemory MemoryTypeInternalData::GetMemory(IDObject<MemoryAllocationData> memoryId) const
	{
		return _allocationsList.GetConstObject(memoryId).GetMemory();
	}

	bool MemoryTypeInternalData::FreeMemory(IDObject<MemoryAllocationData> memoryId, bool throwOnIDNotFound, bool throwOnSuballocationsNotEmpty)
	{
		if (_allocationsList.CheckForID(memoryId))
		{
			if (throwOnSuballocationsNotEmpty && !_allocationsList.GetConstObject(memoryId).SuballocationListEmpty())
				throw std::runtime_error("MemoryTypeInternalData::FreeMemory Error: Program tried to delete suballocated memory!");

			return _allocationsList.RemoveObject(memoryId, true);
		}
		else if (throwOnIDNotFound)
			throw std::runtime_error("MemoryTypeInternalData::FreeMemory Error: Program tried to delete memory allocation while its still suballocated!");
		else
			return false;
	}

	uint32_t MemoryTypeInternalData::GetHeapIndex() const
	{
		return _heapIndex;
	}

	uint32_t MemoryTypeInternalData::GetTypeIndex() const
	{
		return _typeIndex;
	}

	MemoryTypeProperties MemoryTypeInternalData::GetProperties() const
	{
		return _properties;
	}

	size_t MemoryTypeInternalData::GetMemoryAllocationsSize(IDObject<MemoryAllocationData> allocationID) const
	{
		return _allocationsList.GetConstObject(allocationID).GetTotalSize();
	}

	size_t MemoryTypeInternalData::BindImage(IDObject<MemoryAllocationData> allocationID, VkImage image, MemorySize size, MemorySize aligment,
		size_t addOnReserving)
	{
		return _allocationsList.GetObject(allocationID).BindImage(image, size, aligment, addOnReserving);
	}

	size_t MemoryTypeInternalData::BindBuffer(IDObject<MemoryAllocationData> allocationID, VkBuffer buffer, MemorySize size, MemorySize aligment,
		size_t addOnReserving)
	{
		return _allocationsList.GetObject(allocationID).BindBuffer(buffer, size, aligment, addOnReserving);
	}

	bool MemoryTypeInternalData::CheckForAllocationsExistence(IDObject<MemoryAllocationData> allocationID)
	{
		return _allocationsList.CheckForID(allocationID);
	}

	bool MemoryTypeInternalData::RemoveSuballocation(IDObject<MemoryAllocationData> allocationID, size_t beggining, bool throwOnNotFound)
	{
		return _allocationsList.GetObject(allocationID).RemoveSuballocation(beggining, throwOnNotFound);
	}

	void MemoryTypeInternalData::WriteToMemory(MemorySuballocationFullID suballocationID, MemorySize writeOffset, const unsigned char& writeData,
		MemorySize writeSize)
	{
		_allocationsList.GetObject(suballocationID.first.first).WriteToMemory(suballocationID.second, writeOffset, writeData, writeSize);
	}

	bool MemoryTypeInternalData::IsMemoryMapped() const
	{
		return (_properties & HOST_VISIBLE) == HOST_VISIBLE;
	}

}