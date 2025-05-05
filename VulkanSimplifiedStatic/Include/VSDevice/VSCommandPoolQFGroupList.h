#pragma once

#include "VSCommandPoolQFGroupListDef.h"

namespace VulkanSimplifiedInternal
{
	class CommandPoolQFGroupListInternal;

	class AutoCleanupFence;
}

namespace VulkanSimplified
{
	class NIRCommandPool;
	class IRCommandPool;

	struct CommandBufferSubmissionData;

	class CommandPoolQFGroupList
	{
	public:
		CommandPoolQFGroupList(VulkanSimplifiedInternal::CommandPoolQFGroupListInternal& ref);
		~CommandPoolQFGroupList();

		CommandPoolQFGroupList& operator=(const CommandPoolQFGroupList&) noexcept = delete;

		IDObject<NIRPoolPointer> AddCommandPoolWithoutIndividualReset(bool frequentlyRedoneBuffers, size_t queueID,
			size_t primaryBufferListInitialCapacity, size_t secondaryBufferListInitialCapacity, size_t addOnReserving = 0);
		IDObject<IRPoolPointer> AddCommandPoolWithIndividualReset(bool frequentlyRedoneBuffers, size_t queueID,
			size_t primaryBufferListInitialCapacity, size_t secondaryBufferListInitialCapacity, size_t addOnReserving = 0);

		NIRCommandPool GetCommandPoolWithoutIndividualReset(IDObject<NIRPoolPointer> poolID);
		IRCommandPool GetCommandPoolWithIndividualReset(IDObject<IRPoolPointer> poolID);

		const NIRCommandPool GetCommandPoolWithoutIndividualReset(IDObject<NIRPoolPointer> poolID) const;
		const IRCommandPool GetCommandPoolWithIndividualReset(IDObject<IRPoolPointer> poolID) const;

		void SubmitBuffers(size_t queueID, const std::vector<CommandBufferSubmissionData>& submitInfos, std::optional<IDObject<VulkanSimplifiedInternal::AutoCleanupFence>> fenceID);

	private:
		VulkanSimplifiedInternal::CommandPoolQFGroupListInternal& _internal;
	};
}