#include "SdlEhIpch.h"
#include "SdlControllerEventsData.h"

namespace VulkanSimplified
{
	SdlControllerAxisEventData::SdlControllerAxisEventData()
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

	SdlControllerAxisEventData::~SdlControllerAxisEventData()
	{
	}

	SdlControllerButtonEventData::SdlControllerButtonEventData()
	{
		timestamp = 0;
		which = 0;
		button = 0;
		state = 0;
		padding1 = 0;
		padding2 = 0;
		padding3 = 0;
	}

	SdlControllerButtonEventData::~SdlControllerButtonEventData()
	{
	}

	SdlControllerDeviceEventData::SdlControllerDeviceEventData()
	{
		type = static_cast<SdlControllerDeviceEventType>(std::numeric_limits<uint32_t>::max());
		timestamp = 0;
		which = 0;
		padding = 0;
	}

	SdlControllerDeviceEventData::~SdlControllerDeviceEventData()
	{
	}

	SdlControllerTouchpadEventData::SdlControllerTouchpadEventData()
	{
		type = static_cast<SdlControllerTouchpadEventType>(std::numeric_limits<uint32_t>::max());

		timestamp = 0;
		which = 0;
		touchpad = 0;
		finger = 0;
		x = 0;
		y = 0;
		pressure = 0;
	}

	SdlControllerTouchpadEventData::~SdlControllerTouchpadEventData()
	{
	}

	SdlControllerSensorEventData::SdlControllerSensorEventData()
	{
		timestamp = 0;
		which = 0;
		sensor = 0;
		data[0] = 0;
		data[1] = 0;
		data[2] = 0;
		timestamp_us = 0;
	}

	SdlControllerSensorEventData::~SdlControllerSensorEventData()
	{
	}
}
