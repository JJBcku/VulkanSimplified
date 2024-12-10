#pragma once

struct SdlAppTerminatingEventData
{
	uint32_t timestamp;

	SdlAppTerminatingEventData(const SDL_CommonEvent& eventData);
	~SdlAppTerminatingEventData();
};

struct SdlAppLowMemoryEventData
{
	uint32_t timestamp;

	SdlAppLowMemoryEventData(const SDL_CommonEvent& eventData);
	~SdlAppLowMemoryEventData();
};

struct SdlAppWillEnterBackgroundEventData
{
	uint32_t timestamp;

	SdlAppWillEnterBackgroundEventData(const SDL_CommonEvent& eventData);
	~SdlAppWillEnterBackgroundEventData();
};

struct SdlAppDidEnterBackgroundEventData
{
	uint32_t timestamp;

	SdlAppDidEnterBackgroundEventData(const SDL_CommonEvent& eventData);
	~SdlAppDidEnterBackgroundEventData();
};

struct SdlAppWillEnterForegroundEventData
{
	uint32_t timestamp;

	SdlAppWillEnterForegroundEventData(const SDL_CommonEvent& eventData);
	~SdlAppWillEnterForegroundEventData();
};

struct SdlAppDidEnterForegroundEventData
{
	uint32_t timestamp;

	SdlAppDidEnterForegroundEventData(const SDL_CommonEvent& eventData);
	~SdlAppDidEnterForegroundEventData();
};