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
	struct UniformBufferDescriptorSetWriteData;

	class DescriptorDataLists
	{
	public:
		DescriptorDataLists(VulkanSimplifiedInternal::DescriptorDataListsInternal& ref);
		~DescriptorDataLists();

		IDObject<VulkanSimplifiedInternal::AutoCleanupDescriptorSetLayout> AddDescriptorSetLayout(uint32_t firstBinding,
			const std::vector<IDObject<VulkanSimplifiedInternal::DescriptorSetLayoutBindingData>>& descriptorSetLayoutBindings, size_t addOnReserving = 0);

		IDObject<VulkanSimplifiedInternal::AutoCleanupNIFDescriptorPool> AddNoIndividualFreeingDescriptorPool(uint32_t maxTotalSetCount,
			const std::vector<std::pair<DescriptorTypeFlagBits, uint32_t>>& maxTypeCountsList, size_t addOnReserving = 0);

		std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupUniformBufferDescriptorSet>> AllocateNIFUniformBufferDescriptorSets(
			IDObject<VulkanSimplifiedInternal::AutoCleanupNIFDescriptorPool> descriptorPoolID,
			std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupDescriptorSetLayout>> descriptorSetLayoutIDs);

		void WriteNIFUniformBufferDescriptorSets(IDObject<VulkanSimplifiedInternal::AutoCleanupNIFDescriptorPool> descriptorPoolID,
			const std::vector<UniformBufferDescriptorSetWriteData>& writeDataList);

		IDObject<VulkanSimplifiedInternal::AutoCleanupIFDescriptorPool> AddIndividualFreeingDescriptorPool(uint32_t maxTotalSetCount,
			const std::vector<std::pair<DescriptorTypeFlagBits, uint32_t>>& maxTypeCountsList, size_t addOnReserving = 0);

		std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupUniformBufferDescriptorSet>> AllocateIFUniformBufferDescriptorSets(
			IDObject<VulkanSimplifiedInternal::AutoCleanupIFDescriptorPool> descriptorPoolID,
			std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupDescriptorSetLayout>> descriptorSetLayoutIDs);

		void WriteIFUniformBufferDescriptorSets(IDObject<VulkanSimplifiedInternal::AutoCleanupIFDescriptorPool> descriptorPoolID,
			const std::vector<UniformBufferDescriptorSetWriteData>& writeDataList);

	private:
		VulkanSimplifiedInternal::DescriptorDataListsInternal& _internal;
	};
}