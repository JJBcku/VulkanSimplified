#pragma once

#include <CustomLists/IDObject.h>

#include "VSArbitraryShaderID.h"

#include <stdint.h>
#include <vector>
#include <optional>

namespace VulkanSimplifiedInternal
{
	struct ShaderStageData;

	struct PipelineViewportData;
	struct PipelineScissorData;

	struct ShaderSpecializationElement;
	struct SharedShaderPipelineData;

	struct VertexInputSharedPipelineData;

	struct PipelineInputAssemblyData;
	struct PipelineRasterizationData;
	struct PipelineMultisampleData;
	struct PipelineDepthStencilStateData;
	struct PipelineColorBlendAttachment;

	class AutoCleanupPipelineLayout;
	class AutoCleanupGraphicsPipeline;
	class AutoCleanupRenderPass;
}

namespace VulkanSimplified
{
	struct ShaderSpecializationData
	{
		std::vector<IDObject<VulkanSimplifiedInternal::ShaderSpecializationElement>> specializationElements;
		size_t dataSize;
		const void* data;

		ShaderSpecializationData();
	};

	struct ShaderStageData
	{
		IDObject<VulkanSimplifiedInternal::SharedShaderPipelineData> sharedData;
		VulkanSimplified::ArbitraryShaderID shaderDeviceID;

		std::optional<ShaderSpecializationData> specializationData;

		ShaderStageData() = default;
	};

	struct ViewportStatePipelineDataPoint
	{
		IDObject<VulkanSimplifiedInternal::PipelineViewportData> viewport;
		IDObject<VulkanSimplifiedInternal::PipelineScissorData> scissor;

		ViewportStatePipelineDataPoint() = default;
	};

	enum class PipelineDerrivationSettings : uint64_t
	{
		DO_NOT_DERRIVE = 0,
		PIPELINE_ID = 1,
		PIPELINE_INDEX = 2,
	};

	union GraphicsPipelineDerrivationData
	{
		PipelineDerrivationSettings settings;

		struct
		{
			PipelineDerrivationSettings settings;
			IDObject<VulkanSimplifiedInternal::AutoCleanupGraphicsPipeline> ID;
		} pipelineID;

		struct
		{
			PipelineDerrivationSettings settings;
			size_t index;
		} pipelineIndex;

		GraphicsPipelineDerrivationData();
	};

	struct GraphicsPipelineCreationData
	{
		std::vector<ShaderStageData> shaderStages;
		IDObject<VulkanSimplifiedInternal::VertexInputSharedPipelineData> vertexInputData;
		IDObject<VulkanSimplifiedInternal::PipelineInputAssemblyData> inputAssemblyData;
		std::vector<ViewportStatePipelineDataPoint> viewportData;
		IDObject<VulkanSimplifiedInternal::PipelineRasterizationData> rasterizationData;
		IDObject<VulkanSimplifiedInternal::PipelineMultisampleData> samplingData;
		std::optional<IDObject<VulkanSimplifiedInternal::PipelineDepthStencilStateData>> depthStencilData;
		std::vector<IDObject<VulkanSimplifiedInternal::PipelineColorBlendAttachment>> colorBlendingData;

		IDObject<VulkanSimplifiedInternal::AutoCleanupPipelineLayout> pipelineLayout;
		IDObject<VulkanSimplifiedInternal::AutoCleanupRenderPass> renderPass;
		uint32_t subpassIndex;
		uint32_t padding;
		GraphicsPipelineDerrivationData pipelineDerrivationData;

		GraphicsPipelineCreationData();
	};
}