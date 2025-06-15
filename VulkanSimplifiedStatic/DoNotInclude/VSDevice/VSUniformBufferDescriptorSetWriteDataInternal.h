#pragma once

#include <CustomLists/IDObject.h>

#include "../../Include/VSDevice/VSDescriptorDataListDef.h"

namespace VulkanSimplifiedInternal
{
	struct UniformBufferDescriptorSetWriteDataInternal
	{
		IDObject<AutoCleanupDescriptorSet> descriptorSetID;
		uint32_t binding;
		uint32_t startArrayIndex;
		std::vector<VkBuffer> bufferList;

		UniformBufferDescriptorSetWriteDataInternal();
	};
}