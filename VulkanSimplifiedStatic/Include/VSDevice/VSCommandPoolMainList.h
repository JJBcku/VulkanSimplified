#pragma once

#include "VSCommandPoolMainListDef.h"

namespace VulkanSimplifiedInternal
{
	class CommandPoolMainListInternal;
}

namespace VulkanSimplified
{
	class CommandPoolQFGroupList;

	struct CommandPoolQFGroupListsInitialCapacities;

	class CommandPoolMainList
	{
	public:
		CommandPoolMainList(VulkanSimplifiedInternal::CommandPoolMainListInternal& ref);
		~CommandPoolMainList();

		CommandPoolMainList& operator=(const CommandPoolMainList&) noexcept = delete;

		IDObject<CommandPoolQFGroupPointer> AddQueueFamiliesPoolGroup(uint32_t queueFamily, const CommandPoolQFGroupListsInitialCapacities& initialCapacities,
			size_t addOnReserving = 0);

		CommandPoolQFGroupList GetQueueFamiliesPoolGroup(IDObject<CommandPoolQFGroupPointer> qfGroupID);

		const CommandPoolQFGroupList GetQueueFamiliesPoolGroup(IDObject<CommandPoolQFGroupPointer> qfGroupID) const;

	private:
		VulkanSimplifiedInternal::CommandPoolMainListInternal& _internal;
	};
}