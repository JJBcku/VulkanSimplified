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
#include "VulkanDescriptorData.h"

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

#include <VSDescriptorPoolGenericID.h>

UniformBufferData ubo;

static UniformBufferData CalculateUniformBuffer()
{
	UniformBufferData ret{};

	static auto startTime = std::chrono::high_resolution_clock::now();

	auto currentTime = std::chrono::high_resolution_clock::now();

	float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

	ret.model = glm::rotate(glm::mat4(1.0), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	ret.view = glm::lookAt(glm::vec3(2.0f), glm::vec3(0.0), glm::vec3(0.0f, 0.0f, 1.0f));
	ret.projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 10.0f);
	ret.projection[1][1] *= -1;

	return ret;
}

void RunFrame(VulkanData& data, uint32_t frameIndex)
{
	auto deviceMain = data.basicData->vsmain->GetInstance().GetChoosenDevicesMainClass();
	auto dataBufferLists = deviceMain.GetDataBufferLists();
	auto synchroList = deviceMain.GetSynchronizationDataLists();

	auto mainPoolList = deviceMain.GetCommandPoolMainList();
	auto graphicQf = mainPoolList.GetQueueFamiliesPoolGroup(data.commandBufferData->graphicGroup);
	auto graphicPool = graphicQf.GetCommandPoolWithIndividualReset(data.commandBufferData->graphicPool);
	auto graphicCommandBuffer = graphicPool.GetPrimaryCommandBuffer(data.commandBufferData->graphicBuffers[frameIndex]);

	auto& memData = *data.memoryData;

	std::vector<VS::CommandBufferSubmissionData>& submitInfo = data.frameData->submitInfo;

	submitInfo[0].waitSemaphores.resize(1);
	submitInfo[0].commandBufferIDs.resize(1);
	submitInfo[0].signalSemaphores.resize(1);

	VS::CommandBufferGenericID submitedBuffersID;
	submitedBuffersID.type = VS::CommandBufferIDType::IR_PRIMARY;

	if (!synchroList.WaitOnFences({ data.synchronizationData->inFlightFences[frameIndex] }, false, 100000000))
		throw std::runtime_error("RunFrame Error: Program timed out while waiting on a fence!");

	synchroList.ResetFences({ data.synchronizationData->inFlightFences[frameIndex] });

	uint32_t imageIndice = 0;
	graphicCommandBuffer.AcquireNextImage(std::numeric_limits<uint64_t>::max(), data.synchronizationData->imageAvailableSemaphores[frameIndex], {},
		imageIndice, data.deviceDependentData->windowID);

	const VS::DataBuffersCopyRegionData& vertexCopyRegion = data.frameData->vertexCopyRegion;
	const VS::DataBuffersCopyRegionData& indexCopyRegion = data.frameData->indexCopyRegion;
	const VS::DataBuffersCopyRegionData& uniformCopyRegion = data.frameData->uniformCopyRegion;

	if (memData.vertexMemoryMapped)
	{
		dataBufferLists.WriteToVertexBuffer(memData.vertexBuffers[frameIndex], 0, reinterpret_cast<const unsigned char&>(*vertices.data()),
			vertexCopyRegion.writeSize);
	}
	else
	{
		dataBufferLists.WriteToStagingBuffer(memData.stagingBuffers[frameIndex], vertexCopyRegion.srcOffset, reinterpret_cast<const unsigned char&>(*vertices.data()),
			vertexCopyRegion.writeSize);
	}
		

	if (memData.indexMemoryMapped)
	{
		dataBufferLists.WriteToIndexBuffer(memData.indexBuffers[frameIndex], 0, reinterpret_cast<const unsigned char&>(*indices.data()),
			indexCopyRegion.writeSize);
	}
	else
	{
		dataBufferLists.WriteToStagingBuffer(memData.stagingBuffers[frameIndex], indexCopyRegion.srcOffset, reinterpret_cast<const unsigned char&>(*indices.data()),
			indexCopyRegion.writeSize);
	}

	ubo = CalculateUniformBuffer();

	if (memData.uniformMemoryMapped)
	{
		dataBufferLists.WriteToUniformBuffer(memData.uniformBuffers[frameIndex], 0, reinterpret_cast<const unsigned char&>(ubo), uniformCopyRegion.writeSize);
	}
	else
	{
		dataBufferLists.WriteToStagingBuffer(memData.stagingBuffers[frameIndex], uniformCopyRegion.srcOffset, reinterpret_cast<const unsigned char&>(ubo),
			uniformCopyRegion.writeSize);
	}

	VS::QueueOwnershipTransferData queueData;

	const std::vector<VS::DataBuffersMemoryBarrierData>& dataBufferMemoryBarrierData = data.frameData->dataBufferMemoryBarrierData[frameIndex];

	if (data.commandBufferData->transferGroup.has_value() && (!memData.vertexMemoryMapped || !memData.indexMemoryMapped || !memData.uniformMemoryMapped))
	{
		auto transferQf = mainPoolList.GetQueueFamiliesPoolGroup(data.commandBufferData->transferGroup.value());
		auto transferPool = transferQf.GetCommandPoolWithIndividualReset(data.commandBufferData->transferPool.value());
		auto transferBuffer = transferPool.GetPrimaryCommandBuffer(data.commandBufferData->transferBuffers[frameIndex]);

		transferBuffer.ResetCommandBuffer(false);
		transferBuffer.BeginRecording(VS::CommandBufferUsage::ONE_USE);

		if (!memData.vertexMemoryMapped)
			transferBuffer.TransferDataToVertexBuffer(memData.stagingBuffers[frameIndex], memData.vertexBuffers[frameIndex], vertexCopyRegion);
		if (!memData.indexMemoryMapped)
			transferBuffer.TransferDataToIndexBuffer(memData.stagingBuffers[frameIndex], memData.indexBuffers[frameIndex], indexCopyRegion);
		if (!memData.uniformMemoryMapped)
			transferBuffer.TransferDataToUniformBuffer(memData.stagingBuffers[frameIndex], memData.uniformBuffers[frameIndex], uniformCopyRegion);

		transferBuffer.CreatePipelineBarrier(VS::PipelineStageFlagBits::PIPELINE_STAGE_TOP_OF_PIPE, VS::PipelineStageFlagBits::PIPELINE_STAGE_TRANSFER,
			{}, dataBufferMemoryBarrierData, {});

		transferBuffer.EndRecording();

		submitInfo[0].waitSemaphores.resize(0);
		submitedBuffersID.IRPrimaryID.commandPoolID = data.commandBufferData->transferPool.value();
		submitedBuffersID.IRPrimaryID.commandBufferID = data.commandBufferData->transferBuffers[frameIndex];

		submitInfo[0].commandBufferIDs[0] = submitedBuffersID;

		submitInfo[0].signalSemaphores[0] = data.synchronizationData->dataTransferFinishedSemaphores[imageIndice];

		transferQf.SubmitBuffers(data.instanceDependentData->transferOnlyQueueIndex.value(), submitInfo, {});

		submitInfo[0].waitSemaphores.resize(1);
	}

	if (data.commandBufferData->presentGroup.has_value())
	{
		auto presentQf = mainPoolList.GetQueueFamiliesPoolGroup(data.commandBufferData->presentGroup.value());
		auto presentPool = presentQf.GetCommandPoolWithIndividualReset(data.commandBufferData->presentPool.value());
		auto presentCommandBuffer = presentPool.GetPrimaryCommandBuffer(data.commandBufferData->presentBuffers[frameIndex]);

		presentCommandBuffer.ResetCommandBuffer(false);
		presentCommandBuffer.BeginRecording(VS::CommandBufferUsage::ONE_USE);

		queueData.srcQueueIndex = data.instanceDependentData->presentingQueueIndex.value();
		queueData.dstQueueIndex = data.instanceDependentData->graphicsQueueIndex;

		presentCommandBuffer.TransitionSwapchainImageToTrasferDestination(data.deviceDependentData->windowID,
			queueData, imageIndice);

		presentCommandBuffer.EndRecording();

		submitInfo[0].waitSemaphores[0] = { data.synchronizationData->imageAvailableSemaphores[frameIndex], VS::PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT };

		submitedBuffersID.IRPrimaryID.commandPoolID = data.commandBufferData->presentPool.value();
		submitedBuffersID.IRPrimaryID.commandBufferID = data.commandBufferData->presentBuffers[frameIndex];

		submitInfo[0].commandBufferIDs[0] = submitedBuffersID;

		submitInfo[0].signalSemaphores[0] = data.synchronizationData->queueTransferFinishedSemaphores[imageIndice];

		presentQf.SubmitBuffers(data.instanceDependentData->presentingQueueIndex.value(), submitInfo, {});
	}

	graphicCommandBuffer.ResetCommandBuffer(false);

	graphicCommandBuffer.BeginRecording(VS::CommandBufferUsage::ONE_USE);

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
		graphicCommandBuffer.CreatePipelineBarrier(VS::PipelineStageFlagBits::PIPELINE_STAGE_TOP_OF_PIPE, VS::PipelineStageFlagBits::PIPELINE_STAGE_TRANSFER,
			{}, dataBufferMemoryBarrierData, {});
	}
	else
	{
		if (!memData.vertexMemoryMapped)
			graphicCommandBuffer.TransferDataToVertexBuffer(memData.stagingBuffers[frameIndex], memData.vertexBuffers[frameIndex], vertexCopyRegion);
		if (!memData.indexMemoryMapped)
			graphicCommandBuffer.TransferDataToIndexBuffer(memData.stagingBuffers[frameIndex], memData.indexBuffers[frameIndex], indexCopyRegion);
		if (!memData.uniformMemoryMapped)
			graphicCommandBuffer.TransferDataToUniformBuffer(memData.stagingBuffers[frameIndex], memData.uniformBuffers[frameIndex], uniformCopyRegion);
	}

	graphicCommandBuffer.BeginRenderPass(data.renderPassData->renderPass, memData.framebuffers[frameIndex], 0U, 0U, swapchainWidth, swapchainHeight, data.renderPassData->clearValues);

	graphicCommandBuffer.BindGraphicsPipeline(data.pipelineData->pipeline);
	graphicCommandBuffer.BindVertexBuffers(0, { {memData.vertexBuffers[frameIndex], 0} });
	graphicCommandBuffer.BindDescriptorSetsToGraphicsPipeline(data.pipelineData->pipelineLayout, 0, data.descriptorData->descriptorPool,
		{ data.descriptorData->descriptorSets[frameIndex] }, {});
	graphicCommandBuffer.BindIndexBuffer(memData.indexBuffers[frameIndex], 0, VS::IndexType::INDEX_TYPE_16_BITS);

	graphicCommandBuffer.DrawIndexed(static_cast<uint32_t>(indices.size()), 1, 0, 0, 0);

	graphicCommandBuffer.EndRenderPass();

	if (data.instanceDependentData->maxSamples != VS::SAMPLE_1)
	{
		graphicCommandBuffer.BlitResolveRenderTargetToSwapchainImage(data.deviceDependentData->windowID, memData.resolveRenderTargetImages[frameIndex], 0, 0,
			swapchainWidth, swapchainHeight, imageIndice);
	}
	else
	{
		graphicCommandBuffer.BlitColorRenderTargetToSwapchainImage(data.deviceDependentData->windowID, memData.colorRenderTargetImages[frameIndex], 0, 0,
			swapchainWidth, swapchainHeight, imageIndice);
	}

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
		submitInfo[0].waitSemaphores[0] = { data.synchronizationData->queueTransferFinishedSemaphores[imageIndice], VS::PIPELINE_STAGE_ALL_COMMANDS };
	}
	else
	{
		submitInfo[0].waitSemaphores[0] = { data.synchronizationData->imageAvailableSemaphores[frameIndex], VS::PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT };
	}

	if (data.commandBufferData->transferGroup.has_value() && (!memData.vertexMemoryMapped || !memData.indexMemoryMapped))
	{
		submitInfo[0].waitSemaphores.emplace_back(data.synchronizationData->dataTransferFinishedSemaphores[imageIndice], VS::PIPELINE_STAGE_VERTEX_INPUT);
	}

	submitedBuffersID.IRPrimaryID.commandPoolID = data.commandBufferData->graphicPool;
	submitedBuffersID.IRPrimaryID.commandBufferID = data.commandBufferData->graphicBuffers[frameIndex];
	submitInfo[0].commandBufferIDs[0] = submitedBuffersID;

	submitInfo[0].signalSemaphores[0] = data.synchronizationData->renderingFinishedSemaphores[imageIndice];

	if (data.commandBufferData->presentGroup.has_value())
	{
		graphicQf.SubmitBuffers(data.instanceDependentData->graphicsQueueIndex, submitInfo, {});

		auto presentQf = mainPoolList.GetQueueFamiliesPoolGroup(data.commandBufferData->presentGroup.value());
		auto presentPool = presentQf.GetCommandPoolWithIndividualReset(data.commandBufferData->presentPool.value());
		auto presentCommandBuffer = presentPool.GetPrimaryCommandBuffer(data.commandBufferData->presentBuffers[frameIndex]);

		presentCommandBuffer.ResetCommandBuffer(false);
		presentCommandBuffer.BeginRecording(VS::CommandBufferUsage::ONE_USE);

		queueData.srcQueueIndex = data.instanceDependentData->graphicsQueueIndex;
		queueData.dstQueueIndex = data.instanceDependentData->presentingQueueIndex.value();

		presentCommandBuffer.TransitionSwapchainImageToPresent(data.deviceDependentData->windowID,
			queueData, imageIndice);

		presentCommandBuffer.EndRecording();

		submitInfo[0].waitSemaphores[0] = { data.synchronizationData->renderingFinishedSemaphores[imageIndice], VS::PIPELINE_STAGE_ALL_COMMANDS };
		
		if (submitInfo[0].waitSemaphores.size() > 1)
			submitInfo[0].waitSemaphores.resize(1);

		submitedBuffersID.IRPrimaryID.commandPoolID = data.commandBufferData->presentPool.value();
		submitedBuffersID.IRPrimaryID.commandBufferID = data.commandBufferData->presentBuffers[frameIndex];

		submitInfo[0].commandBufferIDs[0] = submitedBuffersID;

		submitInfo[0].signalSemaphores[0] = data.synchronizationData->queueTransferFinishedSemaphores[imageIndice];

		presentQf.SubmitBuffers(data.instanceDependentData->presentingQueueIndex.value(), submitInfo, data.synchronizationData->inFlightFences[frameIndex]);

		presentPool.PresentSwapchainToQueue(data.deviceDependentData->windowID, { data.synchronizationData->queueTransferFinishedSemaphores[imageIndice] }, imageIndice);
	}
	else
	{
		graphicQf.SubmitBuffers(data.instanceDependentData->graphicsQueueIndex, submitInfo, data.synchronizationData->inFlightFences[frameIndex]);
		graphicPool.PresentSwapchainToQueue(data.deviceDependentData->windowID, { data.synchronizationData->renderingFinishedSemaphores[imageIndice] }, imageIndice);
	}
}
