#include "SdlEhIpch.h"
#include "SdlRenderEventsData.h"

namespace VulkanSimplified
{
	SdlRenderTargetsResetEventData::SdlRenderTargetsResetEventData(const SDL_CommonEvent& eventData)
	{
		timestamp = eventData.timestamp;
	}

	SdlRenderTargetsResetEventData::~SdlRenderTargetsResetEventData()
	{
	}

	SdlRenderDeviceResetEventData::SdlRenderDeviceResetEventData(const SDL_CommonEvent& eventData)
	{
		timestamp = eventData.timestamp;
	}

	SdlRenderDeviceResetEventData::~SdlRenderDeviceResetEventData()
	{
	}
}
