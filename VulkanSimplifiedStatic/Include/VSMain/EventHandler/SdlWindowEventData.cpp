#include "SdlEhIpch.h"
#include "SdlWindowEventData.h"

namespace VulkanSimplified
{
	SdlWindowEventData::SdlWindowEventData()
	{
		timestamp = 0;
		windowID = 0;
		event = 0;
		padding1 = 0;
		padding2 = 0;
		padding3 = 0;
		data1 = 0;
		data2 = 0;
		padding = 0;
	}

	SdlWindowEventData::~SdlWindowEventData()
	{
	}
}
