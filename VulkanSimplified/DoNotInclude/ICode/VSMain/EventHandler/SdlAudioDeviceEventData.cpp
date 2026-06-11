#include "SdlEhIpch.h"
#include "../../../../Include/VSMain/EventHandler/SdlAudioDeviceEventData.h"

namespace VulkanSimplified
{
	SdlAudioDeviceEventData::SdlAudioDeviceEventData()
	{
		subtype = SdlAudioDeviceEventSubtype::AUDIO_DEVICE_EVENT_UNSET;
		reserved = 0;
		timestamp = 0;
		which = 0;
		recording = false;
		padding1 = 0;
		padding2 = 0;
		padding3 = 0;
	}

	SdlAudioDeviceEventData::~SdlAudioDeviceEventData()
	{
	}
}
