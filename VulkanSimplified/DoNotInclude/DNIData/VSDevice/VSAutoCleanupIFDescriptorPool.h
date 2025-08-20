#pragma once

#include "../../../Include/VSDevice/VSDescriptorDataListsDef.h"

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
	struct DescriptorSetCombined2DArrayTextureSamplerWriteDataInternal;
	struct DescriptorSetCombined2DTextureSamplerWriteDataInternal;

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

		void WriteUniformBufferDescriptorSetBindings(const std::vector<DescriptorSetUniformBufferBindingWriteDataInternal>& uniformBuffer);
		void WriteDescriptorSetCombined2DTextureSamplerBindings(const std::vector<DescriptorSetCombined2DTextureSamplerWriteDataInternal>& combined2DTextureSamplers);
		void WriteDescriptorSetCombined2DArrayTextureSamplerBindings(const std::vector<DescriptorSetCombined2DArrayTextureSamplerWriteDataInternal>& combined2DArrayTextureSamplers);

		void WriteDescriptorSetInputAttachmentBindings(const std::vector<DescriptorSetCombined2DTextureSamplerWriteDataInternal> inputImages);

		VkDescriptorSet GetDescriptorSet(IDObject<AutoCleanupDescriptorSet> descriptorSetID) const;
		std::vector<VkDescriptorSet> GetDescriptorSetList(const std::vector<IDObject<AutoCleanupDescriptorSet>>& descriptorSetIDs) const;

		VkDescriptorPool GetDescriptorPool() const;

		std::vector<bool> FreeDescriptorSets(const std::vector<IDObject<AutoCleanupDescriptorSet>>& descriptorSetsIDs, bool throwOnIDNotFound);

	private:
		VkDevice _device;
		VkDescriptorPool _pool;

		UnsortedIDVector<AutoCleanupDescriptorSet> _descriptorSetList;

		void DestroyDescriptorPool() noexcept;
	};
}