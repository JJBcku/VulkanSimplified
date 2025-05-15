#pragma once

#include <CustomLists/UnsortedIDVector.h>

#include "../../Include/VSCommon/VSDescriptorTypeFlagsDef.h"

#include "../../Include/VSDevice/VSDescriptorDataListDef.h"

namespace VulkanSimplified
{
	struct DescriptorListsInitialCapacities;
}

namespace VulkanSimplifiedInternal
{
	class SharedDescriptorDataListInternal;

	struct DescriptorSetLayoutBindingData;

	class DescriptorDataListsInternal
	{
	public:
		DescriptorDataListsInternal(const SharedDescriptorDataListInternal& sharedDescriptorData, VkDevice device,
			const VulkanSimplified::DescriptorListsInitialCapacities& initialCapacities);
		~DescriptorDataListsInternal();

		IDObject<AutoCleanupDescriptorSetLayout> AddDescriptorSetLayout(uint32_t firstBinding,
			const std::vector<IDObject<DescriptorSetLayoutBindingData>>& descriptorSetLayoutBindings, size_t addOnReserving);

		std::vector<VkDescriptorSetLayout> GetDescriptorSetLayouts(const std::vector<IDObject<AutoCleanupDescriptorSetLayout>>& layoutIDs) const;

		IDObject<AutoCleanupNIFDescriptorPool> AddNoIndividualFreeingDescriptorPool(uint32_t maxTotalSetCount,
			const std::vector<std::pair<VulkanSimplified::DescriptorTypeFlagBits, uint32_t>>& maxTypeCountsList, size_t addOnReserving);

		IDObject<AutoCleanupIFDescriptorPool> AddIndividualFreeingDescriptorPool(uint32_t maxTotalSetCount,
			const std::vector<std::pair<VulkanSimplified::DescriptorTypeFlagBits, uint32_t>>& maxTypeCountsList, size_t addOnReserving);

	private:
		const SharedDescriptorDataListInternal& _sharedDescriptorData;
		VkDevice _device;

		UnsortedIDVector<AutoCleanupDescriptorSetLayout> _descriptorSetLayouts;

		UnsortedIDVector<AutoCleanupNIFDescriptorPool> _NIFDescriptorPools;
		UnsortedIDVector<AutoCleanupIFDescriptorPool> _IFDescriptorPools;
	};
}