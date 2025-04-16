#pragma once

#include <CustomLists/IDObject.h>

namespace VulkanSimplifiedInternal
{
	struct SharedShaderPipelineData;
	struct VertexInputSharedPipelineData;

	struct PipelineScissorData;
	struct PipelineViewportData;

	struct PipelineInputAssemblyData;
	struct PipelineRasterizationData;
	struct PipelineMultisampleData;
	struct PipelineDepthStencilStateData;
	struct PipelineColorBlendAttachment;
}

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