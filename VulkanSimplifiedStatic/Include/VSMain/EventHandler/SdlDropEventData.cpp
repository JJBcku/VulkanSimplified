#include "SdlEhIpch.h"
#include "SdlDropEventData.h"

namespace VulkanSimplified
{
	SdlDropEventData::SdlDropEventData(const SDL_DropEvent& eventData)
	{
		switch (eventData.type)
		{
		case SDL_DROPBEGIN:
			type = SdlDropEventType::DROPEVENT_BEGIN;
			break;
		case SDL_DROPFILE:
			type = SdlDropEventType::DROPEVENT_FILE;
			break;
		case SDL_DROPTEXT:
			type = SdlDropEventType::DROPEVENT_TEXT;
			break;
		case SDL_DROPCOMPLETE:
			type = SdlDropEventType::DROPEVENT_COMPLETE;
			break;
		default:
			throw std::runtime_error("SdlDropEventData error: Program was given wrong type of SDL event!");
		}

		timestamp = eventData.timestamp;
		file = eventData.file;
		windowID = eventData.windowID;
		padding = 0;
	}

	SdlDropEventData::~SdlDropEventData()
	{
		if (file != nullptr)
			SDL_free(file);
	}

	SdlDropEventData::SdlDropEventData(SdlDropEventData&& rhs) noexcept : type(rhs.type), timestamp(rhs.timestamp), file(rhs.file), windowID(rhs.windowID), padding(0)
	{
		rhs.type = static_cast<SdlDropEventType>(std::numeric_limits<uint32_t>::max());
		rhs.file = nullptr;
	}

	SdlDropEventData& SdlDropEventData::operator=(SdlDropEventData&& rhs) noexcept
	{
		type = rhs.type;
		timestamp = rhs.timestamp;
		file = rhs.file;
		windowID = rhs.windowID;
		padding = 0;

		rhs.type = static_cast<SdlDropEventType>(std::numeric_limits<uint32_t>::max());
		rhs.file = nullptr;
		return *this;
	}
}
