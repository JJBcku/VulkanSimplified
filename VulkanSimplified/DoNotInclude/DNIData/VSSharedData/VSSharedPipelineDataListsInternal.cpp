#include "VSSharedDNIpch.h"
#include "VSSharedPipelineDataListsInternal.h"

#include "../../../Include/VSSharedData/VSSharedPipelineDataListsCapacities.h"
#include "../../../Include/VSSharedData/VSVertexBindingInputRate.h"
#include "../../../Include/VSSharedData/VSPipelinePrimitiveTopology.h"
#include "../../../Include/VSSharedData/VSPipelinePolygonMode.h"
#include "../../../Include/VSSharedData/VSDepthUsage.h"
#include "../../../Include/VSSharedData/VSColorBlendingPreset.h"
#include "../../../Include/VSSharedData/VSColorBlendingComponentFlags.h"

#include "../../../Include/VSCommon/VSShaderTypeFlags.h"
#include "../../../Include/VSCommon/VSDataFormatFlags.h"
#include "../../../Include/VSCommon/VSImageSampleFlags.h"
#include "../../../Include/VSCommon/VSCompareOperationsType.h"

#include "../VSCommon/VSDataFormatFlagsInternal.h"

namespace VulkanSimplified
{
	SharedPipelineDataListsInternal::SharedPipelineDataListsInternal(const SharedPipelineDataListsssCapacities& initialCapacities) :
		_shaderSpecializationElements(initialCapacities.initialSpecializationElementsCapacity), _shaderPipelineData(initialCapacities.initialShaderPipelineInfoCapacity),
		_vertexAttributeData(initialCapacities.initialVertexAttributeInfoCapacity), _vertexBindingData(initialCapacities.initialVertexBindingInfoCapacity),
		_vertexInputData(initialCapacities.initialVertexInputPipelineInfoCapacity), _pipelineScissorData(initialCapacities.initialPipelineScissorDataCapacity),
		_pipelineViewportData(initialCapacities.initialPipelineViewportDataCapacity), _pipelineInputAssemblyData(initialCapacities.initialPipelineInputAssemblyInfoCapacity),
		_pipelineRasterizationData(initialCapacities.initialPipelineRasterizationInfoCapacity), _pipelineMultisampleData(initialCapacities.initialPipelineMultisampleInfoCapacity),
		_pipelineDepthStencilStateData(initialCapacities.initialPipelineDepthStencilInfoCapacity),
		_pipelineColorBlendData(initialCapacities.initialPipelineColorBlendAttachmentInfoCapacity), _pushConstantData(initialCapacities.initialPushConstantDataCapacity)
	{
	}

	SharedPipelineDataListsInternal::~SharedPipelineDataListsInternal()
	{
	}

	IDObject<ShaderSpecializationElement> SharedPipelineDataListsInternal::AddShaderSpecializationElement(uint32_t constantID, uint32_t dataOffset, size_t dataSize,
		size_t addOnReserving)
	{
		ShaderSpecializationElement add;
		add.ID = constantID;
		add.offset = dataOffset;
		add.size = dataSize;

		return _shaderSpecializationElements.AddObject(std::move(add), addOnReserving);
	}

	IDObject<SharedShaderPipelineData> SharedPipelineDataListsInternal::AddSharedShaderPipelineData(std::string& entryPointName, ShaderTypeFlagBit shaderType,
		size_t addOnReserving)
	{
		SharedShaderPipelineData add;

		switch (shaderType)
		{
		case SHADER_TYPE_VERTEX:
			add.shaderStage = VK_SHADER_STAGE_VERTEX_BIT;
			break;
		case SHADER_TYPE_FRAGMENT:
			add.shaderStage = VK_SHADER_STAGE_FRAGMENT_BIT;
			break;
		default:
			throw std::runtime_error("SharedPipelineDataListsInternal::AddSharedShaderPipelineData Error: Program was given an erroneous shader type value!");
		}

		add.entryPointName = std::move(entryPointName);

		return _shaderPipelineData.AddObject(std::move(add), addOnReserving);
	}

	IDObject<VertexAttributeDescriptionData> SharedPipelineDataListsInternal::AddVertexAttributeDescriptionData(uint32_t offset, DataFormatSetIndependentID format,
		size_t addOnReserving)
	{
		VertexAttributeDescriptionData add;
		add.format = TranslateDataFormatToVkFormat(format);
		add.offset = offset;

		return _vertexAttributeData.AddObject(std::move(add), addOnReserving);
	}

	IDObject<VertexBindingDescriptionData> SharedPipelineDataListsInternal::AddVertexBindingData(uint32_t stride, VertexBindingInputRate inputRate,
		const std::vector<IDObject<VertexAttributeDescriptionData>>& vertexAttributeIDs, size_t addOnReserving)
	{
		VertexBindingDescriptionData add;
		add.stride = stride;

		switch (inputRate)
		{
		case VertexBindingInputRate::INSTANCE:
			add.inputRate = VK_VERTEX_INPUT_RATE_INSTANCE;
			break;
		case VertexBindingInputRate::VERTEX:
			add.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
			break;
		default:
			throw std::runtime_error("SharedPipelineDataListsInternal::AddVertexBindingData Error: Program was give an erroneous input rate value!");
		}

		add.vertexAttributes = vertexAttributeIDs;

		return _vertexBindingData.AddObject(std::move(add), addOnReserving);
	}

	IDObject<VertexInputSharedPipelineData> SharedPipelineDataListsInternal::AddVertexInputSharedPipelineData(const std::vector<IDObject<VertexBindingDescriptionData>>& bindings,
		size_t addOnReserving)
	{
		VertexInputSharedPipelineData add;
		add.vertexBindings = bindings;

		return _vertexInputData.AddObject(std::move(add), addOnReserving);
	}

	IDObject<PipelineScissorData> SharedPipelineDataListsInternal::AddPipelineScissorData(int32_t offsetX, int32_t offsetY, uint32_t width, uint32_t height, size_t addOnReserving)
	{
		PipelineScissorData add;
		add.offsetX = offsetX;
		add.offsetY = offsetY;
		add.width = width;
		add.height = height;

		return _pipelineScissorData.AddObject(std::move(add), addOnReserving);
	}

	IDObject<PipelineViewportData> SharedPipelineDataListsInternal::AddPipelineViewportData(uint32_t startX, uint32_t startY, uint32_t width, uint32_t height,
		float minDepth, float maxDepth, size_t addOnReserving)
	{
		PipelineViewportData add;
		add.startX = static_cast<float>(startX);
		add.startY = static_cast<float>(startY);
		add.width = static_cast<float>(width);
		add.height = static_cast<float>(height);
		add.minDepth = minDepth;
		add.maxDepth = maxDepth;

		return _pipelineViewportData.AddObject(std::move(add), addOnReserving);
	}

	IDObject<PipelineInputAssemblyData> SharedPipelineDataListsInternal::AddPipelineInputAssemblyData(PipelinePrimitiveTopology topology, bool primitiveRestartEnable,
		size_t addOnReserving)
	{
		PipelineInputAssemblyData add;

		switch (topology)
		{
		case PipelinePrimitiveTopology::PATCH_LIST:
			add.topology = VK_PRIMITIVE_TOPOLOGY_PATCH_LIST;
			break;
		case PipelinePrimitiveTopology::TRIANGLE_STRIP_WITH_ADJACENCY:
			add.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY;
			break;
		case PipelinePrimitiveTopology::TRIANGLE_LIST_WITH_ADJACENCY:
			add.topology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY;
			break;
		case PipelinePrimitiveTopology::LINE_STRIP_WITH_ADJACENCY:
			add.topology = VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY;
			break;
		case PipelinePrimitiveTopology::LINE_LIST_WITH_ADJACENCY:
			add.topology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY;
			break;
		case PipelinePrimitiveTopology::TRIANGLE_FAN:
			add.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN;
			break;
		case PipelinePrimitiveTopology::TRIANGLE_STRIP:
			add.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
			break;
		case PipelinePrimitiveTopology::TRIANGLE_LIST:
			add.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
			break;
		case PipelinePrimitiveTopology::LINE_STRIP:
			add.topology = VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
			break;
		case PipelinePrimitiveTopology::LINE_LIST:
			add.topology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
			break;
		case PipelinePrimitiveTopology::POINT_LIST:
			add.topology = VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
			break;
		default:
			throw std::runtime_error("SharedPipelineDataListsInternal::AddPipelineInputAssemblyData Error: Program was given an erroneous pipeline primitive topology value!");
		}

		if (primitiveRestartEnable)
			add.primitiveRestartEnable = VK_TRUE;
		else
			add.primitiveRestartEnable = VK_FALSE;

		return _pipelineInputAssemblyData.AddObject(std::move(add), addOnReserving);
	}

	IDObject<PipelineRasterizationData> SharedPipelineDataListsInternal::AddPipelineRasterizationData(PipelinePolygonMode polygonMode, bool cullPolygonBacks,
		bool frontClockwise, size_t addOnReserving)
	{
		PipelineRasterizationData add;

		switch (polygonMode)
		{
		case PipelinePolygonMode::POINT:
			add.polygonMode = VK_POLYGON_MODE_POINT;
			break;
		case PipelinePolygonMode::LINE:
			add.polygonMode = VK_POLYGON_MODE_LINE;
			break;
		case PipelinePolygonMode::FILL:
			add.polygonMode = VK_POLYGON_MODE_FILL;
			break;
		default:
			throw std::runtime_error("SharedPipelineDataListsInternal::AddPipelineRasterizationData Error: Program was given an erroneous pipeline polygon mode value!");
		}

		if (cullPolygonBacks)
			add.cullMode = VK_CULL_MODE_BACK_BIT;
		else
			add.cullMode = VK_CULL_MODE_NONE;

		if (frontClockwise)
			add.frontFace = VK_FRONT_FACE_CLOCKWISE;
		else
			add.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;

		return _pipelineRasterizationData.AddObject(std::move(add), addOnReserving);
	}

	IDObject<PipelineMultisampleData> SharedPipelineDataListsInternal::AddPipelineMultisampleData(ImageSampleFlagBits samplingSetting,
		std::optional<uint32_t> minSampleShading, size_t addOnReserving)
	{
		PipelineMultisampleData add;

		switch (samplingSetting)
		{
		case SAMPLE_64:
			add.sampleCount = VK_SAMPLE_COUNT_64_BIT;
			break;
		case SAMPLE_32:
			add.sampleCount = VK_SAMPLE_COUNT_32_BIT;
			break;
		case SAMPLE_16:
			add.sampleCount = VK_SAMPLE_COUNT_16_BIT;
			break;
		case SAMPLE_8:
			add.sampleCount = VK_SAMPLE_COUNT_8_BIT;
			break;
		case SAMPLE_4:
			add.sampleCount = VK_SAMPLE_COUNT_4_BIT;
			break;
		case SAMPLE_2:
			add.sampleCount = VK_SAMPLE_COUNT_2_BIT;
			break;
		case SAMPLE_1:
			add.sampleCount = VK_SAMPLE_COUNT_1_BIT;
			break;
		default:
			throw std::runtime_error("SharedPipelineDataListsInternal::AddPipelineMultisampleData Error: Program was given an erroneous pipeline sampling value!");
		}

		if (minSampleShading.has_value())
		{
			add.sampleShadingEnable = VK_TRUE;
			add.minSampleShading = static_cast<float>(minSampleShading.value()) / static_cast<float>(std::numeric_limits<uint32_t>::max());
		}
		else
		{
			add.sampleShadingEnable = VK_FALSE;
			add.minSampleShading = 0.0f;
		}

		return _pipelineMultisampleData.AddObject(std::move(add), addOnReserving);
	}

	IDObject<PipelineDepthStencilStateData> SharedPipelineDataListsInternal::AddPipelineDepthStencilStateData(DepthUsage depthUsage,
		CompareOperationsType compareOp, float minDepth, float maxDepth, size_t addOnReserving)
	{
		PipelineDepthStencilStateData add;

		switch (depthUsage)
		{
		case DepthUsage::TEST_AND_WRITE:
			add.depthTestEnable = VK_TRUE;
			add.depthWriteEnable = VK_TRUE;
			break;
		case DepthUsage::WRITE:
			add.depthTestEnable = VK_FALSE;
			add.depthWriteEnable = VK_TRUE;
			break;
		case DepthUsage::TEST:
			add.depthTestEnable = VK_TRUE;
			add.depthWriteEnable = VK_FALSE;
			break;
		default:
			throw std::runtime_error("SharedPipelineDataListsInternal::AddPipelineDepthStencilStateData Error: Program was given an erroneous pipeline depth usage value!");
		}

		switch (compareOp)
		{
		case CompareOperationsType::COMPARE_OPERATION_NOT_EQUAL:
			add.compareOp = VK_COMPARE_OP_NOT_EQUAL;
			break;
		case CompareOperationsType::COMPARE_OPERATION_GREATER_OR_EQUAL:
			add.compareOp = VK_COMPARE_OP_GREATER_OR_EQUAL;
			break;
		case CompareOperationsType::COMPARE_OPERATION_GREATER:
			add.compareOp = VK_COMPARE_OP_GREATER;
			break;
		case CompareOperationsType::COMPARE_OPERATION_LESS_OR_EQUAL:
			add.compareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
			break;
		case CompareOperationsType::COMPARE_OPERATION_LESS:
			add.compareOp = VK_COMPARE_OP_LESS;
			break;
		case CompareOperationsType::COMPARE_OPERATION_EQUAL:
			add.compareOp = VK_COMPARE_OP_EQUAL;
			break;
		case CompareOperationsType::COMPARE_OPERATION_ALWAYS:
			add.compareOp = VK_COMPARE_OP_ALWAYS;
			break;
		case CompareOperationsType::COMPARE_OPERATION_NEVER:
			add.compareOp = VK_COMPARE_OP_NEVER;
			break;
		default:
			throw std::runtime_error("SharedPipelineDataListsInternal::AddPipelineDepthStencilStateData Error: Program was given an erroneous compare operation value!");
		}

		add.minDepth = minDepth;
		add.maxDepth = maxDepth;

		return _pipelineDepthStencilStateData.AddObject(std::move(add), addOnReserving);
	}

	IDObject<PipelineColorBlendAttachment> SharedPipelineDataListsInternal::AddPipelineColorBlendAttachment(ColorBlendingComponentFlags blendingComponents,
		ColorBlendingPreset blendingPreset, size_t addOnReserving)
	{
		PipelineColorBlendAttachment add;

		switch (blendingPreset)
		{
		case ColorBlendingPreset::NO_BLENDING:
			add.blendEnable = VK_FALSE;
			add.srcColorBlend = VK_BLEND_FACTOR_ONE;
			add.dstColorBlend = VK_BLEND_FACTOR_ZERO;
			add.colorBlendOp = VK_BLEND_OP_ADD;
			add.srcAlphaBlend = VK_BLEND_FACTOR_ONE;
			add.dstAlphaBlend = VK_BLEND_FACTOR_ZERO;
			add.alphaBlendOp = VK_BLEND_OP_ADD;
			break;
		case ColorBlendingPreset::ALPHA_BLENDING:
			add.blendEnable = VK_TRUE;
			add.srcColorBlend = VK_BLEND_FACTOR_SRC_ALPHA;
			add.dstColorBlend = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
			add.colorBlendOp = VK_BLEND_OP_ADD;
			add.srcAlphaBlend = VK_BLEND_FACTOR_ONE;
			add.dstAlphaBlend = VK_BLEND_FACTOR_ZERO;
			add.alphaBlendOp = VK_BLEND_OP_ADD;
			break;
		case ColorBlendingPreset::ADDITIVE_BLENDING:
			add.blendEnable = VK_TRUE;
			add.srcColorBlend = VK_BLEND_FACTOR_SRC_ALPHA;
			add.dstColorBlend = VK_BLEND_FACTOR_ONE;
			add.colorBlendOp = VK_BLEND_OP_ADD;
			add.srcAlphaBlend = VK_BLEND_FACTOR_ONE;
			add.dstAlphaBlend = VK_BLEND_FACTOR_ZERO;
			add.alphaBlendOp = VK_BLEND_OP_ADD;
			break;
		default:
			throw std::runtime_error("SharedPipelineDataListsInternal::AddPipelineColorBlendAttachment Error: Program was given an erroneous blending preset value!");
		}

		add.colorWriteMask = 0;

		if ((blendingComponents & COLOR_COMPONENT_R) == COLOR_COMPONENT_R)
		{
			add.colorWriteMask |= VK_COLOR_COMPONENT_R_BIT;
			blendingComponents ^= COLOR_COMPONENT_R;
		}

		if ((blendingComponents & COLOR_COMPONENT_G) == COLOR_COMPONENT_G)
		{
			add.colorWriteMask |= VK_COLOR_COMPONENT_G_BIT;
			blendingComponents ^= COLOR_COMPONENT_G;
		}

		if ((blendingComponents & COLOR_COMPONENT_B) == COLOR_COMPONENT_B)
		{
			add.colorWriteMask |= VK_COLOR_COMPONENT_B_BIT;
			blendingComponents ^= COLOR_COMPONENT_B;
		}

		if ((blendingComponents & COLOR_COMPONENT_A) == COLOR_COMPONENT_A)
		{
			add.colorWriteMask |= VK_COLOR_COMPONENT_A_BIT;
			blendingComponents ^= COLOR_COMPONENT_A;
		}

		if (blendingComponents != 0)
			throw std::runtime_error("SharedPipelineDataListsInternal::AddPipelineColorBlendAttachment Error: Program was given an erroneous blending components value!");

		return _pipelineColorBlendData.AddObject(std::move(add), addOnReserving);
	}

	IDObject<PushConstantData> SharedPipelineDataListsInternal::AddPushConstantData(ShaderTypeFlagBit shaderType, uint32_t offset, uint32_t size, size_t addOnReserving)
	{
		PushConstantData add;

		switch (shaderType)
		{
		case SHADER_TYPE_VERTEX:
			add.shaderStages = VK_SHADER_STAGE_VERTEX_BIT;
			break;
		case SHADER_TYPE_FRAGMENT:
			add.shaderStages = VK_SHADER_STAGE_FRAGMENT_BIT;
			break;
		default:
			throw std::runtime_error("SharedPipelineDataListsInternal::AddPushConstantData Error: Program was given an erroneous shader type value!");
		}

		add.offset = offset;
		add.size = size;

		return _pushConstantData.AddObject(std::move(add), addOnReserving);
	}

	IDObject<ShaderSpecializationElement> SharedPipelineDataListsInternal::AddUniqueShaderSpecializationElement(uint32_t constantID, uint32_t dataOffset, size_t dataSize,
		size_t addOnReserving)
	{
		ShaderSpecializationElement add;
		add.ID = constantID;
		add.offset = dataOffset;
		add.size = dataSize;

		return _shaderSpecializationElements.AddUniqueObject(std::move(add), addOnReserving);
	}

	IDObject<SharedShaderPipelineData> SharedPipelineDataListsInternal::AddUniqueSharedShaderPipelineData(std::string& entryPointName, ShaderTypeFlagBit shaderType,
		size_t addOnReserving)
	{
		SharedShaderPipelineData add;

		switch (shaderType)
		{
		case SHADER_TYPE_VERTEX:
			add.shaderStage = VK_SHADER_STAGE_VERTEX_BIT;
			break;
		case SHADER_TYPE_FRAGMENT:
			add.shaderStage = VK_SHADER_STAGE_FRAGMENT_BIT;
			break;
		default:
			throw std::runtime_error("SharedPipelineDataListsInternal::AddUniqueSharedShaderPipelineData Error: Program was given an erroneous shader type value!");
		}

		add.entryPointName = std::move(entryPointName);

		return _shaderPipelineData.AddUniqueObject(std::move(add), addOnReserving);
	}

	IDObject<VertexAttributeDescriptionData> SharedPipelineDataListsInternal::AddUniqueVertexAttributeDescriptionData(uint32_t offset,
		DataFormatSetIndependentID format, size_t addOnReserving)
	{
		VertexAttributeDescriptionData add;
		add.format = TranslateDataFormatToVkFormat(format);
		add.offset = offset;

		return _vertexAttributeData.AddUniqueObject(std::move(add), addOnReserving);
	}

	IDObject<VertexBindingDescriptionData> SharedPipelineDataListsInternal::AddUniqueVertexBindingData(uint32_t stride, VertexBindingInputRate inputRate,
		const std::vector<IDObject<VertexAttributeDescriptionData>>& vertexAttributeIDs, size_t addOnReserving)
	{
		VertexBindingDescriptionData add;
		add.stride = stride;

		switch (inputRate)
		{
		case VertexBindingInputRate::INSTANCE:
			add.inputRate = VK_VERTEX_INPUT_RATE_INSTANCE;
			break;
		case VertexBindingInputRate::VERTEX:
			add.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
			break;
		default:
			throw std::runtime_error("SharedPipelineDataListsInternal::AddUniqueVertexBindingData Error: Program was give an erroneous input rate value!");
		}

		add.vertexAttributes = vertexAttributeIDs;

		return _vertexBindingData.AddUniqueObject(std::move(add), addOnReserving);
	}

	IDObject<VertexInputSharedPipelineData> SharedPipelineDataListsInternal::AddUniqueVertexInputSharedPipelineData(const std::vector<IDObject<VertexBindingDescriptionData>>& bindings,
		size_t addOnReserving)
	{
		VertexInputSharedPipelineData add;
		add.vertexBindings = bindings;

		return _vertexInputData.AddUniqueObject(std::move(add), addOnReserving);
	}

	IDObject<PipelineScissorData> SharedPipelineDataListsInternal::AddUniquePipelineScissorData(int32_t offsetX, int32_t offsetY, uint32_t width, uint32_t height, size_t addOnReserving)
	{
		PipelineScissorData add;
		add.offsetX = offsetX;
		add.offsetY = offsetY;
		add.width = width;
		add.height = height;

		return _pipelineScissorData.AddUniqueObject(std::move(add), addOnReserving);
	}

	IDObject<PipelineViewportData> SharedPipelineDataListsInternal::AddUniquePipelineViewportData(uint32_t startX, uint32_t startY, uint32_t width, uint32_t height,
		float minDepth, float maxDepth, size_t addOnReserving)
	{
		PipelineViewportData add;
		add.startX = static_cast<float>(startX);
		add.startY = static_cast<float>(startY);
		add.width = static_cast<float>(width);
		add.height = static_cast<float>(height);
		add.minDepth = minDepth;
		add.maxDepth = maxDepth;

		return _pipelineViewportData.AddUniqueObject(std::move(add), addOnReserving);
	}

	IDObject<PipelineInputAssemblyData> SharedPipelineDataListsInternal::AddUniquePipelineInputAssemblyData(PipelinePrimitiveTopology topology,
		bool primitiveRestartEnable, size_t addOnReserving)
	{
		PipelineInputAssemblyData add;

		switch (topology)
		{
		case PipelinePrimitiveTopology::PATCH_LIST:
			add.topology = VK_PRIMITIVE_TOPOLOGY_PATCH_LIST;
			break;
		case PipelinePrimitiveTopology::TRIANGLE_STRIP_WITH_ADJACENCY:
			add.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY;
			break;
		case PipelinePrimitiveTopology::TRIANGLE_LIST_WITH_ADJACENCY:
			add.topology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY;
			break;
		case PipelinePrimitiveTopology::LINE_STRIP_WITH_ADJACENCY:
			add.topology = VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY;
			break;
		case PipelinePrimitiveTopology::LINE_LIST_WITH_ADJACENCY:
			add.topology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY;
			break;
		case PipelinePrimitiveTopology::TRIANGLE_FAN:
			add.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN;
			break;
		case PipelinePrimitiveTopology::TRIANGLE_STRIP:
			add.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
			break;
		case PipelinePrimitiveTopology::TRIANGLE_LIST:
			add.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
			break;
		case PipelinePrimitiveTopology::LINE_STRIP:
			add.topology = VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
			break;
		case PipelinePrimitiveTopology::LINE_LIST:
			add.topology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
			break;
		case PipelinePrimitiveTopology::POINT_LIST:
			add.topology = VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
			break;
		default:
			throw std::runtime_error("SharedPipelineDataListsInternal::AddUniquePipelineInputAssemblyData Error: Program was given an erroneous pipeline primitive topology value!");
		}

		if (primitiveRestartEnable)
			add.primitiveRestartEnable = VK_TRUE;
		else
			add.primitiveRestartEnable = VK_FALSE;

		return _pipelineInputAssemblyData.AddUniqueObject(std::move(add), addOnReserving);
	}

	IDObject<PipelineRasterizationData> SharedPipelineDataListsInternal::AddUniquePipelineRasterizationData(PipelinePolygonMode polygonMode, bool cullPolygonBacks,
		bool frontClockwise, size_t addOnReserving)
	{
		PipelineRasterizationData add;

		switch (polygonMode)
		{
		case PipelinePolygonMode::POINT:
			add.polygonMode = VK_POLYGON_MODE_POINT;
			break;
		case PipelinePolygonMode::LINE:
			add.polygonMode = VK_POLYGON_MODE_LINE;
			break;
		case PipelinePolygonMode::FILL:
			add.polygonMode = VK_POLYGON_MODE_FILL;
			break;
		default:
			throw std::runtime_error("SharedPipelineDataListsInternal::AddUniquePipelineRasterizationData Error: Program was given an erroneous pipeline polygon mode value!");
		}

		if (cullPolygonBacks)
			add.cullMode = VK_CULL_MODE_BACK_BIT;
		else
			add.cullMode = VK_CULL_MODE_NONE;

		if (frontClockwise)
			add.frontFace = VK_FRONT_FACE_CLOCKWISE;
		else
			add.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;

		return _pipelineRasterizationData.AddObject(std::move(add), addOnReserving);
	}

	IDObject<PipelineMultisampleData> SharedPipelineDataListsInternal::AddUniquePipelineMultisampleData(ImageSampleFlagBits samplingSetting,
		std::optional<uint32_t> minSampleShading, size_t addOnReserving)
	{
		PipelineMultisampleData add;

		switch (samplingSetting)
		{
		case SAMPLE_64:
			add.sampleCount = VK_SAMPLE_COUNT_64_BIT;
			break;
		case SAMPLE_32:
			add.sampleCount = VK_SAMPLE_COUNT_32_BIT;
			break;
		case SAMPLE_16:
			add.sampleCount = VK_SAMPLE_COUNT_16_BIT;
			break;
		case SAMPLE_8:
			add.sampleCount = VK_SAMPLE_COUNT_8_BIT;
			break;
		case SAMPLE_4:
			add.sampleCount = VK_SAMPLE_COUNT_4_BIT;
			break;
		case SAMPLE_2:
			add.sampleCount = VK_SAMPLE_COUNT_2_BIT;
			break;
		case SAMPLE_1:
			add.sampleCount = VK_SAMPLE_COUNT_1_BIT;
			break;
		default:
			throw std::runtime_error("SharedPipelineDataListsInternal::AddUniquePipelineMultisampleData Error: Program was given an erroneous pipeline sampling value!");
		}

		if (minSampleShading.has_value())
		{
			add.sampleShadingEnable = VK_TRUE;
			add.minSampleShading = static_cast<float>(minSampleShading.value()) / static_cast<float>(std::numeric_limits<uint32_t>::max());
		}
		else
		{
			add.sampleShadingEnable = VK_FALSE;
			add.minSampleShading = 0;
		}

		return _pipelineMultisampleData.AddUniqueObject(std::move(add), addOnReserving);
	}

	IDObject<PipelineDepthStencilStateData> SharedPipelineDataListsInternal::AddUniquePipelineDepthStencilStateData(DepthUsage depthUsage, CompareOperationsType compareOp, float minDepth, float maxDepth, size_t addOnReserving)
	{
		PipelineDepthStencilStateData add;

		switch (depthUsage)
		{
		case DepthUsage::TEST_AND_WRITE:
			add.depthTestEnable = VK_TRUE;
			add.depthWriteEnable = VK_TRUE;
			break;
		case DepthUsage::WRITE:
			add.depthTestEnable = VK_FALSE;
			add.depthWriteEnable = VK_TRUE;
			break;
		case DepthUsage::TEST:
			add.depthTestEnable = VK_TRUE;
			add.depthWriteEnable = VK_FALSE;
			break;
		default:
			throw std::runtime_error("SharedPipelineDataListsInternal::AddUniquePipelineDepthStencilStateData Error: Program was given an erroneous pipeline depth usage value!");
		}

		switch (compareOp)
		{
		case CompareOperationsType::COMPARE_OPERATION_NOT_EQUAL:
			add.compareOp = VK_COMPARE_OP_NOT_EQUAL;
			break;
		case CompareOperationsType::COMPARE_OPERATION_GREATER_OR_EQUAL:
			add.compareOp = VK_COMPARE_OP_GREATER_OR_EQUAL;
			break;
		case CompareOperationsType::COMPARE_OPERATION_GREATER:
			add.compareOp = VK_COMPARE_OP_GREATER;
			break;
		case CompareOperationsType::COMPARE_OPERATION_LESS_OR_EQUAL:
			add.compareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
			break;
		case CompareOperationsType::COMPARE_OPERATION_LESS:
			add.compareOp = VK_COMPARE_OP_LESS;
			break;
		case CompareOperationsType::COMPARE_OPERATION_EQUAL:
			add.compareOp = VK_COMPARE_OP_EQUAL;
			break;
		case CompareOperationsType::COMPARE_OPERATION_ALWAYS:
			add.compareOp = VK_COMPARE_OP_ALWAYS;
			break;
		case CompareOperationsType::COMPARE_OPERATION_NEVER:
			add.compareOp = VK_COMPARE_OP_NEVER;
			break;
		default:
			throw std::runtime_error("SharedPipelineDataListsInternal::AddUniquePipelineDepthStencilStateData Error: Program was given an erroneous compare operation value!");
		}

		add.minDepth = minDepth;
		add.maxDepth = maxDepth;

		return _pipelineDepthStencilStateData.AddUniqueObject(std::move(add), addOnReserving);
	}

	IDObject<PipelineColorBlendAttachment> SharedPipelineDataListsInternal::AddUniquePipelineColorBlendAttachment(ColorBlendingComponentFlags blendingComponents,
		ColorBlendingPreset blendingPreset, size_t addOnReserving)
	{
		PipelineColorBlendAttachment add;

		switch (blendingPreset)
		{
		case ColorBlendingPreset::NO_BLENDING:
			add.blendEnable = VK_FALSE;
			add.srcColorBlend = VK_BLEND_FACTOR_ONE;
			add.dstColorBlend = VK_BLEND_FACTOR_ZERO;
			add.colorBlendOp = VK_BLEND_OP_ADD;
			add.srcAlphaBlend = VK_BLEND_FACTOR_ONE;
			add.dstAlphaBlend = VK_BLEND_FACTOR_ZERO;
			add.alphaBlendOp = VK_BLEND_OP_ADD;
			break;
		case ColorBlendingPreset::ALPHA_BLENDING:
			add.blendEnable = VK_TRUE;
			add.srcColorBlend = VK_BLEND_FACTOR_SRC_ALPHA;
			add.dstColorBlend = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
			add.colorBlendOp = VK_BLEND_OP_ADD;
			add.srcAlphaBlend = VK_BLEND_FACTOR_ONE;
			add.dstAlphaBlend = VK_BLEND_FACTOR_ZERO;
			add.alphaBlendOp = VK_BLEND_OP_ADD;
			break;
		case ColorBlendingPreset::ADDITIVE_BLENDING:
			add.blendEnable = VK_TRUE;
			add.srcColorBlend = VK_BLEND_FACTOR_SRC_ALPHA;
			add.dstColorBlend = VK_BLEND_FACTOR_ONE;
			add.colorBlendOp = VK_BLEND_OP_ADD;
			add.srcAlphaBlend = VK_BLEND_FACTOR_ONE;
			add.dstAlphaBlend = VK_BLEND_FACTOR_ZERO;
			add.alphaBlendOp = VK_BLEND_OP_ADD;
			break;
		default:
			throw std::runtime_error("SharedPipelineDataListsInternal::AddUniquePipelineColorBlendAttachment Error: Program was given an erroneous blending preset value!");
		}

		add.colorWriteMask = 0;

		if ((blendingComponents & COLOR_COMPONENT_R) == COLOR_COMPONENT_R)
		{
			add.colorWriteMask |= VK_COLOR_COMPONENT_R_BIT;
			blendingComponents ^= COLOR_COMPONENT_R;
		}

		if ((blendingComponents & COLOR_COMPONENT_G) == COLOR_COMPONENT_G)
		{
			add.colorWriteMask |= VK_COLOR_COMPONENT_G_BIT;
			blendingComponents ^= COLOR_COMPONENT_G;
		}

		if ((blendingComponents & COLOR_COMPONENT_B) == COLOR_COMPONENT_B)
		{
			add.colorWriteMask |= VK_COLOR_COMPONENT_B_BIT;
			blendingComponents ^= COLOR_COMPONENT_B;
		}

		if ((blendingComponents & COLOR_COMPONENT_A) == COLOR_COMPONENT_A)
		{
			add.colorWriteMask |= VK_COLOR_COMPONENT_A_BIT;
			blendingComponents ^= COLOR_COMPONENT_A;
		}

		if (blendingComponents != 0)
			throw std::runtime_error("SharedPipelineDataListsInternal::AddUniquePipelineColorBlendAttachment Error: Program was given an erroneous blending components value!");

		return _pipelineColorBlendData.AddUniqueObject(std::move(add), addOnReserving);
	}

	IDObject<PushConstantData> SharedPipelineDataListsInternal::AddUniquePushConstantData(ShaderTypeFlagBit shaderType, uint32_t offset, uint32_t size, size_t addOnReserving)
	{
		PushConstantData add;

		switch (shaderType)
		{
		case SHADER_TYPE_VERTEX:
			add.shaderStages = VK_SHADER_STAGE_VERTEX_BIT;
			break;
		case SHADER_TYPE_FRAGMENT:
			add.shaderStages = VK_SHADER_STAGE_FRAGMENT_BIT;
			break;
		default:
			throw std::runtime_error("SharedPipelineDataListsInternal::AddUniquePushConstantData Error: Program was given an erroneous shader type value!");
		}

		add.offset = offset;
		add.size = size;

		return _pushConstantData.AddUniqueObject(std::move(add), addOnReserving);
	}

	std::vector<VkSpecializationMapEntry> SharedPipelineDataListsInternal::GetShaderSpecializationData(const std::vector<IDObject<ShaderSpecializationElement>>& specializationIDs) const
	{
		std::vector<VkSpecializationMapEntry> ret;
		ret.reserve(specializationIDs.size());

		auto dataList = _shaderSpecializationElements.GetObjectList(specializationIDs);

		for (auto& data : dataList)
		{
			VkSpecializationMapEntry add{};

			add.constantID = data.ID;
			add.offset = data.offset;
			add.size = data.size;

			ret.push_back(add);
		}

		return ret;
	}

	SharedShaderPipelineData SharedPipelineDataListsInternal::GetSharedShaderPipelineData(const IDObject<SharedShaderPipelineData>& shaderID) const
	{
		return _shaderPipelineData.GetObjectCopy(shaderID);
	}

	std::vector<VertexAttributeDescriptionData> SharedPipelineDataListsInternal::GetVertexAttributeDescriptionData(const std::vector<IDObject<VertexAttributeDescriptionData>>& attributeIDs) const
	{
		return _vertexAttributeData.GetObjectList(attributeIDs);
	}

	std::vector<VertexBindingDescriptionData> SharedPipelineDataListsInternal::GetVertexBindingDescriptionData(const std::vector<IDObject<VertexBindingDescriptionData>>& bindingIDs) const
	{
		return _vertexBindingData.GetObjectList(bindingIDs);
	}

	VertexInputSharedPipelineData SharedPipelineDataListsInternal::GetVertexInputSharedPipelineData(IDObject<VertexInputSharedPipelineData> vertexDataIDs) const
	{
		return _vertexInputData.GetConstObject(vertexDataIDs);
	}

	VkViewport SharedPipelineDataListsInternal::GetViewports(const IDObject<PipelineViewportData>& viewportID) const
	{
		VkViewport ret{};

		auto& data = _pipelineViewportData.GetConstObject(viewportID);

		ret.x = data.startX;
		ret.y = data.startY;
		ret.width = data.width;
		ret.height = data.height;
		ret.minDepth = data.minDepth;
		ret.maxDepth = data.maxDepth;

		return ret;
	}

	VkRect2D SharedPipelineDataListsInternal::GetScissors(const IDObject<PipelineScissorData>& scissorID) const
	{
		VkRect2D ret{};

		auto& data = _pipelineScissorData.GetConstObject(scissorID);

		ret.extent.width = data.width;
		ret.extent.height = data.height;
		ret.offset.x = data.offsetX;
		ret.offset.y = data.offsetY;

		return ret;
	}

	VkPipelineInputAssemblyStateCreateInfo SharedPipelineDataListsInternal::GetInputAssembly(IDObject<PipelineInputAssemblyData> assemblyID) const
	{
		VkPipelineInputAssemblyStateCreateInfo ret{};

		ret.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;

		auto& data = _pipelineInputAssemblyData.GetConstObject(assemblyID);

		ret.topology = data.topology;
		ret.primitiveRestartEnable = data.primitiveRestartEnable;

		return ret;
	}

	VkPipelineRasterizationStateCreateInfo SharedPipelineDataListsInternal::GetRasterizationState(IDObject<PipelineRasterizationData> rasterizationID) const
	{
		VkPipelineRasterizationStateCreateInfo ret{};
		ret.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		ret.depthClampEnable = VK_FALSE;
		ret.rasterizerDiscardEnable = VK_FALSE;
		ret.lineWidth = 1.0f;

		auto& data = _pipelineRasterizationData.GetConstObject(rasterizationID);

		ret.polygonMode = data.polygonMode;
		ret.cullMode = data.cullMode;
		ret.frontFace = data.frontFace;
		ret.depthBiasEnable = VK_FALSE;

		return ret;
	}

	VkPipelineMultisampleStateCreateInfo SharedPipelineDataListsInternal::GetMultisamplingState(IDObject<PipelineMultisampleData> multisamplingID) const
	{
		VkPipelineMultisampleStateCreateInfo ret{};
		ret.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;

		auto& data = _pipelineMultisampleData.GetConstObject(multisamplingID);

		ret.rasterizationSamples = data.sampleCount;
		ret.sampleShadingEnable = data.sampleShadingEnable;
		ret.minSampleShading = data.minSampleShading;

		return ret;
	}

	VkPipelineDepthStencilStateCreateInfo SharedPipelineDataListsInternal::GetDepthStencilState(IDObject<PipelineDepthStencilStateData> depthStencilID) const
	{
		VkPipelineDepthStencilStateCreateInfo ret{};
		ret.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;

		auto& data = _pipelineDepthStencilStateData.GetConstObject(depthStencilID);

		ret.depthTestEnable = data.depthTestEnable;
		ret.depthWriteEnable = data.depthWriteEnable;
		ret.depthCompareOp = data.compareOp;
		ret.depthBoundsTestEnable = VK_FALSE;
		ret.stencilTestEnable = VK_FALSE;
		ret.minDepthBounds = data.minDepth;
		ret.maxDepthBounds = data.maxDepth;

		return ret;
	}

	std::vector<VkPipelineColorBlendAttachmentState> SharedPipelineDataListsInternal::GetColorBlendAttachments(const std::vector<IDObject<PipelineColorBlendAttachment>>& attachmentIDs) const
	{
		std::vector<VkPipelineColorBlendAttachmentState> ret;
		ret.reserve(attachmentIDs.size());

		auto dataList = _pipelineColorBlendData.GetObjectList(attachmentIDs);

		for (auto& data : dataList)
		{
			VkPipelineColorBlendAttachmentState add{};
			add.blendEnable = data.blendEnable;
			add.srcColorBlendFactor = data.srcColorBlend;
			add.dstColorBlendFactor = data.dstColorBlend;
			add.colorBlendOp = data.colorBlendOp;
			add.srcAlphaBlendFactor = data.srcAlphaBlend;
			add.dstAlphaBlendFactor = data.dstAlphaBlend;
			add.alphaBlendOp = data.alphaBlendOp;
			add.colorWriteMask = data.colorWriteMask;

			ret.push_back(add);
		}

		return ret;
	}

	std::vector<VkPushConstantRange> SharedPipelineDataListsInternal::GetPushConstantData(std::vector<IDObject<PushConstantData>> pushConstantIDs) const
	{
		std::vector<VkPushConstantRange> ret;

		auto pushDataList = _pushConstantData.GetObjectList(pushConstantIDs);

		ret.reserve(pushDataList.size());

		for (auto& pushData : pushDataList)
		{
			VkPushConstantRange add{};
			add.stageFlags = pushData.shaderStages;
			add.offset = pushData.offset;
			add.size = pushData.size;

			ret.push_back(add);
		}

		return ret;
	}

}