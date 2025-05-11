#pragma once

#include <CustomLists/IDObject.h>

#include <VSSynchronizationDataListsDef.h>

struct VulkanSynchronizationData
{
	std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupFence>> inFlightFences;
	std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupSemaphore>> imageAvailableSemaphores;
	std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupSemaphore>> renderingFinishedSemaphores;
	std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupSemaphore>> queueTransferFinishedSemaphores;
	std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupSemaphore>> dataTransferFinishedSemaphores;

	VulkanSynchronizationData();
	~VulkanSynchronizationData();
};