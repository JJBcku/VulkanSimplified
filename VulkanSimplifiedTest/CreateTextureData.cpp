#include "pch.h"
#include "CreateTextureData.h"

#include "VulkanData.h"
#include "VulkanBasicData.h"
#include "VulkanInstanceDependentData.h"
#include "VulkanCommandBufferData.h"
#include "VulkanSynchronizationData.h"
#include "VulkanFrameData.h"
#include "VulkanTextureData.h"

#include <VSMain.h>
#include <VSInstance.h>
#include <VSDeviceMain.h>

#include <VSDataBufferLists.h>
#include <VSImageDataLists.h>
#include <VSMemoryObjectsList.h>

#include <VSSynchronizationDataLists.h>

#include <VSDataFormatFlags.h>
#include <VSMemoryTypeProperties.h>
#include <VSMemorySizeDef.h>

#include <VSCommandPoolMainList.h>
#include <VSCommandPoolQFGroupList.h>
#include <VSIRCommandPool.h>
#include <VSPrimaryIRCommandBuffer.h>

#include <VSCommandBufferUsage.h>
#include <VSCommandBufferGenericID.h>

#include <VSImagesMemoryBarrierData.h>
#include <VSDataBuffersMemoryBarrierData.h>
#include <VSGlobalMemoryBarrierData.h>

#include <VSPipelineStageFlags.h>
#include <VSAccessFlags.h>
#include <VSImageLayoutFlags.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

void CreateTextureData(VulkanData& data)
{
	data.textureData = std::make_unique<VulkanTextureData>();

	auto& texData = *data.textureData;

	uint32_t width = 0;
	uint32_t height = 0;

	stbi_uc* pixels = stbi_load("Textures/Texture.png", reinterpret_cast<int*>(&width), reinterpret_cast<int*>(&height), nullptr, STBI_rgb_alpha);

	if (pixels == nullptr)
		throw std::runtime_error("CreateTextureData Error: Program failed to load the texture!");

	VulkanSimplified::MemorySize imageSize = width;
	imageSize *= height;
	imageSize = imageSize << 2;

	VulkanSimplified::MemoryAllocationFullID stagingMemoryAllocation;
	IDObject<VulkanSimplifiedInternal::AutoCleanupStagingBuffer> stagingBuffer;

	auto device = data.basicData->vsmain->GetInstance().GetChoosenDevicesMainClass();
	auto imageList = device.GetImageDataLists();
	auto memoryList = device.GetMemoryObjectsList();
	auto bufferLists = device.GetDataBufferLists();

	{
		texData.textureID = imageList.Add2DTextureImage(width, height, 1, VulkanSimplified::DATA_FORMAT_RGBA8_UNORM, {}, false, 1);

		VulkanSimplified::MemorySize allocationSize = imageList.Get2DTextureImagesSize(texData.textureID);
		uint32_t memoryTypeMask = imageList.Get2DTextureImagesMemoryTypeMask(texData.textureID);

		std::vector<VulkanSimplified::MemoryTypeProperties> acceptableMemoryTypes;
		acceptableMemoryTypes.reserve(7);
		acceptableMemoryTypes.push_back(VulkanSimplified::DEVICE_LOCAL);
		acceptableMemoryTypes.push_back(VulkanSimplified::DEVICE_LOCAL | VulkanSimplified::HOST_VISIBLE | VulkanSimplified::HOST_CACHED);
		acceptableMemoryTypes.push_back(VulkanSimplified::DEVICE_LOCAL | VulkanSimplified::HOST_COHERENT | VulkanSimplified::HOST_VISIBLE | VulkanSimplified::HOST_CACHED);
		acceptableMemoryTypes.push_back(VulkanSimplified::DEVICE_LOCAL | VulkanSimplified::HOST_COHERENT | VulkanSimplified::HOST_VISIBLE);
		acceptableMemoryTypes.push_back(VulkanSimplified::HOST_VISIBLE | VulkanSimplified::HOST_CACHED);
		acceptableMemoryTypes.push_back(VulkanSimplified::HOST_COHERENT | VulkanSimplified::HOST_VISIBLE | VulkanSimplified::HOST_CACHED);
		acceptableMemoryTypes.push_back(VulkanSimplified::HOST_COHERENT | VulkanSimplified::HOST_VISIBLE);

		texData.textureMemoryAllocation = memoryList.AllocateMemory(allocationSize, 1, acceptableMemoryTypes, memoryTypeMask);
		imageList.Bind2DTextureImage(texData.textureID, texData.textureMemoryAllocation);

		texData.textureImageView = imageList.Add2DTextureImageFullView(texData.textureID);
	}

	{
		VulkanSimplified::MemorySize allocationSize = imageList.Get2DTextureImagesSize(texData.textureID);
		stagingBuffer = bufferLists.AddStagingBuffer(allocationSize, {});

		allocationSize = bufferLists.GetStagingBuffersSize(stagingBuffer);
		uint32_t memoryTypeMask = bufferLists.GetStagingBuffersMemoryTypeMask(stagingBuffer);

		std::vector<VulkanSimplified::MemoryTypeProperties> acceptableMemoryTypes;
		acceptableMemoryTypes.reserve(5);
		acceptableMemoryTypes.push_back(VulkanSimplified::DEVICE_LOCAL | VulkanSimplified::HOST_COHERENT | VulkanSimplified::HOST_VISIBLE | VulkanSimplified::HOST_CACHED);
		acceptableMemoryTypes.push_back(VulkanSimplified::DEVICE_LOCAL | VulkanSimplified::HOST_COHERENT | VulkanSimplified::HOST_VISIBLE);
		acceptableMemoryTypes.push_back(VulkanSimplified::HOST_VISIBLE | VulkanSimplified::HOST_CACHED);
		acceptableMemoryTypes.push_back(VulkanSimplified::HOST_COHERENT | VulkanSimplified::HOST_VISIBLE | VulkanSimplified::HOST_CACHED);
		acceptableMemoryTypes.push_back(VulkanSimplified::HOST_COHERENT | VulkanSimplified::HOST_VISIBLE);

		stagingMemoryAllocation = memoryList.AllocateMemory(allocationSize, 1, acceptableMemoryTypes, memoryTypeMask);
		bufferLists.BindStagingBuffer(stagingBuffer, stagingMemoryAllocation);
	}

	{
		bufferLists.WriteToStagingBuffer(stagingBuffer, 0, *pixels, imageSize);

		auto mainPoolList = device.GetCommandPoolMainList();

		std::vector<VulkanSimplified::CommandBufferSubmissionData>& submitInfo = data.frameData->submitInfo;

		submitInfo[0].waitSemaphores.resize(0);
		submitInfo[0].commandBufferIDs.resize(1);

		auto graphicQfGroup = mainPoolList.GetQueueFamiliesPoolGroup(data.commandBufferData->graphicGroup);
		auto graphicPool = graphicQfGroup.GetCommandPoolWithIndividualReset(data.commandBufferData->graphicPool);
		auto graphicBuffer = graphicPool.GetPrimaryCommandBuffer(data.commandBufferData->graphicBuffers[0]);

		auto synchro = device.GetSynchronizationDataLists();
		synchro.ResetFences({ data.synchronizationData->inFlightFences[0] });

		VulkanSimplified::ImagesMemoryBarrierData imageMemBOne, imageMemBTwo;
		imageMemBOne.srcAccess = VulkanSimplified::AccessFlagBits::ACCESS_NONE;
		imageMemBOne.dstAccess = VulkanSimplified::AccessFlagBits::ACCESS_TRANSFER_WRITE;
		imageMemBOne.oldLayout = VulkanSimplified::ImageLayoutFlags::UNDEFINED;
		imageMemBOne.newLayout = VulkanSimplified::ImageLayoutFlags::TRANSFER_DESTINATION;
		imageMemBOne.imageID = VulkanSimplified::ImagesGenericID(texData.textureID);

		imageMemBTwo.srcAccess = VulkanSimplified::AccessFlagBits::ACCESS_TRANSFER_WRITE;
		imageMemBTwo.dstAccess = VulkanSimplified::AccessFlagBits::ACCESS_MEMORY_READ;
		imageMemBTwo.oldLayout = VulkanSimplified::ImageLayoutFlags::TRANSFER_DESTINATION;
		imageMemBTwo.newLayout = VulkanSimplified::ImageLayoutFlags::SHADER_READ_ONLY;
		imageMemBTwo.imageID = VulkanSimplified::ImagesGenericID(texData.textureID);

		if (data.commandBufferData->transferGroup.has_value())
		{
			imageMemBTwo.queueData.emplace();
			imageMemBTwo.queueData.value().srcQueueIndex = data.instanceDependentData->transferOnlyQueueIndex.value();
			imageMemBTwo.queueData.value().dstQueueIndex = data.instanceDependentData->graphicsQueueIndex;

			auto transferQfGroup = mainPoolList.GetQueueFamiliesPoolGroup(data.commandBufferData->transferGroup.value());
			auto transferPool = transferQfGroup.GetCommandPoolWithIndividualReset(data.commandBufferData->transferPool.value());
			auto transferBuffer = transferPool.GetPrimaryCommandBuffer(data.commandBufferData->transferBuffers[0]);

			{
				transferBuffer.BeginRecording(VulkanSimplified::CommandBufferUsage::ONE_USE);

				transferBuffer.CreatePipelineBarrier(VulkanSimplified::PipelineStageFlagBits::PIPELINE_STAGE_TOP_OF_PIPE,
					VulkanSimplified::PipelineStageFlagBits::PIPELINE_STAGE_TRANSFER, {}, {}, { imageMemBOne });

				transferBuffer.TransferDataTo2dTextureSimple(stagingBuffer, texData.textureID, 0);

				transferBuffer.CreatePipelineBarrier(VulkanSimplified::PipelineStageFlagBits::PIPELINE_STAGE_TRANSFER,
					VulkanSimplified::PipelineStageFlagBits::PIPELINE_STAGE_BOTTOM_OF_PIPE, {}, {}, { imageMemBTwo });

				transferBuffer.EndRecording();

				submitInfo[0].commandBufferIDs[0].IRPrimaryID.type = VulkanSimplified::CommandBufferIDType::IR_PRIMARY;
				submitInfo[0].commandBufferIDs[0].IRPrimaryID.commandPoolID = data.commandBufferData->transferPool.value();
				submitInfo[0].commandBufferIDs[0].IRPrimaryID.commandBufferID = data.commandBufferData->transferBuffers[0];

				submitInfo[0].signalSemaphores.resize(1);
				submitInfo[0].signalSemaphores[0] = data.synchronizationData->dataTransferFinishedSemaphores[0];

				transferQfGroup.SubmitBuffers(data.instanceDependentData->transferOnlyQueueIndex.value(), submitInfo, {});
			}

			{
				graphicBuffer.BeginRecording(VulkanSimplified::CommandBufferUsage::ONE_USE);

				graphicBuffer.CreatePipelineBarrier(VulkanSimplified::PipelineStageFlagBits::PIPELINE_STAGE_TRANSFER,
					VulkanSimplified::PipelineStageFlagBits::PIPELINE_STAGE_BOTTOM_OF_PIPE, {}, {}, { imageMemBTwo });

				graphicBuffer.EndRecording();

				submitInfo[0].waitSemaphores.resize(1);
				submitInfo[0].waitSemaphores[0].first = submitInfo[0].signalSemaphores[0];
				submitInfo[0].waitSemaphores[0].second = VulkanSimplified::PipelineStageFlagBits::PIPELINE_STAGE_FRAGMENT_SHADER;

				submitInfo[0].commandBufferIDs[0].IRPrimaryID.type = VulkanSimplified::CommandBufferIDType::IR_PRIMARY;
				submitInfo[0].commandBufferIDs[0].IRPrimaryID.commandPoolID = data.commandBufferData->graphicPool;
				submitInfo[0].commandBufferIDs[0].IRPrimaryID.commandBufferID = data.commandBufferData->graphicBuffers[0];

				submitInfo[0].signalSemaphores.resize(0);

				graphicQfGroup.SubmitBuffers(data.instanceDependentData->graphicsQueueIndex, submitInfo, data.synchronizationData->inFlightFences[0]);
			}
		}
		else
		{
			submitInfo[0].signalSemaphores.resize(0);

			graphicBuffer.BeginRecording(VulkanSimplified::CommandBufferUsage::ONE_USE);

			graphicBuffer.CreatePipelineBarrier(VulkanSimplified::PipelineStageFlagBits::PIPELINE_STAGE_TOP_OF_PIPE, VulkanSimplified::PipelineStageFlagBits::PIPELINE_STAGE_TRANSFER,
				{}, {}, { imageMemBOne });

			graphicBuffer.TransferDataTo2dTextureSimple(stagingBuffer, texData.textureID, 0);

			graphicBuffer.CreatePipelineBarrier(VulkanSimplified::PipelineStageFlagBits::PIPELINE_STAGE_TRANSFER,
				VulkanSimplified::PipelineStageFlagBits::PIPELINE_STAGE_FRAGMENT_SHADER, {}, {}, { imageMemBTwo });

			graphicBuffer.EndRecording();

			submitInfo[0].commandBufferIDs[0].IRPrimaryID.type = VulkanSimplified::CommandBufferIDType::IR_PRIMARY;
			submitInfo[0].commandBufferIDs[0].IRPrimaryID.commandPoolID = data.commandBufferData->graphicPool;
			submitInfo[0].commandBufferIDs[0].IRPrimaryID.commandBufferID = data.commandBufferData->graphicBuffers[0];

			graphicQfGroup.SubmitBuffers(data.instanceDependentData->graphicsQueueIndex, submitInfo, data.synchronizationData->inFlightFences[0]);
		}

		synchro.WaitOnFences({ data.synchronizationData->inFlightFences[0] }, false, 1000000);

		bufferLists.RemoveStagingBuffer(stagingBuffer, true);
		memoryList.FreeMemory(stagingMemoryAllocation, true, true);
	}

	stbi_image_free(pixels);
}
