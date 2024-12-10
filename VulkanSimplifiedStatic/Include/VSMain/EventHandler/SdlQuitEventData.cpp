#include "SdlEhIpch.h"
#include "SdlQuitEventData.h"

SdlQuitEventData::SdlQuitEventData(const SDL_QuitEvent& eventData)
{
	timestamp = eventData.timestamp;
}

SdlQuitEventData::~SdlQuitEventData()
{
}
