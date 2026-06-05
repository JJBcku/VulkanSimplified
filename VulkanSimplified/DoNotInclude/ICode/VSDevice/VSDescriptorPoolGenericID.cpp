#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSDescriptorPoolGenericID.h"

namespace VulkanSimplified
{
	DescriptorPoolGenericID::DescriptorPoolGenericID() noexcept
	{
		type = DescriptorPoolIDType::UNKNOWN;
	}

	DescriptorPoolGenericID::DescriptorPoolGenericID(const IDObject<AutoCleanupNIFDescriptorPool>& ID) noexcept : NifID(ID)
	{
	}

	DescriptorPoolGenericID::DescriptorPoolGenericID(const IDObject<AutoCleanupIFDescriptorPool>& ID) noexcept : IfID(ID)
	{
	}

	DescriptorPoolGenericID::DescriptorPoolGenericID(const DescriptorPoolGenericID& rhs) noexcept
	{
		std::memcpy(this, &rhs, sizeof(DescriptorPoolGenericID));
	}

	DescriptorPoolGenericID::DescriptorPoolGenericID(DescriptorPoolGenericID&& rhs) noexcept
	{
		std::memcpy(this, &rhs, sizeof(DescriptorPoolGenericID));
		rhs.type = DescriptorPoolIDType::UNKNOWN;
	}

	DescriptorPoolGenericID::~DescriptorPoolGenericID()
	{
	}

	DescriptorPoolGenericID& DescriptorPoolGenericID::operator=(const DescriptorPoolGenericID& rhs) noexcept
	{
		std::memcpy(this, &rhs, sizeof(DescriptorPoolGenericID));
		return *this;
	}

	DescriptorPoolGenericID& DescriptorPoolGenericID::operator=(DescriptorPoolGenericID&& rhs) noexcept
	{
		std::memcpy(this, &rhs, sizeof(DescriptorPoolGenericID));
		rhs.type = DescriptorPoolIDType::UNKNOWN;
		return *this;
	}

	DescriptorPoolGenericID::NifID::NifID(const IDObject<AutoCleanupNIFDescriptorPool>& ID) noexcept : ID(ID)
	{
		type = DescriptorPoolIDType::NIF;
	}

	DescriptorPoolGenericID::IfID::IfID(const IDObject<AutoCleanupIFDescriptorPool>& ID) noexcept : ID(ID)
	{
		type = DescriptorPoolIDType::IF;
	}

}