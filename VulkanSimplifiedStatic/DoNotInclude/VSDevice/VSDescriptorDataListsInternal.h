#pragma once

#include <CustomLists/UnsortedIDVector.h>

#include "../../Include/VSCommon/VSDescriptorTypeFlagsDef.h"

#include "../../Include/VSDevice/VSDescriptorDataListDef.h"
#include "../../Include/VSDevice/VSImageDataListsDef.h"

namespace VulkanSimplified
{
	struct DescriptorListsInitialCapacities;

	struct UniformBufferDescriptorSetWriteData;
}

namespace VulkanSimplifiedInternal
{
	class SharedDescriptorDataListInternal;
	class DataBufferListsInternal;
	class ImageDataListsInternal;

	struct DescriptorSetLayoutBindingData;

	class DescriptorDataListsInternal
	{
	public:
		DescriptorDataListsInternal(const SharedDescriptorDataListInternal& sharedDescriptorData, const DataBufferListsInternal& dataBufferList, const ImageDataListsInternal& imageList,
			VkDevice device, const VulkanSimplified::DescriptorListsInitialCapacities& initialCapacities);
		~DescriptorDataListsInternal();

		IDObject<AutoCleanupDescriptorSetLayout> AddDescriptorSetLayout(uint32_t firstBinding,
			const std::vector<VulkanSimplified::DescriptorSetBindingFullData>& descriptorSetLayoutBindings, size_t addOnReserving);

		std::vector<VkDescriptorSetLayout> GetDescriptorSetLayouts(const std::vector<IDObject<AutoCleanupDescriptorSetLayout>>& layoutIDs) const;

		IDObject<AutoCleanupNIFDescriptorPool> AddNoIndividualFreeingDescriptorPool(uint32_t maxTotalSetCount,
			const std::vector<std::pair<VulkanSimplified::DescriptorTypeFlagBits, uint32_t>>& maxTypeCountsList, size_t addOnReserving);

		std::vector<IDObject<AutoCleanupDescriptorSet>> AllocateNIFDescriptorSets(IDObject<AutoCleanupNIFDescriptorPool> descriptorPoolID,
			const std::vector<IDObject<AutoCleanupDescriptorSetLayout>>& descriptorSetLayoutIDs);

		void WriteNIFUniformBufferDescriptorSetBindings(IDObject<AutoCleanupNIFDescriptorPool> descriptorPoolID,
			const std::vector<VulkanSimplified::UniformBufferDescriptorSetWriteData>& writeDataList);

		VkDescriptorSet GetNIFDescriptorSet(IDObject<AutoCleanupNIFDescriptorPool> descriptorPoolID,
			IDObject<AutoCleanupDescriptorSet> descriptorSetID) const;
		std::vector<VkDescriptorSet> GetNIFDescriptorSetList(IDObject<AutoCleanupNIFDescriptorPool> descriptorPoolID,
			const std::vector<IDObject<AutoCleanupDescriptorSet>>& descriptorSetIDs) const;

		IDObject<AutoCleanupIFDescriptorPool> AddIndividualFreeingDescriptorPool(uint32_t maxTotalSetCount,
			const std::vector<std::pair<VulkanSimplified::DescriptorTypeFlagBits, uint32_t>>& maxTypeCountsList, size_t addOnReserving);

		std::vector<IDObject<AutoCleanupDescriptorSet>> AllocateIFDescriptorSets(IDObject<AutoCleanupIFDescriptorPool> descriptorPoolID,
			const std::vector<IDObject<AutoCleanupDescriptorSetLayout>>& descriptorSetLayoutIDs);

		void WriteIFUniformBufferDescriptorSetBindings(IDObject<AutoCleanupIFDescriptorPool> descriptorPoolID,
			const std::vector<VulkanSimplified::UniformBufferDescriptorSetWriteData>& writeDataList);

		VkDescriptorSet GetIFDescriptorSet(IDObject<AutoCleanupIFDescriptorPool> descriptorPoolID,
			IDObject<AutoCleanupDescriptorSet> descriptorSetID) const;
		std::vector<VkDescriptorSet> GetIFDescriptorSetList(IDObject<AutoCleanupIFDescriptorPool> descriptorPoolID,
			const std::vector<IDObject<AutoCleanupDescriptorSet>>& descriptorSetIDs) const;

	private:
		const SharedDescriptorDataListInternal& _sharedDescriptorData;
		const DataBufferListsInternal& _dataBufferList;
		const ImageDataListsInternal& _imageList;
		VkDevice _device;

		UnsortedIDVector<AutoCleanupDescriptorSetLayout> _descriptorSetLayouts;

		UnsortedIDVector<AutoCleanupNIFDescriptorPool> _NIFDescriptorPools;
		UnsortedIDVector<AutoCleanupIFDescriptorPool> _IFDescriptorPools;
	};
}