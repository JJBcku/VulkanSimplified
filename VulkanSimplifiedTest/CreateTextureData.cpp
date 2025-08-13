#include "pch.h"
#include "CreateTextureData.h"

#include "VulkanData.h"
#include "VulkanBasicData.h"
#include "VulkanInstanceDependentData.h"
#include "VulkanDeviceDependentData.h"
#include "VulkanDescriptorData.h"
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

#include <VSDescriptorSetCombined2DTextureSamplerWriteData.h>
#include <VSDescriptorDataLists.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "SwapchainSizes.h"

#include <iostream>

void CreateTextureData(VulkanData& data)
{
	data.textureData = std::make_unique<VulkanTextureData>();

	auto& texData = *data.textureData;

	uint32_t imageWidth = 0;
	uint32_t imageHeight = 0;

	stbi_uc* pixels = stbi_load("Textures/Texture.png", reinterpret_cast<int*>(&imageWidth), reinterpret_cast<int*>(&imageHeight), nullptr, STBI_rgb_alpha);

	if (pixels == nullptr)
		throw std::runtime_error("CreateTextureData Error: Program failed to load the texture!");

	VS::MemorySize imageSize = imageWidth;
	imageSize *= imageHeight;
	imageSize = imageSize << 2;

	uint32_t mipLevels = 1;
	uint32_t maxSide = std::max(imageWidth, imageHeight);

	while (maxSide > 1)
	{
		maxSide = maxSide >> 1;
		mipLevels++;
	}

	VS::MemoryAllocationFullID stagingMemoryAllocation;
	IDObject<VS::AutoCleanupStagingBuffer> stagingBuffer;

	auto device = data.basicData->vsmain->GetInstance().GetChoosenDevicesMainClass();
	auto imageList = device.GetImageDataLists();
	auto memoryList = device.GetMemoryObjectsList();
	auto bufferLists = device.GetDataBufferLists();

	{
		texData.textureID = imageList.Add2DTextureImage(imageWidth, imageHeight, mipLevels, VS::DATA_FORMAT_RGBA8_SRGB, {}, false, 1);

		VS::MemorySize allocationSize = imageList.Get2DTextureImagesSize(texData.textureID);
		uint32_t memoryTypeMask = imageList.Get2DTextureImagesMemoryTypeMask(texData.textureID);

		std::vector<VS::MemoryTypeProperties> acceptableMemoryTypes;
		acceptableMemoryTypes.reserve(7);
		acceptableMemoryTypes.push_back(VS::DEVICE_LOCAL);
		acceptableMemoryTypes.push_back(VS::DEVICE_LOCAL | VS::HOST_VISIBLE | VS::HOST_CACHED);
		acceptableMemoryTypes.push_back(VS::DEVICE_LOCAL | VS::HOST_COHERENT | VS::HOST_VISIBLE | VS::HOST_CACHED);
		acceptableMemoryTypes.push_back(VS::DEVICE_LOCAL | VS::HOST_COHERENT | VS::HOST_VISIBLE);
		acceptableMemoryTypes.push_back(VS::HOST_VISIBLE | VS::HOST_CACHED);
		acceptableMemoryTypes.push_back(VS::HOST_COHERENT | VS::HOST_VISIBLE | VS::HOST_CACHED);
		acceptableMemoryTypes.push_back(VS::HOST_COHERENT | VS::HOST_VISIBLE);

		texData.textureMemoryAllocation = memoryList.AllocateMemory(allocationSize, 1, acceptableMemoryTypes, memoryTypeMask);
		imageList.Bind2DTextureImage(texData.textureID, texData.textureMemoryAllocation);

		texData.textureImageView = imageList.Add2DTextureImageFullView(texData.textureID);
	}

	{
		VS::MemorySize allocationSize = imageList.Get2DTextureImagesSize(texData.textureID);
		stagingBuffer = bufferLists.AddStagingBuffer(allocationSize, {});

		allocationSize = bufferLists.GetStagingBuffersSize(stagingBuffer);
		uint32_t memoryTypeMask = bufferLists.GetStagingBuffersMemoryTypeMask(stagingBuffer);

		std::vector<VS::MemoryTypeProperties> acceptableMemoryTypes;
		acceptableMemoryTypes.reserve(5);
		acceptableMemoryTypes.push_back(VS::HOST_COHERENT | VS::HOST_VISIBLE);
		acceptableMemoryTypes.push_back(VS::HOST_COHERENT | VS::HOST_VISIBLE | VS::HOST_CACHED);
		acceptableMemoryTypes.push_back(VS::HOST_VISIBLE | VS::HOST_CACHED);
		acceptableMemoryTypes.push_back(VS::DEVICE_LOCAL | VS::HOST_COHERENT | VS::HOST_VISIBLE | VS::HOST_CACHED);
		acceptableMemoryTypes.push_back(VS::DEVICE_LOCAL | VS::HOST_COHERENT | VS::HOST_VISIBLE);

		stagingMemoryAllocation = memoryList.AllocateMemory(allocationSize, 1, acceptableMemoryTypes, memoryTypeMask);
		bufferLists.BindStagingBuffer(stagingBuffer, stagingMemoryAllocation);
	}

	{
		bufferLists.WriteToStagingBuffer(stagingBuffer, 0, *pixels, imageSize);

		auto mainPoolList = device.GetCommandPoolMainList();

		std::vector<VS::CommandBufferSubmissionData>& submitInfo = data.frameData->submitInfo;

		submitInfo[0].waitSemaphores.resize(0);
		submitInfo[0].commandBufferIDs.resize(1);

		auto graphicQfGroup = mainPoolList.GetQueueFamiliesPoolGroup(data.commandBufferData->graphicGroup);
		auto graphicPool = graphicQfGroup.GetCommandPoolWithIndividualReset(data.commandBufferData->graphicPool);
		auto graphicBuffer = graphicPool.GetPrimaryCommandBuffer(data.commandBufferData->graphicBuffers[0]);

		auto synchro = device.GetSynchronizationDataLists();
		synchro.ResetFences({ data.synchronizationData->inFlightFences[0] });

		VS::ImagesMemoryBarrierData imageMemBOne, imageMemBTwo, imageMemBThree, imageMemBFour;
		imageMemBOne.srcAccess = VS::AccessFlagBits::ACCESS_NONE;
		imageMemBOne.dstAccess = VS::AccessFlagBits::ACCESS_TRANSFER_WRITE;
		imageMemBOne.oldLayout = VS::ImageLayoutFlags::UNDEFINED;
		imageMemBOne.newLayout = VS::ImageLayoutFlags::TRANSFER_DESTINATION;
		imageMemBOne.imageID = VS::ImagesGenericID(texData.textureID);

		imageMemBTwo.srcAccess = VS::AccessFlagBits::ACCESS_TRANSFER_WRITE;
		imageMemBTwo.dstAccess = VS::AccessFlagBits::ACCESS_TRANSFER_READ;
		imageMemBTwo.oldLayout = VS::ImageLayoutFlags::TRANSFER_DESTINATION;
		imageMemBTwo.newLayout = VS::ImageLayoutFlags::TRANSFER_DESTINATION;
		imageMemBTwo.imageID = VS::ImagesGenericID(texData.textureID);

		imageMemBThree.srcAccess = VS::AccessFlagBits::ACCESS_TRANSFER_WRITE;
		imageMemBThree.dstAccess = VS::AccessFlagBits::ACCESS_TRANSFER_READ;
		imageMemBThree.oldLayout = VS::ImageLayoutFlags::TRANSFER_DESTINATION;
		imageMemBThree.newLayout = VS::ImageLayoutFlags::TRANSFER_SOURCE;
		imageMemBThree.imageID = VS::ImagesGenericID(texData.textureID);
		imageMemBThree.imageID.texture2D.mipLevelCount = 1;

		imageMemBFour.srcAccess = VS::AccessFlagBits::ACCESS_TRANSFER_WRITE;
		imageMemBFour.dstAccess = VS::AccessFlagBits::ACCESS_MEMORY_READ;
		imageMemBFour.oldLayout = VS::ImageLayoutFlags::TRANSFER_SOURCE;
		imageMemBFour.newLayout = VS::ImageLayoutFlags::SHADER_READ_ONLY;
		imageMemBFour.imageID = VS::ImagesGenericID(texData.textureID);

		if (data.commandBufferData->transferGroup.has_value())
		{
			imageMemBTwo.queueData.emplace();
			imageMemBTwo.queueData.value().srcQueueIndex = data.instanceDependentData->transferOnlyQueueIndex.value();
			imageMemBTwo.queueData.value().dstQueueIndex = data.instanceDependentData->graphicsQueueIndex;

			auto transferQfGroup = mainPoolList.GetQueueFamiliesPoolGroup(data.commandBufferData->transferGroup.value());
			auto transferPool = transferQfGroup.GetCommandPoolWithIndividualReset(data.commandBufferData->transferPool.value());
			auto transferBuffer = transferPool.GetPrimaryCommandBuffer(data.commandBufferData->transferBuffers[0]);

			{
				transferBuffer.BeginRecording(VS::CommandBufferUsage::ONE_USE);

				transferBuffer.CreatePipelineBarrier(VS::PipelineStageFlagBits::PIPELINE_STAGE_TOP_OF_PIPE,
					VS::PipelineStageFlagBits::PIPELINE_STAGE_TRANSFER, {}, {}, { imageMemBOne });

				transferBuffer.TransferDataTo2dTextureSimple(stagingBuffer, texData.textureID, 0);

				transferBuffer.CreatePipelineBarrier(VS::PipelineStageFlagBits::PIPELINE_STAGE_TRANSFER,
					VS::PipelineStageFlagBits::PIPELINE_STAGE_BOTTOM_OF_PIPE, {}, {}, { imageMemBTwo });

				transferBuffer.EndRecording();

				submitInfo[0].commandBufferIDs[0].IRPrimaryID.type = VS::CommandBufferIDType::IR_PRIMARY;
				submitInfo[0].commandBufferIDs[0].IRPrimaryID.commandPoolID = data.commandBufferData->transferPool.value();
				submitInfo[0].commandBufferIDs[0].IRPrimaryID.commandBufferID = data.commandBufferData->transferBuffers[0];

				submitInfo[0].signalSemaphores.resize(1);
				submitInfo[0].signalSemaphores[0] = data.synchronizationData->dataTransferFinishedSemaphores[0];

				transferQfGroup.SubmitBuffers(data.instanceDependentData->transferOnlyQueueIndex.value(), submitInfo, {});
			}

			{
				graphicBuffer.BeginRecording(VS::CommandBufferUsage::ONE_USE);

				graphicBuffer.CreatePipelineBarrier(VS::PipelineStageFlagBits::PIPELINE_STAGE_TRANSFER,
					VS::PipelineStageFlagBits::PIPELINE_STAGE_TRANSFER, {}, {}, { imageMemBTwo });

				imageMemBThree.imageID.texture2D.baseMipLevel = 0;

				graphicBuffer.CreatePipelineBarrier(VS::PipelineStageFlagBits::PIPELINE_STAGE_TRANSFER, VS::PipelineStageFlagBits::PIPELINE_STAGE_TRANSFER,
					{}, {}, { imageMemBThree });

				for (uint32_t i = 1; i < mipLevels; ++i)
				{
					graphicBuffer.BlitDataBetween2DTexturesSimple(texData.textureID, i - 1, texData.textureID, i);

					imageMemBThree.imageID.texture2D.baseMipLevel = i;

					graphicBuffer.CreatePipelineBarrier(VS::PipelineStageFlagBits::PIPELINE_STAGE_TRANSFER, VS::PipelineStageFlagBits::PIPELINE_STAGE_TRANSFER,
						{}, {}, { imageMemBThree });
				}

				graphicBuffer.CreatePipelineBarrier(VS::PipelineStageFlagBits::PIPELINE_STAGE_TRANSFER,
					VS::PipelineStageFlagBits::PIPELINE_STAGE_FRAGMENT_SHADER, {}, {}, { imageMemBFour });

				graphicBuffer.EndRecording();

				submitInfo[0].waitSemaphores.resize(1);
				submitInfo[0].waitSemaphores[0].first = submitInfo[0].signalSemaphores[0];
				submitInfo[0].waitSemaphores[0].second = VS::PipelineStageFlagBits::PIPELINE_STAGE_FRAGMENT_SHADER;

				submitInfo[0].commandBufferIDs[0].IRPrimaryID.type = VS::CommandBufferIDType::IR_PRIMARY;
				submitInfo[0].commandBufferIDs[0].IRPrimaryID.commandPoolID = data.commandBufferData->graphicPool;
				submitInfo[0].commandBufferIDs[0].IRPrimaryID.commandBufferID = data.commandBufferData->graphicBuffers[0];

				submitInfo[0].signalSemaphores.resize(0);

				graphicQfGroup.SubmitBuffers(data.instanceDependentData->graphicsQueueIndex, submitInfo, data.synchronizationData->inFlightFences[0]);
			}
		}
		else
		{
			submitInfo[0].signalSemaphores.resize(0);

			graphicBuffer.BeginRecording(VS::CommandBufferUsage::ONE_USE);

			graphicBuffer.CreatePipelineBarrier(VS::PipelineStageFlagBits::PIPELINE_STAGE_TOP_OF_PIPE, VS::PipelineStageFlagBits::PIPELINE_STAGE_TRANSFER,
				{}, {}, { imageMemBOne });

			graphicBuffer.TransferDataTo2dTextureSimple(stagingBuffer, texData.textureID, 0);

			imageMemBThree.imageID.texture2D.baseMipLevel = 0;

			graphicBuffer.CreatePipelineBarrier(VS::PipelineStageFlagBits::PIPELINE_STAGE_TRANSFER, VS::PipelineStageFlagBits::PIPELINE_STAGE_TRANSFER,
				{}, {}, { imageMemBThree });

			for (uint32_t i = 1; i < mipLevels; ++i)
			{
				graphicBuffer.BlitDataBetween2DTexturesSimple(texData.textureID, i - 1, texData.textureID, i);

				imageMemBThree.imageID.texture2D.baseMipLevel = i;

				graphicBuffer.CreatePipelineBarrier(VS::PipelineStageFlagBits::PIPELINE_STAGE_TRANSFER, VS::PipelineStageFlagBits::PIPELINE_STAGE_TRANSFER,
					{}, {}, { imageMemBThree });
			}

			graphicBuffer.CreatePipelineBarrier(VS::PipelineStageFlagBits::PIPELINE_STAGE_TRANSFER,
				VS::PipelineStageFlagBits::PIPELINE_STAGE_FRAGMENT_SHADER, {}, {}, { imageMemBFour });

			graphicBuffer.EndRecording();

			submitInfo[0].commandBufferIDs[0].IRPrimaryID.type = VS::CommandBufferIDType::IR_PRIMARY;
			submitInfo[0].commandBufferIDs[0].IRPrimaryID.commandPoolID = data.commandBufferData->graphicPool;
			submitInfo[0].commandBufferIDs[0].IRPrimaryID.commandBufferID = data.commandBufferData->graphicBuffers[0];

			graphicQfGroup.SubmitBuffers(data.instanceDependentData->graphicsQueueIndex, submitInfo, data.synchronizationData->inFlightFences[0]);
		}

		if (!synchro.WaitOnFences({ data.synchronizationData->inFlightFences[0] }, false, 1000000000))
			throw std::runtime_error("CreateTextureData Error: Waiting on fence timedout!");

		bufferLists.RemoveStagingBuffer(stagingBuffer, true);
		memoryList.FreeMemory(stagingMemoryAllocation, true, true);
	}

	stbi_image_free(pixels);

	std::vector<VS::DescriptorSetCombined2DTextureSamplerWriteData> textureWriteData;
	textureWriteData.resize(framesInFlight);

	for (size_t i = 0; i < framesInFlight; ++i)
	{
		textureWriteData[i].descriptorSetID = data.descriptorData->descriptorSets[i];
		textureWriteData[i].binding = 1;
		textureWriteData[i].startArrayIndex = 0;

		VS::Optional2DTextureView texViewID = { {texData.textureID, texData.textureImageView} };
		VS::OptionalSampler samplerID = data.deviceDependentData->sampler;
		VS::Combined2DTextureSamplerIDs combinedIDs = { texViewID, samplerID };

		textureWriteData[i].imageDataList.emplace_back(combinedIDs, VS::ImageLayoutFlags::SHADER_READ_ONLY);
	}

	device.GetDescriptorDataLists().WriteNIFDescriptorSetCombined2DTextureSamplerBindings(data.descriptorData->descriptorPool, textureWriteData);
}
