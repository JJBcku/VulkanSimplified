#include "VSSharedIpch.h"
#include "../../../Include/VSSharedData/VSSharedDescriptorDataList.h"

#include "../../../DoNotInclude/DNIHeaders/VSSharedData/VSSharedDescriptorDataListInternal.h"

#include "../../../Include/VSCommon/VSDescriptorTypeFlags.h"
#include "../../../Include/VSCommon/VSShaderTypeFlags.h"

namespace VulkanSimplified
{
	SharedDescriptorDataList::SharedDescriptorDataList(SharedDescriptorDataListInternal& ref) :  _internal(ref)
	{
	}

	SharedDescriptorDataList::~SharedDescriptorDataList()
	{
	}

	IDObject<DescriptorSetLayoutBindingData> SharedDescriptorDataList::AddDescriptorSetLayoutBindingsData(
		DescriptorTypeFlagBits descriptorType, uint32_t descriptorAmount, ShaderTypeFlags shaderStageFlags, size_t addOnReserving)
	{
		return _internal.AddDescriptorSetLayoutBindingsData(descriptorType, descriptorAmount, shaderStageFlags, addOnReserving);
	}

}