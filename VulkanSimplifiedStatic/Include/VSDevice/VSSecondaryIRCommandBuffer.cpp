#include "VSDeviceIpch.h"
#include "VSSecondaryIRCommandBuffer.h"

#include "../../DoNotInclude/VSDevice/VSSecondaryIRCommandBufferInternal.h"

namespace VulkanSimplified
{
	SecondaryIRCommandBuffer::SecondaryIRCommandBuffer(VulkanSimplifiedInternal::SecondaryIRCommandBufferInternal& ref) : SecondaryNIRCommandBuffer(ref),
		_internal(ref)
	{
	}

	SecondaryIRCommandBuffer::~SecondaryIRCommandBuffer()
	{
	}

	void SecondaryIRCommandBuffer::ResetCommandBuffer(bool freeResources)
	{
		_internal.ResetCommandBuffer(freeResources);
	}

}