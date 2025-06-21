#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSSecondaryNIRCommandBuffer.h"

#include "../../../DoNotInclude/DNIData/VSDevice/VSSecondaryNIRCommandBufferInternal.h"

namespace VulkanSimplified
{
	SecondaryNIRCommandBuffer::SecondaryNIRCommandBuffer(SecondaryNIRCommandBufferInternal& ref) : CommandBufferBase(ref), _internal(ref)
	{
	}

	SecondaryNIRCommandBuffer::~SecondaryNIRCommandBuffer()
	{
	}

}