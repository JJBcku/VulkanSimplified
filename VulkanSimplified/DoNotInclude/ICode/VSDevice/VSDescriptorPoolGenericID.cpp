#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSDescriptorPoolGenericID.h"

namespace VulkanSimplified
{
	DescriptorPoolGenericID::DescriptorPoolGenericID()
	{
		type = DescriptorPoolIDType::UNKNOWN;
	}

	DescriptorPoolGenericID::DescriptorPoolGenericID(IDObject<AutoCleanupNIFDescriptorPool> ID)
	{
		NifID.type = DescriptorPoolIDType::NIF;
		NifID.ID = ID;
	}

	DescriptorPoolGenericID::DescriptorPoolGenericID(IDObject<AutoCleanupIFDescriptorPool> ID)
	{
		IfID.type = DescriptorPoolIDType::IF;
		IfID.ID = ID;
	}
}