#pragma once

#include <CustomLists/IDObject.h>

#include <VSSynchronizationDataListsDef.h>

struct VulkanSynchronizationData
{
	std::vector<IDObject<VulkanSimplified::AutoCleanupFence>> inFlightFences;
	std::vector<IDObject<VulkanSimplified::AutoCleanupSemaphore>> imageAvailableSemaphores;
	std::vector<IDObject<VulkanSimplified::AutoCleanupSemaphore>> renderingFinishedSemaphores;
	std::vector<IDObject<VulkanSimplified::AutoCleanupSemaphore>> queueTransferFinishedSemaphores;
	std::vector<IDObject<VulkanSimplified::AutoCleanupSemaphore>> dataTransferFinishedSemaphores;

	VulkanSynchronizationData();
	~VulkanSynchronizationData();
};