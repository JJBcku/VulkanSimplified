#include "SdlEhIpch.h"
#include "../../../../Include/VSMain/EventHandler/SdlUserEventData.h"

namespace VulkanSimplified
{
	SdlUserEventData::SdlUserEventData()
	{
		timestamp = 0;
		windowID = 0;
		code = 0;
		padding = 0;
		data1 = 0;
		data2 = 0;
	}

	SdlUserEventData::~SdlUserEventData()
	{
	}
}
