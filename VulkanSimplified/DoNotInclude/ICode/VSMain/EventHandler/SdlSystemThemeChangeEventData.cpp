#include "SdlEhIpch.h"
#include "../../../../Include/VSMain/EventHandler/SdlSystemThemeChangeEventData.h"

namespace VulkanSimplified
{
	SdlSystemThemeChangeEventData::SdlSystemThemeChangeEventData()
	{
		reserved = 0;
		padding = 0;
		timestamp = 0;
	}

	SdlSystemThemeChangeEventData::~SdlSystemThemeChangeEventData()
	{
	}

}