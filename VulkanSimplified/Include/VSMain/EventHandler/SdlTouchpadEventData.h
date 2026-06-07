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
}
