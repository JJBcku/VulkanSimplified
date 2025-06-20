#include "SdlEhIpch.h"
#include "../../../../Include/VSMain/EventHandler/SdlKeyboardEventsData.h"

namespace VulkanSimplified
{
	SdlKeysymData::SdlKeysymData()
	{
		scancode = static_cast<SdlScancode>(0);
		sym = static_cast<SdlKeycode>(0);
		mod = 0;
		padding = 0;
		unused = 0;
	}

	SdlKeysymData::~SdlKeysymData()
	{
	}

	SdlKeyboardEventData::SdlKeyboardEventData()
	{
		timestamp = 0;
		windowID = 0;
		state = 0;
		repeat = 0;
		padding2 = 0;
		padding3 = 0;
		padding = 0;
	}

	SdlKeyboardEventData::~SdlKeyboardEventData()
	{
	}

	SdlKeymapChangedEventData::SdlKeymapChangedEventData()
	{
		timestamp = 0;
	}

	SdlKeymapChangedEventData::~SdlKeymapChangedEventData()
	{
	}
}
