#include "VSDeviceNIpch.h"
#include "VSDataBufferListsInternal.h"

#include "../../../Include/VSDevice/VSDataBufferListsInitialCapacities.h"
#include "../../../Include/VSDevice/VSIndexType.h"

#include "VSAutoCleanupVertexBuffer.h"
#include "VSAutoCleanupStagingBuffer.h"
#include "VSAutoCleanupIndexBuffer.h"
#include "VSAutoCleanupUniformBuffer.h"

#include "VSDeviceCoreInternal.h"
#include "VSMemoryObjectsListInternal.h"

namespace VulkanSimplified
{
	DataBufferListsInternal::DataBufferListsInternal(const DeviceCoreInternal& deviceCore, MemoryObjectsListInternal& memoryObjectsList, VkDevice device,
		const DataBufferListsInitialCapacities& initialCapacities) : _deviceCore(deviceCore), _memoryObjectsList(memoryObjectsList), _device(device),
		_vertexBuffers(initialCapacities.vertexBufferListInitialCapacity), _stagingBuffers(initialCapacities.stagingBufferListInitialCapacity),
		_indexBuffers(initialCapacities.indexBufferListInitialCapacity), _uniformBuffers(initialCapacities.uniformBufferListInitialCapacity)
	{
	}

	DataBufferListsInternal::~DataBufferListsInternal()
	{
	}

	IDObject<AutoCleanupVertexBuffer> DataBufferListsInternal::AddVertexBuffer(MemorySize size, const std::vector<size_t>& queuesUsingBuffer, size_t addOnReserving)
	{
		VkBufferCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		createInfo.size = size;
		createInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;

		std::vector<uint32_t> queueFamilies;

		if (queuesUsingBuffer.size() > 1)
		{
			queueFamilies = _deviceCore.GetQueuesFamilies(queuesUsingBuffer);

			std::stable_sort(queueFamilies.begin(), queueFamilies.end());
			queueFamilies.erase(std::unique(queueFamilies.begin(), queueFamilies.end()), queueFamilies.end());
		}

		if (queueFamilies.size() > 1)
		{
			createInfo.sharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = static_cast<uint32_t>(queueFamilies.size());
			createInfo.pQueueFamilyIndices = queueFamilies.data();
		}
		else
		{
			createInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		}

		VkBuffer add = VK_NULL_HANDLE;

		if (vkCreateBuffer(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
			throw std::runtime_error("DataBufferListsInternal::AddVertexBuffer Error: Program failed to create a data buffer!");

		return _vertexBuffers.AddObject(AutoCleanupVertexBuffer(_device, add), addOnReserving);
	}

	IDObject<AutoCleanupStagingBuffer> DataBufferListsInternal::AddStagingBuffer(MemorySize size, const std::vector<size_t>& queuesUsingBuffer, size_t addOnReserving)
	{
		VkBufferCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		createInfo.size = size;
		createInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;

		std::vector<uint32_t> queueFamilies;

		if (queuesUsingBuffer.size() > 1)
		{
			queueFamilies = _deviceCore.GetQueuesFamilies(queuesUsingBuffer);

			std::stable_sort(queueFamilies.begin(), queueFamilies.end());
			queueFamilies.erase(std::unique(queueFamilies.begin(), queueFamilies.end()), queueFamilies.end());
		}

		if (queueFamilies.size() > 1)
		{
			createInfo.sharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = static_cast<uint32_t>(queueFamilies.size());
			createInfo.pQueueFamilyIndices = queueFamilies.data();
		}
		else
		{
			createInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		}

		VkBuffer add = VK_NULL_HANDLE;

		if (vkCreateBuffer(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
			throw std::runtime_error("DataBufferListsInternal::AddStagingBuffer Error: Program failed to create a data buffer!");

		return _stagingBuffers.AddObject(AutoCleanupStagingBuffer(_device, add), addOnReserving);
	}

	IDObject<AutoCleanupIndexBuffer> DataBufferListsInternal::AddIndexBuffer(size_t indicesCount, IndexType indexType,
		const std::vector<size_t>& queuesUsingBuffer, size_t addOnReserving)
	{
		VkBufferCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		createInfo.usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT;

		switch (indexType)
		{
		case IndexType::INDEX_TYPE_16_BITS:
			if (indicesCount > std::numeric_limits<uint32_t>::max())
				throw std::runtime_error("DataBufferListsInternal::AddIndexBuffer Error: Program was given 16 bit index count above maximum value!");
			createInfo.size = indicesCount << 1;
			break;
		case IndexType::INDEX_TYPE_32_BITS:
			if (indicesCount > (std::numeric_limits<uint32_t>::max() >> 1))
				throw std::runtime_error("DataBufferListsInternal::AddIndexBuffer Error: Program was given 32 bit index count above maximum value!");
			createInfo.size = indicesCount << 2;
			break;
		default:
			throw std::runtime_error("DataBufferListsInternal::AddIndexBuffer Error: Program was given an erroneous index type value!");
		}

		std::vector<uint32_t> queueFamilies;

		if (queuesUsingBuffer.size() > 1)
		{
			queueFamilies = _deviceCore.GetQueuesFamilies(queuesUsingBuffer);

			std::stable_sort(queueFamilies.begin(), queueFamilies.end());
			queueFamilies.erase(std::unique(queueFamilies.begin(), queueFamilies.end()), queueFamilies.end());
		}

		if (queueFamilies.size() > 1)
		{
			createInfo.sharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = static_cast<uint32_t>(queueFamilies.size());
			createInfo.pQueueFamilyIndices = queueFamilies.data();
		}
		else
		{
			createInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		}

		VkBuffer add = VK_NULL_HANDLE;

		if (vkCreateBuffer(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
			throw std::runtime_error("DataBufferListsInternal::AddIndexBuffer Error: Program failed to create a data buffer!");

		return _indexBuffers.AddObject(AutoCleanupIndexBuffer(_device, add), addOnReserving);
	}

	IDObject<AutoCleanupUniformBuffer> DataBufferListsInternal::AddUniformBuffer(MemorySize size, const std::vector<size_t>& queuesUsingBuffer, size_t addOnReserving)
	{
		VkBufferCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		createInfo.size = size;
		createInfo.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;

		std::vector<uint32_t> queueFamilies;

		if (queuesUsingBuffer.size() > 1)
		{
			queueFamilies = _deviceCore.GetQueuesFamilies(queuesUsingBuffer);

			std::stable_sort(queueFamilies.begin(), queueFamilies.end());
			queueFamilies.erase(std::unique(queueFamilies.begin(), queueFamilies.end()), queueFamilies.end());
		}

		if (queueFamilies.size() > 1)
		{
			createInfo.sharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = static_cast<uint32_t>(queueFamilies.size());
			createInfo.pQueueFamilyIndices = queueFamilies.data();
		}
		else
		{
			createInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		}

		VkBuffer add = VK_NULL_HANDLE;

		if (vkCreateBuffer(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
			throw std::runtime_error("DataBufferListsInternal::AddUniformBuffer Error: Program failed to create a data buffer!");

		return _uniformBuffers.AddObject(AutoCleanupUniformBuffer(_device, add), addOnReserving);
	}

	void DataBufferListsInternal::BindVertexBuffer(IDObject<AutoCleanupVertexBuffer> bufferID, MemoryAllocationFullID allocationID, size_t addOnReserving)
	{
		auto& bufferData = _vertexBuffers.GetObject(bufferID);

		VkBuffer buffer = bufferData.GetDataBuffer();
		size_t size = bufferData.GetBuffersSize();
		size_t aligment = bufferData.GetBuffersRequiredAligment();

		auto beggining = _memoryObjectsList.BindBuffer(allocationID, buffer, size, aligment, addOnReserving);

		bufferData.BindDataBuffer(allocationID, beggining);
	}

	void DataBufferListsInternal::BindStagingBuffer(IDObject<AutoCleanupStagingBuffer> bufferID, MemoryAllocationFullID allocationID, size_t addOnReserving)
	{
		auto& bufferData = _stagingBuffers.GetObject(bufferID);

		VkBuffer buffer = bufferData.GetDataBuffer();
		size_t size = bufferData.GetBuffersSize();
		size_t aligment = bufferData.GetBuffersRequiredAligment();

		auto beggining = _memoryObjectsList.BindBuffer(allocationID, buffer, size, aligment, addOnReserving);

		bufferData.BindDataBuffer(allocationID, beggining);
	}

	void DataBufferListsInternal::BindIndexBuffer(IDObject<AutoCleanupIndexBuffer> bufferID, MemoryAllocationFullID allocationID, size_t addOnReserving)
	{
		auto& bufferData = _indexBuffers.GetObject(bufferID);

		VkBuffer buffer = bufferData.GetDataBuffer();
		size_t size = bufferData.GetBuffersSize();
		size_t aligment = bufferData.GetBuffersRequiredAligment();

		auto beggining = _memoryObjectsList.BindBuffer(allocationID, buffer, size, aligment, addOnReserving);

		bufferData.BindDataBuffer(allocationID, beggining);
	}

	void DataBufferListsInternal::BindUniformBuffer(IDObject<AutoCleanupUniformBuffer> bufferID, MemoryAllocationFullID allocationID, size_t addOnReserving)
	{
		auto& bufferData = _uniformBuffers.GetObject(bufferID);

		VkBuffer buffer = bufferData.GetDataBuffer();
		size_t size = bufferData.GetBuffersSize();
		size_t aligment = bufferData.GetBuffersRequiredAligment();

		auto beggining = _memoryObjectsList.BindBuffer(allocationID, buffer, size, aligment, addOnReserving);

		bufferData.BindDataBuffer(allocationID, beggining);
	}

	VkBuffer DataBufferListsInternal::GetVertexBuffer(IDObject<AutoCleanupVertexBuffer> bufferID) const
	{
		return _vertexBuffers.GetConstObject(bufferID).GetDataBuffer();
	}

	VkBuffer DataBufferListsInternal::GetStagingBuffer(IDObject<AutoCleanupStagingBuffer> bufferID) const
	{
		return _stagingBuffers.GetConstObject(bufferID).GetDataBuffer();
	}

	VkBuffer DataBufferListsInternal::GetIndexBuffer(IDObject<AutoCleanupIndexBuffer> bufferID) const
	{
		return _indexBuffers.GetConstObject(bufferID).GetDataBuffer();
	}

	VkBuffer DataBufferListsInternal::GetUniformBuffer(IDObject<AutoCleanupUniformBuffer> bufferID) const
	{
		return _uniformBuffers.GetConstObject(bufferID).GetDataBuffer();
	}

	const AutoCleanupVertexBuffer& DataBufferListsInternal::GetVertexBufferInternal(IDObject<AutoCleanupVertexBuffer> bufferID) const
	{
		return _vertexBuffers.GetConstObject(bufferID);
	}

	const AutoCleanupStagingBuffer& DataBufferListsInternal::GetStagingBufferInternal(IDObject<AutoCleanupStagingBuffer> bufferID) const
	{
		return _stagingBuffers.GetConstObject(bufferID);
	}

	const AutoCleanupIndexBuffer& DataBufferListsInternal::GetIndexBufferInternal(IDObject<AutoCleanupIndexBuffer> bufferID) const
	{
		return _indexBuffers.GetConstObject(bufferID);
	}

	const AutoCleanupUniformBuffer& DataBufferListsInternal::GetUniformBufferInternal(IDObject<AutoCleanupUniformBuffer> bufferID) const
	{
		return _uniformBuffers.GetConstObject(bufferID);
	}

	bool DataBufferListsInternal::RemoveVertexBuffer(IDObject<AutoCleanupVertexBuffer> bufferID, bool throwOnIDNotFound)
	{
		if (_vertexBuffers.CheckForID(bufferID))
		{
			auto& bufferData = _vertexBuffers.GetObject(bufferID);

			auto suballocation = bufferData.GetBoundMemorySuballocationData();

			_vertexBuffers.RemoveObject(bufferID, true);

			if (suballocation.has_value())
				_memoryObjectsList.RemoveSuballocation(suballocation.value(), true);

			return true;
		}
		else if (throwOnIDNotFound)
			throw std::runtime_error("DataBufferListsInternal::RemoveVertexBuffer Error: Program failed to find buffer to be removed!");
		else
			return false;
	}

	bool DataBufferListsInternal::RemoveStagingBuffer(IDObject<AutoCleanupStagingBuffer> bufferID, bool throwOnIDNotFound)
	{
		if (_stagingBuffers.CheckForID(bufferID))
		{
			auto& bufferData = _stagingBuffers.GetObject(bufferID);

			auto suballocation = bufferData.GetBoundMemorySuballocationData();

			_stagingBuffers.RemoveObject(bufferID, true);

			if (suballocation.has_value())
				_memoryObjectsList.RemoveSuballocation(suballocation.value(), true);

			return true;
		}
		else if (throwOnIDNotFound)
			throw std::runtime_error("DataBufferListsInternal::RemoveStagingBuffer Error: Program failed to find buffer to be removed!");
		else
			return false;
	}

	bool DataBufferListsInternal::RemoveIndexBuffer(IDObject<AutoCleanupIndexBuffer> bufferID, bool throwOnIDNotFound)
	{
		if (_indexBuffers.CheckForID(bufferID))
		{
			auto& bufferData = _indexBuffers.GetObject(bufferID);

			auto suballocation = bufferData.GetBoundMemorySuballocationData();

			_indexBuffers.RemoveObject(bufferID, true);

			if (suballocation.has_value())
				_memoryObjectsList.RemoveSuballocation(suballocation.value(), true);

			return true;
		}
		else if (throwOnIDNotFound)
			throw std::runtime_error("DataBufferListsInternal::RemoveIndexBuffer Error: Program failed to find buffer to be removed!");
		else
			return false;
	}

	bool DataBufferListsInternal::RemoveUniformBuffer(IDObject<AutoCleanupUniformBuffer> bufferID, bool throwOnIDNotFound)
	{
		if (_uniformBuffers.CheckForID(bufferID))
		{
			auto& bufferData = _uniformBuffers.GetObject(bufferID);

			auto suballocation = bufferData.GetBoundMemorySuballocationData();

			_uniformBuffers.RemoveObject(bufferID, true);

			if (suballocation.has_value())
				_memoryObjectsList.RemoveSuballocation(suballocation.value(), true);

			return true;
		}
		else if (throwOnIDNotFound)
			throw std::runtime_error("DataBufferListsInternal::RemoveUniformBuffer Error: Program failed to find buffer to be removed!");
		else
			return false;
	}

	uint32_t DataBufferListsInternal::GetVertexBuffersMemoryTypeMask(IDObject<AutoCleanupVertexBuffer> bufferID) const
	{
		return _vertexBuffers.GetConstObject(bufferID).GetBuffersMemoryTypeMask();
	}

	MemorySize DataBufferListsInternal::GetVertexBuffersSize(IDObject<AutoCleanupVertexBuffer> bufferID) const
	{
		return _vertexBuffers.GetConstObject(bufferID).GetBuffersSize();
	}

	MemorySize DataBufferListsInternal::GetVertexBuffersRequiredAligment(IDObject<AutoCleanupVertexBuffer> bufferID) const
	{
		return _vertexBuffers.GetConstObject(bufferID).GetBuffersRequiredAligment();
	}

	uint32_t DataBufferListsInternal::GetStagingBuffersMemoryTypeMask(IDObject<AutoCleanupStagingBuffer> bufferID) const
	{
		return _stagingBuffers.GetConstObject(bufferID).GetBuffersMemoryTypeMask();
	}

	MemorySize DataBufferListsInternal::GetStagingBuffersSize(IDObject<AutoCleanupStagingBuffer> bufferID) const
	{
		return _stagingBuffers.GetConstObject(bufferID).GetBuffersSize();
	}

	MemorySize DataBufferListsInternal::GetStagingBuffersRequiredAligment(IDObject<AutoCleanupStagingBuffer> bufferID) const
	{
		return _stagingBuffers.GetConstObject(bufferID).GetBuffersRequiredAligment();
	}

	uint32_t DataBufferListsInternal::GetIndexBuffersMemoryTypeMask(IDObject<AutoCleanupIndexBuffer> bufferID) const
	{
		return _indexBuffers.GetConstObject(bufferID).GetBuffersMemoryTypeMask();
	}

	MemorySize DataBufferListsInternal::GetIndexBuffersSize(IDObject<AutoCleanupIndexBuffer> bufferID) const
	{
		return _indexBuffers.GetConstObject(bufferID).GetBuffersSize();
	}

	MemorySize DataBufferListsInternal::GetIndexBuffersRequiredAligment(IDObject<AutoCleanupIndexBuffer> bufferID) const
	{
		return _indexBuffers.GetConstObject(bufferID).GetBuffersRequiredAligment();
	}

	uint32_t DataBufferListsInternal::GetUniformBuffersMemoryTypeMask(IDObject<AutoCleanupUniformBuffer> bufferID) const
	{
		return _uniformBuffers.GetConstObject(bufferID).GetBuffersMemoryTypeMask();
	}

	MemorySize DataBufferListsInternal::GetUniformBuffersSize(IDObject<AutoCleanupUniformBuffer> bufferID) const
	{
		return _uniformBuffers.GetConstObject(bufferID).GetBuffersSize();
	}

	MemorySize DataBufferListsInternal::GetUniformBuffersRequiredAligment(IDObject<AutoCleanupUniformBuffer> bufferID) const
	{
		return _uniformBuffers.GetConstObject(bufferID).GetBuffersRequiredAligment();
	}

	void DataBufferListsInternal::WriteToVertexBuffer(IDObject<AutoCleanupVertexBuffer> bufferID, MemorySize writeOffset, const unsigned char& writeData,
		MemorySize dataSize)
	{
		auto& buffer = _vertexBuffers.GetObject(bufferID);

		_memoryObjectsList.WriteToMemory(buffer.GetBoundMemorySuballocationData().value(), writeOffset, writeData, dataSize);
	}

	void DataBufferListsInternal::WriteToStagingBuffer(IDObject<AutoCleanupStagingBuffer> bufferID, MemorySize writeOffset, const unsigned char& writeData,
		MemorySize dataSize)
	{
		auto& buffer = _stagingBuffers.GetObject(bufferID);

		_memoryObjectsList.WriteToMemory(buffer.GetBoundMemorySuballocationData().value(), writeOffset, writeData, dataSize);
	}

	void DataBufferListsInternal::WriteToIndexBuffer(IDObject<AutoCleanupIndexBuffer> bufferID, MemorySize writeOffset, const unsigned char& writeData,
		MemorySize dataSize)
	{
		auto& buffer = _indexBuffers.GetObject(bufferID);

		_memoryObjectsList.WriteToMemory(buffer.GetBoundMemorySuballocationData().value(), writeOffset, writeData, dataSize);
	}

	void DataBufferListsInternal::WriteToUniformBuffer(IDObject<AutoCleanupUniformBuffer> bufferID, MemorySize writeOffset, const unsigned char& writeData,
		MemorySize dataSize)
	{
		auto& buffer = _uniformBuffers.GetObject(bufferID);

		_memoryObjectsList.WriteToMemory(buffer.GetBoundMemorySuballocationData().value(), writeOffset, writeData, dataSize);
	}

}