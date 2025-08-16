#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSDescriptorSetCombined2DArrayTextureSamplerWriteData.h"

namespace VulkanSimplified
{
	DescriptorSetCombined2DArrayTextureSamplerWriteData::DescriptorSetCombined2DArrayTextureSamplerWriteData()
	{
		binding = std::numeric_limits<uint32_t>::max();
		startArrayIndex = std::numeric_limits<uint32_t>::max();
	}
}