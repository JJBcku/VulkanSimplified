#pragma once

#include "../../Include/VSDevice/VSDescriptorDataListDef.h"

#include <CustomLists/UnsortedIDVector.h>

namespace VulkanSimplifiedInternal
{
	struct DescriptorPoolTypeCapacities;

	struct UniformBufferDescriptorSetWriteDataInternal;

	class AutoCleanupIFDescriptorPool
	{
	public:
		AutoCleanupIFDescriptorPool(VkDevice device, VkDescriptorPool pool, uint32_t maxTotalSetCount, const DescriptorPoolTypeCapacities& capacities);
		~AutoCleanupIFDescriptorPool();

		AutoCleanupIFDescriptorPool(const AutoCleanupIFDescriptorPool& rhs) noexcept = delete;
		AutoCleanupIFDescriptorPool(AutoCleanupIFDescriptorPool&& rhs) noexcept;

		AutoCleanupIFDescriptorPool& operator=(const AutoCleanupIFDescriptorPool& rhs) noexcept = delete;
		AutoCleanupIFDescriptorPool& operator=(AutoCleanupIFDescriptorPool&& rhs) noexcept;

		std::vector<IDObject<AutoCleanupUniformBufferDescriptorSet>> AllocateUniformBufferDescriptorSets(std::vector<VkDescriptorSetLayout> descriptorLayouts);

		void WriteUniformBufferDescriptorSets(const std::vector<UniformBufferDescriptorSetWriteDataInternal>& uniformBuffer);

		VkDescriptorSet GetUniformBufferDescriptorSet(IDObject<AutoCleanupUniformBufferDescriptorSet> descriptorSetID) const;

	private:
		VkDevice _device;
		VkDescriptorPool _pool;

		uint32_t _maxTotalSetCount;
		uint32_t _currentSetCount;

		UnsortedIDVector<AutoCleanupUniformBufferDescriptorSet> _uniformBufferList;

		void DestroyDescriptorPool() noexcept;
	};
}