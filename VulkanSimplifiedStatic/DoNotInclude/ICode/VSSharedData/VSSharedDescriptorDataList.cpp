#include "VSSharedIpch.h"
#include "../../../Include/VSSharedData/VSSharedDescriptorDataList.h"

#include "../../../DoNotInclude/DNIHeaders/VSSharedData/VSSharedDescriptorDataListInternal.h"

#include "../../../Include/VSCommon/VSDescriptorTypeFlags.h"
#include "../../../Include/VSCommon/VSShaderTypeFlags.h"

namespace VulkanSimplified
{
	SharedDescriptorDataList::SharedDescriptorDataList(VulkanSimplifiedInternal::SharedDescriptorDataListInternal& ref) :  _internal(ref)
	{
	}

	SharedDescriptorDataList::~SharedDescriptorDataList()
	{
	}

	IDObject<VulkanSimplifiedInternal::DescriptorSetLayoutBindingData> SharedDescriptorDataList::AddDescriptorSetLayoutBindingsData(
		VulkanSimplified::DescriptorTypeFlagBits descriptorType, uint32_t descriptorAmount, VulkanSimplified::ShaderTypeFlags shaderStageFlags, size_t addOnReserving)
	{
		return _internal.AddDescriptorSetLayoutBindingsData(descriptorType, descriptorAmount, shaderStageFlags, addOnReserving);
	}

}