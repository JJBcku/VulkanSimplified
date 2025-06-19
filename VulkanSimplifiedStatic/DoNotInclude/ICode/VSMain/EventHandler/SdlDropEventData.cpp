#include "SdlEhIpch.h"
#include "../../../../Include/VSMain/EventHandler/SdlDropEventData.h"

namespace VulkanSimplified
{
	SdlDropEventData::SdlDropEventData()
	{
		type = static_cast<SdlDropEventType>(std::numeric_limits<uint32_t>::max());
		timestamp = 0;
		file = nullptr;
		windowID = 0;
		padding = 0;
	}

	SdlDropEventData::~SdlDropEventData()
	{
	}
}
