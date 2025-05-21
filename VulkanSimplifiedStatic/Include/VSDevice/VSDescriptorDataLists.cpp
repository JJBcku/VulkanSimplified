#include "VSDeviceIpch.h"
#include "VSDescriptorDataLists.h"

#include "../../DoNotInclude/VSDevice/VSDescriptorDataListsInternal.h"

namespace VulkanSimplified
{
	DescriptorDataLists::DescriptorDataLists(VulkanSimplifiedInternal::DescriptorDataListsInternal& ref) : _internal(ref)
	{
	}

	DescriptorDataLists::~DescriptorDataLists()
	{
	}

	IDObject<VulkanSimplifiedInternal::AutoCleanupDescriptorSetLayout> DescriptorDataLists::AddDescriptorSetLayout(uint32_t firstBinding,
		const std::vector<IDObject<VulkanSimplifiedInternal::DescriptorSetLayoutBindingData>>& descriptorSetLayoutBindings, size_t addOnReserving)
	{
		return _internal.AddDescriptorSetLayout(firstBinding, descriptorSetLayoutBindings, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::AutoCleanupNIFDescriptorPool> DescriptorDataLists::AddNoIndividualFreeingDescriptorPool(uint32_t maxTotalSetCount,
		const std::vector<std::pair<DescriptorTypeFlagBits, uint32_t>>& maxTypeCountsList, size_t addOnReserving)
	{
		return _internal.AddNoIndividualFreeingDescriptorPool(maxTotalSetCount, maxTypeCountsList, addOnReserving);
	}

	std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupUniformBufferDescriptorSet>> DescriptorDataLists::AllocateNIFUniformBufferDescriptorSets(
		IDObject<VulkanSimplifiedInternal::AutoCleanupNIFDescriptorPool> descriptorPoolID,
		std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupDescriptorSetLayout>> descriptorSetLayoutIDs)
	{
		return _internal.AllocateNIFUniformBufferDescriptorSets(descriptorPoolID, descriptorSetLayoutIDs);
	}

	void DescriptorDataLists::WriteNIFUniformBufferDescriptorSets(IDObject<VulkanSimplifiedInternal::AutoCleanupNIFDescriptorPool> descriptorPoolID,
		const std::vector<UniformBufferDescriptorSetWriteData>& writeDataList)
	{
		_internal.WriteNIFUniformBufferDescriptorSets(descriptorPoolID, writeDataList);
	}

	IDObject<VulkanSimplifiedInternal::AutoCleanupIFDescriptorPool> DescriptorDataLists::AddIndividualFreeingDescriptorPool(uint32_t maxTotalSetCount,
		const std::vector<std::pair<DescriptorTypeFlagBits, uint32_t>>& maxTypeCountsList, size_t addOnReserving)
	{
		return _internal.AddIndividualFreeingDescriptorPool(maxTotalSetCount, maxTypeCountsList, addOnReserving);
	}

	std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupUniformBufferDescriptorSet>> DescriptorDataLists::AllocateIFUniformBufferDescriptorSets(
		IDObject<VulkanSimplifiedInternal::AutoCleanupIFDescriptorPool> descriptorPoolID,
		std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupDescriptorSetLayout>> descriptorSetLayoutIDs)
	{
		return _internal.AllocateIFUniformBufferDescriptorSets(descriptorPoolID, descriptorSetLayoutIDs);
	}

	void DescriptorDataLists::WriteIFUniformBufferDescriptorSets(IDObject<VulkanSimplifiedInternal::AutoCleanupIFDescriptorPool> descriptorPoolID,
		const std::vector<UniformBufferDescriptorSetWriteData>& writeDataList)
	{
		_internal.WriteIFUniformBufferDescriptorSets(descriptorPoolID, writeDataList);
	}

}