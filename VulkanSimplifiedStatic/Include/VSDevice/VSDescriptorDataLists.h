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
	struct DescriptorSetUniformBufferBindingWriteData;
	struct DescriptorSetCombined2DTextureSamplerWriteData;

	class DescriptorDataLists
	{
	public:
		DescriptorDataLists(VulkanSimplifiedInternal::DescriptorDataListsInternal& ref);
		~DescriptorDataLists();

		IDObject<VulkanSimplifiedInternal::AutoCleanupDescriptorSetLayout> AddDescriptorSetLayout(uint32_t firstBinding,
			const std::vector<DescriptorSetBindingFullData>& descriptorSetLayoutBindings, size_t addOnReserving = 0);

		IDObject<VulkanSimplifiedInternal::AutoCleanupNIFDescriptorPool> AddNoIndividualFreeingDescriptorPool(uint32_t maxTotalSetCount,
			const std::vector<std::pair<DescriptorTypeFlagBits, uint32_t>>& maxTypeCountsList, size_t addOnReserving = 0);

		std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupDescriptorSet>> AllocateNIFDescriptorSets(
			IDObject<VulkanSimplifiedInternal::AutoCleanupNIFDescriptorPool> descriptorPoolID,
			std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupDescriptorSetLayout>> descriptorSetLayoutIDs);

		void WriteNIFDescriptorSetUniformBufferBindings(IDObject<VulkanSimplifiedInternal::AutoCleanupNIFDescriptorPool> descriptorPoolID,
			const std::vector<DescriptorSetUniformBufferBindingWriteData>& writeDataList);
		void WriteNIFDescriptorSetCombined2DTextureSamplerBindings(IDObject<VulkanSimplifiedInternal::AutoCleanupNIFDescriptorPool> descriptorPoolID,
			const std::vector<DescriptorSetCombined2DTextureSamplerWriteData>& writeDataList);

		IDObject<VulkanSimplifiedInternal::AutoCleanupIFDescriptorPool> AddIndividualFreeingDescriptorPool(uint32_t maxTotalSetCount,
			const std::vector<std::pair<DescriptorTypeFlagBits, uint32_t>>& maxTypeCountsList, size_t addOnReserving = 0);

		std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupDescriptorSet>> AllocateIFDescriptorSets(
			IDObject<VulkanSimplifiedInternal::AutoCleanupIFDescriptorPool> descriptorPoolID,
			std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupDescriptorSetLayout>> descriptorSetLayoutIDs);

		void WriteIFDescriptorSetUniformBufferBindings(IDObject<VulkanSimplifiedInternal::AutoCleanupIFDescriptorPool> descriptorPoolID,
			const std::vector<DescriptorSetUniformBufferBindingWriteData>& writeDataList);
		void WriteIFDescriptorSetCombined2DTextureSamplerBindings(IDObject<VulkanSimplifiedInternal::AutoCleanupIFDescriptorPool> descriptorPoolID,
			const std::vector<DescriptorSetCombined2DTextureSamplerWriteData>& writeDataList);

	private:
		VulkanSimplifiedInternal::DescriptorDataListsInternal& _internal;
	};
}