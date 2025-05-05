#pragma once

#include "VSPrimaryNIRCommandBuffer.h"

namespace VulkanSimplifiedInternal
{
	class PrimaryIRCommandBufferInternal;
}

namespace VulkanSimplified
{
	class PrimaryIRCommandBuffer : public PrimaryNIRCommandBuffer
	{
	public:
		PrimaryIRCommandBuffer(VulkanSimplifiedInternal::PrimaryIRCommandBufferInternal& ref);
		~PrimaryIRCommandBuffer();

		PrimaryIRCommandBuffer& operator=(const PrimaryIRCommandBuffer& rhs) noexcept = delete;

		void ResetCommandBuffer(bool freeResources);

	private:
		VulkanSimplifiedInternal::PrimaryIRCommandBufferInternal& _internal;
	};
}