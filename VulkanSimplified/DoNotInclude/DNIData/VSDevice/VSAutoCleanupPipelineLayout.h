#pragma once

typedef struct VkDevice_T* VkDevice;
typedef struct VkPipelineLayout_T* VkPipelineLayout;

namespace VulkanSimplified
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