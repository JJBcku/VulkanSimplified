#pragma once

#include <stdint.h>

namespace VulkanSimplified
{
    enum class SdlWindowSubEventID : uint32_t
    {
        SDL_DATA_WINDOWEVENT_UNSET = 0x0000000,

        SDL_DATA_WINDOWEVENT_SHOWN = 0x0000001,                     /**< Window has been shown */
        SDL_DATA_WINDOWEVENT_HIDDEN = 0x0000002,                    /**< Window has been hidden */
        SDL_DATA_WINDOWEVENT_EXPOSED = 0x0000004,                   /**< Window has been exposed and should be redrawn, and can be redrawn directly from event watchers for this event.
                                                                         data1 is 1 for live-resize expose events, 0 otherwise. */
        SDL_DATA_WINDOWEVENT_MOVED = 0x0000008,                     /**< Window has been moved to data1, data2 */
        SDL_DATA_WINDOWEVENT_RESIZED = 0x0000010,                   /**< Window has been resized to data1xdata2 */
        SDL_DATA_WINDOWEVENT_PIXEL_SIZE_CHANGED = 0x0000020,        /**< The pixel size of the window has changed to data1xdata2 */
        SDL_DATA_WINDOWEVENT_METAL_VIEW_RESIZED = 0x0000040,        /**< The pixel size of a Metal view associated with the window has changed */
        SDL_DATA_WINDOWEVENT_MINIMIZED = 0x0000080,                 /**< Window has been minimized */
        SDL_DATA_WINDOWEVENT_MAXIMIZED = 0x0000100,                 /**< Window has been maximized */
        SDL_DATA_WINDOWEVENT_RESTORED = 0x0000200,                  /**< Window has been restored to normal size and position */
        SDL_DATA_WINDOWEVENT_MOUSE_ENTER = 0x0000400,               /**< Window has gained mouse focus */
        SDL_DATA_WINDOWEVENT_MOUSE_LEAVE = 0x0000800,               /**< Window has lost mouse focus */
        SDL_DATA_WINDOWEVENT_FOCUS_GAINED = 0x0001000,              /**< Window has gained keyboard focus */
        SDL_DATA_WINDOWEVENT_FOCUS_LOST = 0x0002000,                /**< Window has lost keyboard focus */
        SDL_DATA_WINDOWEVENT_CLOSE_REQUESTED = 0x0004000,           /**< The window manager requests that the window be closed */
        SDL_DATA_WINDOWEVENT_HIT_TEST = 0x0008000,                  /**< Window had a hit test that wasn't SDL_HITTEST_NORMAL. */
        SDL_DATA_WINDOWEVENT_ICCPROF_CHANGED = 0x0010000,           /**< The ICC profile of the window's display has changed. */
        SDL_DATA_WINDOWEVENT_DISPLAY_CHANGED = 0x0020000,           /**< Window has been moved to display data1. */
        SDL_DATA_WINDOWEVENT_DISPLAY_SCALE_CHANGED = 0x0040000,     /**< Window display scale has been changed */
        SDL_DATA_WINDOWEVENT_SAFE_AREA_CHANGED = 0x0080000,         /**< The window safe area has been changed */
        SDL_DATA_WINDOWEVENT_OCCLUDED = 0x0100000,                  /**< The window has been occluded */
        SDL_DATA_WINDOWEVENT_ENTER_FULLSCREEN = 0x0200000,          /**< The window has entered fullscreen mode */
        SDL_DATA_WINDOWEVENT_LEAVE_FULLSCREEN = 0x0400000,          /**< The window has left fullscreen mode */
        SDL_DATA_WINDOWEVENT_WINDOW_DESTROYED = 0x0800000,          /**< The window with the associated ID is being or has been destroyed. If this message is being handled
                                                                         in an event watcher, the window handle is still valid and can still be used to retrieve any properties
                                                                         associated with the window. Otherwise, the handle has already been destroyed and all resources
                                                                         associated with it are invalid */
        SDL_DATA_WINDOWEVENT_HDR_STATE_CHANGED = 0x1000000,         /**< Window HDR properties have changed */
    };

    struct SdlWindowEventData
    {
        uint64_t timestamp;                 /**< In milliseconds, populated using SDL_GetTicks() */
        uint32_t reserved;    
        uint32_t windowID;                  /**< The associated window */
        SdlWindowSubEventID event;          /**< Event ID */
        int32_t data1;                      /**< event dependent data */
        int32_t data2;                      /**< event dependent data */
        int32_t padding;                    /**< event dependent data */

        SdlWindowEventData();
        ~SdlWindowEventData();
    };
}
