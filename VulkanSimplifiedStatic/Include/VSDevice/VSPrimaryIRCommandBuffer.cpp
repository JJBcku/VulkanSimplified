#include "VSDeviceIpch.h"
#include "VSPrimaryIRCommandBuffer.h"

#include "../../DoNotInclude/VSDevice/VSPrimaryIRCommandBufferInternal.h"

namespace VulkanSimplified
{
	PrimaryIRCommandBuffer::PrimaryIRCommandBuffer(VulkanSimplifiedInternal::PrimaryIRCommandBufferInternal& ref) : PrimaryNIRCommandBuffer(ref), _internal(ref)
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