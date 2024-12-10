#include "SdlEhIpch.h"
#include "SdlClipboardEventData.h"

namespace VulkanSimplified
{
	SdlClipboardEventData::SdlClipboardEventData(const SDL_CommonEvent& eventData)
	{
		timestamp = eventData.timestamp;
	}

	SdlClipboardEventData::~SdlClipboardEventData()
	{
	}
}
