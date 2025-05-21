#pragma once

#include <CustomLists/UnsortedIDVector.h>

#include "../../Include/VSCommon/VSDescriptorTypeFlagsDef.h"

#include "../../Include/VSDevice/VSDescriptorDataListDef.h"

namespace VulkanSimplified
{
	struct DescriptorListsInitialCapacities;

	struct UniformBufferDescriptorSetWriteData;
}

namespace VulkanSimplifiedInternal
{
	class SharedDescriptorDataListInternal;
	class DataBufferListsInternal;

	struct DescriptorSetLayoutBindingData;

	class DescriptorDataListsInternal
	{
	public:
		DescriptorDataListsInternal(const SharedDescriptorDataListInternal& sharedDescriptorData, const DataBufferListsInternal& dataBufferList, VkDevice device,
			const VulkanSimplified::DescriptorListsInitialCapacities& initialCapacities);
		~DescriptorDataListsInternal();

		IDObject<AutoCleanupDescriptorSetLayout> AddDescriptorSetLayout(uint32_t firstBinding,
			const std::vector<IDObject<DescriptorSetLayoutBindingData>>& descriptorSetLayoutBindings, size_t addOnReserving);

		std::vector<VkDescriptorSetLayout> GetDescriptorSetLayouts(const std::vector<IDObject<AutoCleanupDescriptorSetLayout>>& layoutIDs) const;

		IDObject<AutoCleanupNIFDescriptorPool> AddNoIndividualFreeingDescriptorPool(uint32_t maxTotalSetCount,
			const std::vector<std::pair<VulkanSimplified::DescriptorTypeFlagBits, uint32_t>>& maxTypeCountsList, size_t addOnReserving);

		std::vector<IDObject<AutoCleanupUniformBufferDescriptorSet>> AllocateNIFUniformBufferDescriptorSets(IDObject<AutoCleanupNIFDescriptorPool> descriptorPoolID,
			std::vector<IDObject<AutoCleanupDescriptorSetLayout>> descriptorSetLayoutIDs);

		void WriteNIFUniformBufferDescriptorSets(IDObject<AutoCleanupNIFDescriptorPool> descriptorPoolID,
			const std::vector<VulkanSimplified::UniformBufferDescriptorSetWriteData>& writeDataList);

		VkDescriptorSet GetNIFUniformBufferDescriptorSet(IDObject<AutoCleanupNIFDescriptorPool> descriptorPoolID,
			IDObject<AutoCleanupUniformBufferDescriptorSet> descriptorSetID) const;

		IDObject<AutoCleanupIFDescriptorPool> AddIndividualFreeingDescriptorPool(uint32_t maxTotalSetCount,
			const std::vector<std::pair<VulkanSimplified::DescriptorTypeFlagBits, uint32_t>>& maxTypeCountsList, size_t addOnReserving);

		std::vector<IDObject<AutoCleanupUniformBufferDescriptorSet>> AllocateIFUniformBufferDescriptorSets(IDObject<AutoCleanupIFDescriptorPool> descriptorPoolID,
			std::vector<IDObject<AutoCleanupDescriptorSetLayout>> descriptorSetLayoutIDs);

		void WriteIFUniformBufferDescriptorSets(IDObject<AutoCleanupIFDescriptorPool> descriptorPoolID,
			const std::vector<VulkanSimplified::UniformBufferDescriptorSetWriteData>& writeDataList);

		VkDescriptorSet GetIFUniformBufferDescriptorSet(IDObject<AutoCleanupIFDescriptorPool> descriptorPoolID,
			IDObject<AutoCleanupUniformBufferDescriptorSet> descriptorSetID) const;

	private:
		const SharedDescriptorDataListInternal& _sharedDescriptorData;
		const DataBufferListsInternal& _dataBufferList;
		VkDevice _device;

		UnsortedIDVector<AutoCleanupDescriptorSetLayout> _descriptorSetLayouts;

		UnsortedIDVector<AutoCleanupNIFDescriptorPool> _NIFDescriptorPools;
		UnsortedIDVector<AutoCleanupIFDescriptorPool> _IFDescriptorPools;
	};
}