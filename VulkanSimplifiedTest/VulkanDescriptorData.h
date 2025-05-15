#pragma once

#include <CustomLists/IDObject.h>

#include <VSDescriptorDataListDef.h>

struct VulkanDescriptorData
{
	IDObject<VulkanSimplifiedInternal::AutoCleanupNIFDescriptorPool> descriptorPool;

	VulkanDescriptorData();
};