#include "VSDeviceIpch.h"
#include "VSDescriptorSetCombined2DTextureSamplerWriteData.h"

namespace VulkanSimplified
{
	DescriptorSetCombined2DTextureSamplerWriteData::DescriptorSetCombined2DTextureSamplerWriteData()
	{
		binding = std::numeric_limits<uint32_t>::max();
		startArrayIndex = std::numeric_limits<uint32_t>::max();
	}
}