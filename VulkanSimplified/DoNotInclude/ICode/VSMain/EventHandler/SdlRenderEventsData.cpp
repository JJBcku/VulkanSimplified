#include "SdlEhIpch.h"
#include "../../../../Include/VSMain/EventHandler/SdlRenderEventsData.h"

namespace VulkanSimplified
{
	SdlRenderTargetsResetEventData::SdlRenderTargetsResetEventData()
	{
		reserved = 0;
		timestamp = 0;
	}

	SdlRenderTargetsResetEventData::~SdlRenderTargetsResetEventData()
	{
	}

	SdlRenderDeviceResetEventData::SdlRenderDeviceResetEventData()
	{
		reserved = 0;
		timestamp = 0;
	}

	SdlRenderDeviceResetEventData::~SdlRenderDeviceResetEventData()
	{
	}
}
