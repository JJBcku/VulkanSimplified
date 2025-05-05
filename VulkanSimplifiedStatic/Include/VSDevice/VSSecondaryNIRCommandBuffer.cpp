#include "VSDeviceIpch.h"
#include "VSSecondaryNIRCommandBuffer.h"

#include "../../DoNotInclude/VSDevice/VSSecondaryNIRCommandBufferInternal.h"

namespace VulkanSimplified
{
	SecondaryNIRCommandBuffer::SecondaryNIRCommandBuffer(VulkanSimplifiedInternal::SecondaryNIRCommandBufferInternal& ref) : CommandBufferBase(ref), _internal(ref)
	{
	}

	SecondaryNIRCommandBuffer::~SecondaryNIRCommandBuffer()
	{
	}

}