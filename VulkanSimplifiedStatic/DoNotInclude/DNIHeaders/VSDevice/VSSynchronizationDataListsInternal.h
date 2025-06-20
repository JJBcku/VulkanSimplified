#pragma once

#include <CustomLists/UnsortedIDVector.h>

#include <vector>
#include <stdint.h>

typedef struct VkDevice_T* VkDevice;
typedef struct VkFence_T* VkFence;
typedef struct VkSemaphore_T* VkSemaphore;

namespace VulkanSimplified
{
	struct SynchronizationDataListsInitialCapacities;
}

namespace VulkanSimplified
{
	class AutoCleanupFence;
	class AutoCleanupSemaphore;

	class SynchronizationDataListsInternal
	{
	public:
		SynchronizationDataListsInternal(VkDevice device, const SynchronizationDataListsInitialCapacities& initialCapacities);
		~SynchronizationDataListsInternal();

		SynchronizationDataListsInternal(const SynchronizationDataListsInternal& rhs) noexcept = delete;

		SynchronizationDataListsInternal& operator=(const SynchronizationDataListsInternal& rhs) noexcept = delete;

		IDObject<AutoCleanupFence> AddFence(bool createSignaled, size_t addOnReserving);
		VkFence GetFence(IDObject<AutoCleanupFence> fenceIDs) const;

		bool WaitOnFences(const std::vector<IDObject<AutoCleanupFence>>& fenceIDs, bool waitForAll, uint64_t timeout) const;
		void ResetFences(const std::vector<IDObject<AutoCleanupFence>>& fenceIDs);

		IDObject<AutoCleanupSemaphore> AddSemaphore(size_t addOnReserving);
		VkSemaphore GetSemaphore(IDObject<AutoCleanupSemaphore> semaphoreID) const;

	private:
		VkDevice _device;

		UnsortedIDVector<AutoCleanupFence> _fenceList;
		UnsortedIDVector<AutoCleanupSemaphore> _semaphoreList;

	};
}