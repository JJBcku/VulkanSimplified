#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSPrimaryIRCommandBuffer.h"

#include "../../../DoNotInclude/DNIData/VSDevice/VSPrimaryIRCommandBufferInternal.h"

namespace VulkanSimplified
{
	PrimaryIRCommandBuffer::PrimaryIRCommandBuffer(PrimaryIRCommandBufferInternal& ref) : PrimaryNIRCommandBuffer(ref), _internal(ref)
	{
	}

	PrimaryIRCommandBuffer::~PrimaryIRCommandBuffer()
	{
	}

	void PrimaryIRCommandBuffer::ResetCommandBuffer(bool freeResources)
	{
		_internal.ResetCommandBuffer(freeResources);
	}

}