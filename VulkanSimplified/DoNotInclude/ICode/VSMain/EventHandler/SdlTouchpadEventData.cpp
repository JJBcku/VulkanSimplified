#include "SdlEhIpch.h"
#include "../../../../Include/VSMain/EventHandler/SdlTouchpadEventData.h"

namespace VulkanSimplified
{
	SdlTouchFingerEventData::SdlTouchFingerEventData()
	{
		type = SdlTouchFingerEventType::FINGER_UNSET;

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

}
