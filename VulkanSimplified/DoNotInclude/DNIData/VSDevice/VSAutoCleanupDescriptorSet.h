#pragma once

typedef struct VkDescriptorSet_T* VkDescriptorSet;

namespace VulkanSimplified
{
	class AutoCleanupDescriptorSet
	{
	public:
		AutoCleanupDescriptorSet(VkDescriptorSet set);
		~AutoCleanupDescriptorSet();

		AutoCleanupDescriptorSet(const AutoCleanupDescriptorSet& rhs) noexcept = delete;
		AutoCleanupDescriptorSet(AutoCleanupDescriptorSet&& rhs) noexcept;

		AutoCleanupDescriptorSet& operator=(const AutoCleanupDescriptorSet& rhs) noexcept = delete;
		AutoCleanupDescriptorSet& operator=(AutoCleanupDescriptorSet&& rhs) noexcept;

		VkDescriptorSet GetDescriptorSet() const;

	private:
		VkDescriptorSet _set;
	};
}