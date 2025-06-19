#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSCommandPoolQFGroupList.h"

#include "../../../DoNotInclude/DNIHeaders/VSDevice/VSCommandPoolQFGroupListInternal.h"

#include <CustomLists/IDObject.h>

#include "../../../Include/VSDevice/VSNIRCommandPool.h"
#include "../../../Include/VSDevice/VSIRCommandPool.h"

namespace VulkanSimplified
{
	CommandPoolQFGroupList::CommandPoolQFGroupList(VulkanSimplifiedInternal::CommandPoolQFGroupListInternal& ref) : _internal(ref)
	{
	}

	CommandPoolQFGroupList::~CommandPoolQFGroupList()
	{
	}

	IDObject<NIRPoolPointer> CommandPoolQFGroupList::AddCommandPoolWithoutIndividualReset(bool frequentlyRedoneBuffers, size_t queueID, size_t primaryBufferListInitialCapacity,
		size_t secondaryBufferListInitialCapacity, size_t addOnReserving)
	{
		return _internal.AddCommandPoolWithoutIndividualReset(frequentlyRedoneBuffers, queueID, primaryBufferListInitialCapacity, secondaryBufferListInitialCapacity, addOnReserving);
	}

	IDObject<IRPoolPointer> CommandPoolQFGroupList::AddCommandPoolWithIndividualReset(bool frequentlyRedoneBuffers, size_t queueID, size_t primaryBufferListInitialCapacity,
		size_t secondaryBufferListInitialCapacity, size_t addOnReserving)
	{
		return _internal.AddCommandPoolWithIndividualReset(frequentlyRedoneBuffers, queueID, primaryBufferListInitialCapacity, secondaryBufferListInitialCapacity, addOnReserving);
	}

	NIRCommandPool CommandPoolQFGroupList::GetCommandPoolWithoutIndividualReset(IDObject<NIRPoolPointer> poolID)
	{
		return _internal.GetCommandPoolWithoutIndividualReset(poolID);
	}

	IRCommandPool CommandPoolQFGroupList::GetCommandPoolWithIndividualReset(IDObject<IRPoolPointer> poolID)
	{
		return _internal.GetCommandPoolWithIndividualReset(poolID);
	}

	const NIRCommandPool CommandPoolQFGroupList::GetCommandPoolWithoutIndividualReset(IDObject<NIRPoolPointer> poolID) const
	{
		return _internal.GetCommandPoolWithoutIndividualReset(poolID);
	}

	const IRCommandPool CommandPoolQFGroupList::GetCommandPoolWithIndividualReset(IDObject<IRPoolPointer> poolID) const
	{
		return _internal.GetCommandPoolWithIndividualReset(poolID);
	}

	void CommandPoolQFGroupList::SubmitBuffers(size_t queueID, const std::vector<CommandBufferSubmissionData>& submitInfos,
		std::optional<IDObject<VulkanSimplifiedInternal::AutoCleanupFence>> fenceID)
	{
		_internal.SubmitBuffers(queueID, submitInfos, fenceID);
	}

}