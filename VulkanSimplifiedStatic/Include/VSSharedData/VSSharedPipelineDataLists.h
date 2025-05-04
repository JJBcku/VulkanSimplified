#pragma once

#include "../VSCommon/VSImageSampleFlagsDef.h"
#include "../VSCommon/VSShaderTypeFlagsDef.h"

#include <CustomLists\IDObjectDef.h>

namespace VulkanSimplifiedInternal
{
	class SharedPipelineDataListssInternal;

	struct ShaderSpecializationElement;
	struct SharedShaderPipelineData;

	struct VertexAttributeDescriptionData;
	struct VertexBindingDescriptionData;
	struct VertexInputSharedPipelineData;

	struct PipelineScissorData;
	struct PipelineViewportData;

	struct PipelineInputAssemblyData;
	struct PipelineRasterizationData;
	struct PipelineMultisampleData;
	struct PipelineDepthStencilStateData;
	struct PipelineColorBlendAttachment;

	struct PushConstantData;
}

namespace VulkanSimplified
{
	enum ShaderTypeFlagBit : ShaderTypeFlags;
	enum ImageSampleFlagBits : ImageSampleFlags;

	typedef uint64_t ColorBlendingComponentFlags;

	enum class VertexBindingInputRate : uint64_t;
	enum class PipelinePrimitiveTopology : uint64_t;
	enum class PipelinePolygonMode : uint64_t;
	enum class DepthUsage : uint64_t;
	enum class CompareOperationsType : uint64_t;
	enum class ColorBlendingPreset : uint64_t;

	struct DataFormatSetIndependentID;

	class SharedPipelineDataListss
	{
	public:
		SharedPipelineDataListss(VulkanSimplifiedInternal::SharedPipelineDataListssInternal& ref);
		~SharedPipelineDataListss();

		IDObject<VulkanSimplifiedInternal::ShaderSpecializationElement> AddShaderSpecializationElement(uint32_t constantID, uint32_t dataOffset, size_t dataSize,
			size_t addOnReserving = 0);
		IDObject<VulkanSimplifiedInternal::SharedShaderPipelineData> AddSharedShaderPipelineData(std::string entryPointName, ShaderTypeFlagBit shaderType,
			size_t addOnReserving = 0);

		IDObject<VulkanSimplifiedInternal::VertexAttributeDescriptionData> AddVertexAttributeDescriptionData(uint32_t offset, DataFormatSetIndependentID format,
			size_t addOnReserving = 0);
		IDObject<VulkanSimplifiedInternal::VertexBindingDescriptionData> AddVertexBindingData(std::uint32_t stride, VertexBindingInputRate inputRate,
			const std::vector<IDObject<VulkanSimplifiedInternal::VertexAttributeDescriptionData>>& vertexAttributeIDs, size_t addOnReserving = 0);
		IDObject<VulkanSimplifiedInternal::VertexInputSharedPipelineData> AddVertexInputSharedPipelineData(
			const std::vector<IDObject<VulkanSimplifiedInternal::VertexBindingDescriptionData>>& bindings, size_t addOnReserving = 0);

		IDObject<VulkanSimplifiedInternal::PipelineScissorData> AddPipelineScissorData(int32_t offsetX, int32_t offsetY, uint32_t width, uint32_t height, size_t addOnReserving = 0);
		IDObject<VulkanSimplifiedInternal::PipelineViewportData> AddPipelineViewportData(uint32_t startX, uint32_t startY, uint32_t width, uint32_t height,
			float minDepth, float maxDepth, size_t addOnReserving = 0);

		IDObject<VulkanSimplifiedInternal::PipelineInputAssemblyData> AddPipelineInputAssemblyData(PipelinePrimitiveTopology topology, bool primitiveRestartEnable,
			size_t addOnReserving = 0);
		IDObject<VulkanSimplifiedInternal::PipelineRasterizationData> AddPipelineRasterizationData(PipelinePolygonMode polygonMode, bool cullPolygonBacks,
			bool frontClockwise, size_t addOnReserving = 0);
		IDObject<VulkanSimplifiedInternal::PipelineMultisampleData> AddPipelineMultisampleData(ImageSampleFlagBits samplingSetting, std::optional<std::uint32_t> minSampleShading,
			size_t addOnReserving = 0);
		IDObject<VulkanSimplifiedInternal::PipelineDepthStencilStateData> AddPipelineDepthStencilStateData(DepthUsage depthUsage,
			CompareOperationsType compareOp, float minDepth, float maxDepth, size_t addOnReserving = 0);
		IDObject<VulkanSimplifiedInternal::PipelineColorBlendAttachment> AddPipelineColorBlendAttachment(ColorBlendingComponentFlags blendingComponents,
			ColorBlendingPreset blendingPreset, size_t addOnReserving = 0);

		IDObject<VulkanSimplifiedInternal::PushConstantData> AddPushConstantData(ShaderTypeFlagBit shaderType, uint32_t offset, uint32_t size, size_t addOnReserving = 0);

		IDObject<VulkanSimplifiedInternal::ShaderSpecializationElement> AddUniqueShaderSpecializationElement(uint32_t constantID, uint32_t dataOffset, size_t dataSize,
			size_t addOnReserving = 0);
		IDObject<VulkanSimplifiedInternal::SharedShaderPipelineData> AddUniqueSharedShaderPipelineData(std::string entryPointName, ShaderTypeFlagBit shaderType,
			size_t addOnReserving = 0);

		IDObject<VulkanSimplifiedInternal::VertexAttributeDescriptionData> AddUniqueVertexAttributeDescriptionData(uint32_t offset, DataFormatSetIndependentID format,
			size_t addOnReserving = 0);
		IDObject<VulkanSimplifiedInternal::VertexBindingDescriptionData> AddUniqueVertexBindingData(std::uint32_t stride, VertexBindingInputRate inputRate,
			const std::vector<IDObject<VulkanSimplifiedInternal::VertexAttributeDescriptionData>>& vertexAttributeIDs, size_t addOnReserving = 0);
		IDObject<VulkanSimplifiedInternal::VertexInputSharedPipelineData> AddUniqueVertexInputSharedPipelineData(
			const std::vector<IDObject<VulkanSimplifiedInternal::VertexBindingDescriptionData>>& bindings, size_t addOnReserving = 0);

		IDObject<VulkanSimplifiedInternal::PipelineScissorData> AddUniquePipelineScissorData(int32_t offsetX, int32_t offsetY, uint32_t width, uint32_t height,
			size_t addOnReserve = 0);
		IDObject<VulkanSimplifiedInternal::PipelineViewportData> AddUniquePipelineViewportData(uint32_t startX, uint32_t startY, uint32_t width, uint32_t height,
			float minDepth, float maxDepth, size_t addOnReserving = 0);

		IDObject<VulkanSimplifiedInternal::PipelineInputAssemblyData> AddUniquePipelineInputAssemblyData(PipelinePrimitiveTopology topology,
			bool primitiveRestartEnable, size_t addOnReserving);
		IDObject<VulkanSimplifiedInternal::PipelineRasterizationData> AddUniquePipelineRasterizationData(PipelinePolygonMode polygonMode, bool cullPolygonBacks,
			bool frontClockwise, size_t addOnReserving = 0);
		IDObject<VulkanSimplifiedInternal::PipelineMultisampleData> AddUniquePipelineMultisampleData(ImageSampleFlagBits samplingSetting, std::optional<std::uint32_t> minSampleShading,
			size_t addOnReserving = 0);
		IDObject<VulkanSimplifiedInternal::PipelineDepthStencilStateData> AddUniquePipelineDepthStencilStateData(DepthUsage depthUsage,
			CompareOperationsType compareOp, float minDepth, float maxDepth, size_t addOnReserving = 0);
		IDObject<VulkanSimplifiedInternal::PipelineColorBlendAttachment> AddUniquePipelineColorBlendAttachment(ColorBlendingComponentFlags blendingComponents,
			ColorBlendingPreset blendingPreset, size_t addOnReserving = 0);

		IDObject<VulkanSimplifiedInternal::PushConstantData> AddUniquePushConstantData(VulkanSimplified::ShaderTypeFlagBit shaderType, uint32_t offset, uint32_t size,
			size_t addOnReserving = 0);

	private:
		VulkanSimplifiedInternal::SharedPipelineDataListssInternal& _internal;
	};
}