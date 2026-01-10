#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSCommandBufferGenericID.h"

namespace VulkanSimplified
{
	CommandBufferGenericID::CommandBufferGenericID() noexcept
	{
		type = CommandBufferIDType::UNKNOWN;
	}

	CommandBufferGenericID::CommandBufferGenericID(const CommandBufferGenericID& rhs) noexcept
	{
		std::memcpy(this, &rhs, sizeof(CommandBufferGenericID));
	}

	CommandBufferGenericID::CommandBufferGenericID(CommandBufferGenericID&& rhs) noexcept
	{
		std::memcpy(this, &rhs, sizeof(CommandBufferGenericID));
		rhs.type = CommandBufferIDType::UNKNOWN;
	}

	CommandBufferGenericID::~CommandBufferGenericID()
	{
	}

	CommandBufferGenericID& CommandBufferGenericID::operator=(const CommandBufferGenericID& rhs) noexcept
	{
		std::memcpy(this, &rhs, sizeof(CommandBufferGenericID));

		return *this;
	}

	CommandBufferGenericID& CommandBufferGenericID::operator=(CommandBufferGenericID&& rhs) noexcept
	{
		std::memcpy(this, &rhs, sizeof(CommandBufferGenericID));
		rhs.type = CommandBufferIDType::UNKNOWN;
		return *this;
	}

}