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

	void DescriptorDataLists::WriteNIFDescriptorSetCombined2DArrayTextureSamplerBindings(IDObject<AutoCleanupNIFDescriptorPool> descriptorPoolID,
		const std::vector<DescriptorSetCombined2DArrayTextureSamplerWriteData>& writeDataList)
	{
		_internal.WriteNIFDescriptorSetCombined2DArrayTextureSamplerBindings(descriptorPoolID, writeDataList);
	}

	void DescriptorDataLists::ResetNIFDescriptorPool(IDObject<AutoCleanupNIFDescriptorPool> descriptorPoolID)
	{
		_internal.ResetNIFDescriptorPool(descriptorPoolID);
	}

	bool DescriptorDataLists::DeleteNIFDescriptorPool(IDObject<AutoCleanupNIFDescriptorPool> descriptorPoolID, bool throwOnIDNotFound)
	{
		return _internal.DeleteNIFDescriptorPool(descriptorPoolID, throwOnIDNotFound);
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

	void DescriptorDataLists::WriteIFDescriptorSetCombined2DArrayTextureSamplerBindings(IDObject<AutoCleanupIFDescriptorPool> descriptorPoolID,
		const std::vector<DescriptorSetCombined2DArrayTextureSamplerWriteData>& writeDataList)
	{
		_internal.WriteIFDescriptorSetCombined2DArrayTextureSamplerBindings(descriptorPoolID, writeDataList);
	}

	std::vector<bool> DescriptorDataLists::FreeDescriptorSets(IDObject<AutoCleanupIFDescriptorPool> descriptorPoolID,
		const std::vector<IDObject<AutoCleanupDescriptorSet>>& descriptorSetsIDs, bool throwOnIDNotFound)
	{
		return _internal.FreeDescriptorSets(descriptorPoolID, descriptorSetsIDs, throwOnIDNotFound);
	}

	void DescriptorDataLists::ResetIFDescriptorPool(IDObject<AutoCleanupIFDescriptorPool> descriptorPoolID)
	{
		_internal.ResetIFDescriptorPool(descriptorPoolID);
	}

	bool DescriptorDataLists::DeleteIFDescriptorPool(IDObject<AutoCleanupIFDescriptorPool> descriptorPoolID, bool throwOnIDNotFound)
	{
		return _internal.DeleteIFDescriptorPool(descriptorPoolID, throwOnIDNotFound);
	}

}