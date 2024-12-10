#pragma once

struct SDL_QuitEvent;

namespace VulkanSimplified
{
	struct SdlQuitEventData
	{
		uint32_t timestamp;

		SdlQuitEventData(const SDL_QuitEvent& eventData);
		~SdlQuitEventData();
	};
}
