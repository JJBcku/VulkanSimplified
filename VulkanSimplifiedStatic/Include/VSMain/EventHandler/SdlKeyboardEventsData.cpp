#include "SdlEhIpch.h"
#include "SdlKeyboardEventsData.h"

SdlKeysymData::SdlKeysymData(const SDL_Keysym& keyData)
{
	scancode = static_cast<SdlScancode>(keyData.scancode);
	sym = static_cast<SdlKeycode>(keyData.sym);
	mod = keyData.mod;
	padding = 0;
	unused = keyData.unused;
}

SdlKeysymData::~SdlKeysymData()
{
}

SdlKeyboardEventData::SdlKeyboardEventData(const SDL_KeyboardEvent& eventData) : keysym(eventData.keysym)
{
	timestamp = eventData.timestamp;
	windowID = eventData.windowID;
	state = eventData.state;
	repeat = eventData.repeat;
	padding2 = eventData.padding2;
	padding3 = eventData.padding3;
	padding = 0;
}

SdlKeyboardEventData::~SdlKeyboardEventData()
{
}

SdlKeymapChangedEventData::SdlKeymapChangedEventData(const SDL_CommonEvent& eventData)
{
	timestamp = eventData.timestamp;
}

SdlKeymapChangedEventData::~SdlKeymapChangedEventData()
{
}
