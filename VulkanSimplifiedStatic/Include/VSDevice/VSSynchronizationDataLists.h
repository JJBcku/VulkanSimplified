#pragma once

#include <CustomLists\IDObjectDef.h>

#include "VSSynchronizationDataListsDef.h"

#include <vector>
#include <stdint.h>
#include <limits>

namespace VulkanSimplifiedInternal
{
	class SynchronizationDataListsInternal;
}

namespace VulkanSimplified
{
	class SynchronizationDataLists
	{
	public:
		SynchronizationDataLists(VulkanSimplifiedInternal::SynchronizationDataListsInternal& ref);
		~SynchronizationDataLists();

		SynchronizationDataLists& operator=(const SynchronizationDataLists&) noexcept = delete;

		IDObject<VulkanSimplifiedInternal::AutoCleanupFence> AddFence(bool createSignaled = true, size_t addOnReserving = 0);

		bool WaitOnFences(const std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupFence>>& fenceIDs, bool waitForAll,
			uint64_t timeout = std::numeric_limits<uint64_t>::max()) const;
		void ResetFences(const std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupFence>>& fenceIDs);

		IDObject<VulkanSimplifiedInternal::AutoCleanupSemaphore> AddSemaphore(size_t addOnReserving = 0);

	private:
		VulkanSimplifiedInternal::SynchronizationDataListsInternal& _internal;
	};
}