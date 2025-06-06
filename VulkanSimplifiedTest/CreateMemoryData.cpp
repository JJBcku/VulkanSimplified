#include "pch.h"
#include "CreateMemoryData.h"

#include "VulkanData.h"
#include "VulkanBasicData.h"
#include "VulkanInstanceDependentData.h"
#include "VulkanRenderPassData.h"
#include "VulkanMemoryData.h"

#include "SwapchainSizes.h"
#include "VertexData.h"

#include <VSMain.h>
#include <VSInstance.h>
#include <VSDeviceMain.h>

#include <VSDataBufferLists.h>
#include <VSImageDataLists.h>
#include <VSMemoryObjectsList.h>
#include <VSMultitypeImagesID.h>

#include <VSImageUsageFlags.h>
#include <VSMemoryTypeProperties.h>
#include <VSMemorySizeDef.h>
#include <VSIndexType.h>

void CreateMemoryData(VulkanData& data)
{
	auto device = data.basicData->vsmain->GetInstance().GetChoosenDevicesMainClass();
	auto imageList = device.GetImageDataLists();
	auto memoryList = device.GetMemoryObjectsList();

	auto format = data.instanceDependentData->supportedFormat;

	data.memoryData = std::make_unique<VulkanMemoryData>();
	auto& memData = *data.memoryData;
	
	memData.colorRenderTargetImages.reserve(framesInFlight);
	memData.colorRenderTargetImageViews.reserve(framesInFlight);
	memData.framebuffers.reserve(framesInFlight);

	for (size_t i = 0; i < framesInFlight; ++i)
	{
		memData.colorRenderTargetImages.push_back(imageList.AddColorRenderTargetImage(width, height, format, {}, false, 1, framesInFlight));
	}

	VulkanSimplified::MemorySize allocationSize = imageList.GetColorRenderTargetImagesSize(memData.colorRenderTargetImages.back()) * framesInFlight;
	uint32_t memoryTypeMask = imageList.GetColorRenderTargetImagesMemoryTypeMask(memData.colorRenderTargetImages.back());

	std::vector<VulkanSimplified::MemoryTypeProperties> acceptableMemoryTypes;
	acceptableMemoryTypes.reserve(7);
	acceptableMemoryTypes.push_back(VulkanSimplified::DEVICE_LOCAL);
	acceptableMemoryTypes.push_back(VulkanSimplified::DEVICE_LOCAL | VulkanSimplified::HOST_VISIBLE | VulkanSimplified::HOST_CACHED);
	acceptableMemoryTypes.push_back(VulkanSimplified::DEVICE_LOCAL | VulkanSimplified::HOST_COHERENT | VulkanSimplified::HOST_VISIBLE | VulkanSimplified::HOST_CACHED);
	acceptableMemoryTypes.push_back(VulkanSimplified::DEVICE_LOCAL | VulkanSimplified::HOST_COHERENT | VulkanSimplified::HOST_VISIBLE);
	acceptableMemoryTypes.push_back(VulkanSimplified::HOST_VISIBLE | VulkanSimplified::HOST_CACHED);
	acceptableMemoryTypes.push_back(VulkanSimplified::HOST_COHERENT | VulkanSimplified::HOST_VISIBLE | VulkanSimplified::HOST_CACHED);
	acceptableMemoryTypes.push_back(VulkanSimplified::HOST_COHERENT | VulkanSimplified::HOST_VISIBLE);

	memData.imageMemoryAllocation = memoryList.AllocateMemory(allocationSize, framesInFlight, acceptableMemoryTypes, memoryTypeMask, 4);

	size_t stagingBufferSize = 0;

	for (size_t i = 0; i < framesInFlight; ++i)
	{
		imageList.BindColorRenderTargetImage(memData.colorRenderTargetImages[i], memData.imageMemoryAllocation);
		memData.colorRenderTargetImageViews.push_back(imageList.AddColorRenderTargetImageView(memData.colorRenderTargetImages[i]));

		std::vector<std::pair<VulkanSimplified::MultitypeImagesID, IDObject<VulkanSimplifiedInternal::AutoCleanupImageView>>> attachments;
		attachments.resize(1);

		attachments[0].first = memData.colorRenderTargetImages[i];
		attachments[0].second = memData.colorRenderTargetImageViews[i];

		memData.framebuffers.push_back(imageList.AddFramebuffer(data.renderPassData->renderPass, attachments, width, height, 1));
	}

	auto bufferLists = device.GetDataBufferLists();

	memData.vertexBuffers.reserve(framesInFlight);
	memData.indexBuffers.reserve(framesInFlight);
	memData.stagingBuffers.reserve(framesInFlight);
	for (size_t i = 0; i < framesInFlight; ++i)
	{
		memData.vertexBuffers.push_back(bufferLists.AddVertexBuffer(vertices.size() * sizeof(vertices[0]), {}, framesInFlight));
		memData.indexBuffers.push_back(bufferLists.AddIndexBuffer(indices.size(), VulkanSimplified::IndexType::INDEX_TYPE_16_BITS, {}, framesInFlight));
		memData.uniformBuffers.push_back(bufferLists.AddUniformBuffer(sizeof(UniformBufferData), {}, framesInFlight));
	}

	allocationSize = bufferLists.GetVertexBuffersSize(memData.vertexBuffers.back()) * framesInFlight;
	memoryTypeMask = bufferLists.GetVertexBuffersMemoryTypeMask(memData.vertexBuffers.back());

	memData.vertexMemoryAllocation = memoryList.AllocateMemory(allocationSize, framesInFlight, acceptableMemoryTypes, memoryTypeMask, 8);
	memData.vertexMemoryMapped = memoryList.IsMemoryMapped(memData.vertexMemoryAllocation);

	if (!memData.vertexMemoryMapped)
		stagingBufferSize += bufferLists.GetVertexBuffersSize(memData.vertexBuffers.back());

	allocationSize = bufferLists.GetIndexBuffersSize(memData.indexBuffers.back()) * framesInFlight;
	memoryTypeMask = bufferLists.GetIndexBuffersMemoryTypeMask(memData.indexBuffers.back());

	memData.indexMemoryAllocation = memoryList.AllocateMemory(allocationSize, framesInFlight, acceptableMemoryTypes, memoryTypeMask, 8);
	memData.indexMemoryMapped = memoryList.IsMemoryMapped(memData.indexMemoryAllocation);

	if (!memData.indexMemoryMapped)
		stagingBufferSize += bufferLists.GetIndexBuffersSize(memData.indexBuffers.back());

	acceptableMemoryTypes.clear();
	acceptableMemoryTypes.push_back(VulkanSimplified::DEVICE_LOCAL | VulkanSimplified::HOST_VISIBLE | VulkanSimplified::HOST_CACHED);
	acceptableMemoryTypes.push_back(VulkanSimplified::DEVICE_LOCAL | VulkanSimplified::HOST_COHERENT | VulkanSimplified::HOST_VISIBLE | VulkanSimplified::HOST_CACHED);
	acceptableMemoryTypes.push_back(VulkanSimplified::DEVICE_LOCAL | VulkanSimplified::HOST_COHERENT | VulkanSimplified::HOST_VISIBLE);
	acceptableMemoryTypes.push_back(VulkanSimplified::HOST_VISIBLE | VulkanSimplified::HOST_CACHED);
	acceptableMemoryTypes.push_back(VulkanSimplified::HOST_COHERENT | VulkanSimplified::HOST_VISIBLE | VulkanSimplified::HOST_CACHED);
	acceptableMemoryTypes.push_back(VulkanSimplified::HOST_COHERENT | VulkanSimplified::HOST_VISIBLE);
	acceptableMemoryTypes.push_back(VulkanSimplified::DEVICE_LOCAL);

	allocationSize = bufferLists.GetUniformBuffersSize(memData.uniformBuffers.back()) * framesInFlight;
	memoryTypeMask = bufferLists.GetUniformBuffersMemoryTypeMask(memData.uniformBuffers.back());

	memData.uniformMemoryAllocation = memoryList.AllocateMemory(allocationSize, framesInFlight, acceptableMemoryTypes, memoryTypeMask, 8);
	memData.uniformMemoryMapped = memoryList.IsMemoryMapped(memData.uniformMemoryAllocation);

	if (!memData.uniformMemoryMapped)
		stagingBufferSize += bufferLists.GetUniformBuffersSize(memData.uniformBuffers.back());

	if (stagingBufferSize > 0)
	{
		for (size_t i = 0; i < framesInFlight; ++i)
		{
			memData.stagingBuffers.push_back(bufferLists.AddStagingBuffer(stagingBufferSize, {}, framesInFlight));
		}

		acceptableMemoryTypes.clear();
		acceptableMemoryTypes.push_back(VulkanSimplified::DEVICE_LOCAL | VulkanSimplified::HOST_COHERENT | VulkanSimplified::HOST_VISIBLE | VulkanSimplified::HOST_CACHED);
		acceptableMemoryTypes.push_back(VulkanSimplified::DEVICE_LOCAL | VulkanSimplified::HOST_COHERENT | VulkanSimplified::HOST_VISIBLE);
		acceptableMemoryTypes.push_back(VulkanSimplified::HOST_VISIBLE | VulkanSimplified::HOST_CACHED);
		acceptableMemoryTypes.push_back(VulkanSimplified::HOST_COHERENT | VulkanSimplified::HOST_VISIBLE | VulkanSimplified::HOST_CACHED);
		acceptableMemoryTypes.push_back(VulkanSimplified::HOST_COHERENT | VulkanSimplified::HOST_VISIBLE);

		allocationSize = bufferLists.GetStagingBuffersSize(memData.stagingBuffers.back()) * framesInFlight;
		memoryTypeMask = bufferLists.GetStagingBuffersMemoryTypeMask(memData.stagingBuffers.back());

		memData.stagingMemoryAllocation = memoryList.AllocateMemory(allocationSize, framesInFlight, acceptableMemoryTypes, memoryTypeMask, 8);
	}

	for (size_t i = 0; i < framesInFlight; ++i)
	{
		bufferLists.BindVertexBuffer(memData.vertexBuffers[i], memData.vertexMemoryAllocation, framesInFlight);
		bufferLists.BindIndexBuffer(memData.indexBuffers[i], memData.indexMemoryAllocation, framesInFlight);
		bufferLists.BindUniformBuffer(memData.uniformBuffers[i], memData.uniformMemoryAllocation, framesInFlight);
	}

	if (stagingBufferSize > 0)
	{
		for (size_t i = 0; i < framesInFlight; ++i)
		{
			bufferLists.BindStagingBuffer(memData.stagingBuffers[i], memData.stagingMemoryAllocation, framesInFlight);
		}
	}
}
