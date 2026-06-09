#include "SdlEhIpch.h"
#include "../../../../Include/VSMain/EventHandler/SdlMouseEventsData.h"

namespace VulkanSimplified
{
	SdlMouseMotionEventData::SdlMouseMotionEventData()
	{
		timestamp = 0;
		reserved = 0;
		windowID = 0;
		mouseID = 0;
		state = 0;
		x = 0.0f;
		y = 0.0f;
		xrel = 0.0f;
		yrel = 0.0f;
	}

	SdlMouseMotionEventData::~SdlMouseMotionEventData()
	{
	}

	SdlMouseButtonEventData::SdlMouseButtonEventData()
	{
		timestamp = 0;
		reserved = 0;
		windowID = 0;
		mouseID = 0;
		button = 0;
		down = false;
		clicks = 0;
		padding = 0;
		x = 0.0f;
		y = 0.0f;
	}

	SdlMouseButtonEventData::~SdlMouseButtonEventData()
	{
	}

	SdlMouseWheelEventData::SdlMouseWheelEventData()
	{
		timestamp = 0;
		reserved = 0;
		windowID = 0;
		mouseID = 0;
		x = 0.0f;
		y = 0.0f;
		direction = 0;
		mouse_x = 0.0f;
		mouse_y = 0.0f;
		int_x = 0;
		int_y = 0;
	}

	SdlMouseWheelEventData::~SdlMouseWheelEventData()
	{
	}

	SdlMouseDeviceEventData::SdlMouseDeviceEventData()
	{
		type = SdlMouseDeviceEventType::MOUSE_DEVICE_UNSET;
		reserved = 0;
		timestamp = 0;
		mouseID = 0;
		padding = 0;
	}

	SdlMouseDeviceEventData::~SdlMouseDeviceEventData()
	{
	}

}
