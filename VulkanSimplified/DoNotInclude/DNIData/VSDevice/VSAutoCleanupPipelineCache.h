#pragma once

typedef struct VkDevice_T* VkDevice;
typedef struct VkPipelineCache_T* VkPipelineCache;

namespace VulkanSimplified
{
	class AutoCleanupPipelineCache
	{
	public:
		AutoCleanupPipelineCache(VkDevice device, VkPipelineCache pipelineCache);
		~AutoCleanupPipelineCache();

		AutoCleanupPipelineCache(const AutoCleanupPipelineCache& rhs) noexcept = delete;
		AutoCleanupPipelineCache(AutoCleanupPipelineCache&& rhs) noexcept;

		AutoCleanupPipelineCache& operator=(const AutoCleanupPipelineCache& rhs) noexcept = delete;
		AutoCleanupPipelineCache& operator=(AutoCleanupPipelineCache&& rhs) noexcept;

		VkPipelineCache GetPipelineCache() const;

	private:
		VkDevice _device;
		VkPipelineCache _pipelineCache;

		void DestroyCache();
	};
}
