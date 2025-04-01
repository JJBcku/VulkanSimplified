#pragma once

#include "VSAutoCleanupShaderModule.h"

namespace VulkanSimplifiedInternal
{
	class AutoCleanupVertexShaderModule : public AutoCleanupShaderModule
	{
	public:
		AutoCleanupVertexShaderModule(VkDevice device, VkShaderModule shader);
		~AutoCleanupVertexShaderModule();

		AutoCleanupVertexShaderModule(const AutoCleanupVertexShaderModule& rhs) noexcept = delete;
		AutoCleanupVertexShaderModule(AutoCleanupVertexShaderModule&& rhs) noexcept = default;

		AutoCleanupVertexShaderModule& operator=(const AutoCleanupVertexShaderModule& rhs) noexcept = delete;
		AutoCleanupVertexShaderModule& operator=(AutoCleanupVertexShaderModule&& rhs) noexcept = default;
	};
}