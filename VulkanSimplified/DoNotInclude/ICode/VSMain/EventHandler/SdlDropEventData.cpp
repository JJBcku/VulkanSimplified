#include "SdlEhIpch.h"
#include "../../../../Include/VSMain/EventHandler/SdlDropEventData.h"

namespace VulkanSimplified
{
	SdlDropEventData::SdlDropEventData()
	{
		type = static_cast<SdlDropEventType>(std::numeric_limits<uint32_t>::max());
		reserved = 0;
		timestamp = 0;
		windowID = 0;
		padding = 0;
		x = 0.0f;
		y = 0.0f;
		source = nullptr;
		data = nullptr;
	}

	SdlDropEventData::~SdlDropEventData()
	{
	}
}
