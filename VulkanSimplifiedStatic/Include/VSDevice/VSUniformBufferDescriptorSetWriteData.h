#pragma once

#include <CustomLists/IDObject.h>

#include "VSDescriptorDataListDef.h"
#include "VSDataBufferListsDef.h"

namespace VulkanSimplified
{
	struct UniformBufferDescriptorSetWriteData
	{
		IDObject<VulkanSimplifiedInternal::AutoCleanupDescriptorSet> descriptorSetID;
		uint32_t binding;
		uint32_t startArrayIndex;
		std::vector<std::optional<IDObject<VulkanSimplifiedInternal::AutoCleanupUniformBuffer>>> uniformBufferIDList;

		UniformBufferDescriptorSetWriteData();
	};
}