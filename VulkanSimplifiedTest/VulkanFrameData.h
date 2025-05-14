#pragma once

#include <VSDataBuffersCopyRegionData.h>
#include <VSDataBuffersMemoryBarrierData.h>
#include <VSCommandBufferSubmissionData.h>

struct VulkanFrameData
{
	VulkanSimplified::DataBuffersCopyRegionData vertexCopyRegion;
	VulkanSimplified::DataBuffersCopyRegionData indexCopyRegion;
	VulkanSimplified::DataBuffersCopyRegionData uniformCopyRegion;

	std::vector<std::vector<VulkanSimplified::DataBuffersMemoryBarrierData>> dataBufferMemoryBarrierData;
	std::vector<VulkanSimplified::CommandBufferSubmissionData> submitInfo;

	VulkanFrameData();
};