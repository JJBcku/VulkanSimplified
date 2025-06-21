#pragma once

#include "../../../Include/VSDevice/VSDescriptorDataListDef.h"

#include <CustomLists/UnsortedIDVector.h>

#include <vector>

typedef struct VkDevice_T* VkDevice;
typedef struct VkDescriptorPool_T* VkDescriptorPool;
typedef struct VkDescriptorSet_T* VkDescriptorSet;
typedef struct VkDescriptorSetLayout_T* VkDescriptorSetLayout;

namespace VulkanSimplified
{
	struct DescriptorSetUniformBufferBindingWriteDataInternal;
	struct DescriptorSetCombined2DTextureSamplerWriteDataInternal;

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

		void WriteDescriptorSetUniformBufferBindings(const std::vector<DescriptorSetUniformBufferBindingWriteDataInternal>& uniformBuffer);
		void WriteDescriptorSetCombined2DTextureSamplerBindings(const std::vector<DescriptorSetCombined2DTextureSamplerWriteDataInternal>& combined2DTextureSamplers);

		VkDescriptorSet GetDescriptorSet(IDObject<AutoCleanupDescriptorSet> descriptorSetID) const;
		std::vector<VkDescriptorSet> GetDescriptorSetList(const std::vector<IDObject<AutoCleanupDescriptorSet>>& descriptorSetIDs) const;

	private:
		VkDevice _device;
		VkDescriptorPool _pool;

		UnsortedIDVector<AutoCleanupDescriptorSet> _descriptorSetList;

		void DestroyDescriptorPool() noexcept;
	};
}