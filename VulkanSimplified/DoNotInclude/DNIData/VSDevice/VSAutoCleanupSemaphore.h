#pragma once

typedef struct VkDevice_T* VkDevice;
typedef struct VkSemaphore_T* VkSemaphore;

namespace VulkanSimplified
{
	class AutoCleanupSemaphore
	{
	public:
		AutoCleanupSemaphore(VkDevice device, VkSemaphore semaphore);
		~AutoCleanupSemaphore();

		AutoCleanupSemaphore(const AutoCleanupSemaphore&) noexcept = delete;
		AutoCleanupSemaphore(AutoCleanupSemaphore&& rhs) noexcept;

		AutoCleanupSemaphore& operator=(const AutoCleanupSemaphore&) noexcept = delete;
		AutoCleanupSemaphore& operator=(AutoCleanupSemaphore&& rhs) noexcept;

		VkSemaphore GetSemaphore() const;

	private:
		VkDevice _device;
		VkSemaphore _semaphore;

		void DestroySemaphore();
	};
}