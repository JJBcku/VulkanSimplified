#include "VSDeviceDNIpch.h"
#include "VSAutoCleanupNIFDescriptorPool.h"

#include "VSAutoCleanupDescriptorSet.h"

#include "VSDescriptorSetUniformBufferBindingWriteDataInternal.h"
#include "VSDescriptorSetCombined2DTextureSamplerWriteDataInternal.h"

namespace VulkanSimplified
{
	AutoCleanupNIFDescriptorPool::AutoCleanupNIFDescriptorPool(VkDevice device, VkDescriptorPool pool, uint32_t maxTotalSetCount) :
		_device(device), _pool(pool), _descriptorSetList(maxTotalSetCount)
	{
	}

	AutoCleanupNIFDescriptorPool::~AutoCleanupNIFDescriptorPool()
	{
		DestroyDescriptorPool();
	}

	AutoCleanupNIFDescriptorPool::AutoCleanupNIFDescriptorPool(AutoCleanupNIFDescriptorPool&& rhs) noexcept : _device(rhs._device), _pool(rhs._pool),
		_descriptorSetList(std::move(rhs._descriptorSetList))
	{
		rhs._device = VK_NULL_HANDLE;
		rhs._pool = VK_NULL_HANDLE;
	}

	AutoCleanupNIFDescriptorPool& AutoCleanupNIFDescriptorPool::operator=(AutoCleanupNIFDescriptorPool&& rhs) noexcept
	{
		_device = rhs._device;
		_pool = rhs._pool;

		_descriptorSetList = std::move(rhs._descriptorSetList);

		rhs._device = VK_NULL_HANDLE;
		rhs._pool = VK_NULL_HANDLE;

		return *this;
	}

	std::vector<IDObject<AutoCleanupDescriptorSet>> AutoCleanupNIFDescriptorPool::AllocateDescriptorSets(std::vector<VkDescriptorSetLayout> descriptorLayouts)
	{
		std::vector<IDObject<AutoCleanupDescriptorSet>> ret;

		if (descriptorLayouts.empty())
			return ret;

		if (_descriptorSetList.GetUnusedAndDeletedCapacity() < descriptorLayouts.size())
			throw std::runtime_error("AutoCleanupNIFDescriptorPool::AllocateUniformBufferDescriptorSets Error: Program tried to allocate more descriptor set than the maximum total amount allowed!");

		ret.reserve(descriptorLayouts.size());

		std::vector<VkDescriptorSet> descriptorSets;
		descriptorSets.resize(descriptorLayouts.size(), VK_NULL_HANDLE);

		VkDescriptorSetAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		allocInfo.descriptorPool = _pool;
		allocInfo.descriptorSetCount = static_cast<uint32_t>(descriptorLayouts.size());
		allocInfo.pSetLayouts = descriptorLayouts.data();

		if (vkAllocateDescriptorSets(_device, &allocInfo, descriptorSets.data()) != VK_SUCCESS)
			throw std::runtime_error("AutoCleanupNIFDescriptorPool::AllocateUniformBufferDescriptorSets Error: Program failed to allocate uniform buffer descriptor sets!");

		for (size_t i = 0; i < descriptorSets.size(); ++i)
		{
			ret.push_back(_descriptorSetList.AddObject(AutoCleanupDescriptorSet(descriptorSets[i]), 0));
		}

		return ret;
	}

	void AutoCleanupNIFDescriptorPool::WriteDescriptorSetUniformBufferBindings(const std::vector<DescriptorSetUniformBufferBindingWriteDataInternal>& uniformBuffers)
	{
		if (uniformBuffers.empty())
			return;

		std::vector<VkWriteDescriptorSet> descriptorWriteDataList;
		descriptorWriteDataList.resize(uniformBuffers.size());

		std::vector<std::vector<VkDescriptorBufferInfo>> descriptorBufferDataLists;
		descriptorBufferDataLists.resize(uniformBuffers.size());

		for (size_t i = 0; i < uniformBuffers.size(); ++i)
		{
			auto& inData = uniformBuffers[i];
			auto& writeData = descriptorWriteDataList[i];
			auto& bufferData = descriptorBufferDataLists[i];

			writeData.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			writeData.dstSet = _descriptorSetList.GetConstObject(inData.descriptorSetID).GetDescriptorSet();
			writeData.dstBinding = inData.binding;
			writeData.dstArrayElement = inData.startArrayIndex;
			writeData.descriptorCount = static_cast<uint32_t>(inData.bufferList.size());
			writeData.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;

			bufferData.resize(inData.bufferList.size());

			for (size_t j = 0; j < inData.bufferList.size(); ++j)
			{
				bufferData[j].buffer = inData.bufferList[j];
				bufferData[j].offset = 0;
				bufferData[j].range = VK_WHOLE_SIZE;
			}

			writeData.pBufferInfo = bufferData.data();
		}

		vkUpdateDescriptorSets(_device, static_cast<uint32_t>(descriptorWriteDataList.size()), descriptorWriteDataList.data(), 0, nullptr);
	}

	void AutoCleanupNIFDescriptorPool::WriteDescriptorSetCombined2DTextureSamplerBindings(
		const std::vector<DescriptorSetCombined2DTextureSamplerWriteDataInternal>& combined2DTextureSamplers)
	{
		if (combined2DTextureSamplers.empty())
			return;

		std::vector<VkWriteDescriptorSet> descriptorWriteDataList;
		descriptorWriteDataList.resize(combined2DTextureSamplers.size());

		for (size_t i = 0; i < combined2DTextureSamplers.size(); ++i)
		{
			auto& inData = combined2DTextureSamplers[i];
			auto& writeData = descriptorWriteDataList[i];

			writeData.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			writeData.dstSet = _descriptorSetList.GetConstObject(inData.descriptorSetID).GetDescriptorSet();
			writeData.dstBinding = inData.binding;
			writeData.dstArrayElement = inData.startArrayIndex;
			writeData.descriptorCount = static_cast<uint32_t>(inData.imageInfo.size());
			writeData.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;

			writeData.pImageInfo = inData.imageInfo.data();
		}

		vkUpdateDescriptorSets(_device, static_cast<uint32_t>(descriptorWriteDataList.size()), descriptorWriteDataList.data(), 0, nullptr);
	}

	VkDescriptorSet AutoCleanupNIFDescriptorPool::GetDescriptorSet(IDObject<AutoCleanupDescriptorSet> descriptorSetID) const
	{
		return _descriptorSetList.GetConstObject(descriptorSetID).GetDescriptorSet();
	}

	std::vector<VkDescriptorSet> AutoCleanupNIFDescriptorPool::GetDescriptorSetList(const std::vector<IDObject<AutoCleanupDescriptorSet>>& descriptorSetIDs) const
	{
		std::vector<VkDescriptorSet> ret;
		ret.reserve(descriptorSetIDs.size());

		for (size_t i = 0; i < descriptorSetIDs.size(); ++i)
		{
			ret.push_back(GetDescriptorSet(descriptorSetIDs[i]));
		}

		return ret;
	}

	void AutoCleanupNIFDescriptorPool::DestroyDescriptorPool() noexcept
	{
		if (_pool != VK_NULL_HANDLE)
		{
			vkDestroyDescriptorPool(_device, _pool, nullptr);
			_pool = VK_NULL_HANDLE;
		}
	}

}