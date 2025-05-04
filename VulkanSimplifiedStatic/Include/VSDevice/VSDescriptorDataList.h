#pragma once

#include <CustomLists\IDObjectDef.h>

#include "VSDescriptorDataListDef.h"

namespace VulkanSimplifiedInternal
{
	class DescriptorDataListInternal;

	struct DescriptorSetLayoutBindingData;
}

namespace VulkanSimplified
{
	class DescriptorDataList
	{
	public:
		DescriptorDataList(VulkanSimplifiedInternal::DescriptorDataListInternal& ref);
		~DescriptorDataList();

		IDObject<VulkanSimplifiedInternal::AutoCleanupDescriptorSetLayout> AddDescriptorSetLayout(uint32_t firstBinding,
			const std::vector<IDObject<VulkanSimplifiedInternal::DescriptorSetLayoutBindingData>>& descriptorSetLayoutBindings, size_t addOnReserving = 0);

	private:
		VulkanSimplifiedInternal::DescriptorDataListInternal& _internal;
	};
}