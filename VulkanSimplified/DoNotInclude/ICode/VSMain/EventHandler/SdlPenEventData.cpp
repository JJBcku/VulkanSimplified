#include "SdlEhIpch.h"
#include "../../../../Include/VSMain/EventHandler/SdlPenEventData.h"

namespace VulkanSimplified
{
	SdlPenAxisEventData::SdlPenAxisEventData()
	{
		timestamp = 0;
		reserved = 0;
		windowID = 0;
		penID = 0;
		pen_state = 0;
		x = 0.0f;
		y = 0.0f;
		axis = 0;
		value = 0.0f;
	}

	SdlPenAxisEventData::~SdlPenAxisEventData()
	{
	}

	SdlPenButtonEventData::SdlPenButtonEventData()
	{
		subtype = SdlPenButtonEventSubtype::PEN_BUTTON_UNSET;
		reserved = 0;
		timestamp = 0;
		windowID = 0;
		penID = 0;
		pen_state = 0;
		x = 0.0f;
		y = 0.0f;
		button = 0;
		down = false;
		padding = 0;
	}

	SdlPenButtonEventData::~SdlPenButtonEventData()
	{
	}

	SdlPenMotionEventData::SdlPenMotionEventData()
	{
		timestamp = 0;
		reserved = 0;
		windowID = 0;
		penID = 0;
		pen_state = 0;
		x = 0.0f;
		y = 0.0f;
	}

	SdlPenMotionEventData::~SdlPenMotionEventData()
	{
	}

	SdlPenTouchEventData::SdlPenTouchEventData()
	{
		subtype = SdlPenTouchEventSubtype::PEN_TOUCH_UNSET;
		reserved = 0;
		timestamp = 0;
		windowID = 0;
		penID = 0;
		pen_state = 0;
		x = 0.0f;
		y = 0.0f;
		eraser = false;
		down = false;
		padding = 0;
	}

	SdlPenTouchEventData::~SdlPenTouchEventData()
	{
	}

	SdlPenProximityEventData::SdlPenProximityEventData()
	{
		subtype = SdlPenProximityEventSubtype::PEN_PROXIMITY_UNSET;
		reserved = 0;
		timestamp = 0;
		windowID = 0;
		penID = 0;
	}

	SdlPenProximityEventData::~SdlPenProximityEventData()
	{
	}

}