#include "SdlEhIpch.h"
#include "SdlJoyEventsData.h"

namespace VulkanSimplified
{
	SdlJoyAxisEventData::SdlJoyAxisEventData(const SDL_JoyAxisEvent& eventData)
	{
		timestamp = eventData.timestamp;
		which = eventData.which;
		axis = eventData.axis;
		padding1 = eventData.padding1;
		padding2 = eventData.padding2;
		padding3 = eventData.padding3;
		value = eventData.value;
		padding4 = 0;
	}

	SdlJoyAxisEventData::~SdlJoyAxisEventData()
	{
	}

	SdlJoyBallEventData::SdlJoyBallEventData(const SDL_JoyBallEvent& eventData)
	{
		timestamp = eventData.timestamp;
		which = eventData.which;
		ball = eventData.ball;
		padding1 = eventData.padding1;
		padding2 = eventData.padding2;
		padding3 = eventData.padding3;
		xrel = eventData.xrel;
		yrel = eventData.yrel;
	}

	SdlJoyBallEventData::~SdlJoyBallEventData()
	{
	}

	SdlJoyHatEventData::SdlJoyHatEventData(const SDL_JoyHatEvent& eventData)
	{
		timestamp = eventData.timestamp;
		which = eventData.which;
		hat = eventData.hat;
		value = eventData.value;
		padding1 = eventData.padding1;
		padding2 = eventData.padding2;
		padding3 = 0;
	}

	SdlJoyHatEventData::~SdlJoyHatEventData()
	{
	}

	SdlJoyButtonEventData::SdlJoyButtonEventData(const SDL_JoyButtonEvent& eventData)
	{
		timestamp = eventData.timestamp;
		which = eventData.which;
		button = eventData.button;
		state = eventData.state;
		padding1 = eventData.padding1;
		padding2 = eventData.padding2;
		padding3 = 0;
	}

	SdlJoyDeviceEventData::SdlJoyDeviceEventData(const SDL_JoyDeviceEvent& eventData)
	{
		if (eventData.type == static_cast<std::uint32_t>(SDL_EventType::SDL_JOYDEVICEADDED))
			type = 1;
		else
			type = 0;

		timestamp = eventData.timestamp;
		which = eventData.which;
	}

	SdlJoyDeviceEventData::~SdlJoyDeviceEventData()
	{
	}

	SdlJoyBatteryEventData::SdlJoyBatteryEventData(const SDL_JoyBatteryEvent& eventData)
	{
		timestamp = eventData.timestamp;
		which = eventData.which;
		level = static_cast<SdlJoystickPowerLevel>(eventData.level);
	}

	SdlJoyBatteryEventData::~SdlJoyBatteryEventData()
	{
	}
}
