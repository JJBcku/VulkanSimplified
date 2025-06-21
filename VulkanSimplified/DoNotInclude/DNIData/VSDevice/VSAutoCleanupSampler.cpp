#include "VSDeviceDNIpch.h"
#include "VSAutoCleanupSampler.h"

namespace VulkanSimplified
{
	AutoCleanupSampler::AutoCleanupSampler(VkDevice device, VkSampler sampler) : _device(device), _sampler(sampler)
	{
	}

	AutoCleanupSampler::~AutoCleanupSampler()
	{
		DestroySampler();
	}

	AutoCleanupSampler::AutoCleanupSampler(AutoCleanupSampler&& rhs) noexcept : _device(rhs._device), _sampler(rhs._sampler)
	{
		rhs._device = VK_NULL_HANDLE;
		rhs._sampler = VK_NULL_HANDLE;
	}

	AutoCleanupSampler& AutoCleanupSampler::operator=(AutoCleanupSampler&& rhs) noexcept
	{
		_device = rhs._device;
		_sampler = rhs._sampler;

		rhs._device = VK_NULL_HANDLE;
		rhs._sampler = VK_NULL_HANDLE;

		return *this;
	}

	VkSampler AutoCleanupSampler::GetSampler() const
	{
		return _sampler;
	}

	void AutoCleanupSampler::DestroySampler()
	{
		if (_sampler != VK_NULL_HANDLE)
		{
			vkDestroySampler(_device, _sampler, nullptr);
			_sampler = VK_NULL_HANDLE;
		}
	}

}