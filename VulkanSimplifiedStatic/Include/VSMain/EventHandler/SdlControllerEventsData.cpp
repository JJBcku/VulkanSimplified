#include "SdlEhIpch.h"
#include "SdlControllerEventsData.h"

#include <stdexcept>

SdlControllerAxisEventData::SdlControllerAxisEventData(const SDL_ControllerAxisEvent& eventData)
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

SdlControllerAxisEventData::~SdlControllerAxisEventData()
{
}

SdlControllerButtonEventData::SdlControllerButtonEventData(const SDL_ControllerButtonEvent& eventData)
{
	timestamp = eventData.timestamp;
	which = eventData.which;
	button = eventData.button;
	state = eventData.state;
	padding1 = eventData.padding1;
	padding2 = eventData.padding2;
	padding3 = 0;
}

SdlControllerButtonEventData::~SdlControllerButtonEventData()
{
}

SdlControllerDeviceEventData::SdlControllerDeviceEventData(const SDL_ControllerDeviceEvent& eventData)
{
	switch (eventData.type)
	{
	case SDL_CONTROLLERDEVICEADDED:
		type = SdlControllerDeviceEventType::DEVICE_ADDED;
		break;
	case SDL_CONTROLLERDEVICEREMOVED:
		type = SdlControllerDeviceEventType::DEVICE_REMOVED;
		break;
	case SDL_CONTROLLERDEVICEREMAPPED:
		type = SdlControllerDeviceEventType::DEVICE_REMMAPED;
		break;
	default:
		throw std::runtime_error("SdlControllerDeviceEventData error: Wrong event type was passed to the constructor!");
	}
	timestamp = eventData.timestamp;
	which = eventData.which;
	padding = 0;
}

SdlControllerDeviceEventData::~SdlControllerDeviceEventData()
{
}

SdlControllerTouchpadEventData::SdlControllerTouchpadEventData(const SDL_ControllerTouchpadEvent& eventData)
{
	switch (eventData.type)
	{
	case SDL_CONTROLLERTOUCHPADDOWN:
		type = SdlControllerTouchpadEventType::TOUCHPAD_DOWN;
		break;
	case SDL_CONTROLLERTOUCHPADMOTION:
		type = SdlControllerTouchpadEventType::TOUCHPAD_MOTION;
		break;
	case SDL_CONTROLLERTOUCHPADUP:
		type = SdlControllerTouchpadEventType::TOUCHPAD_DOWN;
		break;
	default:
		throw std::runtime_error("SdlControllerTouchpadEventData error: Wrong event type was passed to the constructor!");
	}

	timestamp = eventData.timestamp;
	which = eventData.which;
	touchpad = eventData.touchpad;
	finger = eventData.finger;
	x = eventData.x;
	y = eventData.y;
	pressure = eventData.pressure;
}

SdlControllerTouchpadEventData::~SdlControllerTouchpadEventData()
{
}

SdlControllerSensorEventData::SdlControllerSensorEventData(const SDL_ControllerSensorEvent& eventData)
{
	timestamp = eventData.timestamp;
	which = eventData.which;
	sensor = eventData.sensor;
	data[0] = eventData.data[0];
	data[1] = eventData.data[1];
	data[2] = eventData.data[2];
	timestamp_us = eventData.timestamp_us;
}

SdlControllerSensorEventData::~SdlControllerSensorEventData()
{
}
