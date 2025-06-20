#pragma once

#include "../../../Include/VSCommon/VSMemorySizeDef.h"

namespace VulkanSimplified
{
	struct SuballocationInternalData
	{
		MemorySize beggining;
		MemorySize size;

		SuballocationInternalData();
	};
}