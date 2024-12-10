#include "SdlEhIpch.h"
#include "SdlWindowEventData.h"

namespace VulkanSimplified
{
	SdlWindowEventData::SdlWindowEventData(const SDL_WindowEvent& eventData)
	{
		timestamp = eventData.timestamp;
		windowID = eventData.windowID;
		event = eventData.event;
		padding1 = eventData.padding1;
		padding2 = eventData.padding2;
		padding3 = eventData.padding3;
		data1 = eventData.data1;
		data2 = eventData.data2;
		padding = 0;
	}

	SdlWindowEventData::~SdlWindowEventData()
	{
	}
}