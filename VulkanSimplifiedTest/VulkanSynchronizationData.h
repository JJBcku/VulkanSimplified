#pragma once

#include <CustomLists/IDObject.h>

namespace VulkanSimplifiedInternal
{
	class AutoCleanupFence;
	class AutoCleanupSemaphore;
}

struct VulkanSynchronizationData
{
	std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupFence>> inFlightFence;
	std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupSemaphore>> imageAvailableSemaphore;
	std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupSemaphore>> renderingFinishedSemaphore;
	std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupSemaphore>> transferFinishedSemaphore;

	VulkanSynchronizationData();
	~VulkanSynchronizationData();
};