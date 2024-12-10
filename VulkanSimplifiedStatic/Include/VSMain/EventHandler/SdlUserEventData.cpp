#include "SdlEhIpch.h"
#include "SdlUserEventData.h"

SdlUserEventData::SdlUserEventData(const SDL_UserEvent& eventData)
{
	timestamp = eventData.timestamp;
	windowID = eventData.windowID;
	code = eventData.code;
	padding = 0;
	data1 = eventData.data1;
	data2 = eventData.data2;
}

SdlUserEventData::~SdlUserEventData()
{
}
