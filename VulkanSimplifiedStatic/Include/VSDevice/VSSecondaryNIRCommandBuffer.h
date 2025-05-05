#pragma once

#include "VSCommandBufferBase.h"

namespace VulkanSimplifiedInternal
{
	class SecondaryNIRCommandBufferInternal;
}

namespace VulkanSimplified
{
	class SecondaryNIRCommandBuffer : public CommandBufferBase
	{
	public:
		SecondaryNIRCommandBuffer(VulkanSimplifiedInternal::SecondaryNIRCommandBufferInternal& ref);
		~SecondaryNIRCommandBuffer();

		SecondaryNIRCommandBuffer& operator=(const SecondaryNIRCommandBuffer&) noexcept = delete;

	private:
		VulkanSimplifiedInternal::SecondaryNIRCommandBufferInternal& _internal;
	};
}