#pragma once

#include "VSAutoCleanupDataBuffer.h"

namespace VulkanSimplifiedInternal
{
	class AutoCleanupUniformBuffer : public AutoCleanupDataBuffer
	{
	public:
		AutoCleanupUniformBuffer(VkDevice device, VkBuffer buffer);
		~AutoCleanupUniformBuffer();

		AutoCleanupUniformBuffer(const AutoCleanupUniformBuffer& rhs) noexcept = delete;
		AutoCleanupUniformBuffer(AutoCleanupUniformBuffer&& rhs) noexcept = default;

		AutoCleanupUniformBuffer& operator=(const AutoCleanupUniformBuffer& rhs) noexcept = delete;
		AutoCleanupUniformBuffer& operator=(AutoCleanupUniformBuffer&& rhs) noexcept = default;
	};
}