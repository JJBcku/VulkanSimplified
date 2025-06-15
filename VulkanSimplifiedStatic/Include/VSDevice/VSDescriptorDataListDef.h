#pragma once

#include <CustomLists/IDObjectDef.h>

namespace VulkanSimplifiedInternal
{
	class AutoCleanupDescriptorSetLayout;

	class AutoCleanupNIFDescriptorPool;
	class AutoCleanupIFDescriptorPool;

	class AutoCleanupDescriptorSet;

	struct DescriptorSetLayoutBindingData;
	class AutoCleanupSampler;
}

namespace VulkanSimplified
{
	typedef std::pair<IDObject<VulkanSimplifiedInternal::DescriptorSetLayoutBindingData>,
		std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupSampler>>> DescriptorSetBindingFullData;
}