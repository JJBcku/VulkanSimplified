#pragma once

#include <CustomLists/IDObject.h>

#include <VSSharedPipelineDataListsDef.h>
#include <VSSharedDescriptorDataListDef.h>

struct VulkanSharedData
{
	IDObject<VulkanSimplifiedInternal::SharedShaderPipelineData> fragmentShaderData;
	IDObject<VulkanSimplifiedInternal::SharedShaderPipelineData> vertexShaderData;

	IDObject<VulkanSimplifiedInternal::VertexAttributeDescriptionData> vertexAttribute1Data;
	IDObject<VulkanSimplifiedInternal::VertexAttributeDescriptionData> vertexAttribute2Data;
	IDObject<VulkanSimplifiedInternal::VertexBindingDescriptionData> vertexBindingData;
	IDObject<VulkanSimplifiedInternal::VertexInputSharedPipelineData> vertexInputData;

	IDObject<VulkanSimplifiedInternal::PipelineScissorData> scissorData;
	IDObject<VulkanSimplifiedInternal::PipelineViewportData> viewportData;

	IDObject<VulkanSimplifiedInternal::PipelineInputAssemblyData> inputAssemblyData;
	IDObject<VulkanSimplifiedInternal::PipelineRasterizationData> rasterizationData;
	IDObject<VulkanSimplifiedInternal::PipelineMultisampleData> multisamplingData;
	std::optional<IDObject<VulkanSimplifiedInternal::PipelineDepthStencilStateData>> depthStencilData;
	IDObject<VulkanSimplifiedInternal::PipelineColorBlendAttachment> colorBlendData;

	IDObject<VulkanSimplifiedInternal::DescriptorSetLayoutBindingData> uniformBufferBinding;

	VulkanSharedData();
};