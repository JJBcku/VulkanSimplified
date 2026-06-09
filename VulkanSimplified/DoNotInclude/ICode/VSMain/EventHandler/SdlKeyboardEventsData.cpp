#include "SdlEhIpch.h"
#include "../../../../Include/VSMain/EventHandler/SdlKeyboardEventsData.h"

namespace VulkanSimplified
{
	SdlKeysymData::SdlKeysymData()
	{
		scancode = static_cast<SdlScancode>(0);
		keycode = static_cast<SdlKeycode>(0);
		mod = 0;
		rawData = 0;
		padding = 0;
	}

	SdlKeysymData::~SdlKeysymData()
	{
	}

	SdlKeyboardEventData::SdlKeyboardEventData() : keysym()
	{
		timestamp = 0;
		reserved = 0;
		windowID = 0;
		keyboardID = 0;
		down = false;
		repeat = false;
		padding = 0;
	}

	SdlKeyboardEventData::~SdlKeyboardEventData()
	{
	}

	SdlKeymapChangedEventData::SdlKeymapChangedEventData()
	{
		reserved = 0;
		timestamp = 0;
	}

	SdlKeymapChangedEventData::~SdlKeymapChangedEventData()
	{
	}

	SdlKeyboardDeviceEvent::SdlKeyboardDeviceEvent()
	{
		type = SdlKeyboardDeviceSubEventType::KEYBOARD_DEVICE_UNSET;
		reserved = 0;
		timestamp = 0;
		keyboardID = 0;
		padding = 0;
	}

	SdlKeyboardDeviceEvent::~SdlKeyboardDeviceEvent()
	{
	}

}
