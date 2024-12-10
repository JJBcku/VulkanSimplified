#pragma once

struct SDL_CommonEvent;

namespace VulkanSimplified
{
	struct SdlClipboardEventData
	{
		uint32_t timestamp;

		SdlClipboardEventData(const SDL_CommonEvent& eventData);
		~SdlClipboardEventData();
	};
}
