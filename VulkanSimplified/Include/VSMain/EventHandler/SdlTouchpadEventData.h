#pragma once

#include <stdint.h>

namespace VulkanSimplified
{
    enum class SdlTouchFingerEventType : uint32_t
    {
        FINGER_UNSET = 0x0,

        FINGER_DOWN = 0x1,
        FINGER_UP = 0x2,
        FINGER_MOTION = 0x4,
        FINGER_CANCELLED = 0x8,
    };

    struct SdlTouchFingerEventData
    {
        SdlTouchFingerEventType type;
        uint32_t reserved;
        uint64_t timestamp;     /**< In milliseconds, populated using SDL_GetTicks() */
        uint64_t touchId;       /**< The touch device id */
        uint64_t fingerId;
        float x;                /**< Normalized in the range 0...1 */
        float y;                /**< Normalized in the range 0...1 */
        float dx;               /**< Normalized in the range -1...1 */
        float dy;               /**< Normalized in the range -1...1 */
        float pressure;         /**< Normalized in the range 0...1 */
        uint32_t windowID;      /**< The window underneath the finger, if any */

        SdlTouchFingerEventData();
        ~SdlTouchFingerEventData();
    };

    enum class SdlTouchPinchEventType : uint32_t
    {
        PINCH_UNSET = 0x0,

        PINCH_BEGIN = 0x1,
        PINCH_UPDATE = 0x2,
        PINCH_END = 0x4,
    };

    struct SdlTouchPinchEventData
    {
        SdlTouchPinchEventType type;
        uint32_t reserved;
        uint64_t timestamp;         /**< In nanoseconds, populated using SDL_GetTicksNS() */
        float scale;                /**< The scale change since the last SDL_EVENT_PINCH_UPDATE. Scale < 1 is "zoom out". Scale > 1 is "zoom in". */
        uint32_t windowID;          /**< The window underneath the finger, if any */

        SdlTouchPinchEventData();
        ~SdlTouchPinchEventData();
    };
}
