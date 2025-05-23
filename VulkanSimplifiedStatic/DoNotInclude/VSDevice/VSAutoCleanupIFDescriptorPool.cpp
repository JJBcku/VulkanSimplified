#include "VSDeviceNIpch.h"
#include "VSAutoCleanupIFDescriptorPool.h"

#include "VSDescriptorPoolTypeCapacities.h"

#include "VSAutoCleanupUniformBufferDescriptorSet.h"

#include "VSUniformBufferDescriptorSetWriteDataInternal.h"

namespace VulkanSimplifiedInternal
{
	AutoCleanupIFDescriptorPool::AutoCleanupIFDescriptorPool(VkDevice device, VkDescriptorPool pool, uint32_t maxTotalSetCount, const DescriptorPoolTypeCapacities& capacities) :
		_device(device), _pool(pool), _maxTotalSetCount(maxTotalSetCount), _currentSetCount(0), _uniformBufferList(capacities.uniformBufferCapacity)
	{
	}

	AutoCleanupIFDescriptorPool::~AutoCleanupIFDescriptorPool()
	{
	}

	AutoCleanupIFDescriptorPool::AutoCleanupIFDescriptorPool(AutoCleanupIFDescriptorPool&& rhs) noexcept : _device(rhs._device), _pool(rhs._pool),
		_maxTotalSetCount(rhs._maxTotalSetCount), _currentSetCount(rhs._currentSetCount), _uniformBufferList(std::move(rhs._uniformBufferList))
	{
		rhs._device = VK_NULL_HANDLE;
		rhs._pool = VK_NULL_HANDLE;

		rhs._maxTotalSetCount = 0;
		rhs._currentSetCount = 0;
	}

	AutoCleanupIFDescriptorPool& AutoCleanupIFDescriptorPool::operator=(AutoCleanupIFDescriptorPool&& rhs) noexcept
	{
		_device = rhs._device;
		_pool = rhs._pool;

		_maxTotalSetCount = rhs._maxTotalSetCount;
		_currentSetCount = rhs._currentSetCount;

		_uniformBufferList = std::move(rhs._uniformBufferList);

		rhs._device = VK_NULL_HANDLE;
		rhs._pool = VK_NULL_HANDLE;

		rhs._maxTotalSetCount = 0;
		rhs._currentSetCount = 0;

		return *this;
	}

	std::vector<IDObject<AutoCleanupUniformBufferDescriptorSet>> AutoCleanupIFDescriptorPool::AllocateUniformBufferDescriptorSets(std::vector<VkDescriptorSetLayout> descriptorLayouts)
	{
		std::vector<IDObject<AutoCleanupUniformBufferDescriptorSet>> ret;

		if (descriptorLayouts.empty())
			return ret;

		if (static_cast<uint64_t>(_maxTotalSetCount) - _currentSetCount < descriptorLayouts.size())
			throw std::runtime_error("AutoCleanupIFDescriptorPool::AllocateUniformBufferDescriptorSets Error: Program tried to allocate more descriptor set than the maximum total amount allowed!");

		if (_uniformBufferList.GetUnusedAndDeletedCapacity() < descriptorLayouts.size())
			throw std::runtime_error("AutoCleanupIFDescriptorPool::AllocateUniformBufferDescriptorSets Error: Program tried to allocate more descriptor set than the maximum type amount allowed!");

		ret.reserve(descriptorLayouts.size());

		std::vector<VkDescriptorSet> descriptorSets;
		descriptorSets.resize(descriptorLayouts.size(), VK_NULL_HANDLE);

		VkDescriptorSetAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		allocInfo.descriptorPool = _pool;
		allocInfo.descriptorSetCount = static_cast<uint32_t>(descriptorLayouts.size());
		allocInfo.pSetLayouts = descriptorLayouts.data();

		if (vkAllocateDescriptorSets(_device, &allocInfo, descriptorSets.data()) != VK_SUCCESS)
			throw std::runtime_error("AutoCleanupIFDescriptorPool::AllocateUniformBufferDescriptorSets Error: Program failed to allocate uniform buffer descriptor sets!");

		for (size_t i = 0; i < descriptorSets.size(); ++i)
		{
			ret.push_back(_uniformBufferList.AddObject(AutoCleanupUniformBufferDescriptorSet(descriptorSets[i]), 0));
		}

		return ret;
	}

	void AutoCleanupIFDescriptorPool::WriteUniformBufferDescriptorSets(const std::vector<UniformBufferDescriptorSetWriteDataInternal>& uniformBuffer)
	{
		if (uniformBuffer.empty())
			return;

		std::vector<VkWriteDescriptorSet> descriptorWriteDataList;
		descriptorWriteDataList.resize(uniformBuffer.size());

		std::vector<std::vector<VkDescriptorBufferInfo>> descriptorBufferDataLists;
		descriptorBufferDataLists.resize(uniformBuffer.size());

		for (size_t i = 0; i < uniformBuffer.size(); ++i)
		{
			auto& inData = uniformBuffer[i];
			auto& writeData = descriptorWriteDataList[i];
			auto& bufferData = descriptorBufferDataLists[i];

			writeData.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			writeData.dstSet = _uniformBufferList.GetConstObject(inData.descriptorSetID).GetDescriptorSet();
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

	VkDescriptorSet AutoCleanupIFDescriptorPool::GetUniformBufferDescriptorSet(IDObject<AutoCleanupUniformBufferDescriptorSet> descriptorSetID) const
	{
		return _uniformBufferList.GetConstObject(descriptorSetID).GetDescriptorSet();
	}

	void AutoCleanupIFDescriptorPool::DestroyDescriptorPool() noexcept
	{
		if (_pool != VK_NULL_HANDLE)
		{
			vkDestroyDescriptorPool(_device, _pool, nullptr);
			_pool = VK_NULL_HANDLE;
		}
	}

}