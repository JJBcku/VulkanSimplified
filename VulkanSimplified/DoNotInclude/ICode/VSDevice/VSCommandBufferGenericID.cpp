#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSCommandBufferGenericID.h"

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