#pragma once

struct SdlClipboardEventData
{
	uint32_t timestamp;

	SdlClipboardEventData(const SDL_CommonEvent& eventData);
	~SdlClipboardEventData();
};