#include "SdlEhIpch.h"
#include "SdlTextEventsData.h"

namespace VulkanSimplified
{
	SdlTextEditingEventData::SdlTextEditingEventData()
	{
		timestamp = 0;
		windowID = 0;
		for (size_t i = 0; i < SDL_DATA_TEXTEDITINGEVENT_TEXT_SIZE; i++)
			text[i] = 0;
		start = 0;
		length = 0;
	}

	SdlTextEditingEventData::~SdlTextEditingEventData()
	{
	}

	SdlTextEditingExtendedEventData::SdlTextEditingExtendedEventData()
	{
		timestamp = 0;
		windowID = 0;
		text = nullptr;
		start = 0;
		length = 0;
	}

	SdlTextEditingExtendedEventData::~SdlTextEditingExtendedEventData()
	{
	}

	SdlTextInputEventData::SdlTextInputEventData()
	{
		timestamp = 0;
		windowID = 0;
		for (size_t i = 0; i < SDL_DATA_TEXTINPUTEVENT_TEXT_SIZE; i++)
			text[i] = 0;
	}

	SdlTextInputEventData::~SdlTextInputEventData()
	{
	}
}
