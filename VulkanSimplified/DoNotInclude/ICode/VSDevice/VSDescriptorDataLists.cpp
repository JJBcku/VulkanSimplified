#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSDescriptorDataLists.h"

#include "../../../DoNotInclude/DNIData/VSDevice/VSDescriptorDataListsInternal.h"

namespace VulkanSimplified
{
	DescriptorDataLists::DescriptorDataLists(DescriptorDataListsInternal& ref) : _internal(ref)
	{
	}

	DescriptorDataLists::~DescriptorDataLists()
	{
	}

	IDObject<AutoCleanupDescriptorSetLayout> DescriptorDataLists::AddDescriptorSetLayout(uint32_t firstBinding,
		const std::vector<DescriptorSetBindingFullData>& descriptorSetLayoutBindings, size_t addOnReserving)
	{
		return _internal.AddDescriptorSetLayout(firstBinding, descriptorSetLayoutBindings, addOnReserving);
	}

	IDObject<AutoCleanupNIFDescriptorPool> DescriptorDataLists::AddNoIndividualFreeingDescriptorPool(uint32_t maxTotalSetCount,
		const std::vector<std::pair<DescriptorTypeFlagBits, uint32_t>>& maxTypeCountsList, size_t addOnReserving)
	{
		return _internal.AddNoIndividualFreeingDescriptorPool(maxTotalSetCount, maxTypeCountsList, addOnReserving);
	}

	std::vector<IDObject<AutoCleanupDescriptorSet>> DescriptorDataLists::AllocateNIFDescriptorSets(
		IDObject<AutoCleanupNIFDescriptorPool> descriptorPoolID,
		std::vector<IDObject<AutoCleanupDescriptorSetLayout>> descriptorSetLayoutIDs)
	{
		return _internal.AllocateNIFDescriptorSets(descriptorPoolID, descriptorSetLayoutIDs);
	}

	void DescriptorDataLists::WriteNIFDescriptorSetUniformBufferBindings(IDObject<AutoCleanupNIFDescriptorPool> descriptorPoolID,
		const std::vector<DescriptorSetUniformBufferBindingWriteData>& writeDataList)
	{
		_internal.WriteNIFDescriptorSetUniformBufferBindings(descriptorPoolID, writeDataList);
	}

	void DescriptorDataLists::WriteNIFDescriptorSetCombined2DTextureSamplerBindings(IDObject<AutoCleanupNIFDescriptorPool> descriptorPoolID,
		const std::vector<DescriptorSetCombined2DTextureSamplerWriteData>& writeDataList)
	{
		_internal.WriteNIFDescriptorSetCombined2DTextureSamplerBindings(descriptorPoolID, writeDataList);
	}

	IDObject<AutoCleanupIFDescriptorPool> DescriptorDataLists::AddIndividualFreeingDescriptorPool(uint32_t maxTotalSetCount,
		const std::vector<std::pair<DescriptorTypeFlagBits, uint32_t>>& maxTypeCountsList, size_t addOnReserving)
	{
		return _internal.AddIndividualFreeingDescriptorPool(maxTotalSetCount, maxTypeCountsList, addOnReserving);
	}

	std::vector<IDObject<AutoCleanupDescriptorSet>> DescriptorDataLists::AllocateIFDescriptorSets(
		IDObject<AutoCleanupIFDescriptorPool> descriptorPoolID,
		std::vector<IDObject<AutoCleanupDescriptorSetLayout>> descriptorSetLayoutIDs)
	{
		return _internal.AllocateIFDescriptorSets(descriptorPoolID, descriptorSetLayoutIDs);
	}

	void DescriptorDataLists::WriteIFDescriptorSetUniformBufferBindings(IDObject<AutoCleanupIFDescriptorPool> descriptorPoolID,
		const std::vector<DescriptorSetUniformBufferBindingWriteData>& writeDataList)
	{
		_internal.WriteIFDescriptorSetUniformBufferBindings(descriptorPoolID, writeDataList);
	}

	void DescriptorDataLists::WriteIFDescriptorSetCombined2DTextureSamplerBindings(IDObject<AutoCleanupIFDescriptorPool> descriptorPoolID,
		const std::vector<DescriptorSetCombined2DTextureSamplerWriteData>& writeDataList)
	{
		_internal.WriteIFDescriptorSetCombined2DTextureSamplerBindings(descriptorPoolID, writeDataList);
	}

}