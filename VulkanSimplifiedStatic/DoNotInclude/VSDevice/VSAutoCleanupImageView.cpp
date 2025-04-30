#include "VSDeviceNIpch.h"
#include "VSAutoCleanupImageView.h"

namespace VulkanSimplifiedInternal
{
	AutoCleanupImageView::AutoCleanupImageView(VkDevice device, VkImageView imageView) : _device(device), _imageView(imageView)
	{
	}

	AutoCleanupImageView::~AutoCleanupImageView()
	{
		DestroyImageView();
	}

	AutoCleanupImageView::AutoCleanupImageView(AutoCleanupImageView&& rhs) noexcept : _device(rhs._device), _imageView(rhs._imageView)
	{
		rhs._device = VK_NULL_HANDLE;
		rhs._imageView = VK_NULL_HANDLE;
	}

	AutoCleanupImageView& AutoCleanupImageView::operator=(AutoCleanupImageView&& rhs) noexcept
	{
		DestroyImageView();
		_device = rhs._device;
		_imageView = rhs._imageView;

		rhs._device = VK_NULL_HANDLE;
		rhs._imageView = VK_NULL_HANDLE;
		return *this;
	}

	VkImageView AutoCleanupImageView::GetImageView() const
	{
		return _imageView;
	}

	void AutoCleanupImageView::DestroyImageView()
	{
		if (_imageView != VK_NULL_HANDLE)
		{
			vkDestroyImageView(_device, _imageView, nullptr);
			_imageView = VK_NULL_HANDLE;
		}
	}
}