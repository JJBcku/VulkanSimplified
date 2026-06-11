#include "SdlEhIpch.h"
#include "../../../../Include/VSMain/EventHandler/SdlWindowEventData.h"

namespace VulkanSimplified
{
	SdlWindowEventData::SdlWindowEventData()
	{
		timestamp = 0;
		reserved = 0;
		windowID = 0;
		subtype = SdlWindowEventSubType::SDL_DATA_WINDOWEVENT_UNSET;
		data1 = 0;
		data2 = 0;
		padding = 0;
	}

	SdlWindowEventData::~SdlWindowEventData()
	{
	}
}
