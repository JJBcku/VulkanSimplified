#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSIRCommandPool.h"

#include "../../../DoNotInclude/DNIData/VSDevice/VSIRCommandPoolInternal.h"

#include "../../../Include/VSDevice/VSPrimaryIRCommandBuffer.h"
#include "../../../Include/VSDevice/VSSecondaryIRCommandBuffer.h"

namespace VulkanSimplified
{
	IRCommandPool::IRCommandPool(IRCommandPoolInternal& ref) : _internal(ref)
	{
	}

	IRCommandPool::~IRCommandPool()
	{
	}

	std::vector<IDObject<PrimaryIRPointer>> IRCommandPool::AllocatePrimaryCommandBuffers(uint32_t buffersToAllocate, size_t addOnReserving)
	{
		return _internal.AllocatePrimaryCommandBuffers(buffersToAllocate, addOnReserving);
	}

	std::vector<IDObject<SecondaryIRPointer>> IRCommandPool::AllocateSecondaryCommandBuffers(uint32_t buffersToAllocate, size_t addOnReserving)
	{
		return _internal.AllocateSecondaryCommandBuffers(buffersToAllocate, addOnReserving);
	}

	PrimaryIRCommandBuffer IRCommandPool::GetPrimaryCommandBuffer(IDObject<PrimaryIRPointer> bufferID)
	{
		return _internal.GetPrimaryCommandBuffer(bufferID);
	}

	SecondaryIRCommandBuffer IRCommandPool::GetSecondaryCommandBuffer(IDObject<SecondaryIRPointer> bufferID)
	{
		return _internal.GetSecondaryCommandBuffer(bufferID);
	}

	const PrimaryIRCommandBuffer IRCommandPool::GetPrimaryCommandBuffer(IDObject<PrimaryIRPointer> bufferID) const
	{
		return _internal.GetPrimaryCommandBuffer(bufferID);
	}

	const SecondaryIRCommandBuffer IRCommandPool::GetSecondaryCommandBuffer(IDObject<SecondaryIRPointer> bufferID) const
	{
		return _internal.GetSecondaryCommandBuffer(bufferID);
	}

	void IRCommandPool::ResetCommandPool(bool freeResources)
	{
		_internal.ResetCommandPool(freeResources);
	}

	bool IRCommandPool::PresentSwapchainToQueue(IDObject<WindowPointer> windowID, const std::vector<IDObject<AutoCleanupSemaphore>>& waitSemaphoreIDs,
		uint32_t imageIndex)
	{
		return _internal.PresentSwapchainToQueue(windowID, waitSemaphoreIDs, imageIndex);
	}

	void IRCommandPool::RecordExecuteSecondaryBufferCommand(IDObject<PrimaryIRPointer> primaryBufferID, const std::vector<IDObject<SecondaryIRPointer>>& secondaryBufferIDs)
	{
		_internal.RecordExecuteSecondaryBufferCommand(primaryBufferID, secondaryBufferIDs);
	}

}