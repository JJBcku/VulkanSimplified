#pragma once

#include <CustomLists/IDObject.h>

#include <VSDescriptorDataListDef.h>

struct VulkanDescriptorData
{
	IDObject<VulkanSimplifiedInternal::AutoCleanupNIFDescriptorPool> descriptorPool;

	std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupUniformBufferDescriptorSet>> uniformDescriptorSets;

	VulkanDescriptorData();
};