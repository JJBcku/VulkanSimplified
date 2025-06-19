#pragma once

typedef struct VkDevice_T* VkDevice;
typedef struct VkPipeline_T* VkPipeline;

namespace VulkanSimplifiedInternal
{
	class AutoCleanupGraphicsPipeline
	{
	public:
		AutoCleanupGraphicsPipeline(VkDevice device, VkPipeline pipeline);
		~AutoCleanupGraphicsPipeline();

		AutoCleanupGraphicsPipeline(const AutoCleanupGraphicsPipeline&) noexcept = delete;
		AutoCleanupGraphicsPipeline(AutoCleanupGraphicsPipeline&& rhs) noexcept;

		AutoCleanupGraphicsPipeline& operator=(const AutoCleanupGraphicsPipeline&) noexcept = delete;
		AutoCleanupGraphicsPipeline& operator=(AutoCleanupGraphicsPipeline&& rhs) noexcept;

		VkPipeline GetPipeline() const;

	private:
		VkDevice _device;
		VkPipeline _pipeline;

		void DestroyPipeline();
	};
}