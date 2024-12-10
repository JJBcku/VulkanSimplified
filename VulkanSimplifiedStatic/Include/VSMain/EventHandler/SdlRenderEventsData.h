#pragma once

struct SDL_CommonEvent;

namespace VulkanSimplified
{
	struct SdlRenderTargetsResetEventData
	{
		uint32_t timestamp;

		SdlRenderTargetsResetEventData(const SDL_CommonEvent& eventData);
		~SdlRenderTargetsResetEventData();
	};

	struct SdlRenderDeviceResetEventData
	{
		uint32_t timestamp;

		SdlRenderDeviceResetEventData(const SDL_CommonEvent& eventData);
		~SdlRenderDeviceResetEventData();
	};
}
