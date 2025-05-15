#pragma once

#include "VSAutoCleanupNIFDescriptorPool.h"

namespace VulkanSimplifiedInternal
{
	struct DescriptorPoolTypeCapacities;

	class AutoCleanupIFDescriptorPool : public AutoCleanupNIFDescriptorPool
	{
	public:
		AutoCleanupIFDescriptorPool(VkDevice device, VkDescriptorPool pool, uint32_t maxSetCount, const DescriptorPoolTypeCapacities& capacities);
		~AutoCleanupIFDescriptorPool();

		AutoCleanupIFDescriptorPool(const AutoCleanupIFDescriptorPool& rhs) noexcept = delete;
		AutoCleanupIFDescriptorPool(AutoCleanupIFDescriptorPool&& rhs) noexcept = default;

		AutoCleanupIFDescriptorPool& operator=(const AutoCleanupIFDescriptorPool& rhs) noexcept = delete;
		AutoCleanupIFDescriptorPool& operator=(AutoCleanupIFDescriptorPool&& rhs) noexcept = default;
	};
}