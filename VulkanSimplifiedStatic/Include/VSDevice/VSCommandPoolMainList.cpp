#include "VSDeviceIpch.h"
#include "VSCommandPoolMainList.h"

#include "../../DoNotInclude/VSDevice/VSCommandPoolMainListInternal.h"

#include "VSCommandPoolQFGroupList.h"

namespace VulkanSimplified
{
	CommandPoolMainList::CommandPoolMainList(VulkanSimplifiedInternal::CommandPoolMainListInternal& ref) : _internal(ref)
	{
	}

	CommandPoolMainList::~CommandPoolMainList()
	{
	}

	IDObject<CommandPoolQFGroupPointer> CommandPoolMainList::AddQueueFamiliesPoolGroup(uint32_t queueFamily, const CommandPoolQFGroupListsInitialCapacities& initialCapacities,
		size_t addOnReserving)
	{
		return _internal.AddQueueFamiliesPoolGroup(queueFamily, initialCapacities, addOnReserving);
	}

	CommandPoolQFGroupList CommandPoolMainList::GetQueueFamiliesPoolGroup(IDObject<CommandPoolQFGroupPointer> qfGroupID)
	{
		return _internal.GetQueueFamiliesPoolGroup(qfGroupID);
	}

	const CommandPoolQFGroupList CommandPoolMainList::GetQueueFamiliesPoolGroup(IDObject<CommandPoolQFGroupPointer> qfGroupID) const
	{
		return _internal.GetQueueFamiliesPoolGroup(qfGroupID);
	}

}