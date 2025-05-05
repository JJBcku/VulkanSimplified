#pragma once

#include "VSIRCommandPoolDef.h"

#include "VSWindowListDef.h"

namespace VulkanSimplifiedInternal
{
	class IRCommandPoolInternal;
	class AutoCleanupSemaphore;
}

namespace VulkanSimplified
{
	class PrimaryIRCommandBuffer;
	class SecondaryIRCommandBuffer;

	class IRCommandPool
	{
	public:
		IRCommandPool(VulkanSimplifiedInternal::IRCommandPoolInternal& ref);
		~IRCommandPool();

		IRCommandPool& operator=(const IRCommandPool&) noexcept = delete;

		std::vector<IDObject<PrimaryIRPointer>> AllocatePrimaryCommandBuffers(uint32_t buffersToAllocate, size_t addOnReserving = 0);
		std::vector<IDObject<SecondaryIRPointer>> AllocateSecondaryCommandBuffers(uint32_t buffersToAllocate, size_t addOnReserving = 0);

		PrimaryIRCommandBuffer GetPrimaryCommandBuffer(IDObject<PrimaryIRPointer> bufferID);
		SecondaryIRCommandBuffer GetSecondaryCommandBuffer(IDObject<SecondaryIRPointer> bufferID);

		const PrimaryIRCommandBuffer GetPrimaryCommandBuffer(IDObject<PrimaryIRPointer> bufferID) const;
		const SecondaryIRCommandBuffer GetSecondaryCommandBuffer(IDObject<SecondaryIRPointer> bufferID) const;

		void ResetCommandPool(bool freeResources);

		bool PresentSwapchainToQueue(IDObject<WindowPointer> windowID, const std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupSemaphore>>& waitSemaphoreIDs,
			uint32_t imageIndex);

	private:
		VulkanSimplifiedInternal::IRCommandPoolInternal& _internal;
	};
}