#include "SdlEhIpch.h"
#include "../../../../Include/VSMain/EventHandler/SdlUserEventData.h"

namespace VulkanSimplified
{
	SdlUserEventData::SdlUserEventData()
	{
		userEventType = 0;
		reserved = 0;
		timestamp = 0;
		windowID = 0;
		code = 0;
		data1 = nullptr;
		data2 = nullptr;
	}

	SdlUserEventData::~SdlUserEventData()
	{
	}
}
