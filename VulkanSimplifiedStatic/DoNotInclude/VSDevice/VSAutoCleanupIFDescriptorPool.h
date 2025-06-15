#pragma once

#include "../../Include/VSDevice/VSDescriptorDataListDef.h"

#include <CustomLists/UnsortedIDVector.h>

namespace VulkanSimplifiedInternal
{
	struct UniformBufferDescriptorSetWriteDataInternal;

	class AutoCleanupIFDescriptorPool
	{
	public:
		AutoCleanupIFDescriptorPool(VkDevice device, VkDescriptorPool pool, uint32_t maxTotalSetCount);
		~AutoCleanupIFDescriptorPool();

		AutoCleanupIFDescriptorPool(const AutoCleanupIFDescriptorPool& rhs) noexcept = delete;
		AutoCleanupIFDescriptorPool(AutoCleanupIFDescriptorPool&& rhs) noexcept;

		AutoCleanupIFDescriptorPool& operator=(const AutoCleanupIFDescriptorPool& rhs) noexcept = delete;
		AutoCleanupIFDescriptorPool& operator=(AutoCleanupIFDescriptorPool&& rhs) noexcept;

		std::vector<IDObject<AutoCleanupDescriptorSet>> AllocateDescriptorSets(std::vector<VkDescriptorSetLayout> descriptorLayouts);

		void WriteUniformBufferDescriptorSetBindings(const std::vector<UniformBufferDescriptorSetWriteDataInternal>& uniformBuffer);

		VkDescriptorSet GetDescriptorSet(IDObject<AutoCleanupDescriptorSet> descriptorSetID) const;
		std::vector<VkDescriptorSet> GetDescriptorSetList(const std::vector<IDObject<AutoCleanupDescriptorSet>>& descriptorSetIDs) const;

	private:
		VkDevice _device;
		VkDescriptorPool _pool;

		UnsortedIDVector<AutoCleanupDescriptorSet> _descriptorSetList;

		void DestroyDescriptorPool() noexcept;
	};
}