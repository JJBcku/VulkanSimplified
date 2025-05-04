#pragma once

#include <CustomLists\IDObjectDef.h>

#include "VSSharedDescriptorDataListDef.h"

namespace VulkanSimplifiedInternal
{
	class SharedDescriptorDataListInternal;
}

namespace VulkanSimplified
{
	class SharedDescriptorDataList
	{
	public:
		SharedDescriptorDataList(VulkanSimplifiedInternal::SharedDescriptorDataListInternal& ref);
		~SharedDescriptorDataList();

		IDObject<VulkanSimplifiedInternal::DescriptorSetLayoutBindingData> AddDescriptorSetLayoutBindingsData(VulkanSimplified::DescriptorTypeFlagBits descriptorType,
			uint32_t descriptorAmount, VulkanSimplified::ShaderTypeFlags shaderStageFlags, size_t addOnReserving = 0);

	private:
		VulkanSimplifiedInternal::SharedDescriptorDataListInternal& _internal;
	};
}