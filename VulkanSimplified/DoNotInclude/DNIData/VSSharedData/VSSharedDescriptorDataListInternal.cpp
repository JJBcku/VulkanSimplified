#include "VSSharedNIpch.h"
#include "VSSharedDescriptorDataListInternal.h"

#include "../../../Include/VSSharedData/VSSharedDescriptorDataListCapacities.h"

#include "../../../Include/VSCommon/VSDescriptorTypeFlags.h"
#include "../../../Include/VSCommon/VSShaderTypeFlags.h"

#include "VSDescriptorSetLayoutBindingData.h"

namespace VulkanSimplified
{
	SharedDescriptorDataListInternal::SharedDescriptorDataListInternal(const SharedDescriptorDataListCapacities& initalCapacities) :
		_bindingDataList(initalCapacities.descriptorBindingListInitialCapacity)
	{
	}

	SharedDescriptorDataListInternal::~SharedDescriptorDataListInternal()
	{
	}

	IDObject<DescriptorSetLayoutBindingData> SharedDescriptorDataListInternal::AddDescriptorSetLayoutBindingsData(DescriptorTypeFlagBits descriptorType,
		uint32_t descriptorAmount, ShaderTypeFlags shaderStageFlags, size_t addOnReserving)
	{
		DescriptorSetLayoutBindingData add;

		switch (descriptorType)
		{
		case DescriptorTypeFlagBits::INPUT_ATTACHMENT:
			add.descriptorType = VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;
			break;
		case DescriptorTypeFlagBits::STORAGE_BUFFER_DYNAMIC:
			add.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;;
			break;
		case DescriptorTypeFlagBits::UNIFORM_BUFFER_DYNAMIC:
			add.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
			break;
		case DescriptorTypeFlagBits::STORAGE_BUFFER:
			add.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
			break;
		case DescriptorTypeFlagBits::UNIFORM_BUFFER:
			add.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			break;
		case DescriptorTypeFlagBits::STORAGE_TEXEL_BUFFER:
			add.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER;
			break;
		case DescriptorTypeFlagBits::UNIFORM_TEXEL_BUFFER:
			add.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER;
			break;
		case DescriptorTypeFlagBits::STORAGE_IMAGE:
			add.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
			break;
		case DescriptorTypeFlagBits::SAMPLED_IMAGE:
			add.descriptorType = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
			break;
		case DescriptorTypeFlagBits::COMBINED_IMAGE_SAMPLER:
			add.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			break;
		case DescriptorTypeFlagBits::SAMPLER:
			add.descriptorType = VK_DESCRIPTOR_TYPE_SAMPLER;
			break;
		default:
			throw std::runtime_error("SharedDescriptorDataListInternal::AddDescriptorSetLayoutBindingsData Error: Program was given an erroneous descriptor type value!");
		}

		add.descriptorCount = descriptorAmount;

		add.shaderStages = 0;
		if ((shaderStageFlags & SHADER_TYPE_FRAGMENT) == SHADER_TYPE_FRAGMENT)
			add.shaderStages |= VK_SHADER_STAGE_FRAGMENT_BIT;

		if ((shaderStageFlags & SHADER_TYPE_VERTEX) == SHADER_TYPE_VERTEX)
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