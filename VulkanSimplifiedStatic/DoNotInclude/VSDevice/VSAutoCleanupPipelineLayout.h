#pragma once

namespace VulkanSimplifiedInternal
{
	class AutoCleanupPipelineLayout
	{
	public:
		AutoCleanupPipelineLayout(VkDevice device, VkPipelineLayout layout);
		~AutoCleanupPipelineLayout();

		AutoCleanupPipelineLayout(const AutoCleanupPipelineLayout&) noexcept = delete;
		AutoCleanupPipelineLayout(AutoCleanupPipelineLayout&& rhs) noexcept;

		AutoCleanupPipelineLayout& operator=(const AutoCleanupPipelineLayout&) noexcept = delete;
		AutoCleanupPipelineLayout& operator=(AutoCleanupPipelineLayout&& rhs) noexcept;

		VkPipelineLayout GetPipelineLayout() const;

	private:
		VkDevice _device;
		VkPipelineLayout _layout;

		void DestroyLayout();
	};
}