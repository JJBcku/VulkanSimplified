#pragma once

typedef struct VkDevice_T* VkDevice;
typedef struct VkShaderModule_T* VkShaderModule;

namespace VulkanSimplified
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

		VkShaderModule GetShaderModule() const;

	private:
		VkDevice _device;
		VkShaderModule _shader;

		void DestroyShader();
	};
}