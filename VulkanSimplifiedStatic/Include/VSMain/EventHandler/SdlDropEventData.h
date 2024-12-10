#pragma once

struct SDL_DropEvent;

namespace VulkanSimplified
{
	enum class SdlDropEventType : uint32_t
	{
		DROPEVENT_BEGIN,
		DROPEVENT_FILE,
		DROPEVENT_TEXT,
		DROPEVENT_COMPLETE,
	};

	struct SdlDropEventData
	{
		SdlDropEventType type;
		uint32_t timestamp;   /**< In milliseconds, populated using SDL_GetTicks() */
		char* file;         /**< The file name, which should be freed with SDL_free(), is NULL on begin/complete */
		uint32_t windowID;    /**< The window that was dropped on, if any */
		uint32_t padding;

		SdlDropEventData(const SDL_DropEvent& eventData);
		~SdlDropEventData();

		SdlDropEventData(const SdlDropEventData&) noexcept = delete;
		SdlDropEventData(SdlDropEventData&& rhs) noexcept;

		SdlDropEventData& operator=(const SdlDropEventData&) noexcept = delete;
		SdlDropEventData& operator=(SdlDropEventData&& rhs) noexcept;
	};
}