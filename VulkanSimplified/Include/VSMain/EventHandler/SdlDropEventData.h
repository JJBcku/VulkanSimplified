#pragma once

#include <stdint.h>

namespace VulkanSimplified
{
	enum class SdlDropEventType : uint32_t
	{
		DROPEVENT_UNSET = 0x0,

		DROPEVENT_BEGIN = 0x01,
		DROPEVENT_FILE = 0x02,
		DROPEVENT_TEXT = 0x04,
		DROPEVENT_COMPLETE = 0x08,
		DROPEVENT_POSITION = 0x10,
	};

	struct SdlDropEventData
	{
		SdlDropEventType type;
		uint32_t reserved;
		uint64_t timestamp;   /**< In milliseconds, populated using SDL_GetTicks() */
		uint32_t windowID;    /**< The window that was dropped on, if any */
		uint32_t padding;
		float x; /**< X coordinate, relative to window (not on begin) */
		float y; /**< Y coordinate, relative to window (not on begin) */
		const char* source; /**< The source app that sent this drop event, or NULL if that isn't available */
		const char* data; /**< The text for SDL_EVENT_DROP_TEXT and the file name for SDL_EVENT_DROP_FILE, NULL for other events */

		SdlDropEventData();
		~SdlDropEventData();
	};
}
