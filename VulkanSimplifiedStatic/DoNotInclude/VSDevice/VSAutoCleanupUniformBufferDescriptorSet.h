#pragma once

#include <CustomLists/IDObject.h>

#include "VSAutoCleanupDescriptorSet.h"

#include "../../Include/VSDevice/VSDataBufferListsDef.h"

namespace VulkanSimplifiedInternal
{
	class AutoCleanupUniformBufferDescriptorSet : public AutoCleanupDescriptorSet
	{
	public:
		AutoCleanupUniformBufferDescriptorSet(VkDescriptorSet set);
		~AutoCleanupUniformBufferDescriptorSet();

		AutoCleanupUniformBufferDescriptorSet(const AutoCleanupUniformBufferDescriptorSet& rhs) noexcept = default;
		AutoCleanupUniformBufferDescriptorSet(AutoCleanupUniformBufferDescriptorSet&& rhs) noexcept = default;

		AutoCleanupUniformBufferDescriptorSet& operator=(const AutoCleanupUniformBufferDescriptorSet& rhs) noexcept = default;
		AutoCleanupUniformBufferDescriptorSet& operator=(AutoCleanupUniformBufferDescriptorSet&& rhs) noexcept = default;
	};
}