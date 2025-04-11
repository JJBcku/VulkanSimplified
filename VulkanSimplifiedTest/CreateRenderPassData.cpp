#include "pch.h"
#include "CreateRenderPassData.h"

#include "VulkanData.h"
#include "VulkanBasicData.h"
#include "VulkanInstanceDependentData.h"
#include "VulkanRenderPassData.h"

#include <VSMain.h>
#include <VSSharedDataMainList.h>
#include <VSSharedRenderPassDataList.h>

#include <VSDataFormatFlags.h>
#include <VSImageSampleFlags.h>
#include <VSImageLayoutFlags.h>
#include <VSRenderPassAttachmentOP.h>
#include <VSPipelineStageFlags.h>
#include <VSAccessFlags.h>

void CreateRenderPassData(VulkanData& data)
{
	data.renderPassData = std::make_unique<VulkanRenderPassData>();

	auto sharedData = data.basicData->vsmain.value().GetSharedDataMainList();
	auto sharedRenderPassData = sharedData.GetRenderPassDataList();

	VulkanSimplified::DataFormatSetIndependentID format = data.instanceDependentData->supportedFormat;

	auto& renderPassData = *data.renderPassData;

	renderPassData.renderPassAttachments.push_back(sharedRenderPassData.AddRenderPassAttachment(format, VulkanSimplified::SAMPLE_1, VulkanSimplified::RenderPassAttachmentLoadOP::CLEAR,
		VulkanSimplified::RenderPassAttachmentStoreOP::STORE, VulkanSimplified::ImageLayoutFlags::UNDEFINED, VulkanSimplified::ImageLayoutFlags::TRANSFER_SOURCE));

	renderPassData.colorAttachmentReference = sharedRenderPassData.AddRenderPassAttachmentReference(0, VulkanSimplified::ImageLayoutFlags::COLOR_ATTACHMENT);

	renderPassData.subpassDependency = sharedRenderPassData.AddSubpassDependency(VulkanSimplified::externalSubpass, 0,
		VulkanSimplified::PipelineStageFlagBits::PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT, VulkanSimplified::PipelineStageFlagBits::PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT, 0,
		VulkanSimplified::AccessFlagBits::ACCESS_COLOR_WRITE);
}
