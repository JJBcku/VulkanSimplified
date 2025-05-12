#include "pch.h"
#include "CreateFrameData.h"

#include "VulkanData.h"
#include "VulkanFrameData.h"
#include "VulkanInstanceDependentData.h"
#include "VulkanMemoryData.h"

#include "VertexData.h"
#include "SwapchainSizes.h"

#include "VSAccessFlags.h"

void CreateFrameData(VulkanData& data)
{
	data.frameData = std::make_unique<VulkanFrameData>();

	data.frameData->vertexCopyRegion.srcOffset = 0;
	data.frameData->vertexCopyRegion.dstOffset = 0;
	data.frameData->vertexCopyRegion.writeSize = vertices.size() * sizeof(vertices[0]);

	data.frameData->indexCopyRegion.srcOffset = vertices.size() * sizeof(vertices[0]);
	data.frameData->indexCopyRegion.dstOffset = 0;
	data.frameData->indexCopyRegion.writeSize = indices.size() * sizeof(indices[0]);

	std::vector<std::vector<VulkanSimplified::DataBuffersMemoryBarrierData>>& dataBufferMemoryBarrierData = data.frameData->dataBufferMemoryBarrierData;
	dataBufferMemoryBarrierData.resize(framesInFlight);

	for (size_t i = 0; i < framesInFlight; ++i)
	{
		dataBufferMemoryBarrierData[i].resize(2);

		dataBufferMemoryBarrierData[i][0].srcAccess = VulkanSimplified::AccessFlagBits::ACCESS_MEMORY_WRITE;
		dataBufferMemoryBarrierData[i][0].dstAccess = VulkanSimplified::AccessFlagBits::ACCESS_MEMORY_READ;
		dataBufferMemoryBarrierData[i][0].queueData = { data.instanceDependentData->transferOnlyQueueIndex.value(), data.instanceDependentData->graphicsQueueIndex };
		dataBufferMemoryBarrierData[i][0].bufferID = { data.memoryData->vertexBuffers[i] };

		dataBufferMemoryBarrierData[i][1].srcAccess = VulkanSimplified::AccessFlagBits::ACCESS_MEMORY_WRITE;
		dataBufferMemoryBarrierData[i][1].dstAccess = VulkanSimplified::AccessFlagBits::ACCESS_MEMORY_READ;
		dataBufferMemoryBarrierData[i][1].queueData = { data.instanceDependentData->transferOnlyQueueIndex.value(), data.instanceDependentData->graphicsQueueIndex };
		dataBufferMemoryBarrierData[i][1].bufferID = { data.memoryData->indexBuffers[i] };
	}

	std::vector<VulkanSimplified::CommandBufferSubmissionData>& submitInfo = data.frameData->submitInfo;

	submitInfo.resize(1);
	submitInfo[0].waitSemaphores.reserve(4);
	submitInfo[0].signalSemaphores.reserve(4);
	submitInfo[0].commandBufferIDs.reserve(4);
}
