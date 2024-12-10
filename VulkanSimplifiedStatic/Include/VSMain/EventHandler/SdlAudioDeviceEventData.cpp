#include "SdlEhIpch.h"
#include "SdlAudioDeviceEventData.h"

namespace VulkanSimplified
{
	SdlAudioDeviceEventData::SdlAudioDeviceEventData()
	{
		type = 0;
		timestamp = 0;
		which = 0;
		iscapture = 0;
		padding1 = 0;
		padding2 = 0;
		padding3 = 0;
	}

	SdlAudioDeviceEventData::~SdlAudioDeviceEventData()
	{
	}
}
