#pragma once

#include "EventHandler/SdlEventHandlerInitData.h"
#include "../VSSharedData/VSSharedDataListsCapacities.h"

#include "../VSCommon/VSVersionData.h"

#include <string>

namespace VulkanSimplified
{
	struct MainInitData
	{
		std::string appName;
		std::string appVariantName;
		VersionData appVersion;
		std::string engineName;
		VersionData engineVersion;

		SdlEventHandlerInitData eventHandlerData;
		SharedDataListsCapacities sharedDataCapabilities;

		MainInitData();
		~MainInitData();
	};
}
