#pragma once

#include <CustomLists/IDObject.h>

#include <VSSharedPipelineDataListsDef.h>
#include <VSSharedDescriptorDataListDef.h>

struct VulkanSharedData
{
	IDObject<VulkanSimplified::SharedShaderPipelineData> fragmentShaderData;
	IDObject<VulkanSimplified::SharedShaderPipelineData> vertexShaderData;

	IDObject<VulkanSimplified::VertexAttributeDescriptionData> vertexAttribute1Data;
	IDObject<VulkanSimplified::VertexAttributeDescriptionData> vertexAttribute2Data;
	IDObject<VulkanSimplified::VertexBindingDescriptionData> vertexBindingData;
	IDObject<VulkanSimplified::VertexInputSharedPipelineData> vertexInputData;

	IDObject<VulkanSimplified::PipelineScissorData> scissorData;
	IDObject<VulkanSimplified::PipelineViewportData> viewportData;

	IDObject<VulkanSimplified::PipelineInputAssemblyData> inputAssemblyData;
	IDObject<VulkanSimplified::PipelineRasterizationData> rasterizationData;
	IDObject<VulkanSimplified::PipelineMultisampleData> multisamplingData;
	std::optional<IDObject<VulkanSimplified::PipelineDepthStencilStateData>> depthStencilData;
	IDObject<VulkanSimplified::PipelineColorBlendAttachment> colorBlendData;

	IDObject<VulkanSimplified::DescriptorSetLayoutBindingData> uniformBufferBinding;
	IDObject<VulkanSimplified::DescriptorSetLayoutBindingData> textureBinding;

	VulkanSharedData();
};