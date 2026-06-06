#include "SdlEhIpch.h"
#include "../../../../Include/VSMain/EventHandler/SdlAppEventsData.h"

namespace VulkanSimplified
{
	SdlAppTerminatingEventData::SdlAppTerminatingEventData()
	{
		reserved = 0;
		timestamp = 0;
	}

	SdlAppTerminatingEventData::~SdlAppTerminatingEventData()
	{
	}

	SdlAppLowMemoryEventData::SdlAppLowMemoryEventData()
	{
		reserved = 0;
		timestamp = 0;
	}

	SdlAppLowMemoryEventData::~SdlAppLowMemoryEventData()
	{
	}

	SdlAppWillEnterBackgroundEventData::SdlAppWillEnterBackgroundEventData()
	{
		reserved = 0;
		timestamp = 0;
	}

	SdlAppWillEnterBackgroundEventData::~SdlAppWillEnterBackgroundEventData()
	{
	}

	SdlAppDidEnterBackgroundEventData::SdlAppDidEnterBackgroundEventData()
	{
		reserved = 0;
		timestamp = 0;
	}

	SdlAppDidEnterBackgroundEventData::~SdlAppDidEnterBackgroundEventData()
	{
	}

	SdlAppWillEnterForegroundEventData::SdlAppWillEnterForegroundEventData()
	{
		reserved = 0;
		timestamp = 0;
	}

	SdlAppWillEnterForegroundEventData::~SdlAppWillEnterForegroundEventData()
	{
	}

	SdlAppDidEnterForegroundEventData::SdlAppDidEnterForegroundEventData()
	{
		reserved = 0;
		timestamp = 0;
	}

	SdlAppDidEnterForegroundEventData::~SdlAppDidEnterForegroundEventData()
	{
	}
}
