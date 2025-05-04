#pragma once

#include <CustomLists/IDObject.h>

#include <VSSharedPipelineDataListsDef.h>

struct VulkanSharedData
{
	IDObject<VulkanSimplifiedInternal::SharedShaderPipelineData> fragmentShaderData;
	IDObject<VulkanSimplifiedInternal::SharedShaderPipelineData> vertexShaderData;

	IDObject<VulkanSimplifiedInternal::VertexInputSharedPipelineData> vertexInputData;

	IDObject<VulkanSimplifiedInternal::PipelineScissorData> scissorData;
	IDObject<VulkanSimplifiedInternal::PipelineViewportData> viewportData;

	IDObject<VulkanSimplifiedInternal::PipelineInputAssemblyData> inputAssemblyData;
	IDObject<VulkanSimplifiedInternal::PipelineRasterizationData> rasterizationData;
	IDObject<VulkanSimplifiedInternal::PipelineMultisampleData> multisamplingData;
	std::optional<IDObject<VulkanSimplifiedInternal::PipelineDepthStencilStateData>> depthStencilData;
	IDObject<VulkanSimplifiedInternal::PipelineColorBlendAttachment> colorBlendData;

	VulkanSharedData();
};