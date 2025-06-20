#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSDataBufferLists.h"

#include "../../../DoNotInclude/DNIHeaders/VSDevice/VSDataBufferListsInternal.h"

namespace VulkanSimplified
{
	DataBufferLists::DataBufferLists(DataBufferListsInternal& ref) : _internal(ref)
	{
	}

	DataBufferLists::~DataBufferLists()
	{
	}

	IDObject<AutoCleanupVertexBuffer> DataBufferLists::AddVertexBuffer(MemorySize size, const std::vector<size_t>& queuesUsingBuffer, size_t addOnReserving)
	{
		return _internal.AddVertexBuffer(size, queuesUsingBuffer, addOnReserving);
	}

	IDObject<AutoCleanupStagingBuffer> DataBufferLists::AddStagingBuffer(MemorySize size, const std::vector<size_t>& queuesUsingBuffer, size_t addOnReserving)
	{
		return _internal.AddStagingBuffer(size, queuesUsingBuffer, addOnReserving);
	}

	IDObject<AutoCleanupIndexBuffer> DataBufferLists::AddIndexBuffer(size_t indicesCount, IndexType indexType,
		const std::vector<size_t>& queuesUsingBuffer, size_t addOnReserving)
	{
		return _internal.AddIndexBuffer(indicesCount, indexType, queuesUsingBuffer, addOnReserving);
	}

	IDObject<AutoCleanupUniformBuffer> DataBufferLists::AddUniformBuffer(MemorySize size, const std::vector<size_t>& queuesUsingBuffer, size_t addOnReserving)
	{
		return _internal.AddUniformBuffer(size, queuesUsingBuffer, addOnReserving);
	}

	void DataBufferLists::BindVertexBuffer(IDObject<AutoCleanupVertexBuffer> bufferID, MemoryAllocationFullID allocationID,
		size_t addOnReserving)
	{
		_internal.BindVertexBuffer(bufferID, allocationID, addOnReserving);
	}

	void DataBufferLists::BindStagingBuffer(IDObject<AutoCleanupStagingBuffer> bufferID, MemoryAllocationFullID allocationID, size_t addOnReserving)
	{
		_internal.BindStagingBuffer(bufferID, allocationID, addOnReserving);
	}

	void DataBufferLists::BindIndexBuffer(IDObject<AutoCleanupIndexBuffer> bufferID, MemoryAllocationFullID allocationID, size_t addOnReserving)
	{
		_internal.BindIndexBuffer(bufferID, allocationID, addOnReserving);
	}

	void DataBufferLists::BindUniformBuffer(IDObject<AutoCleanupUniformBuffer> bufferID, MemoryAllocationFullID allocationID, size_t addOnReserving)
	{
		_internal.BindUniformBuffer(bufferID, allocationID, addOnReserving);
	}

	bool DataBufferLists::RemoveVertexBuffer(IDObject<AutoCleanupVertexBuffer> bufferID, bool throwOnIDNotFound)
	{
		return _internal.RemoveVertexBuffer(bufferID, throwOnIDNotFound);
	}

	bool DataBufferLists::RemoveStagingBuffer(IDObject<AutoCleanupStagingBuffer> bufferID, bool throwOnIDNotFound)
	{
		return _internal.RemoveStagingBuffer(bufferID, throwOnIDNotFound);
	}

	bool DataBufferLists::RemoveIndexBuffer(IDObject<AutoCleanupIndexBuffer> bufferID, bool throwOnIDNotFound)
	{
		return _internal.RemoveIndexBuffer(bufferID, throwOnIDNotFound);
	}

	bool DataBufferLists::RemoveUniformBuffer(IDObject<AutoCleanupUniformBuffer> bufferID, bool throwOnIDNotFound)
	{
		return _internal.RemoveUniformBuffer(bufferID, throwOnIDNotFound);
	}

	uint32_t DataBufferLists::GetVertexBuffersMemoryTypeMask(IDObject<AutoCleanupVertexBuffer> bufferID) const
	{
		return _internal.GetVertexBuffersMemoryTypeMask(bufferID);
	}

	MemorySize DataBufferLists::GetVertexBuffersSize(IDObject<AutoCleanupVertexBuffer> bufferID) const
	{
		return _internal.GetVertexBuffersSize(bufferID);
	}

	MemorySize DataBufferLists::GetVertexBuffersRequiredAligment(IDObject<AutoCleanupVertexBuffer> bufferID) const
	{
		return _internal.GetVertexBuffersRequiredAligment(bufferID);
	}

	uint32_t DataBufferLists::GetStagingBuffersMemoryTypeMask(IDObject<AutoCleanupStagingBuffer> bufferID) const
	{
		return _internal.GetStagingBuffersMemoryTypeMask(bufferID);
	}

	MemorySize DataBufferLists::GetStagingBuffersSize(IDObject<AutoCleanupStagingBuffer> bufferID) const
	{
		return _internal.GetStagingBuffersSize(bufferID);
	}

	MemorySize DataBufferLists::GetStagingBuffersRequiredAligment(IDObject<AutoCleanupStagingBuffer> bufferID) const
	{
		return _internal.GetStagingBuffersRequiredAligment(bufferID);
	}

	uint32_t DataBufferLists::GetIndexBuffersMemoryTypeMask(IDObject<AutoCleanupIndexBuffer> bufferID) const
	{
		return _internal.GetIndexBuffersMemoryTypeMask(bufferID);
	}

	MemorySize DataBufferLists::GetIndexBuffersSize(IDObject<AutoCleanupIndexBuffer> bufferID) const
	{
		return _internal.GetIndexBuffersSize(bufferID);
	}

	MemorySize DataBufferLists::GetIndexBuffersRequiredAligment(IDObject<AutoCleanupIndexBuffer> bufferID) const
	{
		return _internal.GetIndexBuffersRequiredAligment(bufferID);
	}

	uint32_t DataBufferLists::GetUniformBuffersMemoryTypeMask(IDObject<AutoCleanupUniformBuffer> bufferID) const
	{
		return _internal.GetUniformBuffersMemoryTypeMask(bufferID);
	}

	MemorySize DataBufferLists::GetUniformBuffersSize(IDObject<AutoCleanupUniformBuffer> bufferID) const
	{
		return _internal.GetUniformBuffersSize(bufferID);
	}

	MemorySize DataBufferLists::GetUniformBuffersRequiredAligment(IDObject<AutoCleanupUniformBuffer> bufferID) const
	{
		return _internal.GetUniformBuffersRequiredAligment(bufferID);
	}

	void DataBufferLists::WriteToVertexBuffer(IDObject<AutoCleanupVertexBuffer> bufferID, MemorySize writeOffset, const unsigned char& writeData,
		MemorySize dataSize)
	{
		_internal.WriteToVertexBuffer(bufferID, writeOffset, writeData, dataSize);
	}

	void DataBufferLists::WriteToStagingBuffer(IDObject<AutoCleanupStagingBuffer> bufferID, MemorySize writeOffset, const unsigned char& writeData,
		MemorySize dataSize)
	{
		_internal.WriteToStagingBuffer(bufferID, writeOffset, writeData, dataSize);
	}

	void DataBufferLists::WriteToIndexBuffer(IDObject<AutoCleanupIndexBuffer> bufferID, MemorySize writeOffset, const unsigned char& writeData,
		MemorySize dataSize)
	{
		_internal.WriteToIndexBuffer(bufferID, writeOffset, writeData, dataSize);
	}

	void DataBufferLists::WriteToUniformBuffer(IDObject<AutoCleanupUniformBuffer> bufferID, MemorySize writeOffset, const unsigned char& writeData,
		MemorySize dataSize)
	{
		_internal.WriteToUniformBuffer(bufferID, writeOffset, writeData, dataSize);
	}

}