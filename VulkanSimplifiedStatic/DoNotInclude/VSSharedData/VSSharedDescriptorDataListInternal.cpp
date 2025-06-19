#include "VSSharedNIpch.h"
#include "VSSharedDescriptorDataListInternal.h"

#include "../../Include/VSSharedData/VSSharedDescriptorDataListCapacities.h"

#include "../../Include/VSCommon/VSDescriptorTypeFlags.h"
#include "../../Include/VSCommon/VSShaderTypeFlags.h"

#include "VSDescriptorSetLayoutBindingData.h"

namespace VulkanSimplifiedInternal
{
	SharedDescriptorDataListInternal::SharedDescriptorDataListInternal(const VulkanSimplified::SharedDescriptorDataListCapacities& initalCapacities) :
		_bindingDataList(initalCapacities.descriptorBindingListInitialCapacity)
	{
	}

	SharedDescriptorDataListInternal::~SharedDescriptorDataListInternal()
	{
	}

	IDObject<DescriptorSetLayoutBindingData> SharedDescriptorDataListInternal::AddDescriptorSetLayoutBindingsData(VulkanSimplified::DescriptorTypeFlagBits descriptorType,
		uint32_t descriptorAmount, VulkanSimplified::ShaderTypeFlags shaderStageFlags, size_t addOnReserving)
	{
		DescriptorSetLayoutBindingData add;

		switch (descriptorType)
		{
		case VulkanSimplified::DescriptorTypeFlagBits::INPUT_ATTACHMENT:
			add.descriptorType = VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;
			break;
		case VulkanSimplified::DescriptorTypeFlagBits::STORAGE_BUFFER_DYNAMIC:
			add.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;;
			break;
		case VulkanSimplified::DescriptorTypeFlagBits::UNIFORM_BUFFER_DYNAMIC:
			add.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
			break;
		case VulkanSimplified::DescriptorTypeFlagBits::STORAGE_BUFFER:
			add.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
			break;
		case VulkanSimplified::DescriptorTypeFlagBits::UNIFORM_BUFFER:
			add.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			break;
		case VulkanSimplified::DescriptorTypeFlagBits::STORAGE_TEXEL_BUFFER:
			add.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER;
			break;
		case VulkanSimplified::DescriptorTypeFlagBits::UNIFORM_TEXEL_BUFFER:
			add.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER;
			break;
		case VulkanSimplified::DescriptorTypeFlagBits::STORAGE_IMAGE:
			add.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
			break;
		case VulkanSimplified::DescriptorTypeFlagBits::SAMPLED_IMAGE:
			add.descriptorType = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
			break;
		case VulkanSimplified::DescriptorTypeFlagBits::COMBINED_IMAGE_SAMPLER:
			add.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			break;
		case VulkanSimplified::DescriptorTypeFlagBits::SAMPLER:
			add.descriptorType = VK_DESCRIPTOR_TYPE_SAMPLER;
			break;
		default:
			throw std::runtime_error("SharedDescriptorDataListInternal::AddDescriptorSetLayoutBindingsData Error: Program was given an erroneous descriptor type value!");
		}

		add.descriptorCount = descriptorAmount;

		add.shaderStages = 0;
		if ((shaderStageFlags & VulkanSimplified::SHADER_TYPE_FRAGMENT) == VulkanSimplified::SHADER_TYPE_FRAGMENT)
			add.shaderStages |= VK_SHADER_STAGE_FRAGMENT_BIT;

		if ((shaderStageFlags & VulkanSimplified::SHADER_TYPE_VERTEX) == VulkanSimplified::SHADER_TYPE_VERTEX)
			add.shaderStages |= VK_SHADER_STAGE_VERTEX_BIT;

		return _bindingDataList.AddUniqueObject(std::move(add), addOnReserving);
	}

	std::vector<VkDescriptorSetLayoutBinding> SharedDescriptorDataListInternal::GetDescriptorSetLayoutBindings(uint32_t firstBinding,
		const std::vector<IDObject<DescriptorSetLayoutBindingData>>& bindingIDs) const
	{
		assert(!bindingIDs.empty());

		std::vector<VkDescriptorSetLayoutBinding> ret;
		ret.reserve(bindingIDs.size());

		uint32_t currentBinding = firstBinding;

		if ((std::numeric_limits<uint32_t>::max() - static_cast<size_t>(firstBinding)) < (bindingIDs.size() - 1))
			throw std::runtime_error("SharedDescriptorDataListInternal::GetDescriptorSetLayoutBindings Error: Program was given too high first binding value to fit all bindings in the list!");

		auto bindingList = _bindingDataList.GetObjectList(bindingIDs);

		for (size_t i = 0; i < bindingIDs.size(); i++)
		{
			VkDescriptorSetLayoutBinding add{};
			add.binding = currentBinding++;
			add.descriptorType = bindingList[i].descriptorType;
			add.descriptorCount = bindingList[i].descriptorCount;
			add.stageFlags = bindingList[i].shaderStages;
			add.pImmutableSamplers = nullptr;

			ret.push_back(add);
		}

		return ret;
	}

}