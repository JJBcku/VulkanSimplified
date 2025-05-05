#include "VSDeviceIpch.h"
#include "VSCommandBufferGenericID.h"

namespace VulkanSimplified
{
	CommandBufferGenericID::CommandBufferGenericID()
	{
		type = CommandBufferIDType::UNKNOWN;
	}

	CommandBufferGenericID::~CommandBufferGenericID()
	{
	}
}