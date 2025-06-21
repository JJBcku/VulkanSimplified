#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSSecondaryIRCommandBuffer.h"

#include "../../../DoNotInclude/DNIData/VSDevice/VSSecondaryIRCommandBufferInternal.h"

namespace VulkanSimplified
{
	SecondaryIRCommandBuffer::SecondaryIRCommandBuffer(SecondaryIRCommandBufferInternal& ref) : SecondaryNIRCommandBuffer(ref),
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