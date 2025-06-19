#include "VSDeviceNIpch.h"
#include "../../DNIHeaders/VSDevice/VSDescriptorSetCombined2DTextureSamplerWriteDataInternal.h"

namespace VulkanSimplifiedInternal
{
	DescriptorSetCombined2DTextureSamplerWriteDataInternal::DescriptorSetCombined2DTextureSamplerWriteDataInternal()
	{
		binding = std::numeric_limits<uint32_t>::max();
		startArrayIndex = std::numeric_limits<uint32_t>::max();
	}
}