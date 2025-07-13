#pragma once

#include <CustomLists/UnsortedIDVector.h>

#include "../../../Include/VSCommon/VSDescriptorTypeFlagsDef.h"
#include "../../../Include/VSCommon/VSShaderTypeFlagsDef.h"

#include <stdint.h>
#include <vector>

struct VkDescriptorSetLayoutBinding;

namespace VulkanSimplified
{
	struct SharedDescriptorDataListCapacities;
}

namespace VulkanSimplified
{
	struct DescriptorSetLayoutBindingData;

	class SharedDescriptorDataListInternal
	{
	public:
		SharedDescriptorDataListInternal(const SharedDescriptorDataListCapacities& initalCapacities);
		~SharedDescriptorDataListInternal();

		IDObject<DescriptorSetLayoutBindingData> AddDescriptorSetLayoutBindingsData(DescriptorTypeFlagBits descriptorType, uint32_t descriptorAmount,
			ShaderTypeFlags shaderStageFlags, size_t addOnReserving);

		IDObject<DescriptorSetLayoutBindingData> AddUniqueDescriptorSetLayoutBindingsData(DescriptorTypeFlagBits descriptorType, uint32_t descriptorAmount,
			ShaderTypeFlags shaderStageFlags, size_t addOnReserving);

		std::vector<VkDescriptorSetLayoutBinding> GetDescriptorSetLayoutBindings(uint32_t firstBinding, const std::vector<IDObject<DescriptorSetLayoutBindingData>>& bindingIDs) const;

	private:
		UnsortedIDVector<DescriptorSetLayoutBindingData> _bindingDataList;
	};
}