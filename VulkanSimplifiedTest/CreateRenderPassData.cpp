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
#include <VSSubpassCreationDataWithResolving.h>

void CreateRenderPassData(VulkanData& data)
{
	data.renderPassData = std::make_unique<VulkanRenderPassData>();

	auto sharedData = data.basicData->vsmain->GetSharedDataMainList();
	auto sharedRenderPassData = sharedData.GetSharedRenderPassDataList();

	VS::DataFormatSetIndependentID format = data.instanceDependentData->supportedColorFormat;

	auto& renderPassData = *data.renderPassData;

	renderPassData.renderPassAttachments.reserve(3);

	if (data.instanceDependentData->maxSamples != VS::SAMPLE_1)
	{
		renderPassData.renderPassAttachments.push_back(sharedRenderPassData.AddRenderPassAttachment(format, data.instanceDependentData->maxSamples,
			VS::RenderPassAttachmentLoadOP::CLEAR, VS::RenderPassAttachmentStoreOP::IGNORE, VS::ImageLayoutFlags::UNDEFINED,
			VS::ImageLayoutFlags::TRANSFER_SOURCE));
	}
	else
	{
		renderPassData.renderPassAttachments.push_back(sharedRenderPassData.AddRenderPassAttachment(format, VS::SAMPLE_1,
			VS::RenderPassAttachmentLoadOP::CLEAR, VS::RenderPassAttachmentStoreOP::STORE, VS::ImageLayoutFlags::UNDEFINED,
			VS::ImageLayoutFlags::TRANSFER_SOURCE));
	}

	renderPassData.renderPassAttachments.push_back(sharedRenderPassData.AddRenderPassAttachment(data.instanceDependentData->supportedDepthFormat,
		data.instanceDependentData->maxSamples, VS::RenderPassAttachmentLoadOP::CLEAR, VS::RenderPassAttachmentStoreOP::IGNORE,
		VS::ImageLayoutFlags::UNDEFINED, VS::ImageLayoutFlags::DEPTH_STENCIL_READ_WRITE));

	if (data.instanceDependentData->maxSamples != VS::SAMPLE_1)
	{
		renderPassData.renderPassAttachments.push_back(sharedRenderPassData.AddRenderPassAttachment(format, VS::SAMPLE_1,
			VS::RenderPassAttachmentLoadOP::IGNORE, VS::RenderPassAttachmentStoreOP::STORE, VS::ImageLayoutFlags::UNDEFINED,
			VS::ImageLayoutFlags::TRANSFER_SOURCE));
	}

	renderPassData.colorAttachmentReference = sharedRenderPassData.AddRenderPassAttachmentReference(0, VS::ImageLayoutFlags::COLOR_ATTACHMENT);
	renderPassData.depthAttachmentReference = sharedRenderPassData.AddRenderPassAttachmentReference(1, VS::ImageLayoutFlags::DEPTH_STENCIL_READ_WRITE);
	renderPassData.resolveAttachmentReference = sharedRenderPassData.AddRenderPassAttachmentReference(2, VS::ImageLayoutFlags::COLOR_ATTACHMENT);

	renderPassData.subpassDependency = sharedRenderPassData.AddSubpassDependency(VS::externalSubpass, 0,
		VS::PipelineStageFlagBits::PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT, VS::PipelineStageFlagBits::PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT, 0,
		VS::AccessFlagBits::ACCESS_COLOR_ATTACHMENT_WRITE);

	renderPassData.clearValues.resize(2);
	renderPassData.clearValues[0].emplace(sharedRenderPassData.AddFloatColorClearValue(0.0f, 0.0f, 0.0f, 0.0f));
	renderPassData.clearValues[1].emplace(sharedRenderPassData.AddDepthStencilClearValue(1.0f, 0));

	auto instance = data.basicData->vsmain->GetInstance();
	auto device = instance.GetChoosenDevicesMainClass();
	auto deviceRenderPassData = device.GetRenderPassList();

	if (data.instanceDependentData->maxSamples != VS::SAMPLE_1)
	{
		VS::SubpassCreationDataWithResolving subpassData;
		subpassData.colorAttachments.emplace_back(renderPassData.colorAttachmentReference, renderPassData.resolveAttachmentReference);
		subpassData.depthStencilAttachment = renderPassData.depthAttachmentReference;

		renderPassData.renderPass = deviceRenderPassData.AddRenderPassWithResolveAttachments(renderPassData.renderPassAttachments, { subpassData },
			{ renderPassData.subpassDependency });
	}
	else
	{
		VS::SubpassCreationDataWithoutResolving subpassData;
		subpassData.colorAttachments.push_back(renderPassData.colorAttachmentReference);
		subpassData.depthStencilAttachment = renderPassData.depthAttachmentReference;

		renderPassData.renderPass = deviceRenderPassData.AddRenderPassWithoutResolveAttachments(renderPassData.renderPassAttachments, { subpassData },
			{ renderPassData.subpassDependency });
	}
}
