#include "VSDeviceNIpch.h"
#include "VSDescriptorDataListsInternal.h"

#include  "../VSSharedData/VSSharedDescriptorDataListInternal.h"
#include  "../VSSharedData/VSDescriptorSetLayoutBindingData.h"

#include "../../Include/VSDevice/VSDescriptorListsInitialCapacities.h"

#include "../VSCommon/VSDescriptorTypeFlagsInternal.h"

#include "VSAutoCleanupDescriptorSetLayout.h"
#include "VSAutoCleanupNIFDescriptorPool.h"
#include "VSAutoCleanupIFDescriptorPool.h"

#include "VSDescriptorPoolTypeCapacities.h"

namespace VulkanSimplifiedInternal
{
	DescriptorDataListsInternal::DescriptorDataListsInternal(const SharedDescriptorDataListInternal& sharedDescriptorData, VkDevice device,
		const VulkanSimplified::DescriptorListsInitialCapacities& initialCapacities) : _sharedDescriptorData(sharedDescriptorData), _device(device),
		_descriptorSetLayouts(initialCapacities.descriptorSetListInitialCapacity), _NIFDescriptorPools(initialCapacities.noIndividualFreeingDescriptorPoolsListInitialCapacity),
		_IFDescriptorPools(initialCapacities.individualFreeingDescriptorPoolsListInitialCapacity)
	{
	}

	DescriptorDataListsInternal::~DescriptorDataListsInternal()
	{
	}

	IDObject<AutoCleanupDescriptorSetLayout> DescriptorDataListsInternal::AddDescriptorSetLayout(uint32_t firstBinding,
		const std::vector<IDObject<DescriptorSetLayoutBindingData>>& descriptorSetLayoutBindings, size_t addOnReserving)
	{
		std::vector<VkDescriptorSetLayoutBinding> bindingList;

		VkDescriptorSetLayout add = VK_NULL_HANDLE;
		VkDescriptorSetLayoutCreateInfo createInfo{};

		createInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;

		if (!descriptorSetLayoutBindings.empty())
		{
			bindingList = _sharedDescriptorData.GetDescriptorSetLayoutBindings(firstBinding, descriptorSetLayoutBindings);

			createInfo.bindingCount = static_cast<std::uint32_t>(bindingList.size());
			createInfo.pBindings = bindingList.data();
		}

		if (vkCreateDescriptorSetLayout(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
			throw std::runtime_error("DeviceDescriptorDataInternal::AddDescriptorSetLayout Error: Program failed to create ");

		return _descriptorSetLayouts.AddObject(AutoCleanupDescriptorSetLayout(_device, add), addOnReserving);
	}

	std::vector<VkDescriptorSetLayout> DescriptorDataListsInternal::GetDescriptorSetLayouts(const std::vector<IDObject<AutoCleanupDescriptorSetLayout>>& layoutIDs) const
	{
		std::vector<VkDescriptorSetLayout> ret;

		ret.reserve(layoutIDs.size());

		for (auto& ID : layoutIDs)
		{
			auto& descriptor = _descriptorSetLayouts.GetConstObject(ID);
			ret.push_back(descriptor.GetDescriptorSetLayout());
		}

		return ret;
	}

	IDObject<AutoCleanupNIFDescriptorPool> DescriptorDataListsInternal::AddNoIndividualFreeingDescriptorPool(uint32_t maxTotalSetCount,
		const std::vector<std::pair<VulkanSimplified::DescriptorTypeFlagBits, uint32_t>>& maxTypeCountsList, size_t addOnReserving)
	{
		if (maxTotalSetCount == 0)
			throw std::runtime_error("DescriptorDataListsInternal::AddNoIdividualFreeingDescriptorPool Error: Program was given zero as the max total set amount!");

		std::vector<VkDescriptorPoolSize> descriptorPoolSizes;
		descriptorPoolSizes.reserve(maxTypeCountsList.size());

		for (size_t i = 0; i < maxTypeCountsList.size(); ++i)
		{
			bool found = false;

			VkDescriptorType type = TranslateDescriptorTypeFlags(maxTypeCountsList[i].first);

			for (size_t j = 0; j < descriptorPoolSizes.size(); ++j)
			{
				if (descriptorPoolSizes[j].type == type)
				{
					descriptorPoolSizes[j].descriptorCount += maxTypeCountsList[i].second;
					found = true;
					break;
				}
			}

			if (!found)
			{
				descriptorPoolSizes.emplace_back();

				auto& back = descriptorPoolSizes.back();

				back.type = type;
				back.descriptorCount = maxTypeCountsList[i].second;
			}
		}

		if (descriptorPoolSizes.empty())
			throw std::runtime_error("DescriptorDataListsInternal::AddNoIdividualFreeingDescriptorPool Error: Program tried to add a pool with no descriptor types allowed!");

		if (descriptorPoolSizes.size() > std::numeric_limits<uint32_t>::max())
			throw std::runtime_error("DescriptorDataListsInternal::AddNoIdividualFreeingDescriptorPool Error: Descriptor pool sizes list overflowed!");

		VkDescriptorPoolCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		createInfo.maxSets = maxTotalSetCount;
		createInfo.poolSizeCount = static_cast<uint32_t>(descriptorPoolSizes.size());
		createInfo.pPoolSizes = descriptorPoolSizes.data();

		VkDescriptorPool add = VK_NULL_HANDLE;

		if (vkCreateDescriptorPool(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
			throw std::runtime_error("DescriptorDataListsInternal::AddNoIdividualFreeingDescriptorPool Error: Program failed to create a descriptor pool!");

		DescriptorPoolTypeCapacities capacities;

		for (size_t i = 0; i < descriptorPoolSizes.size(); ++i)
		{
			auto& type = descriptorPoolSizes[i].type;
			auto& size = descriptorPoolSizes[i].descriptorCount;

			switch (type)
			{
			case VK_DESCRIPTOR_TYPE_SAMPLER:
				capacities.samplerCapacity = size;
				break;
			case VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER:
				capacities.combinedImageSamplerCapacity = size;
				break;
			case VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE:
				capacities.sampledImageCapacity = size;
				break;
			case VK_DESCRIPTOR_TYPE_STORAGE_IMAGE:
				capacities.storageImageCapacity = size;
				break;
			case VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER:
				capacities.uniformTexelBufferCapacity = size;
				break;
			case VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER:
				capacities.storageTexelBufferCapacity = size;
				break;
			case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER:
				capacities.uniformBufferCapacity = size;
				break;
			case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER:
				capacities.storageBufferCapacity = size;
				break;
			case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC:
				capacities.dynamicUniformBufferCapacity = size;
				break;
			case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC:
				capacities.dynamicStorageBufferCapacity = size;
				break;
			case VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT:
				capacities.inputAttachmentCapacity = size;
				break;
			default:
				throw std::runtime_error("DescriptorDataListsInternal::AddNoIdividualFreeingDescriptorPool Error: Program was given an erroneous descriptor type!");
			}
		}

		return _NIFDescriptorPools.AddObject(AutoCleanupNIFDescriptorPool(_device, add, maxTotalSetCount, capacities), addOnReserving);
	}

	IDObject<AutoCleanupIFDescriptorPool> DescriptorDataListsInternal::AddIndividualFreeingDescriptorPool(uint32_t maxTotalSetCount,
		const std::vector<std::pair<VulkanSimplified::DescriptorTypeFlagBits, uint32_t>>& maxTypeCountsList, size_t addOnReserving)
	{
		if (maxTotalSetCount == 0)
			throw std::runtime_error("DescriptorDataListsInternal::AddIndividualFreeingDescriptorPool Error: Program was given zero as the max total set amount!");

		std::vector<VkDescriptorPoolSize> descriptorPoolSizes;
		descriptorPoolSizes.reserve(maxTypeCountsList.size());

		for (size_t i = 0; i < maxTypeCountsList.size(); ++i)
		{
			bool found = false;

			VkDescriptorType type = TranslateDescriptorTypeFlags(maxTypeCountsList[i].first);

			for (size_t j = 0; j < descriptorPoolSizes.size(); ++j)
			{
				if (descriptorPoolSizes[j].type == type)
				{
					descriptorPoolSizes[j].descriptorCount += maxTypeCountsList[i].second;
					found = true;
					break;
				}
			}

			if (!found)
			{
				descriptorPoolSizes.emplace_back();

				auto& back = descriptorPoolSizes.back();

				back.type = type;
				back.descriptorCount = maxTypeCountsList[i].second;
			}
		}

		if (descriptorPoolSizes.empty())
			throw std::runtime_error("DescriptorDataListsInternal::AddIndividualFreeingDescriptorPool Error: Program tried to add a pool with no descriptor types allowed!");

		if (descriptorPoolSizes.size() > std::numeric_limits<uint32_t>::max())
			throw std::runtime_error("DescriptorDataListsInternal::AddIndividualFreeingDescriptorPool Error: Descriptor pool sizes list overflowed!");

		VkDescriptorPoolCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		createInfo.maxSets = maxTotalSetCount;
		createInfo.poolSizeCount = static_cast<uint32_t>(descriptorPoolSizes.size());
		createInfo.pPoolSizes = descriptorPoolSizes.data();
		createInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;

		VkDescriptorPool add = VK_NULL_HANDLE;

		if (vkCreateDescriptorPool(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
			throw std::runtime_error("DescriptorDataListsInternal::AddIndividualFreeingDescriptorPool Error: Program failed to create a descriptor pool!");

		DescriptorPoolTypeCapacities capacities;

		for (size_t i = 0; i < descriptorPoolSizes.size(); ++i)
		{
			auto& type = descriptorPoolSizes[i].type;
			auto& size = descriptorPoolSizes[i].descriptorCount;

			switch (type)
			{
			case VK_DESCRIPTOR_TYPE_SAMPLER:
				capacities.samplerCapacity = size;
				break;
			case VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER:
				capacities.combinedImageSamplerCapacity = size;
				break;
			case VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE:
				capacities.sampledImageCapacity = size;
				break;
			case VK_DESCRIPTOR_TYPE_STORAGE_IMAGE:
				capacities.storageImageCapacity = size;
				break;
			case VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER:
				capacities.uniformTexelBufferCapacity = size;
				break;
			case VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER:
				capacities.storageTexelBufferCapacity = size;
				break;
			case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER:
				capacities.uniformBufferCapacity = size;
				break;
			case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER:
				capacities.storageBufferCapacity = size;
				break;
			case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC:
				capacities.dynamicUniformBufferCapacity = size;
				break;
			case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC:
				capacities.dynamicStorageBufferCapacity = size;
				break;
			case VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT:
				capacities.inputAttachmentCapacity = size;
				break;
			default:
				throw std::runtime_error("DescriptorDataListsInternal::AddIndividualFreeingDescriptorPool Error: Program was given an erroneous descriptor type!");
			}
		}

		return _IFDescriptorPools.AddObject(AutoCleanupIFDescriptorPool(_device, add, maxTotalSetCount, capacities), addOnReserving);
	}

}