#include "SdlEhIpch.h"
#include "SdlLocaleChangedEventData.h"

SdlLocaleChangeEventData::SdlLocaleChangeEventData(const SDL_CommonEvent& eventData)
{
	timestamp = eventData.timestamp;
}

SdlLocaleChangeEventData::~SdlLocaleChangeEventData()
{
}
