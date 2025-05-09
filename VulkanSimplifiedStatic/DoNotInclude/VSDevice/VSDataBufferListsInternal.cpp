#include "VSDeviceNIpch.h"
#include "VSDataBufferListsInternal.h"

#include "../../Include/VSDevice/VSDataBufferListsInitialCapacities.h"

#include "VSAutoCleanupVertexBuffer.h"

#include "VSDeviceCoreInternal.h"
#include "VSMemoryObjectsListInternal.h"

namespace VulkanSimplifiedInternal
{
	DataBufferListsInternal::DataBufferListsInternal(const DeviceCoreInternal& deviceCore, MemoryObjectsListInternal& memoryObjectsList, VkDevice device,
		const VulkanSimplified::DataBufferListsInitialCapacities& initialCapacities) : _deviceCore(deviceCore), _memoryObjectsList(memoryObjectsList), _device(device),
		_vertexBuffers(initialCapacities.vertexBufferListInitialCapacity)
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
		createInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;

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
			throw std::runtime_error("DataBufferListsInternal::AddVertexBuffer Error: Program failed to create");

		return _vertexBuffers.AddObject(AutoCleanupVertexBuffer(_device, add), addOnReserving);
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

	VkBuffer DataBufferListsInternal::GetVertexBuffer(IDObject<AutoCleanupVertexBuffer> bufferID) const
	{
		return _vertexBuffers.GetConstObject(bufferID).GetDataBuffer();
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

}