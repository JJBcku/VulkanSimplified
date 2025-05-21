#pragma once

#include <CustomLists/IDObject.h>

#include "VSDescriptorDataListDef.h"

namespace VulkanSimplified
{
	enum class DescriptorSetIDType : uint64_t
	{
		UNKNOWN = 0,
		UNIFORM_BUFFER = 1,
	};

	union DescriptorSetGenericID
	{
		DescriptorSetIDType type;

		struct
		{
			DescriptorSetIDType type;
			IDObject<VulkanSimplifiedInternal::AutoCleanupUniformBufferDescriptorSet> ID;
		} uniformBufferID;

		DescriptorSetGenericID();
		DescriptorSetGenericID(IDObject<VulkanSimplifiedInternal::AutoCleanupUniformBufferDescriptorSet> ID);
	};
}