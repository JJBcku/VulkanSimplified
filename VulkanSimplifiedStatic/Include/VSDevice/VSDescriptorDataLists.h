#pragma once

#include <CustomLists\IDObjectDef.h>

#include "VSDescriptorDataListDef.h"

#include "../VSCommon/VSDescriptorTypeFlagsDef.h"

namespace VulkanSimplifiedInternal
{
	class DescriptorDataListsInternal;

	struct DescriptorSetLayoutBindingData;
}

namespace VulkanSimplified
{
	class DescriptorDataLists
	{
	public:
		DescriptorDataLists(VulkanSimplifiedInternal::DescriptorDataListsInternal& ref);
		~DescriptorDataLists();

		IDObject<VulkanSimplifiedInternal::AutoCleanupDescriptorSetLayout> AddDescriptorSetLayout(uint32_t firstBinding,
			const std::vector<IDObject<VulkanSimplifiedInternal::DescriptorSetLayoutBindingData>>& descriptorSetLayoutBindings, size_t addOnReserving = 0);

		IDObject<VulkanSimplifiedInternal::AutoCleanupNIFDescriptorPool> AddNoIndividualFreeingDescriptorPool(uint32_t maxTotalSetCount,
			const std::vector<std::pair<DescriptorTypeFlagBits, uint32_t>>& maxTypeCountsList, size_t addOnReserving = 0);

		IDObject<VulkanSimplifiedInternal::AutoCleanupIFDescriptorPool> AddIndividualFreeingDescriptorPool(uint32_t maxTotalSetCount,
			const std::vector<std::pair<DescriptorTypeFlagBits, uint32_t>>& maxTypeCountsList, size_t addOnReserving = 0);

	private:
		VulkanSimplifiedInternal::DescriptorDataListsInternal& _internal;
	};
}