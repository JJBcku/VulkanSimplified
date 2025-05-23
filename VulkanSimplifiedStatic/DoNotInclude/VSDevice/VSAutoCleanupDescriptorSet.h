#pragma once

namespace VulkanSimplifiedInternal
{
	class AutoCleanupDescriptorSet
	{
	public:
		VkDescriptorSet GetDescriptorSet() const;

	protected:
		AutoCleanupDescriptorSet(VkDescriptorSet set);
		~AutoCleanupDescriptorSet();

		AutoCleanupDescriptorSet(const AutoCleanupDescriptorSet& rhs) noexcept = default;
		AutoCleanupDescriptorSet(AutoCleanupDescriptorSet&& rhs) noexcept = default;

		AutoCleanupDescriptorSet& operator=(const AutoCleanupDescriptorSet& rhs) noexcept = default;
		AutoCleanupDescriptorSet& operator=(AutoCleanupDescriptorSet&& rhs) noexcept = default;

		VkDescriptorSet _set;
	};
}