#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSDescriptorPoolGenericID.h"

namespace VulkanSimplified
{
	DescriptorPoolGenericID::DescriptorPoolGenericID() noexcept
	{
		type = DescriptorPoolIDType::UNKNOWN;
	}

	DescriptorPoolGenericID::DescriptorPoolGenericID(IDObject<AutoCleanupNIFDescriptorPool> ID) noexcept
	{
		NifID.type = DescriptorPoolIDType::NIF;
		NifID.ID = ID;
	}

	DescriptorPoolGenericID::DescriptorPoolGenericID(IDObject<AutoCleanupIFDescriptorPool> ID) noexcept
	{
		IfID.type = DescriptorPoolIDType::IF;
		IfID.ID = ID;
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

}