#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSSynchronizationDataLists.h"

#include "../../../DoNotInclude/DNIHeaders/VSDevice/VSSynchronizationDataListsInternal.h"

namespace VulkanSimplified
{
	SynchronizationDataLists::SynchronizationDataLists(VulkanSimplifiedInternal::SynchronizationDataListsInternal& ref) : _internal(ref)
	{
	}

	SynchronizationDataLists::~SynchronizationDataLists()
	{
	}

	IDObject<VulkanSimplifiedInternal::AutoCleanupFence> SynchronizationDataLists::AddFence(bool createSignaled, size_t addOnReserving)
	{
		return _internal.AddFence(createSignaled, addOnReserving);
	}

	bool SynchronizationDataLists::WaitOnFences(const std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupFence>>& fenceIDs, bool waitForAll, uint64_t timeout) const
	{
		return _internal.WaitOnFences(fenceIDs, waitForAll, timeout);
	}

	void SynchronizationDataLists::ResetFences(const std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupFence>>& fenceIDs)
	{
		_internal.ResetFences(fenceIDs);
	}

	IDObject<VulkanSimplifiedInternal::AutoCleanupSemaphore> SynchronizationDataLists::AddSemaphore(size_t addOnReserving)
	{
		return _internal.AddSemaphore(addOnReserving);
	}

}