#pragma once

#include "VSAutoCleanupDataBuffer.h"

namespace VulkanSimplified
{
	class AutoCleanupVertexBuffer : public AutoCleanupDataBuffer
	{
	public:
		AutoCleanupVertexBuffer(VkDevice device, VkBuffer buffer);
		~AutoCleanupVertexBuffer();

		AutoCleanupVertexBuffer(const AutoCleanupVertexBuffer& rhs) noexcept = delete;
		AutoCleanupVertexBuffer(AutoCleanupVertexBuffer&& rhs) noexcept = default;

		AutoCleanupVertexBuffer& operator=(const AutoCleanupVertexBuffer& rhs) noexcept = delete;
		AutoCleanupVertexBuffer& operator=(AutoCleanupVertexBuffer&& rhs) noexcept = default;
	};
}