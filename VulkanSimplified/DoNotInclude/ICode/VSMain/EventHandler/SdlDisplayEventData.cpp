#include "SdlEhIpch.h"
#include "../../../../Include/VSMain/EventHandler/SdlDisplayEventData.h"

namespace VulkanSimplified
{
	SdlDisplayEventData::SdlDisplayEventData()
	{
		timestamp = 0;
		reserved = 0;
		display = 0;
		event = SdlDisplayEventID::SDL_DATA_DISPLAYEVENT_UNSET;
		data1 = 0;
		data2 = 0;
	}

	SdlDisplayEventData::~SdlDisplayEventData()
	{
	}
}
