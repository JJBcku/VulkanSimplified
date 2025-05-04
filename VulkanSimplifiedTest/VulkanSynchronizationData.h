#pragma once

#include <CustomLists/IDObject.h>

#include <VSSynchronizationDataListsDef.h>

struct VulkanSynchronizationData
{
	std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupFence>> inFlightFence;
	std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupSemaphore>> imageAvailableSemaphore;
	std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupSemaphore>> renderingFinishedSemaphore;
	std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupSemaphore>> transferFinishedSemaphore;

	VulkanSynchronizationData();
	~VulkanSynchronizationData();
};