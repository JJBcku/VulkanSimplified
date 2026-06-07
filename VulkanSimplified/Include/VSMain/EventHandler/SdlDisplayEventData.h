#pragma once

#include <stdint.h>

namespace VulkanSimplified
{
    enum class SdlDisplayEventID : uint32_t
    {
        SDL_DATA_DISPLAYEVENT_UNSET = 0x0,

        SDL_DATA_DISPLAYEVENT_ORIENTATION = 0x01,                  /**< Display orientation has changed to data1 */
        SDL_DATA_DISPLAYEVENT_ADDED = 0x02,                        /**< Display has been added to the system */
        SDL_DATA_DISPLAYEVENT_REMOVED = 0x04,                      /**< Display has been removed from the system */
        SDL_DATA_DISPLAYEVENT_MOVED = 0x08,                        /**< Display has changed position */
        SDL_DATA_DISPLAYEVENT_DESKTOP_MODE_CHANGED = 0x10,         /**< Display has changed desktop mode */
        SDL_DATA_DISPLAYEVENT_CURRENT_MODE_CHANGED = 0x20,         /**< Display has changed current mode */
        SDL_DATA_DISPLAYEVENT_CONTENT_SCALE_CHANGED = 0x40,        /**< Display has changed content scale */
        SDL_DATA_DISPLAYEVENT_USABLE_BOUNDS_CHANGED = 0x80,        /**< Display has changed usable bounds */
    };

    struct SdlDisplayEventData
    {
        uint64_t timestamp;             /**< In milliseconds, populated using SDL_GetTicks() */
        uint64_t reserved;
        uint32_t display;               /**< The associated display index */
        SdlDisplayEventID event;        /**< Event ID */
        int32_t data1;                  /**< event dependent data */
        int32_t data2;                  /**< event dependent data */

        SdlDisplayEventData();
        ~SdlDisplayEventData();
    };
}
