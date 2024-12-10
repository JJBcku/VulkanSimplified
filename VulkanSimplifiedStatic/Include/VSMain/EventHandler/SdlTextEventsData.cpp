#include "SdlEhIpch.h"
#include "SdlTextEventsData.h"

namespace VulkanSimplified
{
	SdlTextEditingEventData::SdlTextEditingEventData(const SDL_TextEditingEvent& eventData)
	{
		timestamp = eventData.timestamp;
		windowID = eventData.windowID;
		for (size_t i = 0; i < SDL_DATA_TEXTEDITINGEVENT_TEXT_SIZE; i++)
			text[i] = eventData.text[i];
		start = eventData.start;
		length = eventData.length;
	}

	SdlTextEditingEventData::~SdlTextEditingEventData()
	{
	}

	SdlTextEditingExtendedEventData::SdlTextEditingExtendedEventData(const SDL_TextEditingExtEvent& eventData)
	{
		timestamp = eventData.timestamp;
		windowID = eventData.windowID;
		text = eventData.text;
		vpadding = nullptr;
		start = eventData.start;
		length = eventData.length;
	}

	SdlTextEditingExtendedEventData::~SdlTextEditingExtendedEventData()
	{
	}

	SdlTextInputEventData::SdlTextInputEventData(const SDL_TextInputEvent& eventData)
	{
		timestamp = eventData.timestamp;
		windowID = eventData.windowID;
		for (size_t i = 0; i < SDL_DATA_TEXTINPUTEVENT_TEXT_SIZE; i++)
			text[i] = eventData.text[i];
	}

	SdlTextInputEventData::~SdlTextInputEventData()
	{
	}
}
