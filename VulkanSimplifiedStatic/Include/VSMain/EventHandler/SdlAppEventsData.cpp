#include "SdlEhIpch.h"
#include "SdlAppEventsData.h"

SdlAppTerminatingEventData::SdlAppTerminatingEventData(const SDL_CommonEvent& eventData)
{
	timestamp = eventData.timestamp;
}

SdlAppTerminatingEventData::~SdlAppTerminatingEventData()
{
}

SdlAppLowMemoryEventData::SdlAppLowMemoryEventData(const SDL_CommonEvent& eventData)
{
	timestamp = eventData.timestamp;
}

SdlAppLowMemoryEventData::~SdlAppLowMemoryEventData()
{
}

SdlAppWillEnterBackgroundEventData::SdlAppWillEnterBackgroundEventData(const SDL_CommonEvent& eventData)
{
	timestamp = eventData.timestamp;
}

SdlAppWillEnterBackgroundEventData::~SdlAppWillEnterBackgroundEventData()
{
}

SdlAppDidEnterBackgroundEventData::SdlAppDidEnterBackgroundEventData(const SDL_CommonEvent& eventData)
{
	timestamp = eventData.timestamp;
}

SdlAppDidEnterBackgroundEventData::~SdlAppDidEnterBackgroundEventData()
{
}

SdlAppWillEnterForegroundEventData::SdlAppWillEnterForegroundEventData(const SDL_CommonEvent& eventData)
{
	timestamp = eventData.timestamp;
}

SdlAppWillEnterForegroundEventData::~SdlAppWillEnterForegroundEventData()
{
}

SdlAppDidEnterForegroundEventData::SdlAppDidEnterForegroundEventData(const SDL_CommonEvent& eventData)
{
	timestamp = eventData.timestamp;
}

SdlAppDidEnterForegroundEventData::~SdlAppDidEnterForegroundEventData()
{
}