#pragma once

namespace VulkanSimplifiedInternal
{
	struct DescriptorPoolTypeCapacities;

	class AutoCleanupNIFDescriptorPool
	{
	public:
		AutoCleanupNIFDescriptorPool(VkDevice device, VkDescriptorPool pool, uint32_t maxTotalSetCount, const DescriptorPoolTypeCapacities& capacities);
		~AutoCleanupNIFDescriptorPool();

		AutoCleanupNIFDescriptorPool(const AutoCleanupNIFDescriptorPool& rhs) noexcept = delete;
		AutoCleanupNIFDescriptorPool(AutoCleanupNIFDescriptorPool&& rhs) noexcept;

		AutoCleanupNIFDescriptorPool& operator=(const AutoCleanupNIFDescriptorPool& rhs) noexcept = delete;
		AutoCleanupNIFDescriptorPool& operator=(AutoCleanupNIFDescriptorPool&& rhs) noexcept;

	protected:
		VkDevice GetDevice() const;

	private:
		VkDevice _device;
		VkDescriptorPool _pool;

		uint32_t _maxTotalSetCount;
		uint32_t _currentSetCount;

		void DestroyDescriptorPool() noexcept;
	};
}