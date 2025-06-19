#include "VSCommonNIpch.h"
#include "../../DNIHeaders/VSCommon/VSPipelineStageFlagsInternal.h"

namespace VulkanSimplifiedInternal
{
	VkPipelineStageFlags TranslateStageFlags(VulkanSimplified::PipelineStageFlags stageFlags)
	{
		VkPipelineStageFlags ret = 0;

		if ((stageFlags & VulkanSimplified::PIPELINE_STAGE_TOP_OF_PIPE) == VulkanSimplified::PIPELINE_STAGE_TOP_OF_PIPE)
			ret |= VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;

		if ((stageFlags & VulkanSimplified::PIPELINE_STAGE_DRAW_INDIRECT) == VulkanSimplified::PIPELINE_STAGE_DRAW_INDIRECT)
			ret |= VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT;

		if ((stageFlags & VulkanSimplified::PIPELINE_STAGE_VERTEX_INPUT) == VulkanSimplified::PIPELINE_STAGE_VERTEX_INPUT)
			ret |= VK_PIPELINE_STAGE_VERTEX_INPUT_BIT;

		if ((stageFlags & VulkanSimplified::PIPELINE_STAGE_VERTEX_SHADER) == VulkanSimplified::PIPELINE_STAGE_VERTEX_SHADER)
			ret |= VK_PIPELINE_STAGE_VERTEX_SHADER_BIT;

		if ((stageFlags & VulkanSimplified::PIPELINE_STAGE_TESSELATION_CONTROL_SHADER) == VulkanSimplified::PIPELINE_STAGE_TESSELATION_CONTROL_SHADER)
			ret |= VK_PIPELINE_STAGE_TESSELLATION_CONTROL_SHADER_BIT;

		if ((stageFlags & VulkanSimplified::PIPELINE_STAGE_TESSELATION_EVALUATION_SHADER) == VulkanSimplified::PIPELINE_STAGE_TESSELATION_EVALUATION_SHADER)
			ret |= VK_PIPELINE_STAGE_TESSELLATION_EVALUATION_SHADER_BIT;

		if ((stageFlags & VulkanSimplified::PIPELINE_STAGE_GEOMETRY_SHADER) == VulkanSimplified::PIPELINE_STAGE_GEOMETRY_SHADER)
			ret |= VK_PIPELINE_STAGE_GEOMETRY_SHADER_BIT;

		if ((stageFlags & VulkanSimplified::PIPELINE_STAGE_FRAGMENT_SHADER) == VulkanSimplified::PIPELINE_STAGE_FRAGMENT_SHADER)
			ret |= VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;

		if ((stageFlags & VulkanSimplified::PIPELINE_STAGE_EARLY_FRAGMENT_TEST) == VulkanSimplified::PIPELINE_STAGE_EARLY_FRAGMENT_TEST)
			ret |= VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;

		if ((stageFlags & VulkanSimplified::PIPELINE_STAGE_LATE_FRAGMENT_TEST) == VulkanSimplified::PIPELINE_STAGE_LATE_FRAGMENT_TEST)
			ret |= VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;

		if ((stageFlags & VulkanSimplified::PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT) == VulkanSimplified::PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT)
			ret |= VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

		if ((stageFlags & VulkanSimplified::PIPELINE_STAGE_COMPUTE_SHADER) == VulkanSimplified::PIPELINE_STAGE_COMPUTE_SHADER)
			ret |= VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;

		if ((stageFlags & VulkanSimplified::PIPELINE_STAGE_TRANSFER) == VulkanSimplified::PIPELINE_STAGE_TRANSFER)
			ret |= VK_PIPELINE_STAGE_TRANSFER_BIT;

		if ((stageFlags & VulkanSimplified::PIPELINE_STAGE_BOTTOM_OF_PIPE) == VulkanSimplified::PIPELINE_STAGE_BOTTOM_OF_PIPE)
			ret |= VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;

		if ((stageFlags & VulkanSimplified::PIPELINE_STAGE_HOST) == VulkanSimplified::PIPELINE_STAGE_HOST)
			ret |= VK_PIPELINE_STAGE_HOST_BIT;

		if ((stageFlags & VulkanSimplified::PIPELINE_STAGE_ALL_GRAPHICS) == VulkanSimplified::PIPELINE_STAGE_ALL_GRAPHICS)
			ret |= VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT;

		if ((stageFlags & VulkanSimplified::PIPELINE_STAGE_ALL_COMMANDS) == VulkanSimplified::PIPELINE_STAGE_ALL_COMMANDS)
			ret |= VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;

		return ret;
	}
}