#include "SdlEhIpch.h"
#include "../../../../Include/VSMain/EventHandler/SdlTouchpadEventsData.h"

namespace VulkanSimplified
{
	SdlTouchFingerEventData::SdlTouchFingerEventData()
	{
		subtype = SdlTouchFingerEventType::FINGER_UNSET;
		reserved = 0;
		timestamp = 0;
		touchId = 0;
		fingerId = 0;
		x = 0;
		y = 0;
		dx = 0;
		dy = 0;
		pressure = 0;
		windowID = 0;
	}

	SdlTouchFingerEventData::~SdlTouchFingerEventData()
	{
	}

	SdlTouchPinchEventData::SdlTouchPinchEventData()
	{
		subtype = SdlTouchPinchEventType::PINCH_UNSET;
		reserved = 0;
		timestamp = 0;
		scale = 0.0f;
		windowID = 0;
	}

	SdlTouchPinchEventData::~SdlTouchPinchEventData()
	{
	}

}
