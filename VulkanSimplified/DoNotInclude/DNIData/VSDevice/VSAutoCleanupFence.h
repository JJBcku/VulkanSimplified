#pragma once

typedef struct VkDevice_T* VkDevice;
typedef struct VkFence_T* VkFence;

namespace VulkanSimplified
{
	class AutoCleanupFence
	{
	public:
		AutoCleanupFence(VkDevice device, VkFence fence);
		~AutoCleanupFence();

		VkFence GetFence() const;

		AutoCleanupFence(const AutoCleanupFence&) noexcept = delete;
		AutoCleanupFence(AutoCleanupFence&& rhs) noexcept;

		AutoCleanupFence& operator=(const AutoCleanupFence&) noexcept = delete;
		AutoCleanupFence& operator=(AutoCleanupFence&& rhs) noexcept;

	private:
		VkDevice _device;
		VkFence _fence;

		void DestroyFence();
	};
}