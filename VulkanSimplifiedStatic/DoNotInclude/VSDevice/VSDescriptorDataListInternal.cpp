#include "VSDeviceNIpch.h"
#include "VSDescriptorDataListInternal.h"

#include  "../VSSharedData/VSSharedDescriptorDataListInternal.h"
#include  "../VSSharedData/VSDescriptorSetLayoutBindingData.h"

#include "../../Include/VSDevice/VSDescriptorListsInitialCapacities.h"

#include "VSAutoCleanupDescriptorSetLayout.h"

namespace VulkanSimplifiedInternal
{
	DescriptorDataListInternal::DescriptorDataListInternal(const SharedDescriptorDataListInternal& sharedDescriptorData, VkDevice device,
		const VulkanSimplified::DescriptorListsInitialCapacities& initialCapacities) : _sharedDescriptorData(sharedDescriptorData), _device(device),
		_descriptorSetLayouts(initialCapacities.descriptorSetListInitialCapacity)
	{
	}

	DescriptorDataListInternal::~DescriptorDataListInternal()
	{
	}

	IDObject<AutoCleanupDescriptorSetLayout> DescriptorDataListInternal::AddDescriptorSetLayout(uint32_t firstBinding,
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

	std::vector<VkDescriptorSetLayout> DescriptorDataListInternal::GetDescriptorSetLayouts(const std::vector<IDObject<AutoCleanupDescriptorSetLayout>>& layoutIDs) const
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

}