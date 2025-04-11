#include "VSDeviceIpch.h"
#include "VSDescriptorDataList.h"

#include "../../DoNotInclude/VSDevice/VSDescriptorDataListInternal.h"

namespace VulkanSimplified
{
	DescriptorDataList::DescriptorDataList(VulkanSimplifiedInternal::DescriptorDataListInternal& ref) : _internal(ref)
	{
	}

	DescriptorDataList::~DescriptorDataList()
	{
	}

	IDObject<VulkanSimplifiedInternal::AutoCleanupDescriptorSetLayout> DescriptorDataList::AddDescriptorSetLayout(uint32_t firstBinding,
		const std::vector<IDObject<VulkanSimplifiedInternal::DescriptorSetLayoutBindingData>>& descriptorSetLayoutBindings, size_t addOnReserving)
	{
		return _internal.AddDescriptorSetLayout(firstBinding, descriptorSetLayoutBindings, addOnReserving);
	}

}