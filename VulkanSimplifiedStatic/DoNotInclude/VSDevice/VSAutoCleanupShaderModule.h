#pragma once

namespace VulkanSimplifiedInternal
{
	class AutoCleanupShaderModule
	{
	public:
		AutoCleanupShaderModule(VkDevice device, VkShaderModule shader);
		~AutoCleanupShaderModule();

		AutoCleanupShaderModule(const AutoCleanupShaderModule& rhs) noexcept = delete;
		AutoCleanupShaderModule(AutoCleanupShaderModule&& rhs) noexcept;

		AutoCleanupShaderModule& operator=(const AutoCleanupShaderModule& rhs) noexcept = delete;
		AutoCleanupShaderModule& operator=(AutoCleanupShaderModule&& rhs) noexcept;

	private:
		VkDevice _device;
		VkShaderModule _shader;

		void DestroyShader();
	};
}