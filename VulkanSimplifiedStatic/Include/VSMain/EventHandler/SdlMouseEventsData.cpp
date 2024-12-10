#include "SdlEhIpch.h"
#include "SdlMouseEventsData.h"

namespace VulkanSimplified
{
	SdlMouseMotionEventData::SdlMouseMotionEventData()
	{
		timestamp = 0;
		windowID = 0;
		which = 0;
		state = 0;
		x = 0;
		y = 0;
		xrel = 0;
		yrel = 0;
	}

	SdlMouseMotionEventData::~SdlMouseMotionEventData()
	{
	}

	SdlMouseButtonEventData::SdlMouseButtonEventData()
	{
		timestamp = 0;
		windowID = 0;
		which = 0;
		button = 0;
		state = 0;
		clicks = 0;
		padding1 = 0;
		x = 0;
		y = 0;
	}

	SdlMouseButtonEventData::~SdlMouseButtonEventData()
	{
	}

	SdlMouseWheelEventData::SdlMouseWheelEventData()
	{
		timestamp = 0;
		windowID = 0;
		which = 0;
		x = 0;
		y = 0;
		direction = 0;
		preciseX = 0;
		preciseY = 0;
		mouseX = 0;
		mouseY = 0;
	}

	SdlMouseWheelEventData::~SdlMouseWheelEventData()
	{
	}
}
