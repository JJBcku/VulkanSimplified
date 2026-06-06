#include "SdlEhIpch.h"
#include "../../../../Include/VSMain/EventHandler/SdlControllerEventsData.h"

namespace VulkanSimplified
{
	SdlGamepadAxisEventData::SdlGamepadAxisEventData()
	{
		timestamp = 0;
		reserved = 0;
		which = 0;
		axis = 0;
		padding1 = 0;
		padding2 = 0;
		padding3 = 0;
		value = 0;
		padding4 = 0;
	}

	SdlGamepadAxisEventData::~SdlGamepadAxisEventData()
	{
	}

	SdlGamepadButtonEventData::SdlGamepadButtonEventData()
	{
		timestamp = 0;
		reserved = 0;
		which = 0;
		button = 0;
		down = false;
		padding1 = 0;
		padding2 = 0;
		padding3 = 0;
	}

	SdlGamepadButtonEventData::~SdlGamepadButtonEventData()
	{
	}

	SdlGamepadDeviceEventData::SdlGamepadDeviceEventData()
	{
		type = SdlGamepadDeviceSubEventType::DEVICE_UNKNOWN;
		reserved = 0;
		timestamp = 0;
		which = 0;
		padding = 0;
	}

	SdlGamepadDeviceEventData::~SdlGamepadDeviceEventData()
	{
	}

	SdlGamepadTouchpadEventData::SdlGamepadTouchpadEventData()
	{
		type = SdlGamepadTouchpadEventType::TOUCHPAD_UNKNOWN;
		reserved = 0;
		timestamp = 0;
		which = 0;
		touchpad = 0;
		finger = 0;
		x = 0;
		y = 0;
		pressure = 0;
	}

	SdlGamepadTouchpadEventData::~SdlGamepadTouchpadEventData()
	{
	}

	SdlGamepadSensorEventData::SdlGamepadSensorEventData()
	{
		timestamp = 0;
		reserved = 0;
		which = 0;
		sensor = 0;
		data[0] = 0;
		data[1] = 0;
		data[2] = 0;
		sensor_timestamp = 0;
	}

	SdlGamepadSensorEventData::~SdlGamepadSensorEventData()
	{
	}
}
