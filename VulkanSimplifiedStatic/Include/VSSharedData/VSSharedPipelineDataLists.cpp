#include "VSSharedIpch.h"
#include "VSSharedPipelineDataLists.h"

#include "../../DoNotInclude/VSSharedData/VSSharedPipelineDataListsInternal.h"

#include "../VSCommon/VSDataFormatFlags.h"
#include "../VSCommon/VSImageSampleFlags.h"

namespace VulkanSimplified
{
	SharedPipelineDataListss::SharedPipelineDataListss(VulkanSimplifiedInternal::SharedPipelineDataListssInternal& ref) : _internal(ref)
	{
	}

	SharedPipelineDataListss::~SharedPipelineDataListss()
	{
	}

	IDObject<VulkanSimplifiedInternal::ShaderSpecializationElement> SharedPipelineDataListss::AddShaderSpecializationElement(uint32_t constantID, uint32_t dataOffset, size_t dataSize,
		size_t addOnReserving)
	{
		return _internal.AddShaderSpecializationElement(constantID, dataOffset, dataSize, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::SharedShaderPipelineData> SharedPipelineDataListss::AddSharedShaderPipelineData(std::string entryPointName,
		ShaderTypeFlagBit shaderType, size_t addOnReserving)
	{
		return _internal.AddSharedShaderPipelineData(entryPointName, shaderType, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::VertexAttributeDescriptionData> SharedPipelineDataListss::AddVertexAttributeDescriptionData(uint32_t offset,
		DataFormatSetIndependentID format, size_t addOnReserving)
	{
		return _internal.AddVertexAttributeDescriptionData(offset, format, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::VertexBindingDescriptionData> SharedPipelineDataListss::AddVertexBindingData(std::uint32_t stride,
		VertexBindingInputRate inputRate, const std::vector<IDObject<VulkanSimplifiedInternal::VertexAttributeDescriptionData>>& vertexAttributeIDs,
		size_t addOnReserving)
	{
		return _internal.AddVertexBindingData(stride, inputRate, vertexAttributeIDs, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::VertexInputSharedPipelineData> SharedPipelineDataListss::AddVertexInputSharedPipelineData(
		const std::vector<IDObject<VulkanSimplifiedInternal::VertexBindingDescriptionData>>& bindings, size_t addOnReserving)
	{
		return _internal.AddVertexInputSharedPipelineData(bindings, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::PipelineScissorData> SharedPipelineDataListss::AddPipelineScissorData(int32_t offsetX, int32_t offsetY, uint32_t width, uint32_t height,
		size_t addOnReserving)
	{
		return _internal.AddPipelineScissorData(offsetX, offsetY, width, height, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::PipelineViewportData> SharedPipelineDataListss::AddPipelineViewportData(uint32_t startX, uint32_t startY, uint32_t width, uint32_t height,
		float minDepth, float maxDepth, size_t addOnReserving)
	{
		return _internal.AddPipelineViewportData(startX, startY, width, height, minDepth, maxDepth, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::PipelineInputAssemblyData> SharedPipelineDataListss::AddPipelineInputAssemblyData(PipelinePrimitiveTopology topology,
		bool primitiveRestartEnable, size_t addOnReserving)
	{
		return _internal.AddPipelineInputAssemblyData(topology, primitiveRestartEnable, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::PipelineRasterizationData> SharedPipelineDataListss::AddPipelineRasterizationData(PipelinePolygonMode polygonMode,
		bool cullPolygonBacks, bool frontClockwise, size_t addOnReserving)
	{
		return _internal.AddPipelineRasterizationData(polygonMode, cullPolygonBacks, frontClockwise, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::PipelineMultisampleData> SharedPipelineDataListss::AddPipelineMultisampleData(ImageSampleFlagBits samplingSetting,
		std::optional<std::uint32_t> minSampleShading, size_t addOnReserving)
	{
		return _internal.AddPipelineMultisampleData(samplingSetting, minSampleShading, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::PipelineDepthStencilStateData> SharedPipelineDataListss::AddPipelineDepthStencilStateData(VulkanSimplified::DepthUsage depthUsage,
		CompareOperationsType compareOp, float minDepth, float maxDepth, size_t addOnReserving)
	{
		return _internal.AddPipelineDepthStencilStateData(depthUsage, compareOp, minDepth, maxDepth, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::PipelineColorBlendAttachment> SharedPipelineDataListss::AddPipelineColorBlendAttachment( ColorBlendingComponentFlags blendingComponents,
		ColorBlendingPreset blendingPreset, size_t addOnReserving)
	{
		return _internal.AddPipelineColorBlendAttachment(blendingComponents, blendingPreset, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::PushConstantData> SharedPipelineDataListss::AddPushConstantData(ShaderTypeFlagBit shaderType, uint32_t offset, uint32_t size, size_t addOnReserving)
	{
		return _internal.AddPushConstantData(shaderType, offset, size, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::ShaderSpecializationElement> SharedPipelineDataListss::AddUniqueShaderSpecializationElement(uint32_t constantID, uint32_t dataOffset,
		size_t dataSize, size_t addOnReserving)
	{
		return _internal.AddUniqueShaderSpecializationElement(constantID, dataOffset, dataSize, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::SharedShaderPipelineData> SharedPipelineDataListss::AddUniqueSharedShaderPipelineData(std::string entryPointName,
		ShaderTypeFlagBit shaderType, size_t addOnReserving)
	{
		return _internal.AddUniqueSharedShaderPipelineData(entryPointName, shaderType, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::VertexAttributeDescriptionData> SharedPipelineDataListss::AddUniqueVertexAttributeDescriptionData(uint32_t offset,
		DataFormatSetIndependentID format, size_t addOnReserving)
	{
		return _internal.AddUniqueVertexAttributeDescriptionData(offset, format, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::VertexBindingDescriptionData> SharedPipelineDataListss::AddUniqueVertexBindingData(std::uint32_t stride,
		VertexBindingInputRate inputRate, const std::vector<IDObject<VulkanSimplifiedInternal::VertexAttributeDescriptionData>>& vertexAttributeIDs,
		size_t addOnReserving)
	{
		return _internal.AddUniqueVertexBindingData(stride, inputRate, vertexAttributeIDs, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::VertexInputSharedPipelineData> SharedPipelineDataListss::AddUniqueVertexInputSharedPipelineData(
		const std::vector<IDObject<VulkanSimplifiedInternal::VertexBindingDescriptionData>>& bindings, size_t addOnReserving)
	{
		return _internal.AddUniqueVertexInputSharedPipelineData(bindings, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::PipelineScissorData> SharedPipelineDataListss::AddUniquePipelineScissorData(int32_t offsetX, int32_t offsetY, uint32_t width, uint32_t height,
		size_t addOnReserving)
	{
		return _internal.AddUniquePipelineScissorData(offsetX, offsetY, width, height, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::PipelineViewportData> SharedPipelineDataListss::AddUniquePipelineViewportData(uint32_t startX, uint32_t startY, uint32_t width, uint32_t height, float minDepth, float maxDepth, size_t addOnReserving)
	{
		return _internal.AddUniquePipelineViewportData(startX, startY, width, height, minDepth, maxDepth, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::PipelineInputAssemblyData> SharedPipelineDataListss::AddUniquePipelineInputAssemblyData(PipelinePrimitiveTopology topology, bool primitiveRestartEnable, size_t addOnReserving)
	{
		return _internal.AddUniquePipelineInputAssemblyData(topology, primitiveRestartEnable, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::PipelineRasterizationData> SharedPipelineDataListss::AddUniquePipelineRasterizationData(PipelinePolygonMode polygonMode,
		bool cullPolygonBacks, bool frontClockwise, size_t addOnReserving)
	{
		return _internal.AddUniquePipelineRasterizationData(polygonMode, cullPolygonBacks, frontClockwise, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::PipelineMultisampleData> SharedPipelineDataListss::AddUniquePipelineMultisampleData(ImageSampleFlagBits samplingSetting,
		std::optional<std::uint32_t> minSampleShading, size_t addOnReserving)
	{
		return _internal.AddUniquePipelineMultisampleData(samplingSetting, minSampleShading, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::PipelineDepthStencilStateData> SharedPipelineDataListss::AddUniquePipelineDepthStencilStateData(DepthUsage depthUsage,
		CompareOperationsType compareOp, float minDepth, float maxDepth, size_t addOnReserving)
	{
		return _internal.AddUniquePipelineDepthStencilStateData(depthUsage, compareOp, minDepth, maxDepth, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::PipelineColorBlendAttachment> SharedPipelineDataListss::AddUniquePipelineColorBlendAttachment(ColorBlendingComponentFlags blendingComponents,
		ColorBlendingPreset blendingPreset, size_t addOnReserving)
	{
		return _internal.AddUniquePipelineColorBlendAttachment(blendingComponents, blendingPreset, addOnReserving);
	}

	IDObject<VulkanSimplifiedInternal::PushConstantData> SharedPipelineDataListss::AddUniquePushConstantData(VulkanSimplified::ShaderTypeFlagBit shaderType, uint32_t offset,
		uint32_t size, size_t addOnReserving)
	{
		return _internal.AddUniquePushConstantData(shaderType, offset, size, addOnReserving);
	}

}