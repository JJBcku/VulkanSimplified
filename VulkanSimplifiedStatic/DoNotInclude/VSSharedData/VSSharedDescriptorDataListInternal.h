#pragma once

#include <CustomLists/UnsortedIDVector.h>

#include "VSDescriptorSetLayoutBindingData.h"

#include "../../Include/VSCommon/VSDescriptorTypeFlagsDef.h"
#include "../../Include/VSCommon/VSShaderTypeFlagsDef.h"

namespace VulkanSimplified
{
	struct SharedDescriptorDataListCapacities;
}

namespace VulkanSimplifiedInternal
{
	class SharedDescriptorDataListInternal
	{
	public:
		SharedDescriptorDataListInternal(const VulkanSimplified::SharedDescriptorDataListCapacities& initalCapacities);
		~SharedDescriptorDataListInternal();

		IDObject<DescriptorSetLayoutBindingData> AddDescriptorSetLayoutBindingsData(VulkanSimplified::DescriptorTypeFlagBits descriptorType, uint32_t descriptorAmount,
			VulkanSimplified::ShaderTypeFlags shaderStageFlags, size_t addOnReserving);

		std::vector<VkDescriptorSetLayoutBinding> GetDescriptorSetLayoutBindings(uint32_t firstBinding, const std::vector<IDObject<DescriptorSetLayoutBindingData>>& bindingIDs) const;

	private:
		UnsortedIDVector<DescriptorSetLayoutBindingData> _bindingDataList;
	};
}