#pragma once

#include "VSAutoCleanupDataBuffer.h"

namespace VulkanSimplified
{
	class AutoCleanupIndexBuffer : public AutoCleanupDataBuffer
	{
	public:
		AutoCleanupIndexBuffer(VkDevice device, VkBuffer buffer);
		~AutoCleanupIndexBuffer();

		AutoCleanupIndexBuffer(const AutoCleanupIndexBuffer& rhs) noexcept = delete;
		AutoCleanupIndexBuffer(AutoCleanupIndexBuffer&& rhs) noexcept = default;

		AutoCleanupIndexBuffer& operator=(const AutoCleanupIndexBuffer& rhs) noexcept = delete;
		AutoCleanupIndexBuffer& operator=(AutoCleanupIndexBuffer&& rhs) noexcept = default;
	};
}