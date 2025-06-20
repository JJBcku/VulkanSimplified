#pragma once

#include <CustomLists/IDObject.h>

#include <VSDescriptorDataListDef.h>

struct VulkanDescriptorData
{
	IDObject<VS::AutoCleanupNIFDescriptorPool> descriptorPool;

	std::vector<IDObject<VS::AutoCleanupDescriptorSet>> descriptorSets;

	VulkanDescriptorData();
};