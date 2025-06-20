#pragma once

#include "VSAutoCleanupDataBuffer.h"

namespace VulkanSimplified
{
	class AutoCleanupStagingBuffer : public AutoCleanupDataBuffer
	{
	public:
		AutoCleanupStagingBuffer(VkDevice device, VkBuffer buffer);
		~AutoCleanupStagingBuffer();

		AutoCleanupStagingBuffer(const AutoCleanupStagingBuffer& rhs) noexcept = delete;
		AutoCleanupStagingBuffer(AutoCleanupStagingBuffer&& rhs) noexcept = default;

		AutoCleanupStagingBuffer& operator=(const AutoCleanupStagingBuffer& rhs) noexcept = delete;
		AutoCleanupStagingBuffer& operator=(AutoCleanupStagingBuffer&& rhs) noexcept = default;
	};

}