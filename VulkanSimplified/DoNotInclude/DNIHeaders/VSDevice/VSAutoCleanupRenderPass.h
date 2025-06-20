#pragma once

typedef struct VkDevice_T* VkDevice;
typedef struct VkRenderPass_T* VkRenderPass;

namespace VulkanSimplified
{
	class AutoCleanupRenderPass
	{
	public:
		AutoCleanupRenderPass(VkDevice device, VkRenderPass renderPass);
		~AutoCleanupRenderPass();

		AutoCleanupRenderPass(const AutoCleanupRenderPass&) noexcept = delete;
		AutoCleanupRenderPass(AutoCleanupRenderPass&& rhs) noexcept;

		AutoCleanupRenderPass& operator=(const AutoCleanupRenderPass&) noexcept = delete;
		AutoCleanupRenderPass& operator=(AutoCleanupRenderPass&& rhs) noexcept;

		VkRenderPass GetRenderPass() const;

	private:
		VkDevice _device;
		VkRenderPass _renderPass;

		void DestroyRenderPass();
	};
}