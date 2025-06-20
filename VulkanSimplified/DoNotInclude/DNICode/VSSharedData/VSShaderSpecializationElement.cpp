#include "VSSharedNIpch.h"
#include "../../DNIHeaders/VSSharedData/VSShaderSpecializationElement.h"

namespace VulkanSimplified
{
	ShaderSpecializationElement::ShaderSpecializationElement()
	{
		ID = std::numeric_limits<uint32_t>::max();
		offset = std::numeric_limits<uint32_t>::max();
		size = std::numeric_limits<size_t>::max();
	}

}
