#pragma once

#include "../../../Include/VSCommon/VSMemorySizeDef.h"

namespace VulkanSimplifiedInternal
{
	struct SuballocationInternalData
	{
		VulkanSimplified::MemorySize beggining;
		VulkanSimplified::MemorySize size;

		SuballocationInternalData();
	};
}