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
#include <VSImageSampleFlags.h>
#include <VSMemoryTypeProperties.h>
#include <VSMemorySizeDef.h>
#include <VSIndexType.h>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tinyobjloader/tiny_obj_loader.h>

void LoadModel()
{
	tinyobj::attrib_t attrib{};
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn, err;

	std::string filename = "Models\\Model.obj.txt";

	if (tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename.c_str()) != true)
		throw std::runtime_error(warn + err);

	size_t totalIndices = 0;

	for (const auto& shape : shapes)
		totalIndices += shape.mesh.indices.size();

	indices.reserve(totalIndices);
	vertices.reserve(totalIndices);

	for (const auto& shape : shapes)
	{
		for (const auto& index : shape.mesh.indices)
		{
			VertexData add{};

			add.position = {
			attrib.vertices[3 * index.vertex_index + 0],
			attrib.vertices[3 * index.vertex_index + 1],
			attrib.vertices[3 * index.vertex_index + 2],
			1.0f };

			add.textureCoordinates = {
				attrib.texcoords[2 * index.texcoord_index + 0],
				1.0f - attrib.texcoords[2 * index.texcoord_index + 1] };

			bool found = false;

			for (size_t i = 0; i < vertices.size(); ++i)
			{
				if (vertices[i] == add)
				{
					found = true;
					indices.push_back(static_cast<uint16_t>(i));
					break;
				}
			}

			if (!found)
			{
				indices.push_back(static_cast<uint16_t>(vertices.size()));
				vertices.push_back(add);
			}
		}
	}

}

void CreateMemoryData(VulkanData& data)
{
	auto device = data.basicData->vsmain->GetInstance().GetChoosenDevicesMainClass();
	auto imageList = device.GetImageDataLists();
	auto memoryList = device.GetMemoryObjectsList();

	data.memoryData = std::make_unique<VulkanMemoryData>();
	auto& memData = *data.memoryData;
	
	memData.colorRenderTargetImages.reserve(framesInFlight);
	memData.colorRenderTargetImageViews.reserve(framesInFlight);
	memData.depthRenderTargetImages.reserve(framesInFlight);
	memData.depthRenderTargetImageViews.reserve(framesInFlight);
	memData.framebuffers.reserve(framesInFlight);

	using VS::ImageSampleFlagBits;
	if (data.instanceDependentData->maxSamples != ImageSampleFlagBits::SAMPLE_1)
	{
		memData.resolveRenderTargetImages.reserve(framesInFlight);
		memData.resolveRenderTargetImageViews.reserve(framesInFlight);
	}

	for (size_t i = 0; i < framesInFlight; ++i)
	{
		memData.colorRenderTargetImages.push_back(imageList.AddColorRenderTargetImage(swapchainWidth, swapchainHeight, data.instanceDependentData->supportedColorFormat,
			data.instanceDependentData->maxSamples, {}, false, 1, framesInFlight));
		memData.depthRenderTargetImages.push_back(imageList.AddDepthStencilRenderTargetImage(swapchainWidth, swapchainHeight, data.instanceDependentData->supportedDepthFormat,
			data.instanceDependentData->maxSamples, {}, false, 1, framesInFlight));

		if (data.instanceDependentData->maxSamples != ImageSampleFlagBits::SAMPLE_1)
		{
			memData.resolveRenderTargetImages.push_back(imageList.AddResolveRenderTargetImage(swapchainWidth, swapchainHeight, data.instanceDependentData->supportedColorFormat,
				{}, false, 1, framesInFlight));
		}
	}

	VS::MemorySize allocationSize = imageList.GetColorRenderTargetImagesSize(memData.colorRenderTargetImages.back());
	allocationSize += imageList.GetDepthStencilRenderTargetImagesSize(memData.depthRenderTargetImages.back());
	if (data.instanceDependentData->maxSamples != ImageSampleFlagBits::SAMPLE_1)
		allocationSize += imageList.GetResolveRenderTargetImagesSize(memData.resolveRenderTargetImages.back());
	allocationSize *= framesInFlight;
	uint32_t memoryTypeMask = imageList.GetColorRenderTargetImagesMemoryTypeMask(memData.colorRenderTargetImages.back());

	std::vector<VS::MemoryTypeProperties> acceptableMemoryTypes;
	acceptableMemoryTypes.reserve(7);
	acceptableMemoryTypes.push_back(VS::DEVICE_LOCAL);
	acceptableMemoryTypes.push_back(VS::DEVICE_LOCAL | VS::HOST_VISIBLE | VS::HOST_CACHED);
	acceptableMemoryTypes.push_back(VS::DEVICE_LOCAL | VS::HOST_COHERENT | VS::HOST_VISIBLE | VS::HOST_CACHED);
	acceptableMemoryTypes.push_back(VS::DEVICE_LOCAL | VS::HOST_COHERENT | VS::HOST_VISIBLE);
	acceptableMemoryTypes.push_back(VS::HOST_VISIBLE | VS::HOST_CACHED);
	acceptableMemoryTypes.push_back(VS::HOST_COHERENT | VS::HOST_VISIBLE | VS::HOST_CACHED);
	acceptableMemoryTypes.push_back(VS::HOST_COHERENT | VS::HOST_VISIBLE);

	memData.imageMemoryAllocation = memoryList.AllocateMemory(allocationSize, framesInFlight, acceptableMemoryTypes, memoryTypeMask, 4);

	size_t stagingBufferSize = 0;

	for (size_t i = 0; i < framesInFlight; ++i)
	{
		imageList.BindColorRenderTargetImage(memData.colorRenderTargetImages[i], memData.imageMemoryAllocation);
		memData.colorRenderTargetImageViews.push_back(imageList.AddColorRenderTargetImageView(memData.colorRenderTargetImages[i]));

		imageList.BindDepthStencilRenderTargetImage(memData.depthRenderTargetImages[i], memData.imageMemoryAllocation);
		memData.depthRenderTargetImageViews.push_back(imageList.AddDepthStencilRenderTargetImageView(memData.depthRenderTargetImages[i]));

		if (data.instanceDependentData->maxSamples != ImageSampleFlagBits::SAMPLE_1)
		{
			imageList.BindResolveRenderTargetImage(memData.resolveRenderTargetImages[i], memData.imageMemoryAllocation);
			memData.resolveRenderTargetImageViews.push_back(imageList.AddResolveRenderTargetImageView(memData.resolveRenderTargetImages[i]));
		}

		std::vector<std::pair<VS::RenderTargetImagesID, IDObject<VS::AutoCleanupImageView>>> attachments;
		
		if (data.instanceDependentData->maxSamples != ImageSampleFlagBits::SAMPLE_1)
		{
			attachments.resize(3);
		}
		else
		{
			attachments.resize(2);
		}

		attachments[0].first = memData.colorRenderTargetImages[i];
		attachments[0].second = memData.colorRenderTargetImageViews[i];
		attachments[1].first = memData.depthRenderTargetImages[i];
		attachments[1].second = memData.depthRenderTargetImageViews[i];

		if (data.instanceDependentData->maxSamples != ImageSampleFlagBits::SAMPLE_1)
		{
			attachments[2].first = memData.resolveRenderTargetImages[i];
			attachments[2].second = memData.resolveRenderTargetImageViews[i];
		}

		memData.framebuffers.push_back(imageList.AddFramebuffer(data.renderPassData->renderPass, attachments, swapchainWidth, swapchainHeight, 1));
	}

	LoadModel();

	auto bufferLists = device.GetDataBufferLists();

	memData.vertexBuffers.reserve(framesInFlight);
	memData.indexBuffers.reserve(framesInFlight);
	memData.stagingBuffers.reserve(framesInFlight);
	for (size_t i = 0; i < framesInFlight; ++i)
	{
		memData.vertexBuffers.push_back(bufferLists.AddVertexBuffer(vertices.size() * sizeof(vertices[0]), {}, framesInFlight));
		memData.indexBuffers.push_back(bufferLists.AddIndexBuffer(indices.size(), VS::IndexType::INDEX_TYPE_16_BITS, {}, framesInFlight));
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
	acceptableMemoryTypes.push_back(VS::DEVICE_LOCAL | VS::HOST_VISIBLE | VS::HOST_CACHED);
	acceptableMemoryTypes.push_back(VS::DEVICE_LOCAL | VS::HOST_COHERENT | VS::HOST_VISIBLE | VS::HOST_CACHED);
	acceptableMemoryTypes.push_back(VS::DEVICE_LOCAL | VS::HOST_COHERENT | VS::HOST_VISIBLE);
	acceptableMemoryTypes.push_back(VS::HOST_VISIBLE | VS::HOST_CACHED);
	acceptableMemoryTypes.push_back(VS::HOST_COHERENT | VS::HOST_VISIBLE | VS::HOST_CACHED);
	acceptableMemoryTypes.push_back(VS::HOST_COHERENT | VS::HOST_VISIBLE);
	acceptableMemoryTypes.push_back(VS::DEVICE_LOCAL);

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
		acceptableMemoryTypes.push_back(VS::DEVICE_LOCAL | VS::HOST_COHERENT | VS::HOST_VISIBLE | VS::HOST_CACHED);
		acceptableMemoryTypes.push_back(VS::DEVICE_LOCAL | VS::HOST_COHERENT | VS::HOST_VISIBLE);
		acceptableMemoryTypes.push_back(VS::HOST_VISIBLE | VS::HOST_CACHED);
		acceptableMemoryTypes.push_back(VS::HOST_COHERENT | VS::HOST_VISIBLE | VS::HOST_CACHED);
		acceptableMemoryTypes.push_back(VS::HOST_COHERENT | VS::HOST_VISIBLE);

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
