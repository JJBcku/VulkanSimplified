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

#include <VSInstance.h>
#include <VSDeviceMain.h>
#include <VSRenderPassDataList.h>
#include <VSSubpassCreationDataWithoutResolving.h>

void CreateRenderPassData(VulkanData& data)
{
	data.renderPassData = std::make_unique<VulkanRenderPassData>();

	auto sharedData = data.basicData->vsmain->GetSharedDataMainList();
	auto sharedRenderPassData = sharedData.GetSharedRenderPassDataList();

	VulkanSimplified::DataFormatSetIndependentID format = data.instanceDependentData->supportedColorFormat;

	auto& renderPassData = *data.renderPassData;

	renderPassData.renderPassAttachments.push_back(sharedRenderPassData.AddRenderPassAttachment(format, VulkanSimplified::SAMPLE_1, VulkanSimplified::RenderPassAttachmentLoadOP::CLEAR,
		VulkanSimplified::RenderPassAttachmentStoreOP::STORE, VulkanSimplified::ImageLayoutFlags::UNDEFINED, VulkanSimplified::ImageLayoutFlags::TRANSFER_SOURCE));
	renderPassData.renderPassAttachments.push_back(sharedRenderPassData.AddRenderPassAttachment(data.instanceDependentData->supportedDepthFormat, VulkanSimplified::SAMPLE_1,
		VulkanSimplified::RenderPassAttachmentLoadOP::CLEAR, VulkanSimplified::RenderPassAttachmentStoreOP::IGNORE, VulkanSimplified::ImageLayoutFlags::UNDEFINED,
		VulkanSimplified::ImageLayoutFlags::DEPTH_STENCIL_READ_WRITE));

	renderPassData.colorAttachmentReference = sharedRenderPassData.AddRenderPassAttachmentReference(0, VulkanSimplified::ImageLayoutFlags::COLOR_ATTACHMENT);
	renderPassData.depthAttachmentReference = sharedRenderPassData.AddRenderPassAttachmentReference(1, VulkanSimplified::ImageLayoutFlags::DEPTH_STENCIL_READ_WRITE);

	renderPassData.subpassDependency = sharedRenderPassData.AddSubpassDependency(VulkanSimplified::externalSubpass, 0,
		VulkanSimplified::PipelineStageFlagBits::PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT, VulkanSimplified::PipelineStageFlagBits::PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT, 0,
		VulkanSimplified::AccessFlagBits::ACCESS_COLOR_ATTACHMENT_WRITE);

	renderPassData.clearValues.resize(2);
	renderPassData.clearValues[0].emplace(sharedRenderPassData.AddFloatColorClearValue(0.0f, 0.0f, 0.0f, 0.0f));
	renderPassData.clearValues[1].emplace(sharedRenderPassData.AddDepthStencilClearValue(1.0f, 0));

	auto instance = data.basicData->vsmain->GetInstance();
	auto device = instance.GetChoosenDevicesMainClass();
	auto deviceRenderPassData = device.GetRenderPassList();

	VulkanSimplified::SubpassCreationDataWithoutResolving subpassData;
	subpassData.colorAttachments.push_back(renderPassData.colorAttachmentReference);
	subpassData.depthStencilAttachment = renderPassData.depthAttachmentReference;

	renderPassData.renderPass = deviceRenderPassData.AddRenderPassWithoutResolveAttachments(renderPassData.renderPassAttachments, { subpassData }, { renderPassData.subpassDependency });
}
