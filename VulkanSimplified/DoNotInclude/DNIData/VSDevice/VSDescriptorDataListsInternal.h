#pragma once

#include "../../../Include/VSCommon/VSDescriptorTypeFlagsDef.h"

#include "../../../Include/VSDevice/VSDescriptorDataListsDef.h"
#include "../../../Include/VSDevice/VSImageDataListsDef.h"

#include <CustomLists/UnsortedIDVector.h>

#include <vector>
#include <utility>
#include <stdint.h>

namespace VulkanSimplified
{
	struct DescriptorListsInitialCapacities;

	struct DescriptorSetUniformBufferBindingWriteData;
	struct DescriptorSetCombined2DTextureSamplerWriteData;
	struct DescriptorSetCombined2DArrayTextureSamplerWriteData;
}

typedef struct VkDevice_T* VkDevice;
typedef struct VkDescriptorSet_T* VkDescriptorSet;
typedef struct VkDescriptorSetLayout_T* VkDescriptorSetLayout;

namespace VulkanSimplified
{
	class SharedDescriptorDataListInternal;
	class DataBufferListsInternal;
	class ImageDataListsInternal;

	struct DescriptorSetLayoutBindingData;

	class DescriptorDataListsInternal
	{
	public:
		DescriptorDataListsInternal(const SharedDescriptorDataListInternal& sharedDescriptorData, const DataBufferListsInternal& dataBufferList, const ImageDataListsInternal& imageList,
			VkDevice device, const DescriptorListsInitialCapacities& initialCapacities);
		~DescriptorDataListsInternal();

		IDObject<AutoCleanupDescriptorSetLayout> AddDescriptorSetLayout(uint32_t firstBinding,
			const std::vector<DescriptorSetBindingFullData>& descriptorSetLayoutBindings, size_t addOnReserving);

		std::vector<VkDescriptorSetLayout> GetDescriptorSetLayouts(const std::vector<IDObject<AutoCleanupDescriptorSetLayout>>& layoutIDs) const;

		IDObject<AutoCleanupNIFDescriptorPool> AddNoIndividualFreeingDescriptorPool(uint32_t maxTotalSetCount,
			const std::vector<std::pair<DescriptorTypeFlagBits, uint32_t>>& maxTypeCountsList, size_t addOnReserving);

		std::vector<IDObject<AutoCleanupDescriptorSet>> AllocateNIFDescriptorSets(IDObject<AutoCleanupNIFDescriptorPool> descriptorPoolID,
			const std::vector<IDObject<AutoCleanupDescriptorSetLayout>>& descriptorSetLayoutIDs);

		void WriteNIFDescriptorSetUniformBufferBindings(IDObject<AutoCleanupNIFDescriptorPool> descriptorPoolID,
			const std::vector<DescriptorSetUniformBufferBindingWriteData>& writeDataList);
		void WriteNIFDescriptorSetCombined2DTextureSamplerBindings(IDObject<AutoCleanupNIFDescriptorPool> descriptorPoolID,
			const std::vector<DescriptorSetCombined2DTextureSamplerWriteData>& writeDataList);
		void WriteNIFDescriptorSetCombined2DArrayTextureSamplerBindings(IDObject<AutoCleanupNIFDescriptorPool> descriptorPoolID,
			const std::vector<DescriptorSetCombined2DArrayTextureSamplerWriteData>& writeDataList);

		VkDescriptorSet GetNIFDescriptorSet(IDObject<AutoCleanupNIFDescriptorPool> descriptorPoolID,
			IDObject<AutoCleanupDescriptorSet> descriptorSetID) const;
		std::vector<VkDescriptorSet> GetNIFDescriptorSetList(IDObject<AutoCleanupNIFDescriptorPool> descriptorPoolID,
			const std::vector<IDObject<AutoCleanupDescriptorSet>>& descriptorSetIDs) const;

		IDObject<AutoCleanupIFDescriptorPool> AddIndividualFreeingDescriptorPool(uint32_t maxTotalSetCount,
			const std::vector<std::pair<DescriptorTypeFlagBits, uint32_t>>& maxTypeCountsList, size_t addOnReserving);

		std::vector<IDObject<AutoCleanupDescriptorSet>> AllocateIFDescriptorSets(IDObject<AutoCleanupIFDescriptorPool> descriptorPoolID,
			const std::vector<IDObject<AutoCleanupDescriptorSetLayout>>& descriptorSetLayoutIDs);

		void WriteIFDescriptorSetUniformBufferBindings(IDObject<AutoCleanupIFDescriptorPool> descriptorPoolID,
			const std::vector<DescriptorSetUniformBufferBindingWriteData>& writeDataList);
		void WriteIFDescriptorSetCombined2DTextureSamplerBindings(IDObject<AutoCleanupIFDescriptorPool> descriptorPoolID,
			const std::vector<DescriptorSetCombined2DTextureSamplerWriteData>& writeDataList);
		void WriteIFDescriptorSetCombined2DArrayTextureSamplerBindings(IDObject<AutoCleanupIFDescriptorPool> descriptorPoolID,
			const std::vector<DescriptorSetCombined2DArrayTextureSamplerWriteData>& writeDataList);

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