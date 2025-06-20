#pragma once

#include <VSDataBuffersCopyRegionData.h>
#include <VSDataBuffersMemoryBarrierData.h>
#include <VSCommandBufferSubmissionData.h>

struct VulkanFrameData
{
	VS::DataBuffersCopyRegionData vertexCopyRegion;
	VS::DataBuffersCopyRegionData indexCopyRegion;
	VS::DataBuffersCopyRegionData uniformCopyRegion;

	std::vector<std::vector<VS::DataBuffersMemoryBarrierData>> dataBufferMemoryBarrierData;
	std::vector<VS::CommandBufferSubmissionData> submitInfo;

	VulkanFrameData();
};