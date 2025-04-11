#pragma once

#include <CustomLists/UnsortedIDVector.h>

namespace VulkanSimplified
{
	struct DescriptorListsInitialCapacities;
}

namespace VulkanSimplifiedInternal
{
	class SharedDescriptorDataListInternal;

	class AutoCleanupDescriptorSetLayout;
	struct DescriptorSetLayoutBindingData;

	class DescriptorDataListInternal
	{
	public:
		DescriptorDataListInternal(const SharedDescriptorDataListInternal& sharedDescriptorData, VkDevice device,
			const VulkanSimplified::DescriptorListsInitialCapacities& initialCapacities);
		~DescriptorDataListInternal();

		IDObject<AutoCleanupDescriptorSetLayout> AddDescriptorSetLayout(uint32_t firstBinding,
			const std::vector<IDObject<DescriptorSetLayoutBindingData>>& descriptorSetLayoutBindings, size_t addOnReserving);

		std::vector<VkDescriptorSetLayout> GetDescriptorSetLayouts(const std::vector<IDObject<AutoCleanupDescriptorSetLayout>>& layoutIDs) const;

	private:
		const SharedDescriptorDataListInternal& _sharedDescriptorData;
		VkDevice _device;

		UnsortedIDVector<AutoCleanupDescriptorSetLayout> _descriptorSetLayouts;
	};
}