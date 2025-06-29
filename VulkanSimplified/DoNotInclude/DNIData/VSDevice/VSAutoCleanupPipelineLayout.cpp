#include "VSDeviceDNIpch.h"
#include "VSAutoCleanupPipelineLayout.h"

namespace VulkanSimplified
{
	AutoCleanupPipelineLayout::AutoCleanupPipelineLayout(VkDevice device, VkPipelineLayout layout) : _device(device), _layout(layout)
	{
	}

	AutoCleanupPipelineLayout::~AutoCleanupPipelineLayout()
	{
		DestroyLayout();
	}

	AutoCleanupPipelineLayout::AutoCleanupPipelineLayout(AutoCleanupPipelineLayout&& rhs) noexcept : _device(rhs._device), _layout(rhs._layout)
	{
		rhs._device = VK_NULL_HANDLE;
		rhs._layout = VK_NULL_HANDLE;
	}

	AutoCleanupPipelineLayout& AutoCleanupPipelineLayout::operator=(AutoCleanupPipelineLayout&& rhs) noexcept
	{
		DestroyLayout();

		_device = rhs._device;
		_layout = rhs._layout;

		rhs._device = VK_NULL_HANDLE;
		rhs._layout = VK_NULL_HANDLE;

		return *this;
	}

	VkPipelineLayout AutoCleanupPipelineLayout::GetPipelineLayout() const
	{
		return _layout;
	}

	void AutoCleanupPipelineLayout::DestroyLayout()
	{
		if (_layout != VK_NULL_HANDLE)
		{
			vkDestroyPipelineLayout(_device, _layout, nullptr);
			_layout = VK_NULL_HANDLE;
		}
	}
}