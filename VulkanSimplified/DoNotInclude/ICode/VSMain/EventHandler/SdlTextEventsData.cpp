#include "SdlEhIpch.h"
#include "../../../../Include/VSMain/EventHandler/SdlTextEventsData.h"

namespace VulkanSimplified
{
	SdlTextEditingEventData::SdlTextEditingEventData()
	{
		reserved = 0;
		timestamp = 0;
		windowID = 0;
		padding = 0;
		text = nullptr;
		start = 0;
		length = 0;
	}

	SdlTextEditingEventData::~SdlTextEditingEventData()
	{
	}

	SdlTextInputEventData::SdlTextInputEventData()
	{
		timestamp = 0;
		reserved = 0;
		windowID = 0;
		text = nullptr;
	}

	SdlTextInputEventData::~SdlTextInputEventData()
	{
	}
}
