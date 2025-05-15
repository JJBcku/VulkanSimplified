#include "VSDeviceIpch.h"
#include "VSDescriptorListsInitialCapacities.h"

namespace VulkanSimplified
{
	DescriptorListsInitialCapacities::DescriptorListsInitialCapacities()
	{
		descriptorSetListInitialCapacity = 0;

		noIndividualFreeingDescriptorPoolsListInitialCapacity = 0;
		individualFreeingDescriptorPoolsListInitialCapacity = 0;
	}
}