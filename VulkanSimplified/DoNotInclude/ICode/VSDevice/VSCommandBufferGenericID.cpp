#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSCommandBufferGenericID.h"

namespace VulkanSimplified
{
	CommandBufferGenericID::CommandBufferGenericID() noexcept
	{
		type = CommandBufferIDType::UNKNOWN;
	}

	CommandBufferGenericID::CommandBufferGenericID(const IDObject<std::unique_ptr<NIRCommandPoolInternal>>& commandPoolID,
		const IDObject<std::unique_ptr<PrimaryNIRCommandBufferInternal>>& commandBufferID) noexcept : NIRPrimaryID(commandPoolID, commandBufferID)
	{
	}

	CommandBufferGenericID::CommandBufferGenericID(const IDObject<std::unique_ptr<NIRCommandPoolInternal>>& commandPoolID,
		const IDObject<std::unique_ptr<SecondaryNIRCommandBufferInternal>>& commandBufferID) noexcept : NIRSecondaryID(commandPoolID, commandBufferID)
	{
	}

	CommandBufferGenericID::CommandBufferGenericID(const IDObject<std::unique_ptr<IRCommandPoolInternal>>& commandPoolID,
		const IDObject<std::unique_ptr<PrimaryIRCommandBufferInternal>>& commandBufferID) noexcept : IRPrimaryID(commandPoolID, commandBufferID)
	{
	}

	CommandBufferGenericID::CommandBufferGenericID(const IDObject<std::unique_ptr<IRCommandPoolInternal>>& commandPoolID,
		const IDObject<std::unique_ptr<SecondaryIRCommandBufferInternal>>& commandBufferID) noexcept : IRSecondaryID(commandPoolID, commandBufferID)
	{
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

	CommandBufferGenericID::NIRPrimaryID::NIRPrimaryID(const IDObject<std::unique_ptr<NIRCommandPoolInternal>>& commandPoolID,
		const IDObject<std::unique_ptr<PrimaryNIRCommandBufferInternal>>& commandBufferID) noexcept : commandPoolID(commandPoolID), commandBufferID(commandBufferID)
	{
		type = CommandBufferIDType::NIR_PRIMARY;
	}

	CommandBufferGenericID::NIRSecondaryID::NIRSecondaryID(const IDObject<std::unique_ptr<NIRCommandPoolInternal>>& commandPoolID,
		const IDObject<std::unique_ptr<SecondaryNIRCommandBufferInternal>>& commandBufferID) noexcept : commandPoolID(commandPoolID), commandBufferID(commandBufferID)
	{
		type = CommandBufferIDType::NIR_SECONDARY;
	}

	CommandBufferGenericID::IRPrimaryID::IRPrimaryID(const IDObject<std::unique_ptr<IRCommandPoolInternal>>& commandPoolID,
		const IDObject<std::unique_ptr<PrimaryIRCommandBufferInternal>>& commandBufferID) noexcept : commandPoolID(commandPoolID), commandBufferID(commandBufferID)
	{
		type = CommandBufferIDType::IR_PRIMARY;
	}

	CommandBufferGenericID::IRSecondaryID::IRSecondaryID(const IDObject<std::unique_ptr<IRCommandPoolInternal>>& commandPoolID,
		const IDObject<std::unique_ptr<SecondaryIRCommandBufferInternal>>& commandBufferID) noexcept : commandPoolID(commandPoolID), commandBufferID(commandBufferID)
	{
		type = CommandBufferIDType::IR_SECONDARY;
	}

}