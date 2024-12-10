#include "SdlEhIpch.h"
#include "SdlTouchpadEventData.h"

namespace VulkanSimplified
{
	SdlTouchFingerEventData::SdlTouchFingerEventData()
	{
		type = static_cast<SdlTouchFingerEventType>(std::numeric_limits<uint32_t>::max());

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

	SdlMultiGestureEventData::SdlMultiGestureEventData()
	{
		timestamp = 0;
		padding2 = 0;
		touchId = 0;
		dTheta = 0;
		dDist = 0;
		x = 0;
		y = 0;
		numFingers = 0;
		padding = 0;
		padding3 = 0;
	}

	SdlMultiGestureEventData::~SdlMultiGestureEventData()
	{
	}

	SdlDollarGestureEventData::SdlDollarGestureEventData()
	{
		type = 0;
		timestamp = 0;
		touchId = 0;
		gestureId = 0;
		numFingers = 0;
		error = 0;
		x = 0;
		y = 0;
	}

	SdlDollarGestureEventData::~SdlDollarGestureEventData()
	{
	}
}
