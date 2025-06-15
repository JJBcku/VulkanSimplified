#pragma once

#include "../../Include/VSDevice/VSDescriptorDataListDef.h"

#include <CustomLists/UnsortedIDVector.h>

namespace VulkanSimplifiedInternal
{
	struct UniformBufferDescriptorSetWriteDataInternal;

	class AutoCleanupNIFDescriptorPool
	{
	public:
		AutoCleanupNIFDescriptorPool(VkDevice device, VkDescriptorPool pool, uint32_t maxTotalSetCount);
		~AutoCleanupNIFDescriptorPool();

		AutoCleanupNIFDescriptorPool(const AutoCleanupNIFDescriptorPool& rhs) noexcept = delete;
		AutoCleanupNIFDescriptorPool(AutoCleanupNIFDescriptorPool&& rhs) noexcept;

		AutoCleanupNIFDescriptorPool& operator=(const AutoCleanupNIFDescriptorPool& rhs) noexcept = delete;
		AutoCleanupNIFDescriptorPool& operator=(AutoCleanupNIFDescriptorPool&& rhs) noexcept;

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