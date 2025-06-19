#pragma once

typedef struct VkDescriptorSet_T* VkDescriptorSet;

namespace VulkanSimplifiedInternal
{
	class AutoCleanupDescriptorSet
	{
	public:
		AutoCleanupDescriptorSet(VkDescriptorSet set);
		~AutoCleanupDescriptorSet();

		AutoCleanupDescriptorSet(const AutoCleanupDescriptorSet& rhs) noexcept = default;
		AutoCleanupDescriptorSet(AutoCleanupDescriptorSet&& rhs) noexcept = default;

		AutoCleanupDescriptorSet& operator=(const AutoCleanupDescriptorSet& rhs) noexcept = default;
		AutoCleanupDescriptorSet& operator=(AutoCleanupDescriptorSet&& rhs) noexcept = default;

		VkDescriptorSet GetDescriptorSet() const;

	private:
		VkDescriptorSet _set;
	};
}