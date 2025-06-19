#pragma once

typedef struct VkDevice_T* VkDevice;
typedef struct VkSampler_T* VkSampler;

namespace VulkanSimplifiedInternal
{
	class AutoCleanupSampler
	{
	public:
		AutoCleanupSampler(VkDevice device, VkSampler sampler);
		~AutoCleanupSampler();

		AutoCleanupSampler(const AutoCleanupSampler& rhs) noexcept = delete;
		AutoCleanupSampler(AutoCleanupSampler&& rhs) noexcept;

		AutoCleanupSampler& operator=(const AutoCleanupSampler& rhs) noexcept = delete;
		AutoCleanupSampler& operator=(AutoCleanupSampler&& rhs) noexcept;

		VkSampler GetSampler() const;

	private:
		VkDevice _device;
		VkSampler _sampler;

		void DestroySampler();
	};
}