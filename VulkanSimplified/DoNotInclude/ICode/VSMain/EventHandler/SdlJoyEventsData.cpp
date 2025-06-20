#include "SdlEhIpch.h"
#include "../../../../Include/VSMain/EventHandler/SdlJoyEventsData.h"

namespace VulkanSimplified
{
	SdlJoyAxisEventData::SdlJoyAxisEventData()
	{
		timestamp = 0;
		which = 0;
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
		which = 0;
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
		which = 0;
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
		which = 0;
		button = 0;
		state = 0;
		padding1 = 0;
		padding2 = 0;
		padding3 = 0;
	}

	SdlJoyDeviceEventData::SdlJoyDeviceEventData()
	{
		type = 0;
		timestamp = 0;
		which = 0;
	}

	SdlJoyDeviceEventData::~SdlJoyDeviceEventData()
	{
	}

	SdlJoyBatteryEventData::SdlJoyBatteryEventData()
	{
		timestamp = 0;
		which = 0;
		level = static_cast<SdlJoystickPowerLevel>(0);
	}

	SdlJoyBatteryEventData::~SdlJoyBatteryEventData()
	{
	}
}
