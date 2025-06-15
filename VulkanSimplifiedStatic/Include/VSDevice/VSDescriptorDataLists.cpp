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
		const std::vector<DescriptorSetBindingFullData>& descriptorSetLayoutBindings, size_t addOnReserving)
	{
		return _internal.AddDescriptorSetLayout(firstBinding, descriptorSetLayoutBindings, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::AutoCleanupNIFDescriptorPool> DescriptorDataLists::AddNoIndividualFreeingDescriptorPool(uint32_t maxTotalSetCount,
		const std::vector<std::pair<DescriptorTypeFlagBits, uint32_t>>& maxTypeCountsList, size_t addOnReserving)
	{
		return _internal.AddNoIndividualFreeingDescriptorPool(maxTotalSetCount, maxTypeCountsList, addOnReserving);
	}

	std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupDescriptorSet>> DescriptorDataLists::AllocateNIFDescriptorSets(
		IDObject<VulkanSimplifiedInternal::AutoCleanupNIFDescriptorPool> descriptorPoolID,
		std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupDescriptorSetLayout>> descriptorSetLayoutIDs)
	{
		return _internal.AllocateNIFDescriptorSets(descriptorPoolID, descriptorSetLayoutIDs);
	}

	void DescriptorDataLists::WriteNIFDescriptorSetUniformBufferBindings(IDObject<VulkanSimplifiedInternal::AutoCleanupNIFDescriptorPool> descriptorPoolID,
		const std::vector<DescriptorSetUniformBufferBindingWriteData>& writeDataList)
	{
		_internal.WriteNIFDescriptorSetUniformBufferBindings(descriptorPoolID, writeDataList);
	}

	void DescriptorDataLists::WriteNIFDescriptorSetCombined2DTextureSamplerBindings(IDObject<VulkanSimplifiedInternal::AutoCleanupNIFDescriptorPool> descriptorPoolID,
		const std::vector<DescriptorSetCombined2DTextureSamplerWriteData>& writeDataList)
	{
		_internal.WriteNIFDescriptorSetCombined2DTextureSamplerBindings(descriptorPoolID, writeDataList);
	}

	IDObject<VulkanSimplifiedInternal::AutoCleanupIFDescriptorPool> DescriptorDataLists::AddIndividualFreeingDescriptorPool(uint32_t maxTotalSetCount,
		const std::vector<std::pair<DescriptorTypeFlagBits, uint32_t>>& maxTypeCountsList, size_t addOnReserving)
	{
		return _internal.AddIndividualFreeingDescriptorPool(maxTotalSetCount, maxTypeCountsList, addOnReserving);
	}

	std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupDescriptorSet>> DescriptorDataLists::AllocateIFDescriptorSets(
		IDObject<VulkanSimplifiedInternal::AutoCleanupIFDescriptorPool> descriptorPoolID,
		std::vector<IDObject<VulkanSimplifiedInternal::AutoCleanupDescriptorSetLayout>> descriptorSetLayoutIDs)
	{
		return _internal.AllocateIFDescriptorSets(descriptorPoolID, descriptorSetLayoutIDs);
	}

	void DescriptorDataLists::WriteIFDescriptorSetUniformBufferBindings(IDObject<VulkanSimplifiedInternal::AutoCleanupIFDescriptorPool> descriptorPoolID,
		const std::vector<DescriptorSetUniformBufferBindingWriteData>& writeDataList)
	{
		_internal.WriteIFDescriptorSetUniformBufferBindings(descriptorPoolID, writeDataList);
	}

	void DescriptorDataLists::WriteIFDescriptorSetCombined2DTextureSamplerBindings(IDObject<VulkanSimplifiedInternal::AutoCleanupIFDescriptorPool> descriptorPoolID,
		const std::vector<DescriptorSetCombined2DTextureSamplerWriteData>& writeDataList)
	{
		_internal.WriteIFDescriptorSetCombined2DTextureSamplerBindings(descriptorPoolID, writeDataList);
	}

}