#pragma once

#include <CustomLists/UnsortedIDVector.h>

#include "VSSharedPipelineDataAllElementsInternal.h"

#include "../../Include/VSCommon/VSImageSampleFlagsDef.h"
#include "../../Include/VSCommon/VSShaderTypeFlagsDef.h"

namespace VulkanSimplified
{
	struct SharedPipelineDataListsssCapacities;
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
}

namespace VulkanSimplifiedInternal
{
	class SharedPipelineDataListInternal
	{
	public:
		SharedPipelineDataListInternal(const VulkanSimplified::SharedPipelineDataListsssCapacities& initialCapacities);
		~SharedPipelineDataListInternal();

		IDObject<ShaderSpecializationElement> AddShaderSpecializationElement(uint32_t constantID, uint32_t dataOffset, size_t dataSize, size_t addOnReserving);
		IDObject<SharedShaderPipelineData> AddSharedShaderPipelineData(std::string& entryPointName, VulkanSimplified::ShaderTypeFlagBit shaderType, size_t addOnReserving);

		IDObject<VertexAttributeDescriptionData> AddVertexAttributeDescriptionData(uint32_t offset, VulkanSimplified::DataFormatSetIndependentID format, size_t addOnReserving);
		IDObject<VertexBindingDescriptionData> AddVertexBindingData(uint32_t stride, VulkanSimplified::VertexBindingInputRate inputRate,
			const std::vector<IDObject<VertexAttributeDescriptionData>>& vertexAttributeIDs, size_t addOnReserving);
		IDObject<VertexInputSharedPipelineData> AddVertexInputSharedPipelineData(const std::vector<IDObject<VertexBindingDescriptionData>>& bindings, size_t addOnReserving);

		IDObject<PipelineScissorData> AddPipelineScissorData(int32_t offsetX, int32_t offsetY, uint32_t width, uint32_t height, size_t addOnReserving);
		IDObject<PipelineViewportData> AddPipelineViewportData(uint32_t startX, uint32_t startY, uint32_t width, uint32_t height, float minDepth, float maxDepth,
			size_t addOnReserving);

		IDObject<PipelineInputAssemblyData> AddPipelineInputAssemblyData(VulkanSimplified::PipelinePrimitiveTopology topology, bool primitiveRestartEnable, size_t addOnReserving);
		IDObject<PipelineRasterizationData> AddPipelineRasterizationData(VulkanSimplified::PipelinePolygonMode polygonMode, bool cullPolygonBacks, bool frontClockwise,
			size_t addOnReserving);
		IDObject<PipelineMultisampleData> AddPipelineMultisampleData(VulkanSimplified::ImageSampleFlagBits samplingSetting,
			std::optional<uint32_t> minSampleShading, size_t addOnReserving);
		IDObject<PipelineDepthStencilStateData> AddPipelineDepthStencilStateData(VulkanSimplified::DepthUsage depthUsage, VulkanSimplified::CompareOperationsType compareOp,
			float minDepth, float maxDepth, size_t addOnReserving);
		IDObject<PipelineColorBlendAttachment> AddPipelineColorBlendAttachment(VulkanSimplified::ColorBlendingComponentFlags blendingComponents,
			VulkanSimplified::ColorBlendingPreset blendingPreset, size_t addOnReserving);

		IDObject<PushConstantData> AddPushConstantData(VulkanSimplified::ShaderTypeFlagBit shaderType, uint32_t offset, uint32_t size, size_t addOnReserving);

		IDObject<ShaderSpecializationElement> AddUniqueShaderSpecializationElement(uint32_t constantID, uint32_t dataOffset, size_t dataSize, size_t addOnReserving);
		IDObject<SharedShaderPipelineData> AddUniqueSharedShaderPipelineData(std::string& entryPointName, VulkanSimplified::ShaderTypeFlagBit shaderType, size_t addOnReserving);

		IDObject<VertexAttributeDescriptionData> AddUniqueVertexAttributeDescriptionData(uint32_t offset, VulkanSimplified::DataFormatSetIndependentID format, size_t addOnReserving);
		IDObject<VertexBindingDescriptionData> AddUniqueVertexBindingData(uint32_t stride, VulkanSimplified::VertexBindingInputRate inputRate,
			const std::vector<IDObject<VertexAttributeDescriptionData>>& vertexAttributeIDs, size_t addOnReserving);
		IDObject<VertexInputSharedPipelineData> AddUniqueVertexInputSharedPipelineData(const std::vector<IDObject<VertexBindingDescriptionData>>& bindings, size_t addOnReserving);

		IDObject<PipelineScissorData> AddUniquePipelineScissorData(int32_t offsetX, int32_t offsetY, uint32_t width, uint32_t height, size_t addOnReserving);
		IDObject<PipelineViewportData> AddUniquePipelineViewportData(uint32_t startX, uint32_t startY, uint32_t width, uint32_t height, float minDepth, float maxDepth,
			size_t addOnReserving);

		IDObject<PipelineInputAssemblyData> AddUniquePipelineInputAssemblyData(VulkanSimplified::PipelinePrimitiveTopology topology, bool primitiveRestartEnable, size_t addOnReserving);
		IDObject<PipelineRasterizationData> AddUniquePipelineRasterizationData(VulkanSimplified::PipelinePolygonMode polygonMode, bool cullPolygonBacks,
			bool frontClockwise, size_t addOnReserving);
		IDObject<PipelineMultisampleData> AddUniquePipelineMultisampleData(VulkanSimplified::ImageSampleFlagBits samplingSetting,
			std::optional<uint32_t> minSampleShading, size_t addOnReserving);
		IDObject<PipelineDepthStencilStateData> AddUniquePipelineDepthStencilStateData(VulkanSimplified::DepthUsage depthUsage, VulkanSimplified::CompareOperationsType compareOp,
			float minDepth, float maxDepth, size_t addOnReserving);
		IDObject<PipelineColorBlendAttachment> AddUniquePipelineColorBlendAttachment(VulkanSimplified::ColorBlendingComponentFlags blendingComponents,
			VulkanSimplified::ColorBlendingPreset blendingPreset, size_t addOnReserving);

		IDObject<PushConstantData> AddUniquePushConstantData(VulkanSimplified::ShaderTypeFlagBit shaderType, uint32_t offset, uint32_t size, size_t addOnReserving);

		std::vector<VkSpecializationMapEntry> GetShaderSpecializationData(const std::vector<IDObject<ShaderSpecializationElement>>& specializationIDs) const;
		SharedShaderPipelineData GetSharedShaderPipelineData(const IDObject<SharedShaderPipelineData>& shaderID) const;

		std::vector<VertexAttributeDescriptionData> GetVertexAttributeDescriptionData(const std::vector<IDObject<VertexAttributeDescriptionData>>& attributeIDs) const;
		std::vector<VertexBindingDescriptionData> GetVertexBindingDescriptionData(const std::vector<IDObject<VertexBindingDescriptionData>>& bindingIDs) const;
		VertexInputSharedPipelineData GetVertexInputSharedPipelineData(IDObject<VertexInputSharedPipelineData> vertexDataIDs) const;

		VkViewport GetViewports(const IDObject<PipelineViewportData>& viewportID) const;
		VkRect2D GetScissors(const IDObject<PipelineScissorData>& scissorID) const;

		VkPipelineInputAssemblyStateCreateInfo GetInputAssembly(IDObject<PipelineInputAssemblyData> assemblyID) const;
		VkPipelineRasterizationStateCreateInfo GetRasterizationState(IDObject<PipelineRasterizationData> rasterizationID) const;
		VkPipelineMultisampleStateCreateInfo GetMultisamplingState(IDObject<PipelineMultisampleData> multisamplingID) const;
		VkPipelineDepthStencilStateCreateInfo GetDepthStencilState(IDObject<PipelineDepthStencilStateData> depthStencilID) const;
		std::vector<VkPipelineColorBlendAttachmentState> GetColorBlendAttachments(const std::vector<IDObject<PipelineColorBlendAttachment>>& attachmentIDs) const;

		std::vector<VkPushConstantRange> GetPushConstantData(std::vector<IDObject<PushConstantData>> pushConstantIDs) const;

	private:
		UnsortedIDVector<ShaderSpecializationElement> _shaderSpecializationElements;
		UnsortedIDVector<SharedShaderPipelineData> _shaderPipelineData;

		UnsortedIDVector<VertexAttributeDescriptionData> _vertexAttributeData;
		UnsortedIDVector<VertexBindingDescriptionData> _vertexBindingData;
		UnsortedIDVector<VertexInputSharedPipelineData> _vertexInputData;

		UnsortedIDVector<PipelineScissorData> _pipelineScissorData;
		UnsortedIDVector<PipelineViewportData> _pipelineViewportData;

		UnsortedIDVector<PipelineInputAssemblyData> _pipelineInputAssemblyData;
		UnsortedIDVector<PipelineRasterizationData> _pipelineRasterizationData;
		UnsortedIDVector<PipelineMultisampleData> _pipelineMultisampleData;
		UnsortedIDVector<PipelineDepthStencilStateData> _pipelineDepthStencilStateData;
		UnsortedIDVector<PipelineColorBlendAttachment> _pipelineColorBlendData;

		UnsortedIDVector<PushConstantData> _pushConstantData;
	};
}