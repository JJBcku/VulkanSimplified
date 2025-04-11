#pragma once

namespace VulkanSimplifiedInternal
{
	class AutoCleanupDescriptorSetLayout
	{
	public:
		AutoCleanupDescriptorSetLayout(VkDevice device, VkDescriptorSetLayout descriptorSetLayout);
		~AutoCleanupDescriptorSetLayout();

		AutoCleanupDescriptorSetLayout(const AutoCleanupDescriptorSetLayout&) noexcept = delete;
		AutoCleanupDescriptorSetLayout(AutoCleanupDescriptorSetLayout&& rhs) noexcept;

		AutoCleanupDescriptorSetLayout& operator=(const AutoCleanupDescriptorSetLayout&) noexcept = delete;
		AutoCleanupDescriptorSetLayout& operator=(AutoCleanupDescriptorSetLayout&& rhs) noexcept;

		VkDescriptorSetLayout GetDescriptorSetLayout() const;

	private:
		VkDevice _device;
		VkDescriptorSetLayout _descriptorSetLayout;

		void DestroyLayout();
	};
}