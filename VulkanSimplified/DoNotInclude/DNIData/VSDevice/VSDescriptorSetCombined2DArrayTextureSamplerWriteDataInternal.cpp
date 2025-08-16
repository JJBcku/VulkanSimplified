#include "VSDeviceDNIpch.h"
#include "VSDescriptorSetCombined2DArrayTextureSamplerWriteDataInternal.h"

namespace VulkanSimplified
{
	DescriptorSetCombined2DArrayTextureSamplerWriteDataInternal::DescriptorSetCombined2DArrayTextureSamplerWriteDataInternal()
	{
		binding = std::numeric_limits<uint32_t>::max();
		startArrayIndex = std::numeric_limits<uint32_t>::max();
	}
}