#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSGraphicsPipelineCreationData.h"

namespace VulkanSimplified
{

	ShaderSpecializationData::ShaderSpecializationData() noexcept
	{
		dataSize = std::numeric_limits<size_t>::max();
		data = nullptr;
	}

	ShaderSpecializationData::ShaderSpecializationData(const ShaderSpecializationData& rhs) noexcept : specializationElements(rhs.specializationElements),
		dataSize(rhs.dataSize), data(rhs.data)
	{
	}

	ShaderSpecializationData::ShaderSpecializationData(ShaderSpecializationData&& rhs) noexcept : specializationElements(std::move(rhs.specializationElements)),
		dataSize(rhs.dataSize), data(rhs.data)
	{
		rhs.dataSize = 0;
		rhs.data = nullptr;
	}

	ShaderSpecializationData::~ShaderSpecializationData()
	{
	}

	ShaderSpecializationData& ShaderSpecializationData::operator=(const ShaderSpecializationData& rhs) noexcept
	{
		specializationElements = rhs.specializationElements;
		dataSize = rhs.dataSize;
		data = rhs.data;

		return *this;
	}

	ShaderSpecializationData& ShaderSpecializationData::operator=(ShaderSpecializationData&& rhs) noexcept
	{
		specializationElements = std::move(rhs.specializationElements);
		dataSize = rhs.dataSize;
		data = rhs.data;

		rhs.dataSize = 0;
		rhs.data = nullptr;

		return *this;
	}

	ShaderStageData::ShaderStageData() noexcept
	{
	}

	ShaderStageData::ShaderStageData(const ShaderStageData& rhs) noexcept : sharedData(rhs.sharedData), shaderDeviceID(rhs.shaderDeviceID), specializationData(rhs.specializationData)
	{
	}

	ShaderStageData::ShaderStageData(ShaderStageData&& rhs) noexcept : sharedData(std::move(rhs.sharedData)), shaderDeviceID(std::move(rhs.shaderDeviceID)),
		specializationData(std::move(rhs.specializationData))
	{
	}

	ShaderStageData::~ShaderStageData()
	{
	}

	ShaderStageData& ShaderStageData::operator=(const ShaderStageData& rhs) noexcept
	{
		sharedData = rhs.sharedData;
		shaderDeviceID = rhs.shaderDeviceID;
		specializationData = rhs.specializationData;

		return *this;
	}

	ShaderStageData& ShaderStageData::operator=(ShaderStageData&& rhs) noexcept
	{
		sharedData = std::move(rhs.sharedData);
		shaderDeviceID = std::move(rhs.shaderDeviceID);
		specializationData = std::move(rhs.specializationData);

		return *this;
	}

	ViewportStatePipelineDataPoint::ViewportStatePipelineDataPoint() noexcept
	{
	}

	ViewportStatePipelineDataPoint::ViewportStatePipelineDataPoint(const ViewportStatePipelineDataPoint& rhs) noexcept : viewport(rhs.viewport), scissor(rhs.scissor)
	{
	}

	ViewportStatePipelineDataPoint::ViewportStatePipelineDataPoint(ViewportStatePipelineDataPoint&& rhs) noexcept : viewport(std::move(rhs.viewport)), scissor(std::move(rhs.scissor))
	{
	}

	ViewportStatePipelineDataPoint::~ViewportStatePipelineDataPoint()
	{
	}

	ViewportStatePipelineDataPoint& ViewportStatePipelineDataPoint::operator=(const ViewportStatePipelineDataPoint& rhs) noexcept
	{
		viewport = rhs.viewport;
		scissor = rhs.scissor;

		return *this;
	}

	ViewportStatePipelineDataPoint& ViewportStatePipelineDataPoint::operator=(ViewportStatePipelineDataPoint&& rhs) noexcept
	{
		viewport = std::move(rhs.viewport);
		scissor = std::move(rhs.scissor);

		return *this;
	}

	GraphicsPipelineDerrivationData::GraphicsPipelineDerrivationData() noexcept
	{
		settings = PipelineDerrivationSettings::DO_NOT_DERRIVE;
	}

	GraphicsPipelineDerrivationData::GraphicsPipelineDerrivationData(const GraphicsPipelineDerrivationData& rhs) noexcept
	{
		std::memcpy(this, &rhs, sizeof(GraphicsPipelineDerrivationData));
	}

	GraphicsPipelineDerrivationData::GraphicsPipelineDerrivationData(GraphicsPipelineDerrivationData&& rhs) noexcept
	{
		std::memcpy(this, &rhs, sizeof(GraphicsPipelineDerrivationData));
		rhs.settings = PipelineDerrivationSettings::DO_NOT_DERRIVE;
	}

	GraphicsPipelineDerrivationData::~GraphicsPipelineDerrivationData()
	{
	}

	GraphicsPipelineDerrivationData& GraphicsPipelineDerrivationData::operator=(const GraphicsPipelineDerrivationData& rhs) noexcept
	{
		std::memcpy(this, &rhs, sizeof(GraphicsPipelineDerrivationData));

		return *this;
	}

	GraphicsPipelineDerrivationData& GraphicsPipelineDerrivationData::operator=(GraphicsPipelineDerrivationData&& rhs) noexcept
	{
		std::memcpy(this, &rhs, sizeof(GraphicsPipelineDerrivationData));
		rhs.settings = PipelineDerrivationSettings::DO_NOT_DERRIVE;
		return *this;
	}

	GraphicsPipelineCreationData::GraphicsPipelineCreationData() noexcept
	{
		subpassIndex = std::numeric_limits<uint32_t>::max();
		padding = 0;
	}

	GraphicsPipelineCreationData::GraphicsPipelineCreationData(const GraphicsPipelineCreationData& rhs) noexcept : shaderStages(rhs.shaderStages), vertexInputData(rhs.vertexInputData),
		inputAssemblyData(rhs.inputAssemblyData), viewportData(rhs.viewportData), rasterizationData(rhs.rasterizationData), samplingData(rhs.samplingData),
		depthStencilData(rhs.depthStencilData), colorBlendingData(rhs.colorBlendingData), pipelineLayout(rhs.pipelineLayout), renderPass(rhs.renderPass), subpassIndex(rhs.subpassIndex),
		padding(0), pipelineDerrivationData(rhs.pipelineDerrivationData)
	{
	}

	GraphicsPipelineCreationData::GraphicsPipelineCreationData(GraphicsPipelineCreationData&& rhs) noexcept : shaderStages(std::move(rhs.shaderStages)),
		vertexInputData(std::move(rhs.vertexInputData)), inputAssemblyData(std::move(rhs.inputAssemblyData)), viewportData(std::move(rhs.viewportData)),
		rasterizationData(std::move(rhs.rasterizationData)), samplingData(std::move(rhs.samplingData)), depthStencilData(std::move(rhs.depthStencilData)),
		colorBlendingData(std::move(rhs.colorBlendingData)), pipelineLayout(std::move(rhs.pipelineLayout)), renderPass(std::move(rhs.renderPass)), subpassIndex(std::move(rhs.subpassIndex)),
		padding(0), pipelineDerrivationData(std::move(rhs.pipelineDerrivationData))
	{
	}

	GraphicsPipelineCreationData::~GraphicsPipelineCreationData()
	{
	}

	GraphicsPipelineCreationData& GraphicsPipelineCreationData::operator=(const GraphicsPipelineCreationData& rhs) noexcept
	{
		shaderStages = rhs.shaderStages;
		vertexInputData = rhs.vertexInputData;
		inputAssemblyData = rhs.inputAssemblyData;
		viewportData = rhs.viewportData;
		rasterizationData = rhs.rasterizationData;
		samplingData = rhs.samplingData;
		depthStencilData = rhs.depthStencilData;
		colorBlendingData = rhs.colorBlendingData;

		pipelineLayout = rhs.pipelineLayout;
		renderPass = rhs.renderPass;
		subpassIndex = rhs.subpassIndex;
		padding = 0;
		pipelineDerrivationData = rhs.pipelineDerrivationData;

		return *this;
	}

	GraphicsPipelineCreationData& GraphicsPipelineCreationData::operator=(GraphicsPipelineCreationData&& rhs) noexcept
	{
		shaderStages = std::move(rhs.shaderStages);
		vertexInputData = std::move(rhs.vertexInputData);
		inputAssemblyData = std::move(rhs.inputAssemblyData);
		viewportData = std::move(rhs.viewportData);
		rasterizationData = std::move(rhs.rasterizationData);
		samplingData = std::move(rhs.samplingData);
		depthStencilData = std::move(rhs.depthStencilData);
		colorBlendingData = std::move(rhs.colorBlendingData);

		pipelineLayout = std::move(rhs.pipelineLayout);
		renderPass = std::move(rhs.renderPass);
		subpassIndex = std::move(rhs.subpassIndex);
		padding = 0;
		pipelineDerrivationData = std::move(rhs.pipelineDerrivationData);

		return *this;
	}

}