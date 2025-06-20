#include "VSDeviceNIpch.h"
#include "../../DNIHeaders/VSDevice/VSSynchronizationDataListsInternal.h"

#include "../../../Include/VSDevice/VSSynchronizationDataListsInitialCapacities.h"

#include "../../DNIHeaders/VSDevice/VSAutoCleanupFence.h"
#include "../../DNIHeaders/VSDevice/VSAutoCleanupSemaphore.h"

namespace VulkanSimplified
{
	SynchronizationDataListsInternal::SynchronizationDataListsInternal(VkDevice device, const SynchronizationDataListsInitialCapacities& initialCapacities) :
		_device(device), _fenceList(initialCapacities.fenceListInitialCapacity), _semaphoreList(initialCapacities.semaphoreListInitialCapacity)
	{
	}

	SynchronizationDataListsInternal::~SynchronizationDataListsInternal()
	{
	}

	IDObject<AutoCleanupFence> SynchronizationDataListsInternal::AddFence(bool createSignaled, size_t addOnReserving)
	{
		VkFenceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;

		if (createSignaled)
			createInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

		VkFence add = VK_NULL_HANDLE;

		if (vkCreateFence(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
			throw std::runtime_error("SynchronizationDataListsInternal::AddFence Error: Program failed to create a fence!");

		return _fenceList.AddObject(AutoCleanupFence(_device, add), addOnReserving);
	}

	VkFence SynchronizationDataListsInternal::GetFence(IDObject<AutoCleanupFence> fenceIDs) const
	{
		return _fenceList.GetConstObject(fenceIDs).GetFence();
	}

	bool SynchronizationDataListsInternal::WaitOnFences(const std::vector<IDObject<AutoCleanupFence>>& fenceIDs, bool waitForAll, uint64_t timeout) const
	{
		if (fenceIDs.empty())
			throw std::runtime_error("SynchronizationDataListsInternal::WaitOnFences Error: Program tried to wait on no fences!");

		if (timeout == 0)
			throw std::runtime_error("SynchronizationDataListsInternal::WaitOnFences Error: Timeout cannot be zero!");

		std::vector<VkFence> fences;
		fences.reserve(fenceIDs.size());

		for (size_t i = 0; i < fenceIDs.size(); ++i)
		{
			fences.push_back(GetFence(fenceIDs[i]));
		}

		VkBool32 waitAll = VK_FALSE;
		if (waitForAll)
			waitAll = VK_TRUE;

		VkResult result = vkWaitForFences(_device, static_cast<uint32_t>(fences.size()), fences.data(), waitAll, timeout);

		if (result != VK_SUCCESS && result != VK_TIMEOUT)
			throw std::runtime_error("SynchronizationDataListsInternal::WaitOnFences Error: Program failed to wait on fences!");

		return result == VK_SUCCESS;
	}

	void SynchronizationDataListsInternal::ResetFences(const std::vector<IDObject<AutoCleanupFence>>& fenceIDs)
	{
		if (fenceIDs.empty())
			throw std::runtime_error("SynchronizationDataListsInternal::ResetFence Error: Program tried to reset no fences!");

		std::vector<VkFence> fences;
		fences.reserve(fenceIDs.size());

		for (size_t i = 0; i < fenceIDs.size(); ++i)
		{
			fences.push_back(GetFence(fenceIDs[i]));
		}

		if (vkResetFences(_device, static_cast<uint32_t>(fences.size()), fences.data()) != VK_SUCCESS)
			throw std::runtime_error("SynchronizationDataListsInternal::ResetFence Error: Program failed to reset the fences!");
	}

	IDObject<AutoCleanupSemaphore> SynchronizationDataListsInternal::AddSemaphore(size_t addOnReserving)
	{
		VkSemaphoreCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		VkSemaphore add = VK_NULL_HANDLE;

		if (vkCreateSemaphore(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
			throw std::runtime_error("SynchronizationDataListsInternal::AddSemaphore Error: Program failed to create a semaphore!");

		return _semaphoreList.AddObject(AutoCleanupSemaphore(_device, add), addOnReserving);
	}

	VkSemaphore SynchronizationDataListsInternal::GetSemaphore(IDObject<AutoCleanupSemaphore> semaphoreID) const
	{
		return _semaphoreList.GetConstObject(semaphoreID).GetSemaphore();
	}
}