#pragma once

#include "EventHandler/SdlEventHandlerInitData.h"
#include "../VSCommon/VulkanVersionData.h"

#include <string>

namespace VulkanSimplified
{
	struct VSMainInitData
	{
		std::string appName;
		std::string appVariantName;
		VulkanVersionData appVersion;
		std::string engineName;
		VulkanVersionData engineVersion;

		SdlEventHandlerInitData eventHandlerData;

		VSMainInitData();
		~VSMainInitData();
	};
}
