#include "VSDeviceNipch.h"
#include "VSAutoCleanupShaderModule.h"

namespace VulkanSimplified
{
	AutoCleanupShaderModule::AutoCleanupShaderModule(VkDevice device, VkShaderModule shader) : _device(device), _shader(shader)
	{
	}

	AutoCleanupShaderModule::~AutoCleanupShaderModule()
	{
		DestroyShader();
	}

	AutoCleanupShaderModule::AutoCleanupShaderModule(AutoCleanupShaderModule&& rhs) noexcept : _device(rhs._device), _shader(rhs._shader)
	{
		rhs._device = VK_NULL_HANDLE;
		rhs._shader = VK_NULL_HANDLE;
	}

	AutoCleanupShaderModule& AutoCleanupShaderModule::operator=(AutoCleanupShaderModule&& rhs) noexcept
	{
		DestroyShader();

		_device = rhs._device;
		_shader = rhs._shader;

		rhs._device = VK_NULL_HANDLE;
		rhs._shader = VK_NULL_HANDLE;

		return *this;
	}

	VkShaderModule AutoCleanupShaderModule::GetShaderModule() const
	{
		return _shader;
	}

	void AutoCleanupShaderModule::DestroyShader()
	{
		if (_shader != VK_NULL_HANDLE)
		{
			vkDestroyShaderModule(_device, _shader, nullptr);
			_shader = VK_NULL_HANDLE;
			_device = VK_NULL_HANDLE;
		}
	}

}