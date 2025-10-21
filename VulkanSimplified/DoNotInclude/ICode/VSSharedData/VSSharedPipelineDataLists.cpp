#include "VSSharedIpch.h"
#include "../../../Include/VSSharedData/VSSharedPipelineDataLists.h"

#include "../../../DoNotInclude/DNIData/VSSharedData/VSSharedPipelineDataListsInternal.h"

#include "../../../Include/VSCommon/VSDataFormatFlags.h"
#include "../../../Include/VSCommon/VSImageSampleFlags.h"

namespace VulkanSimplified
{
	SharedPipelineDataList::SharedPipelineDataList(SharedPipelineDataListsInternal& ref) : _internal(ref)
	{
	}

	SharedPipelineDataList::~SharedPipelineDataList()
	{
	}

	IDObject<ShaderSpecializationElement> SharedPipelineDataList::AddShaderSpecializationElement(uint32_t constantID, uint32_t dataOffset, size_t dataSize,
		size_t addOnReserving)
	{
		return _internal.AddShaderSpecializationElement(constantID, dataOffset, dataSize, addOnReserving);
	}

	IDObject<SharedShaderPipelineData> SharedPipelineDataList::AddSharedShaderPipelineData(std::string entryPointName,
		ShaderTypeFlagBit shaderType, size_t addOnReserving)
	{
		return _internal.AddSharedShaderPipelineData(entryPointName, shaderType, addOnReserving);
	}

	IDObject<VertexAttributeDescriptionData> SharedPipelineDataList::AddVertexAttributeDescriptionData(uint32_t offset,
		DataFormatSetIndependentID format, size_t addOnReserving)
	{
		return _internal.AddVertexAttributeDescriptionData(offset, format, addOnReserving);
	}

	IDObject<VertexBindingDescriptionData> SharedPipelineDataList::AddVertexBindingData(uint32_t stride,
		VertexBindingInputRate inputRate, const std::vector<IDObject<VertexAttributeDescriptionData>>& vertexAttributeIDs,
		size_t addOnReserving)
	{
		return _internal.AddVertexBindingData(stride, inputRate, vertexAttributeIDs, addOnReserving);
	}

	IDObject<VertexInputSharedPipelineData> SharedPipelineDataList::AddVertexInputSharedPipelineData(
		const std::vector<IDObject<VertexBindingDescriptionData>>& bindings, size_t addOnReserving)
	{
		return _internal.AddVertexInputSharedPipelineData(bindings, addOnReserving);
	}

	IDObject<PipelineScissorData> SharedPipelineDataList::AddPipelineScissorData(int32_t offsetX, int32_t offsetY, uint32_t width, uint32_t height,
		size_t addOnReserving)
	{
		return _internal.AddPipelineScissorData(offsetX, offsetY, width, height, addOnReserving);
	}

	IDObject<PipelineViewportData> SharedPipelineDataList::AddPipelineViewportData(uint32_t startX, uint32_t startY, uint32_t width, uint32_t height,
		float minDepth, float maxDepth, size_t addOnReserving)
	{
		return _internal.AddPipelineViewportData(startX, startY, width, height, minDepth, maxDepth, addOnReserving);
	}

	IDObject<PipelineInputAssemblyData> SharedPipelineDataList::AddPipelineInputAssemblyData(PipelinePrimitiveTopology topology,
		bool primitiveRestartEnable, size_t addOnReserving)
	{
		return _internal.AddPipelineInputAssemblyData(topology, primitiveRestartEnable, addOnReserving);
	}

	IDObject<PipelineRasterizationData> SharedPipelineDataList::AddPipelineRasterizationData(PipelinePolygonMode polygonMode,
		bool cullPolygonBacks, bool frontClockwise, size_t addOnReserving)
	{
		return _internal.AddPipelineRasterizationData(polygonMode, cullPolygonBacks, frontClockwise, addOnReserving);
	}

	IDObject<PipelineMultisampleData> SharedPipelineDataList::AddPipelineMultisampleData(ImageSampleFlagBits samplingSetting,
		std::optional<uint32_t> minSampleShading, size_t addOnReserving)
	{
		return _internal.AddPipelineMultisampleData(samplingSetting, minSampleShading, addOnReserving);
	}

	IDObject<PipelineDepthStencilStateData> SharedPipelineDataList::AddPipelineDepthStencilStateData(DepthUsage depthUsage,
		CompareOperationsType compareOp, float minDepth, float maxDepth, size_t addOnReserving)
	{
		return _internal.AddPipelineDepthStencilStateData(depthUsage, compareOp, minDepth, maxDepth, addOnReserving);
	}

	IDObject<PipelineColorBlendAttachment> SharedPipelineDataList::AddPipelineColorBlendAttachment( ColorBlendingComponentFlags blendingComponents,
		ColorBlendingPreset blendingPreset, size_t addOnReserving)
	{
		return _internal.AddPipelineColorBlendAttachment(blendingComponents, blendingPreset, addOnReserving);
	}

	IDObject<PushConstantData> SharedPipelineDataList::AddPushConstantData(ShaderTypeFlagBit shaderType, uint32_t offset, uint32_t size, size_t addOnReserving)
	{
		return _internal.AddPushConstantData(shaderType, offset, size, addOnReserving);
	}

	IDObject<ShaderSpecializationElement> SharedPipelineDataList::AddUniqueShaderSpecializationElement(uint32_t constantID, uint32_t dataOffset,
		size_t dataSize, size_t addOnReserving)
	{
		return _internal.AddUniqueShaderSpecializationElement(constantID, dataOffset, dataSize, addOnReserving);
	}

	IDObject<SharedShaderPipelineData> SharedPipelineDataList::AddUniqueSharedShaderPipelineData(std::string entryPointName,
		ShaderTypeFlagBit shaderType, size_t addOnReserving)
	{
		return _internal.AddUniqueSharedShaderPipelineData(entryPointName, shaderType, addOnReserving);
	}

	IDObject<VertexAttributeDescriptionData> SharedPipelineDataList::AddUniqueVertexAttributeDescriptionData(uint32_t offset,
		DataFormatSetIndependentID format, size_t addOnReserving)
	{
		return _internal.AddUniqueVertexAttributeDescriptionData(offset, format, addOnReserving);
	}

	IDObject<VertexBindingDescriptionData> SharedPipelineDataList::AddUniqueVertexBindingData(uint32_t stride,
		VertexBindingInputRate inputRate, const std::vector<IDObject<VertexAttributeDescriptionData>>& vertexAttributeIDs,
		size_t addOnReserving)
	{
		return _internal.AddUniqueVertexBindingData(stride, inputRate, vertexAttributeIDs, addOnReserving);
	}

	IDObject<VertexInputSharedPipelineData> SharedPipelineDataList::AddUniqueVertexInputSharedPipelineData(
		const std::vector<IDObject<VertexBindingDescriptionData>>& bindings, size_t addOnReserving)
	{
		return _internal.AddUniqueVertexInputSharedPipelineData(bindings, addOnReserving);
	}

	IDObject<PipelineScissorData> SharedPipelineDataList::AddUniquePipelineScissorData(int32_t offsetX, int32_t offsetY, uint32_t width, uint32_t height,
		size_t addOnReserving)
	{
		return _internal.AddUniquePipelineScissorData(offsetX, offsetY, width, height, addOnReserving);
	}

	IDObject<PipelineViewportData> SharedPipelineDataList::AddUniquePipelineViewportData(uint32_t startX, uint32_t startY, uint32_t width, uint32_t height, float minDepth, float maxDepth, size_t addOnReserving)
	{
		return _internal.AddUniquePipelineViewportData(startX, startY, width, height, minDepth, maxDepth, addOnReserving);
	}

	IDObject<PipelineInputAssemblyData> SharedPipelineDataList::AddUniquePipelineInputAssemblyData(PipelinePrimitiveTopology topology, bool primitiveRestartEnable, size_t addOnReserving)
	{
		return _internal.AddUniquePipelineInputAssemblyData(topology, primitiveRestartEnable, addOnReserving);
	}

	IDObject<PipelineRasterizationData> SharedPipelineDataList::AddUniquePipelineRasterizationData(PipelinePolygonMode polygonMode,
		bool cullPolygonBacks, bool frontClockwise, size_t addOnReserving)
	{
		return _internal.AddUniquePipelineRasterizationData(polygonMode, cullPolygonBacks, frontClockwise, addOnReserving);
	}

	IDObject<PipelineMultisampleData> SharedPipelineDataList::AddUniquePipelineMultisampleData(ImageSampleFlagBits samplingSetting,
		std::optional<uint32_t> minSampleShading, size_t addOnReserving)
	{
		return _internal.AddUniquePipelineMultisampleData(samplingSetting, minSampleShading, addOnReserving);
	}

	IDObject<PipelineDepthStencilStateData> SharedPipelineDataList::AddUniquePipelineDepthStencilStateData(DepthUsage depthUsage,
		CompareOperationsType compareOp, float minDepth, float maxDepth, size_t addOnReserving)
	{
		return _internal.AddUniquePipelineDepthStencilStateData(depthUsage, compareOp, minDepth, maxDepth, addOnReserving);
	}

	IDObject<PipelineColorBlendAttachment> SharedPipelineDataList::AddUniquePipelineColorBlendAttachment(ColorBlendingComponentFlags blendingComponents,
		ColorBlendingPreset blendingPreset, size_t addOnReserving)
	{
		return _internal.AddUniquePipelineColorBlendAttachment(blendingComponents, blendingPreset, addOnReserving);
	}

	IDObject<PushConstantData> SharedPipelineDataList::AddUniquePushConstantData(ShaderTypeFlagBit shaderType, uint32_t offset,
		uint32_t size, size_t addOnReserving)
	{
		return _internal.AddUniquePushConstantData(shaderType, offset, size, addOnReserving);
	}

}