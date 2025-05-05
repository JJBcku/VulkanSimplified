#include "VSDeviceIpch.h"
#include "VSNIRCommandPool.h"

#include "../../DoNotInclude/VSDevice/VSNIRCommandPoolInternal.h"

#include "VSPrimaryNIRCommandBuffer.h"
#include "VSSecondaryNIRCommandBuffer.h"

namespace VulkanSimplified
{
	NIRCommandPool::NIRCommandPool(VulkanSimplifiedInternal::NIRCommandPoolInternal& ref) : _internal(ref)
	{
	}

	NIRCommandPool::~NIRCommandPool()
	{
	}

	std::vector<IDObject<PrimaryNIRPointer>> NIRCommandPool::AllocatePrimaryCommandBuffers(uint32_t buffersToAllocate, size_t addOnReserving)
	{
		return _internal.AllocatePrimaryCommandBuffers(buffersToAllocate, addOnReserving);
	}

	std::vector<IDObject<SecondaryNIRPointer>> NIRCommandPool::AllocateSecondaryCommandBuffers(uint32_t buffersToAllocate, size_t addOnReserving)
	{
		return _internal.AllocateSecondaryCommandBuffers(buffersToAllocate, addOnReserving);
	}

	PrimaryNIRCommandBuffer NIRCommandPool::GetPrimaryCommandBuffer(IDObject<PrimaryNIRPointer> bufferID)
	{
		return _internal.GetPrimaryCommandBuffer(bufferID);
	}

	SecondaryNIRCommandBuffer NIRCommandPool::GetSecondaryCommandBuffer(IDObject<SecondaryNIRPointer> bufferID)
	{
		return _internal.GetSecondaryCommandBuffer(bufferID);
	}

	const PrimaryNIRCommandBuffer NIRCommandPool::GetPrimaryCommandBuffer(IDObject<PrimaryNIRPointer> bufferID) const
	{
		return _internal.GetPrimaryCommandBuffer(bufferID);
	}

	const SecondaryNIRCommandBuffer NIRCommandPool::GetSecondaryCommandBuffer(IDObject<SecondaryNIRPointer> bufferID) const
	{
		return _internal.GetSecondaryCommandBuffer(bufferID);
	}

	void NIRCommandPool::ResetCommandPool(bool freeResources)
	{
		_internal.ResetCommandPool(freeResources);
	}

	bool NIRCommandPool::PresentSwapchainToQueue(IDObject<WindowPointer> windowID, const std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupSemaphore>>& waitSemaphoreIDs,
		uint32_t imageIndex)
	{
		return _internal.PresentSwapchainToQueue(windowID, waitSemaphoreIDs, imageIndex);
	}

}