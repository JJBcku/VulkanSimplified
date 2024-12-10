#pragma once

struct SDL_CommonEvent;

namespace VulkanSimplified
{
	struct SdlLocaleChangeEventData
	{
		uint32_t timestamp;

		SdlLocaleChangeEventData(const SDL_CommonEvent& eventData);
		~SdlLocaleChangeEventData();
	};
}
