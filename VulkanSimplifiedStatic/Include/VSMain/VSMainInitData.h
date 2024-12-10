#pragma once

#include "EventHandler/SdlEventHandlerInitData.h"

namespace VulkanSimplified
{
	struct VSMainInitData
	{
		SdlEventHandlerInitData eventHandlerData;
		uint64_t stump;

		VSMainInitData();
		~VSMainInitData();
	};
}
