#pragma once

#include <CustomLists/IDObject.h>

#include "../../../Include/VSDevice/VSDescriptorDataListDef.h"

#include <vector>
#include <stdint.h>

typedef struct VkBuffer_T* VkBuffer;

namespace VulkanSimplified
{
	struct DescriptorSetUniformBufferBindingWriteDataInternal
	{
		IDObject<AutoCleanupDescriptorSet> descriptorSetID;
		uint32_t binding;
		uint32_t startArrayIndex;
		std::vector<VkBuffer> bufferList;

		DescriptorSetUniformBufferBindingWriteDataInternal();
	};
}