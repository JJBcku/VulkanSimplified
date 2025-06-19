#include "VSDeviceNIpch.h"
#include "../../DNIHeaders/VSDevice/VSAutoCleanupGraphicsPipeline.h"

namespace VulkanSimplifiedInternal
{
	AutoCleanupGraphicsPipeline::AutoCleanupGraphicsPipeline(VkDevice device, VkPipeline pipeline) : _device(device), _pipeline(pipeline)
	{
	}

	AutoCleanupGraphicsPipeline::~AutoCleanupGraphicsPipeline()
	{
		DestroyPipeline();
	}

	AutoCleanupGraphicsPipeline::AutoCleanupGraphicsPipeline(AutoCleanupGraphicsPipeline&& rhs) noexcept : _device(rhs._device), _pipeline(rhs._pipeline)
	{
		rhs._device = VK_NULL_HANDLE;
		rhs._pipeline = VK_NULL_HANDLE;
	}

	AutoCleanupGraphicsPipeline& AutoCleanupGraphicsPipeline::operator=(AutoCleanupGraphicsPipeline&& rhs) noexcept
	{
		DestroyPipeline();
		_device = rhs._device;
		_pipeline = rhs._pipeline;

		rhs._device = VK_NULL_HANDLE;
		rhs._pipeline = VK_NULL_HANDLE;
		return *this;
	}

	VkPipeline AutoCleanupGraphicsPipeline::GetPipeline() const
	{
		return _pipeline;
	}

	void AutoCleanupGraphicsPipeline::DestroyPipeline()
	{
		if (_pipeline != VK_NULL_HANDLE)
		{
			vkDestroyPipeline(_device, _pipeline, nullptr);
			_pipeline = VK_NULL_HANDLE;
		}
	}
}