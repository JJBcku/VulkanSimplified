#include "SdlEhIpch.h"
#include "SdlQuitEventData.h"

namespace VulkanSimplified
{
	SdlQuitEventData::SdlQuitEventData(const SDL_QuitEvent& eventData)
	{
		timestamp = eventData.timestamp;
	}

	SdlQuitEventData::~SdlQuitEventData()
	{
	}
}
