#include "SdlEhIpch.h"
#include "SdlDisplayEventData.h"

namespace VulkanSimplified
{
	SdlDisplayEventData::SdlDisplayEventData(const SDL_DisplayEvent& eventData)
	{
		timestamp = eventData.timestamp;
		display = eventData.display;

		switch (eventData.event)
		{
		case SDL_DisplayEventID::SDL_DISPLAYEVENT_NONE:
			event = SDL_DATA_DISPLAYEVENT_NONE;
			break;
		case SDL_DisplayEventID::SDL_DISPLAYEVENT_ORIENTATION:
			event = SDL_DATA_DISPLAYEVENT_ORIENTATION;
			break;
		case SDL_DisplayEventID::SDL_DISPLAYEVENT_CONNECTED:
			event = SDL_DATA_DISPLAYEVENT_CONNECTED;
			break;
		case SDL_DisplayEventID::SDL_DISPLAYEVENT_DISCONNECTED:
			event = SDL_DATA_DISPLAYEVENT_DISCONNECTED;
			break;
		case SDL_DisplayEventID::SDL_DISPLAYEVENT_MOVED:
			event = SDL_DATA_DISPLAYEVENT_MOVED;
			break;
		default:
			throw std::runtime_error("SdlDisplayEventData::SdlDisplayEventData Error: Wrong event type was passed to the constructor!");
		}

		padding1 = eventData.padding1;
		padding2 = eventData.padding2;
		padding3 = eventData.padding3;
		data1 = eventData.data1;
	}

	SdlDisplayEventData::~SdlDisplayEventData()
	{
	}
}
