#pragma once

#include "VSAutoCleanupShaderModule.h"

namespace VulkanSimplified
{
	class AutoCleanupFragmentShaderModule : public AutoCleanupShaderModule
	{
	public:
		AutoCleanupFragmentShaderModule(VkDevice device, VkShaderModule shader);
		~AutoCleanupFragmentShaderModule();

		AutoCleanupFragmentShaderModule(const AutoCleanupFragmentShaderModule& rhs) noexcept = delete;
		AutoCleanupFragmentShaderModule(AutoCleanupFragmentShaderModule&& rhs) noexcept = default;

		AutoCleanupFragmentShaderModule& operator=(const AutoCleanupFragmentShaderModule& rhs) noexcept = delete;
		AutoCleanupFragmentShaderModule& operator=(AutoCleanupFragmentShaderModule&& rhs) noexcept = default;
	};
}