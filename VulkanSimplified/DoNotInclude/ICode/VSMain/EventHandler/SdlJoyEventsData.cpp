#include "SdlEhIpch.h"
#include "../../../../Include/VSMain/EventHandler/SdlJoyEventsData.h"

namespace VulkanSimplified
{
	SdlJoyAxisEventData::SdlJoyAxisEventData()
	{
		timestamp = 0;
		reserved = 0;
		joystickID = 0;
		axis = 0;
		padding1 = 0;
		padding2 = 0;
		padding3 = 0;
		value = 0;
		padding4 = 0;
	}

	SdlJoyAxisEventData::~SdlJoyAxisEventData()
	{
	}

	SdlJoyBallEventData::SdlJoyBallEventData()
	{
		timestamp = 0;
		reserved = 0;
		joystickID = 0;
		ball = 0;
		padding1 = 0;
		padding2 = 0;
		padding3 = 0;
		xrel = 0;
		yrel = 0;
	}

	SdlJoyBallEventData::~SdlJoyBallEventData()
	{
	}

	SdlJoyHatEventData::SdlJoyHatEventData()
	{
		timestamp = 0;
		reserved = 0;
		joystickID = 0;
		hat = 0;
		value = 0;
		padding1 = 0;
		padding2 = 0;
		padding3 = 0;
	}

	SdlJoyHatEventData::~SdlJoyHatEventData()
	{
	}

	SdlJoyButtonEventData::SdlJoyButtonEventData()
	{
		timestamp = 0;
		reserved = 0;
		joystickID = 0;
		button = 0;
		down = false;
		padding1 = 0;
		padding2 = 0;
		padding3 = 0;
	}

	SdlJoyDeviceEventData::SdlJoyDeviceEventData()
	{
		type = SDL_JOYSTICK_DEVICE_SUBEVENT_DEVICE_UNKNOWN;
		timestamp = 0;
		reserved = 0;
		joystickID = 0;
	}

	SdlJoyDeviceEventData::~SdlJoyDeviceEventData()
	{
	}

	SdlJoyBatteryEventData::SdlJoyBatteryEventData()
	{
		timestamp = 0;
		reserved = 0;
		joystickID = 0;
		powerState = SDL_DATA_JOYSTICK_POWER_ERROR;
		powerPercentage = 0;
	}

	SdlJoyBatteryEventData::~SdlJoyBatteryEventData()
	{
	}
}
