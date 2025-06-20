#include "SdlEhIpch.h"
#include "../../../../Include/VSMain/EventHandler/SdlDisplayEventData.h"

namespace VulkanSimplified
{
	SdlDisplayEventData::SdlDisplayEventData()
	{
		timestamp = 0;
		display = 0;
		event = 0;
		padding1 = 0;
		padding2 = 0;
		padding3 = 0;
		data1 = 0;
	}

	SdlDisplayEventData::~SdlDisplayEventData()
	{
	}
}
