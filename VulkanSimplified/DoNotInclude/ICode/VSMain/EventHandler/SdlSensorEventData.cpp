#include "SdlEhIpch.h"
#include "../../../../Include/VSMain/EventHandler/SdlSensorEventData.h"

namespace VulkanSimplified
{
	SdlSensorEventData::SdlSensorEventData()
	{
		timestamp = 0;
		which = 0;
		data[0] = 0;
		data[1] = 0;
		data[2] = 0;
		data[3] = 0;
		data[4] = 0;
		data[5] = 0;
		timestamp_us = 0;
	}

	SdlSensorEventData::~SdlSensorEventData()
	{
	}
}
