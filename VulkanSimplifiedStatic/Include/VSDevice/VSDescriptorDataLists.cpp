#include "VSDeviceIpch.h"
#include "VSDescriptorDataLists.h"

#include "../../DoNotInclude/VSDevice/VSDescriptorDataListsInternal.h"

namespace VulkanSimplified
{
	DescriptorDataLists::DescriptorDataLists(VulkanSimplifiedInternal::DescriptorDataListsInternal& ref) : _internal(ref)
	{
	}

	DescriptorDataLists::~DescriptorDataLists()
	{
	}

	IDObject<VulkanSimplifiedInternal::AutoCleanupDescriptorSetLayout> DescriptorDataLists::AddDescriptorSetLayout(uint32_t firstBinding,
		const std::vector<IDObject<VulkanSimplifiedInternal::DescriptorSetLayoutBindingData>>& descriptorSetLayoutBindings, size_t addOnReserving)
	{
		return _internal.AddDescriptorSetLayout(firstBinding, descriptorSetLayoutBindings, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::AutoCleanupNIFDescriptorPool> DescriptorDataLists::AddNoIndividualFreeingDescriptorPool(uint32_t maxTotalSetCount,
		const std::vector<std::pair<DescriptorTypeFlagBits, uint32_t>>& maxTypeCountsList, size_t addOnReserving)
	{
		return _internal.AddNoIndividualFreeingDescriptorPool(maxTotalSetCount, maxTypeCountsList, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::AutoCleanupIFDescriptorPool> DescriptorDataLists::AddIndividualFreeingDescriptorPool(uint32_t maxTotalSetCount,
		const std::vector<std::pair<DescriptorTypeFlagBits, uint32_t>>& maxTypeCountsList, size_t addOnReserving)
	{
		return _internal.AddIndividualFreeingDescriptorPool(maxTotalSetCount, maxTypeCountsList, addOnReserving);
	}

}