#include "pch.h"
#include "RunFrame.h"

#include "VulkanData.h"
#include "VulkanBasicData.h"
#include "VulkanInstanceDependentData.h"
#include "VulkanDeviceDependentData.h"
#include "VulkanRenderPassData.h"
#include "VulkanPipelineData.h"
#include "VulkanMemoryData.h"
#include "VulkanCommandBufferData.h"
#include "VulkanSynchronizationData.h"
#include "VulkanFrameData.h"

#include "SwapchainSizes.h"
#include "VertexData.h"

#include <VSMain.h>
#include <VSInstance.h>
#include <VSDeviceMain.h>
#include <VSDataBufferLists.h>
#include <VSSynchronizationDataLists.h>
#include <VSCommandPoolMainList.h>

#include <VSCommandPoolQFGroupList.h>
#include <VSIRCommandPool.h>
#include <VSPrimaryIRCommandBuffer.h>
#include <VSQueueOwnershipTransferData.h>

#include <VSCommandBufferSubmissionData.h>
#include <VSCommandBufferUsage.h>

#include <VSPipelineStageFlags.h>
#include <VSAccessFlags.h>
#include <VSIndexType.h>

#include <VSDataBuffersCopyRegionData.h>
#include <VSGlobalMemoryBarrierData.h>
#include <VSDataBuffersMemoryBarrierData.h>
#include <VSImagesMemoryBarrierData.h>

void RunFrame(VulkanData& data, uint32_t frameIndex)
{
	auto deviceMain = data.basicData->vsmain->GetInstance().GetChoosenDevicesMainClass();
	auto dataBufferLists = deviceMain.GetDataBufferLists();
	auto synchroList = deviceMain.GetSynchronizationDataLists();

	auto mainPoolList = deviceMain.GetCommandPoolMainList();
	auto graphicQf = mainPoolList.GetQueueFamiliesPoolGroup(data.commandBufferData->graphicGroup);
	auto graphicPool = graphicQf.GetCommandPoolWithIndividualReset(data.commandBufferData->graphicPool);
	auto graphicCommandBuffer = graphicPool.GetPrimaryCommandBuffer(data.commandBufferData->graphicBuffers[frameIndex]);

	std::vector<VulkanSimplified::CommandBufferSubmissionData>& submitInfo = data.frameData->submitInfo;

	submitInfo[0].waitSemaphores.resize(1);
	submitInfo[0].commandBufferIDs.resize(1);
	submitInfo[0].signalSemaphores.resize(1);

	VulkanSimplified::CommandBufferGenericID submitedBuffersID;
	submitedBuffersID.type = VulkanSimplified::CommandBufferIDType::IR_PRIMARY;

	if (!synchroList.WaitOnFences({ data.synchronizationData->inFlightFences[frameIndex] }, false, 100000000))
		throw std::runtime_error("RunFrame Error: Program timed out while waiting on a fence!");

	synchroList.ResetFences({ data.synchronizationData->inFlightFences[frameIndex] });

	uint32_t imageIndice = 0;
	graphicCommandBuffer.AcquireNextImage(std::numeric_limits<std::uint64_t>::max(), data.synchronizationData->imageAvailableSemaphores[frameIndex], {},
		imageIndice, data.deviceDependentData->windowID);

	dataBufferLists.WriteToStagingBuffer(data.memoryData->stagingBuffers[frameIndex], 0, reinterpret_cast<const unsigned char&>(*vertices.data()), vertices.size() * sizeof(vertices[0]));
	dataBufferLists.WriteToStagingBuffer(data.memoryData->stagingBuffers[frameIndex], vertices.size() * sizeof(vertices[0]),
		reinterpret_cast<const unsigned char&>(*indices.data()), indices.size() * sizeof(indices[0]));

	VulkanSimplified::QueueOwnershipTransferData queueData;

	const VulkanSimplified::DataBuffersCopyRegionData& vertexCopyRegion = data.frameData->vertexCopyRegion;
	const VulkanSimplified::DataBuffersCopyRegionData& indexCopyRegion = data.frameData->indexCopyRegion;

	const std::vector<VulkanSimplified::DataBuffersMemoryBarrierData>& dataBufferMemoryBarrierData = data.frameData->dataBufferMemoryBarrierData[frameIndex];

	if (data.commandBufferData->transferGroup.has_value())
	{
		auto transferQf = mainPoolList.GetQueueFamiliesPoolGroup(data.commandBufferData->transferGroup.value());
		auto transferPool = transferQf.GetCommandPoolWithIndividualReset(data.commandBufferData->transferPool.value());
		auto transferBuffer = transferPool.GetPrimaryCommandBuffer(data.commandBufferData->transferBuffers[frameIndex]);

		transferBuffer.ResetCommandBuffer(false);
		transferBuffer.BeginRecording(VulkanSimplified::CommandBufferUsage::ONE_USE);

		transferBuffer.TranferDataToVertexBuffer(data.memoryData->stagingBuffers[frameIndex], data.memoryData->vertexBuffers[frameIndex], vertexCopyRegion);
		transferBuffer.TranferDataToIndexBuffer(data.memoryData->stagingBuffers[frameIndex], data.memoryData->indexBuffers[frameIndex], indexCopyRegion);

		transferBuffer.CreatePipelineBarrier(VulkanSimplified::PipelineStageFlagBits::PIPELINE_STAGE_TOP_OF_PIPE, VulkanSimplified::PipelineStageFlagBits::PIPELINE_STAGE_TRANSFER,
			{}, dataBufferMemoryBarrierData, {});

		transferBuffer.EndRecording();

		submitInfo[0].waitSemaphores.resize(0);
		submitedBuffersID.IRPrimaryID.commandPoolID = data.commandBufferData->transferPool.value();
		submitedBuffersID.IRPrimaryID.commandBufferID = data.commandBufferData->transferBuffers[frameIndex];

		submitInfo[0].commandBufferIDs[0] = submitedBuffersID;

		submitInfo[0].signalSemaphores[0] = data.synchronizationData->dataTransferFinishedSemaphores[frameIndex];

		transferQf.SubmitBuffers(data.instanceDependentData->transferOnlyQueueIndex.value(), submitInfo, {});

		submitInfo[0].waitSemaphores.resize(1);
	}

	if (data.commandBufferData->presentGroup.has_value())
	{
		auto presentQf = mainPoolList.GetQueueFamiliesPoolGroup(data.commandBufferData->presentGroup.value());
		auto presentPool = presentQf.GetCommandPoolWithIndividualReset(data.commandBufferData->presentPool.value());
		auto presentCommandBuffer = presentPool.GetPrimaryCommandBuffer(data.commandBufferData->presentBuffers[frameIndex]);

		presentCommandBuffer.ResetCommandBuffer(false);
		presentCommandBuffer.BeginRecording(VulkanSimplified::CommandBufferUsage::ONE_USE);

		queueData.srcQueueIndex = data.instanceDependentData->presentingQueueIndex.value();
		queueData.dstQueueIndex = data.instanceDependentData->graphicsQueueIndex;

		presentCommandBuffer.TransitionSwapchainImageToTrasferDestination(data.deviceDependentData->windowID,
			queueData, imageIndice);

		presentCommandBuffer.EndRecording();

		submitInfo[0].waitSemaphores[0] = { data.synchronizationData->imageAvailableSemaphores[frameIndex], VulkanSimplified::PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT };

		submitedBuffersID.IRPrimaryID.commandPoolID = data.commandBufferData->presentPool.value();
		submitedBuffersID.IRPrimaryID.commandBufferID = data.commandBufferData->presentBuffers[frameIndex];

		submitInfo[0].commandBufferIDs[0] = submitedBuffersID;

		submitInfo[0].signalSemaphores[0] = data.synchronizationData->queueTransferFinishedSemaphores[frameIndex];

		presentQf.SubmitBuffers(data.instanceDependentData->presentingQueueIndex.value(), submitInfo, {});
	}

	graphicCommandBuffer.ResetCommandBuffer(false);

	graphicCommandBuffer.BeginRecording(VulkanSimplified::CommandBufferUsage::ONE_USE);

	if (data.commandBufferData->presentGroup.has_value())
	{
		queueData.srcQueueIndex = data.instanceDependentData->presentingQueueIndex.value();
		queueData.dstQueueIndex = data.instanceDependentData->graphicsQueueIndex;

		graphicCommandBuffer.TransitionSwapchainImageToTrasferDestination(data.deviceDependentData->windowID,
			queueData, imageIndice);
	}
	else
	{
		graphicCommandBuffer.TransitionSwapchainImageToTrasferDestination(data.deviceDependentData->windowID, {}, imageIndice);
	}

	if (data.commandBufferData->transferGroup.has_value())
	{
		graphicCommandBuffer.CreatePipelineBarrier(VulkanSimplified::PipelineStageFlagBits::PIPELINE_STAGE_TOP_OF_PIPE, VulkanSimplified::PipelineStageFlagBits::PIPELINE_STAGE_TRANSFER,
			{}, dataBufferMemoryBarrierData, {});
	}
	else
	{
		graphicCommandBuffer.TranferDataToVertexBuffer(data.memoryData->stagingBuffers[frameIndex], data.memoryData->vertexBuffers[frameIndex], vertexCopyRegion);
		graphicCommandBuffer.TranferDataToIndexBuffer(data.memoryData->stagingBuffers[frameIndex], data.memoryData->indexBuffers[frameIndex], indexCopyRegion);
	}

	graphicCommandBuffer.BeginRenderPass(data.renderPassData->renderPass, data.memoryData->framebuffers[frameIndex], 0U, 0U, width, height, data.renderPassData->clearValues);

	graphicCommandBuffer.BindGraphicsPipeline(data.pipelineData->pipeline);
	graphicCommandBuffer.BindVertexBuffers(0, { {data.memoryData->vertexBuffers[frameIndex], 0} });
	graphicCommandBuffer.BindIndexBuffer(data.memoryData->indexBuffers[frameIndex], 0, VulkanSimplified::IndexType::INDEX_TYPE_16_BITS);

	graphicCommandBuffer.DrawIndexed(static_cast<uint32_t>(indices.size()), 1, 0, 0, 0);

	graphicCommandBuffer.EndRenderPass();

	graphicCommandBuffer.BlitToSwapchainImage(data.deviceDependentData->windowID, data.memoryData->colorRenderTargetImages[frameIndex], 0, 0, width, height, imageIndice);

	if (data.commandBufferData->presentGroup.has_value())
	{
		queueData.srcQueueIndex = data.instanceDependentData->graphicsQueueIndex;
		queueData.dstQueueIndex = data.instanceDependentData->presentingQueueIndex.value();

		graphicCommandBuffer.TransitionSwapchainImageToPresent(data.deviceDependentData->windowID,
			queueData, imageIndice);
	}
	else
	{
		graphicCommandBuffer.TransitionSwapchainImageToPresent(data.deviceDependentData->windowID, {}, imageIndice);
	}

	graphicCommandBuffer.EndRecording();

	if (data.commandBufferData->presentGroup.has_value())
	{
		submitInfo[0].waitSemaphores[0] = { data.synchronizationData->queueTransferFinishedSemaphores[frameIndex], VulkanSimplified::PIPELINE_STAGE_ALL_COMMANDS };
	}
	else
	{
		submitInfo[0].waitSemaphores[0] = { data.synchronizationData->imageAvailableSemaphores[frameIndex], VulkanSimplified::PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT };
	}

	if (data.commandBufferData->transferGroup.has_value())
	{
		submitInfo[0].waitSemaphores.emplace_back(data.synchronizationData->dataTransferFinishedSemaphores[frameIndex], VulkanSimplified::PIPELINE_STAGE_VERTEX_INPUT);
	}

	submitedBuffersID.IRPrimaryID.commandPoolID = data.commandBufferData->graphicPool;
	submitedBuffersID.IRPrimaryID.commandBufferID = data.commandBufferData->graphicBuffers[frameIndex];
	submitInfo[0].commandBufferIDs[0] = submitedBuffersID;

	submitInfo[0].signalSemaphores[0] = data.synchronizationData->renderingFinishedSemaphores[frameIndex];

	if (data.commandBufferData->presentGroup.has_value())
	{
		graphicQf.SubmitBuffers(data.instanceDependentData->graphicsQueueIndex, submitInfo, {});

		auto presentQf = mainPoolList.GetQueueFamiliesPoolGroup(data.commandBufferData->presentGroup.value());
		auto presentPool = presentQf.GetCommandPoolWithIndividualReset(data.commandBufferData->presentPool.value());
		auto presentCommandBuffer = presentPool.GetPrimaryCommandBuffer(data.commandBufferData->presentBuffers[frameIndex]);

		presentCommandBuffer.ResetCommandBuffer(false);
		presentCommandBuffer.BeginRecording(VulkanSimplified::CommandBufferUsage::ONE_USE);

		queueData.srcQueueIndex = data.instanceDependentData->graphicsQueueIndex;
		queueData.dstQueueIndex = data.instanceDependentData->presentingQueueIndex.value();

		presentCommandBuffer.TransitionSwapchainImageToPresent(data.deviceDependentData->windowID,
			queueData, imageIndice);

		presentCommandBuffer.EndRecording();

		submitInfo[0].waitSemaphores[0] = { data.synchronizationData->renderingFinishedSemaphores[frameIndex], VulkanSimplified::PIPELINE_STAGE_ALL_COMMANDS };
		
		if (submitInfo[0].waitSemaphores.size() > 1)
			submitInfo[0].waitSemaphores.resize(1);

		submitedBuffersID.IRPrimaryID.commandPoolID = data.commandBufferData->presentPool.value();
		submitedBuffersID.IRPrimaryID.commandBufferID = data.commandBufferData->presentBuffers[frameIndex];

		submitInfo[0].commandBufferIDs[0] = submitedBuffersID;

		submitInfo[0].signalSemaphores[0] = data.synchronizationData->queueTransferFinishedSemaphores[frameIndex];

		presentQf.SubmitBuffers(data.instanceDependentData->presentingQueueIndex.value(), submitInfo, data.synchronizationData->inFlightFences[frameIndex]);

		presentPool.PresentSwapchainToQueue(data.deviceDependentData->windowID, { data.synchronizationData->queueTransferFinishedSemaphores[frameIndex] }, imageIndice);
	}
	else
	{
		graphicQf.SubmitBuffers(data.instanceDependentData->graphicsQueueIndex, submitInfo, data.synchronizationData->inFlightFences[frameIndex]);
		graphicPool.PresentSwapchainToQueue(data.deviceDependentData->windowID, { data.synchronizationData->renderingFinishedSemaphores[frameIndex] }, imageIndice);
	}
}
