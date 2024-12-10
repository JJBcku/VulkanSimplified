#include "SdlEhIpch.h"
#include "SdlAppEventsData.h"

namespace VulkanSimplified
{
	SdlAppTerminatingEventData::SdlAppTerminatingEventData()
	{
		timestamp = 0;
	}

	SdlAppTerminatingEventData::~SdlAppTerminatingEventData()
	{
	}

	SdlAppLowMemoryEventData::SdlAppLowMemoryEventData()
	{
		timestamp = 0;
	}

	SdlAppLowMemoryEventData::~SdlAppLowMemoryEventData()
	{
	}

	SdlAppWillEnterBackgroundEventData::SdlAppWillEnterBackgroundEventData()
	{
		timestamp = 0;
	}

	SdlAppWillEnterBackgroundEventData::~SdlAppWillEnterBackgroundEventData()
	{
	}

	SdlAppDidEnterBackgroundEventData::SdlAppDidEnterBackgroundEventData()
	{
		timestamp = 0;
	}

	SdlAppDidEnterBackgroundEventData::~SdlAppDidEnterBackgroundEventData()
	{
	}

	SdlAppWillEnterForegroundEventData::SdlAppWillEnterForegroundEventData()
	{
		timestamp = 0;
	}

	SdlAppWillEnterForegroundEventData::~SdlAppWillEnterForegroundEventData()
	{
	}

	SdlAppDidEnterForegroundEventData::SdlAppDidEnterForegroundEventData()
	{
		timestamp = 0;
	}

	SdlAppDidEnterForegroundEventData::~SdlAppDidEnterForegroundEventData()
	{
	}
}
