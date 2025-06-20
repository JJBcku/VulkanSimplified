#pragma once

#include <CustomLists/IDObject.h>

#include <VSDescriptorDataListDef.h>

struct VulkanDescriptorData
{
	IDObject<VulkanSimplified::AutoCleanupNIFDescriptorPool> descriptorPool;

	std::vector<IDObject<VulkanSimplified::AutoCleanupDescriptorSet>> descriptorSets;

	VulkanDescriptorData();
};