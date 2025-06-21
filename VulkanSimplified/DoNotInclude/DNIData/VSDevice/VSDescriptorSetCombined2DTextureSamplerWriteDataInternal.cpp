#include "VSDeviceNIpch.h"
#include "VSDescriptorSetCombined2DTextureSamplerWriteDataInternal.h"

namespace VulkanSimplified
{
	DescriptorSetCombined2DTextureSamplerWriteDataInternal::DescriptorSetCombined2DTextureSamplerWriteDataInternal()
	{
		binding = std::numeric_limits<uint32_t>::max();
		startArrayIndex = std::numeric_limits<uint32_t>::max();
	}
}