#pragma once

struct SdlLocaleChangeEventData
{
	uint32_t timestamp;

	SdlLocaleChangeEventData(const SDL_CommonEvent& eventData);
	~SdlLocaleChangeEventData();
};