#include "SdlEhIpch.h"
#include "SdlClipboardEventData.h"

SdlClipboardEventData::SdlClipboardEventData(const SDL_CommonEvent& eventData)
{
	timestamp = eventData.timestamp;
}

SdlClipboardEventData::~SdlClipboardEventData()
{
}