#include "VSDeviceDNIpch.h"
#include "VSMemoryAllocationData.h"

#include "VSSuballocationInternalData.h"

namespace VulkanSimplified
{
	MemoryAllocationData::MemoryAllocationData(VkDevice device, VkDeviceMemory memory, MemorySize totalSize, size_t reservedSuballocations, bool mapMemory) :
		_device(device), _memory(memory), _totalSize(totalSize), _usedSize(0)
	{
		_data = nullptr;
		_suballocationData.reserve(reservedSuballocations);

		if (mapMemory)
		{
			if (vkMapMemory(_device, _memory, 0, VK_WHOLE_SIZE, 0, reinterpret_cast<void**>(&_data)) != VK_SUCCESS)
				throw std::runtime_error("MemoryAllocationData::MemoryAllocationData Error: Program failed to map the allocation memory!");
		}
	}

	MemoryAllocationData::~MemoryAllocationData()
	{
		if (_memory != VK_NULL_HANDLE)
		{
			vkFreeMemory(_device, _memory, nullptr);
		}
	}

	MemoryAllocationData::MemoryAllocationData(MemoryAllocationData&& rhs) noexcept : _device(rhs._device), _memory(rhs._memory), _data(rhs._data), _totalSize(rhs._totalSize),
		_usedSize(rhs._usedSize), _suballocationData(std::move(rhs._suballocationData))
	{
		rhs._device = VK_NULL_HANDLE;
		rhs._memory = VK_NULL_HANDLE;

		rhs._data = nullptr;
		rhs._totalSize = 0;
		rhs._usedSize = 0;
	}

	MemoryAllocationData& MemoryAllocationData::operator=(MemoryAllocationData&& rhs) noexcept
	{
		_device = rhs._device;
		_memory = rhs._memory;
		_data = rhs._data;
		_totalSize = rhs._totalSize;
		_usedSize = rhs._usedSize;

		rhs._device = VK_NULL_HANDLE;
		rhs._memory = VK_NULL_HANDLE;

		rhs._data = nullptr;
		rhs._totalSize = 0;
		rhs._usedSize = 0;
		return *this;
	}

	VkDeviceMemory MemoryAllocationData::GetMemory() const
	{
		return _memory;
	}

	size_t MemoryAllocationData::GetTotalSize() const
	{
		return _totalSize;
	}

	size_t MemoryAllocationData::GetFreeSize() const
	{
		assert(_totalSize >= _usedSize);
		return _totalSize - _usedSize;
	}

	bool MemoryAllocationData::SuballocationListEmpty() const
	{
		return _suballocationData.empty();
	}

	size_t MemoryAllocationData::SuballocationListSize() const
	{
		return _suballocationData.size();
	}

	size_t MemoryAllocationData::BindImage(VkImage image, MemorySize size, MemorySize aligment, size_t addOnReserving)
	{
		CheckSuballocationVectorSize(addOnReserving);

		auto memoryAddresses = FindMemoryAdressAndVectorIndexForSuballocation(size, aligment);

		if (vkBindImageMemory(_device, image, _memory, memoryAddresses.first) != VK_SUCCESS)
			throw std::runtime_error("MemoryAllocationData::BindImage Error: Program failed to bind image to memory!");

		SuballocationInternalData add;
		add.beggining = memoryAddresses.first;
		add.size = size;

		_usedSize += size;

		_suballocationData.insert(_suballocationData.begin() + static_cast<int64_t>(memoryAddresses.second), add);

		return memoryAddresses.first;
	}

	size_t MemoryAllocationData::BindBuffer(VkBuffer buffer, MemorySize size, MemorySize aligment, size_t addOnReserving)
	{
		CheckSuballocationVectorSize(addOnReserving);

		auto memoryAddresses = FindMemoryAdressAndVectorIndexForSuballocation(size, aligment);

		if (vkBindBufferMemory(_device, buffer, _memory, memoryAddresses.first) != VK_SUCCESS)
			throw std::runtime_error("MemoryAllocationData::BindBuffer Error: Program failed to bind data buffer to memory!");

		SuballocationInternalData add;
		add.beggining = memoryAddresses.first;
		add.size = size;

		_usedSize += size;

		_suballocationData.insert(_suballocationData.begin() + static_cast<int64_t>(memoryAddresses.second), add);

		return memoryAddresses.first;
	}

	bool MemoryAllocationData::RemoveSuballocation(MemorySize beggining, bool throwOnNotFound)
	{
		for (auto it = _suballocationData.begin(); it < _suballocationData.end(); ++it)
		{
			if (it->beggining == beggining)
			{
				assert(it->size <= _usedSize);
				_usedSize -= it->size;
				_suballocationData.erase(it);
				return true;
			}
		}

		if (throwOnNotFound)
			throw std::runtime_error("MemoryAllocationData::RemoveSuballocation Error: Program tried to remove non-existent suballocation!");

		return false;
	}

	void MemoryAllocationData::WriteToMemory(MemorySize suballocationBeggining, MemorySize writeOffset, const unsigned char& writeData,
		MemorySize writeSize)
	{
		if (writeOffset >= _totalSize)
			throw std::runtime_error("MemoryAllocationData::WriteToMemory Error: Program tried to write past the memory allocation!");

		std::optional<size_t> suballocationIndex;

		for (size_t i = 0; i < _suballocationData.size(); ++i)
		{
			if (_suballocationData[i].beggining == suballocationBeggining)
			{
				suballocationIndex = i;
				break;
			}
		}

		if (!suballocationIndex.has_value())
			throw std::runtime_error("MemoryAllocationData::WriteToMemory Error: Program tried to write to non-existent memory suballocation!");

		MemorySize submemSize = _suballocationData[suballocationIndex.value()].size;

		if (writeOffset > submemSize)
			throw std::runtime_error("MemoryAllocationData::WriteToMemory Error: Program tried to write past the memory suballocation!");

		if (writeSize > submemSize)
			throw std::runtime_error("MemoryAllocationData::WriteToMemory Error: Program tried to write more data there is than space in the memory suballocation!");

		MemorySize sizeLeft = submemSize - writeOffset;

		if (writeSize > sizeLeft)
			throw std::runtime_error("MemoryAllocationData::WriteToMemory Error: Program tried to write more data than there is space between the offset and suballocation's end!");

		MemorySize totalOffset = _suballocationData[suballocationIndex.value()].beggining + writeOffset;

		std::memcpy(&_data[totalOffset], &writeData, writeSize);
	}

	bool MemoryAllocationData::IsMemoryBound() const
	{
		return _data != nullptr;
	}

	void MemoryAllocationData::CheckSuballocationVectorSize(size_t addOnReserving)
	{
		if (_suballocationData.size() == _suballocationData.capacity())
		{
			if (addOnReserving == 0)
			{
				if (_suballocationData.capacity() == 0)
					_suballocationData.reserve(1);
				else
					_suballocationData.reserve(_suballocationData.capacity() << 1);
			}
			else
			{
				_suballocationData.reserve(_suballocationData.capacity() + addOnReserving);
			}
		}
	}

	std::pair<size_t, size_t> MemoryAllocationData::FindMemoryAdressAndVectorIndexForSuballocation(size_t size, size_t aligment)
	{
		std::pair<size_t, size_t> ret;

		std::optional<size_t> beggining;
		size_t currentPoint = 0;
		size_t i;

		if (_totalSize >= size)
		{
			if (_suballocationData.empty())
			{
				beggining = 0;
				i = 0;
			}
			else
			{
				for (i = 0; i < _suballocationData.size(); ++i)
				{
					if (currentPoint < _suballocationData[i].beggining)
					{
						size_t gapSize = _suballocationData[i].beggining - currentPoint;
						if (gapSize >= size)
						{
							beggining = currentPoint;
							break;
						}
					}

					currentPoint = _suballocationData[i].beggining + _suballocationData[i].size;
					if (currentPoint % aligment != 0)
					{
						currentPoint = (currentPoint / aligment) + 1;
						currentPoint *= aligment;
					}
				}

				if (!beggining.has_value() && _totalSize > currentPoint)
				{
					size_t endSize = _totalSize - currentPoint;
					if (endSize >= size)
					{
						beggining = currentPoint;
					}
				}
			}
		}
		else
			throw std::runtime_error("MemoryAllocationData::FindMemoryAdressAndVectorIndexForSuballocation Error: Program tried to suballocate memory chunk bigger than the whole memory allocation!");

		if (!beggining.has_value())
			throw std::runtime_error("MemoryAllocationData::FindMemoryAdressAndVectorIndexForSuballocation Error: Program failed to find a proper beggining point for a suballocation!");

		ret.first = beggining.value();
		ret.second = i;

		return ret;
	}
}