#pragma once

typedef struct VkDevice_T* VkDevice;
typedef struct VkFramebuffer_T* VkFramebuffer;

namespace VulkanSimplifiedInternal
{
	class AutoCleanupFramebuffer
	{
	public:
		AutoCleanupFramebuffer(VkDevice device, VkFramebuffer framebuffer);
		~AutoCleanupFramebuffer();

		AutoCleanupFramebuffer(const AutoCleanupFramebuffer&) noexcept = delete;
		AutoCleanupFramebuffer(AutoCleanupFramebuffer&& rhs) noexcept;

		AutoCleanupFramebuffer& operator=(const AutoCleanupFramebuffer&) noexcept = delete;
		AutoCleanupFramebuffer& operator=(AutoCleanupFramebuffer&& rhs) noexcept;

		VkFramebuffer GetFramebuffer() const;

	private:
		VkDevice _device;
		VkFramebuffer _framebuffer;

		void DestroyFramebuffer();
	};
}