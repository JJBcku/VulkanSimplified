#include "pch.h"
#include "CreateFrameData.h"

#include "VulkanData.h"
#include "VulkanFrameData.h"
#include "VulkanInstanceDependentData.h"
#include "VulkanMemoryData.h"

#include "VertexData.h"
#include "SwapchainSizes.h"

#include "VSAccessFlags.h"

#include <VSDataBuffersMemoryBarrierData.h>

void CreateFrameData(VulkanData& data)
{
	data.frameData = std::make_unique<VulkanFrameData>();

	data.frameData->vertexCopyRegion.srcOffset = 0;
	data.frameData->vertexCopyRegion.dstOffset = 0;
	data.frameData->vertexCopyRegion.writeSize = vertices.size() * sizeof(vertices[0]);

	data.frameData->indexCopyRegion.srcOffset = data.frameData->vertexCopyRegion.writeSize;
	data.frameData->indexCopyRegion.dstOffset = 0;
	data.frameData->indexCopyRegion.writeSize = indices.size() * sizeof(indices[0]);

	data.frameData->uniformCopyRegion.srcOffset = data.frameData->indexCopyRegion.srcOffset + data.frameData->indexCopyRegion.writeSize;
	data.frameData->uniformCopyRegion.dstOffset = 0;
	data.frameData->uniformCopyRegion.writeSize = sizeof(UniformBufferData);

	std::vector<std::vector<VulkanSimplified::DataBuffersMemoryBarrierData>>& dataBufferMemoryBarrierData = data.frameData->dataBufferMemoryBarrierData;
	dataBufferMemoryBarrierData.resize(framesInFlight);

	for (size_t i = 0; i < framesInFlight; ++i)
	{
		dataBufferMemoryBarrierData[i].reserve(3);

		size_t j = 0;

		if (!data.memoryData->vertexMemoryMapped)
		{
			dataBufferMemoryBarrierData[i].emplace_back();

			dataBufferMemoryBarrierData[i][j].srcAccess = VulkanSimplified::AccessFlagBits::ACCESS_MEMORY_WRITE;
			dataBufferMemoryBarrierData[i][j].dstAccess = VulkanSimplified::AccessFlagBits::ACCESS_MEMORY_READ;
			dataBufferMemoryBarrierData[i][j].queueData = { data.instanceDependentData->transferOnlyQueueIndex.value(), data.instanceDependentData->graphicsQueueIndex };
			dataBufferMemoryBarrierData[i][j].bufferID = { data.memoryData->vertexBuffers[i] };

			j++;
		}

		if (!data.memoryData->indexMemoryMapped)
		{
			dataBufferMemoryBarrierData[i].emplace_back();

			dataBufferMemoryBarrierData[i][j].srcAccess = VulkanSimplified::AccessFlagBits::ACCESS_MEMORY_WRITE;
			dataBufferMemoryBarrierData[i][j].dstAccess = VulkanSimplified::AccessFlagBits::ACCESS_MEMORY_READ;
			dataBufferMemoryBarrierData[i][j].queueData = { data.instanceDependentData->transferOnlyQueueIndex.value(), data.instanceDependentData->graphicsQueueIndex };
			dataBufferMemoryBarrierData[i][j].bufferID = { data.memoryData->indexBuffers[i] };

			j++;
		}

		if (!data.memoryData->uniformMemoryMapped)
		{
			dataBufferMemoryBarrierData[i].emplace_back();

			dataBufferMemoryBarrierData[i][j].srcAccess = VulkanSimplified::AccessFlagBits::ACCESS_MEMORY_WRITE;
			dataBufferMemoryBarrierData[i][j].dstAccess = VulkanSimplified::AccessFlagBits::ACCESS_MEMORY_READ;
			dataBufferMemoryBarrierData[i][j].queueData = { data.instanceDependentData->transferOnlyQueueIndex.value(), data.instanceDependentData->graphicsQueueIndex };
			dataBufferMemoryBarrierData[i][j].bufferID = { data.memoryData->uniformBuffers[i] };

			j++;
		}
	}

	std::vector<VulkanSimplified::CommandBufferSubmissionData>& submitInfo = data.frameData->submitInfo;

	submitInfo.resize(1);
	submitInfo[0].waitSemaphores.reserve(4);
	submitInfo[0].signalSemaphores.reserve(4);
	submitInfo[0].commandBufferIDs.reserve(4);
}
