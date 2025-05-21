#pragma once

#include <CustomLists/IDObject.h>

#include "VSDescriptorDataListDef.h"

namespace VulkanSimplified
{
	enum class DescriptorPoolIDType : uint64_t
	{
		UNKNOWN = 0,
		NIF = 1,
		IF = 2,
	};

	union DescriptorPoolGenericID
	{
		DescriptorPoolIDType type;

		struct
		{
			DescriptorPoolIDType type;
			IDObject<VulkanSimplifiedInternal::AutoCleanupNIFDescriptorPool> ID;
		} NifID;

		struct
		{
			DescriptorPoolIDType type;
			IDObject<VulkanSimplifiedInternal::AutoCleanupIFDescriptorPool> ID;
		} IfID;

		DescriptorPoolGenericID();
		DescriptorPoolGenericID(IDObject<VulkanSimplifiedInternal::AutoCleanupNIFDescriptorPool> ID);
		DescriptorPoolGenericID(IDObject<VulkanSimplifiedInternal::AutoCleanupIFDescriptorPool> ID);
	};
}