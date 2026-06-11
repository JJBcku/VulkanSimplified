#include "SdlEhIpch.h"
#include "../../../../Include/VSMain/EventHandler/SdlDropEventData.h"

namespace VulkanSimplified
{
	SdlDropEventData::SdlDropEventData()
	{
		subtype = SdlDropEventType::DROPEVENT_UNSET;
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
