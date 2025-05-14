#include "VSDeviceIpch.h"
#include "VSDataBufferLists.h"

#include "../../DoNotInclude/VSDevice/VSDataBufferListsInternal.h"

namespace VulkanSimplified
{
	DataBufferLists::DataBufferLists(VulkanSimplifiedInternal::DataBufferListsInternal& ref) : _internal(ref)
	{
	}

	DataBufferLists::~DataBufferLists()
	{
	}

	IDObject<VulkanSimplifiedInternal::AutoCleanupVertexBuffer> DataBufferLists::AddVertexBuffer(MemorySize size, const std::vector<size_t>& queuesUsingBuffer, size_t addOnReserving)
	{
		return _internal.AddVertexBuffer(size, queuesUsingBuffer, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer> DataBufferLists::AddStagingBuffer(MemorySize size, const std::vector<size_t>& queuesUsingBuffer, size_t addOnReserving)
	{
		return _internal.AddStagingBuffer(size, queuesUsingBuffer, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::AutoCleanupIndexBuffer> DataBufferLists::AddIndexBuffer(size_t indicesCount, IndexType indexType,
		const std::vector<size_t>& queuesUsingBuffer, size_t addOnReserving)
	{
		return _internal.AddIndexBuffer(indicesCount, indexType, queuesUsingBuffer, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::AutoCleanupUniformBuffer> DataBufferLists::AddUniformBuffer(MemorySize size, const std::vector<size_t>& queuesUsingBuffer, size_t addOnReserving)
	{
		return _internal.AddUniformBuffer(size, queuesUsingBuffer, addOnReserving);
	}

	void DataBufferLists::BindVertexBuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupVertexBuffer> bufferID, MemoryAllocationFullID allocationID,
		size_t addOnReserving)
	{
		_internal.BindVertexBuffer(bufferID, allocationID, addOnReserving);
	}

	void DataBufferLists::BindStagingBuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer> bufferID, MemoryAllocationFullID allocationID, size_t addOnReserving)
	{
		_internal.BindStagingBuffer(bufferID, allocationID, addOnReserving);
	}

	void DataBufferLists::BindIndexBuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupIndexBuffer> bufferID, MemoryAllocationFullID allocationID, size_t addOnReserving)
	{
		_internal.BindIndexBuffer(bufferID, allocationID, addOnReserving);
	}

	void DataBufferLists::BindUniformBuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupUniformBuffer> bufferID, MemoryAllocationFullID allocationID, size_t addOnReserving)
	{
		_internal.BindUniformBuffer(bufferID, allocationID, addOnReserving);
	}

	uint32_t DataBufferLists::GetVertexBuffersMemoryTypeMask(IDObject<VulkanSimplifiedInternal::AutoCleanupVertexBuffer> bufferID) const
	{
		return _internal.GetVertexBuffersMemoryTypeMask(bufferID);
	}

	MemorySize DataBufferLists::GetVertexBuffersSize(IDObject<VulkanSimplifiedInternal::AutoCleanupVertexBuffer> bufferID) const
	{
		return _internal.GetVertexBuffersSize(bufferID);
	}

	MemorySize DataBufferLists::GetVertexBuffersRequiredAligment(IDObject<VulkanSimplifiedInternal::AutoCleanupVertexBuffer> bufferID) const
	{
		return _internal.GetVertexBuffersRequiredAligment(bufferID);
	}

	uint32_t DataBufferLists::GetStagingBuffersMemoryTypeMask(IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer> bufferID) const
	{
		return _internal.GetStagingBuffersMemoryTypeMask(bufferID);
	}

	MemorySize DataBufferLists::GetStagingBuffersSize(IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer> bufferID) const
	{
		return _internal.GetStagingBuffersSize(bufferID);
	}

	MemorySize DataBufferLists::GetStagingBuffersRequiredAligment(IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer> bufferID) const
	{
		return _internal.GetStagingBuffersRequiredAligment(bufferID);
	}

	uint32_t DataBufferLists::GetIndexBuffersMemoryTypeMask(IDObject<VulkanSimplifiedInternal::AutoCleanupIndexBuffer> bufferID) const
	{
		return _internal.GetIndexBuffersMemoryTypeMask(bufferID);
	}

	MemorySize DataBufferLists::GetIndexBuffersSize(IDObject<VulkanSimplifiedInternal::AutoCleanupIndexBuffer> bufferID) const
	{
		return _internal.GetIndexBuffersSize(bufferID);
	}

	MemorySize DataBufferLists::GetIndexBuffersRequiredAligment(IDObject<VulkanSimplifiedInternal::AutoCleanupIndexBuffer> bufferID) const
	{
		return _internal.GetIndexBuffersRequiredAligment(bufferID);
	}

	uint32_t DataBufferLists::GetUniformBuffersMemoryTypeMask(IDObject<VulkanSimplifiedInternal::AutoCleanupUniformBuffer> bufferID) const
	{
		return _internal.GetUniformBuffersMemoryTypeMask(bufferID);
	}

	MemorySize DataBufferLists::GetUniformBuffersSize(IDObject<VulkanSimplifiedInternal::AutoCleanupUniformBuffer> bufferID) const
	{
		return _internal.GetUniformBuffersSize(bufferID);
	}

	MemorySize DataBufferLists::GetUniformBuffersRequiredAligment(IDObject<VulkanSimplifiedInternal::AutoCleanupUniformBuffer> bufferID) const
	{
		return _internal.GetUniformBuffersRequiredAligment(bufferID);
	}

	void DataBufferLists::WriteToVertexBuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupVertexBuffer> bufferID, MemorySize writeOffset, const unsigned char& writeData,
		MemorySize dataSize)
	{
		_internal.WriteToVertexBuffer(bufferID, writeOffset, writeData, dataSize);
	}

	void DataBufferLists::WriteToStagingBuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer> bufferID, MemorySize writeOffset, const unsigned char& writeData,
		MemorySize dataSize)
	{
		_internal.WriteToStagingBuffer(bufferID, writeOffset, writeData, dataSize);
	}

	void DataBufferLists::WriteToIndexBuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupIndexBuffer> bufferID, MemorySize writeOffset, const unsigned char& writeData,
		MemorySize dataSize)
	{
		_internal.WriteToIndexBuffer(bufferID, writeOffset, writeData, dataSize);
	}

	void DataBufferLists::WriteToUniformBuffer(IDObject<VulkanSimplifiedInternal::AutoCleanupUniformBuffer> bufferID, MemorySize writeOffset, const unsigned char& writeData,
		MemorySize dataSize)
	{
		_internal.WriteToUniformBuffer(bufferID, writeOffset, writeData, dataSize);
	}

}