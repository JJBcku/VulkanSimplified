#pragma once

typedef struct VkDevice_T* VkDevice;
typedef struct VkImageView_T* VkImageView;

namespace VulkanSimplified
{
	class AutoCleanupImageView
	{
	public:
		AutoCleanupImageView(VkDevice device, VkImageView imageView);
		~AutoCleanupImageView();

		AutoCleanupImageView(const AutoCleanupImageView&) noexcept = delete;
		AutoCleanupImageView(AutoCleanupImageView&& rhs) noexcept;

		AutoCleanupImageView& operator=(const AutoCleanupImageView&) noexcept = delete;
		AutoCleanupImageView& operator=(AutoCleanupImageView&& rhs) noexcept;

		VkImageView GetImageView() const;

	private:
		VkDevice _device;
		VkImageView _imageView;

		void DestroyImageView();
	};
}