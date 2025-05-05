#pragma once

#include "VSSecondaryNIRCommandBuffer.h"

namespace VulkanSimplifiedInternal
{
	class SecondaryIRCommandBufferInternal;
}

namespace VulkanSimplified
{
	class SecondaryIRCommandBuffer : public SecondaryNIRCommandBuffer
	{
	public:
		SecondaryIRCommandBuffer(VulkanSimplifiedInternal::SecondaryIRCommandBufferInternal& ref);
		~SecondaryIRCommandBuffer();

		SecondaryIRCommandBuffer& operator=(const SecondaryIRCommandBuffer&) noexcept = delete;

		void ResetCommandBuffer(bool freeResources);

	private:
		VulkanSimplifiedInternal::SecondaryIRCommandBufferInternal& _internal;
	};
}