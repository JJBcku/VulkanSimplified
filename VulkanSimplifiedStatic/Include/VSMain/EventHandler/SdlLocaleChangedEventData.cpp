#include "SdlEhIpch.h"
#include "SdlLocaleChangedEventData.h"

namespace VulkanSimplified
{
	SdlLocaleChangeEventData::SdlLocaleChangeEventData(const SDL_CommonEvent& eventData)
	{
		timestamp = eventData.timestamp;
	}

	SdlLocaleChangeEventData::~SdlLocaleChangeEventData()
	{
	}
}
