#pragma once

#include <stdint.h>

namespace VulkanSimplified
{
    enum SdlPenStateData : uint32_t
    {
        PEN_STATE_INPUT_DOWN = 0x1,
        PEN_STATE_INPUT_BUTTON1 = 0x2,
        PEN_STATE_INPUT_BUTTON2 = 0x4,
        PEN_STATE_INPUT_BUTTON3 = 0x8,
        PEN_STATE_INPUT_BUTTON4 = 0x10,
        PEN_STATE_INPUT_BUTTON5 = 0x20,

        PEN_STATE_INPUT_ERASER_TIPS = 0x20000000,
        PEN_STATE_INPUT_IN_PROXIMITY = 0x40000000,
    };

    enum class SdlPenAxisData : uint32_t
    {
        PEN_AXIS_PRESSURE = 0x01,                   /**< Pen pressure.  Unidirectional: 0 to 1.0 */
        PEN_AXIS_XTILT = 0x02,                      /**< Pen horizontal tilt angle.  Bidirectional: -90.0 to 90.0 (left-to-right). */
        PEN_AXIS_YTILT = 0x04,                      /**< Pen vertical tilt angle.  Bidirectional: -90.0 to 90.0 (top-to-down). */
        PEN_AXIS_DISTANCE = 0x08,                   /**< Pen distance to drawing surface.  Unidirectional: 0.0 to 1.0 */
        PEN_AXIS_ROTATION = 0x10,                   /**< Pen barrel rotation.  Bidirectional: -180 to 179.9 (clockwise, 0 is facing up, -180.0 is facing down). */
        PEN_AXIS_SLIDER = 0x20,                     /**< Pen finger wheel or slider (e.g., Airbrush Pen).  Unidirectional: 0 to 1.0 */
        PEN_AXIS_TANGENTIAL_PRESSURE = 0x40,        /**< Pressure from squeezing the pen ("barrel pressure"). */
        PEN_AXIS_COUNT = 0x40,                      /**< Total known pen axis types in this version of SDL. This number may grow in future releases! */
    };

    struct SdlPenAxisEventData
    {
        uint64_t timestamp;         /**< In nanoseconds, populated using SDL_GetTicksNS() */
        uint32_t reserved;
        uint32_t windowID;          /**< The window with pen focus, if any */
        uint32_t penID;             /**< The pen instance id */
        uint32_t pen_state;         /**< Complete pen input state at time of event */
        float x;                    /**< X coordinate, relative to window */
        float y;                    /**< Y coordinate, relative to window */
        uint32_t axis;              /**< Axis that has changed */
        float value;                /**< New value of axis */

        SdlPenAxisEventData();
        ~SdlPenAxisEventData();
    };

    enum class SdlPenButtonEventSubtype : uint32_t
    {
        PEN_BUTTON_UNSET = 0x0,

        PEN_BUTTON_DOWN = 0x1,
        PEN_BUTTON_UP = 0x2,
    };

    struct SdlPenButtonEventData
    {
        SdlPenButtonEventSubtype subtype;
        uint32_t reserved;
        uint64_t timestamp;                 /**< In nanoseconds, populated using SDL_GetTicksNS() */
        uint32_t windowID;                  /**< The window with mouse focus, if any */
        uint32_t penID;                     /**< The pen instance id */
        uint32_t pen_state;                 /**< Complete pen input state at time of event */
        float x;                            /**< X coordinate, relative to window */
        float y;                            /**< Y coordinate, relative to window */
        uint8_t button;                     /**< The pen button index (first button is 1). */
        bool down;                          /**< true if the button is pressed */
        uint16_t padding;

        SdlPenButtonEventData();
        ~SdlPenButtonEventData();
    };

    struct SdlPenMotionEventData
    {
        uint64_t timestamp;         /**< In nanoseconds, populated using SDL_GetTicksNS() */
        uint32_t reserved;
        uint32_t windowID;          /**< The window with pen focus, if any */
        uint32_t penID;             /**< The pen instance id */
        uint32_t pen_state;         /**< Complete pen input state at time of event */
        float x;                    /**< X coordinate, relative to window */
        float y;                    /**< Y coordinate, relative to window */

        SdlPenMotionEventData();
        ~SdlPenMotionEventData();
    };

    enum class SdlPenTouchEventSubtype : uint32_t
    {
        PEN_TOUCH_UNSET = 0x0,

        PEN_TOUCH_DOWN = 0x1,
        PEN_TOUCH_UP = 0x2,
    };

    struct SdlPenTouchEventData
    {
        SdlPenTouchEventSubtype subtype;
        uint32_t reserved;
        uint64_t timestamp;                 /**< In nanoseconds, populated using SDL_GetTicksNS() */
        uint32_t windowID;                  /**< The window with pen focus, if any */
        uint32_t penID;                     /**< The pen instance id */
        uint32_t pen_state;                 /**< Complete pen input state at time of event */
        float x;                            /**< X coordinate, relative to window */
        float y;                            /**< Y coordinate, relative to window */
        bool eraser;                        /**< true if eraser end is used (not all pens support this). */
        bool down;                          /**< true if the pen is touching or false if the pen is lifted off */
        uint16_t padding;

        SdlPenTouchEventData();
        ~SdlPenTouchEventData();
    };

    enum class SdlPenProximityEventSubtype : uint32_t
    {
        PEN_PROXIMITY_UNSET = 0x0,

        PEN_PROXIMITY_IN = 0x1,
        PEN_PROXIMITY_OUT = 0x2,
    };

    struct SdlPenProximityEventData
    {
        SdlPenProximityEventSubtype subtype;
        uint32_t reserved;
        uint64_t timestamp;                     /**< In nanoseconds, populated using SDL_GetTicksNS() */
        uint32_t windowID;                      /**< The window with pen focus, if any */
        uint32_t penID;                         /**< The pen instance id */

        SdlPenProximityEventData();
        ~SdlPenProximityEventData();
    };

}