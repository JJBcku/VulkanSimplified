#include "SdlEhIpch.h"
#include "SdlAudioDeviceEventData.h"

namespace VulkanSimplified
{
	SdlAudioDeviceEventData::SdlAudioDeviceEventData(const SDL_AudioDeviceEvent& eventData)
	{
		if (eventData.type == SDL_AUDIODEVICEADDED)
			type = 1;
		else
			type = 0;

		timestamp = eventData.timestamp;
		which = eventData.which;
		iscapture = eventData.iscapture;
		padding1 = eventData.padding1;
		padding2 = eventData.padding2;
		padding3 = eventData.padding3;
	}

	SdlAudioDeviceEventData::~SdlAudioDeviceEventData()
	{
	}
}
