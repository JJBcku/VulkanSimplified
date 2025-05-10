#include "VSDeviceNIpch.h"
#include "VSDataBufferListsInternal.h"

#include "../../Include/VSDevice/VSDataBufferListsInitialCapacities.h"

#include "VSAutoCleanupVertexBuffer.h"
#include "VSAutoCleanupStagingBuffer.h"

#include "VSDeviceCoreInternal.h"
#include "VSMemoryObjectsListInternal.h"

namespace VulkanSimplifiedInternal
{
	DataBufferListsInternal::DataBufferListsInternal(const DeviceCoreInternal& deviceCore, MemoryObjectsListInternal& memoryObjectsList, VkDevice device,
		const VulkanSimplified::DataBufferListsInitialCapacities& initialCapacities) : _deviceCore(deviceCore), _memoryObjectsList(memoryObjectsList), _device(device),
		_vertexBuffers(initialCapacities.vertexBufferListInitialCapacity), _stagingBuffers(initialCapacities.stagingBufferListInitialCapacity)
	{
	}

	DataBufferListsInternal::~DataBufferListsInternal()
	{
	}

	IDObject<AutoCleanupVertexBuffer> DataBufferListsInternal::AddVertexBuffer(VulkanSimplified::MemorySize size, const std::vector<size_t>& queuesUsingBuffer, size_t addOnReserving)
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
			createInfo.queueFamilyIndexCount = static_cast<std::uint32_t>(queueFamilies.size());
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

	IDObject<AutoCleanupStagingBuffer> DataBufferListsInternal::AddStagingBuffer(VulkanSimplified::MemorySize size, const std::vector<size_t>& queuesUsingBuffer, size_t addOnReserving)
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
			createInfo.queueFamilyIndexCount = static_cast<std::uint32_t>(queueFamilies.size());
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

	void DataBufferListsInternal::BindVertexBuffer(IDObject<AutoCleanupVertexBuffer> bufferID, VulkanSimplified::MemoryAllocationFullID allocationID, size_t addOnReserving)
	{
		auto& bufferData = _vertexBuffers.GetObject(bufferID);

		VkBuffer buffer = bufferData.GetDataBuffer();
		size_t size = bufferData.GetBuffersSize();
		size_t aligment = bufferData.GetBuffersRequiredAligment();

		auto beggining = _memoryObjectsList.BindBuffer(allocationID, buffer, size, aligment, addOnReserving);

		bufferData.BindDataBuffer(allocationID, beggining);
	}

	void DataBufferListsInternal::BindStagingBuffer(IDObject<AutoCleanupStagingBuffer> bufferID, VulkanSimplified::MemoryAllocationFullID allocationID, size_t addOnReserving)
	{
		auto& bufferData = _stagingBuffers.GetObject(bufferID);

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

	uint32_t DataBufferListsInternal::GetVertexBuffersMemoryTypeMask(IDObject<AutoCleanupVertexBuffer> bufferID) const
	{
		return _vertexBuffers.GetConstObject(bufferID).GetBuffersMemoryTypeMask();
	}

	VulkanSimplified::MemorySize DataBufferListsInternal::GetVertexBuffersSize(IDObject<AutoCleanupVertexBuffer> bufferID) const
	{
		return _vertexBuffers.GetConstObject(bufferID).GetBuffersSize();
	}

	VulkanSimplified::MemorySize DataBufferListsInternal::GetVertexBuffersRequiredAligment(IDObject<AutoCleanupVertexBuffer> bufferID) const
	{
		return _vertexBuffers.GetConstObject(bufferID).GetBuffersRequiredAligment();
	}

	uint32_t DataBufferListsInternal::GetStagingBuffersMemoryTypeMask(IDObject<AutoCleanupStagingBuffer> bufferID) const
	{
		return _stagingBuffers.GetConstObject(bufferID).GetBuffersMemoryTypeMask();
	}

	VulkanSimplified::MemorySize DataBufferListsInternal::GetStagingBuffersSize(IDObject<AutoCleanupStagingBuffer> bufferID) const
	{
		return _stagingBuffers.GetConstObject(bufferID).GetBuffersSize();
	}

	VulkanSimplified::MemorySize DataBufferListsInternal::GetStagingBuffersRequiredAligment(IDObject<AutoCleanupStagingBuffer> bufferID) const
	{
		return _stagingBuffers.GetConstObject(bufferID).GetBuffersRequiredAligment();
	}

	void DataBufferListsInternal::WriteToStagingBuffer(IDObject<AutoCleanupStagingBuffer> bufferID, VulkanSimplified::MemorySize writeOffset, const unsigned char& writeData,
		VulkanSimplified::MemorySize dataSize)
	{
		auto& buffer = _stagingBuffers.GetObject(bufferID);

		_memoryObjectsList.WriteToMemory(buffer.GetBoundMemorySuballocationData().value(), writeOffset, writeData, dataSize);
	}

}