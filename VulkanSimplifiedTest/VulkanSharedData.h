#pragma once

#include <CustomLists/IDObject.h>

#include <VSSharedPipelineDataListsDef.h>
#include <VSSharedDescriptorDataListDef.h>

struct VulkanSharedData
{
	IDObject<VS::SharedShaderPipelineData> fragmentShaderData;
	IDObject<VS::SharedShaderPipelineData> vertexShaderData;

	IDObject<VS::VertexAttributeDescriptionData> vertexAttribute1Data;
	IDObject<VS::VertexAttributeDescriptionData> vertexAttribute2Data;
	IDObject<VS::VertexBindingDescriptionData> vertexBindingData;
	IDObject<VS::VertexInputSharedPipelineData> vertexInputData;

	IDObject<VS::PipelineScissorData> scissorData;
	IDObject<VS::PipelineViewportData> viewportData;

	IDObject<VS::PipelineInputAssemblyData> inputAssemblyData;
	IDObject<VS::PipelineRasterizationData> rasterizationData;
	IDObject<VS::PipelineMultisampleData> multisamplingData;
	std::optional<IDObject<VS::PipelineDepthStencilStateData>> depthStencilData;
	IDObject<VS::PipelineColorBlendAttachment> colorBlendData;

	IDObject<VS::DescriptorSetLayoutBindingData> uniformBufferBinding;
	IDObject<VS::DescriptorSetLayoutBindingData> textureBinding;

	VulkanSharedData();
};