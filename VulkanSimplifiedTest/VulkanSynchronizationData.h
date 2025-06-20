#pragma once

#include <CustomLists/IDObject.h>

#include <VSSynchronizationDataListsDef.h>

struct VulkanSynchronizationData
{
	std::vector<IDObject<VS::AutoCleanupFence>> inFlightFences;
	std::vector<IDObject<VS::AutoCleanupSemaphore>> imageAvailableSemaphores;
	std::vector<IDObject<VS::AutoCleanupSemaphore>> renderingFinishedSemaphores;
	std::vector<IDObject<VS::AutoCleanupSemaphore>> queueTransferFinishedSemaphores;
	std::vector<IDObject<VS::AutoCleanupSemaphore>> dataTransferFinishedSemaphores;

	VulkanSynchronizationData();
	~VulkanSynchronizationData();
};