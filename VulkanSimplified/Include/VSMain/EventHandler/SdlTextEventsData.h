#pragma once

#include <stdint.h>

namespace VulkanSimplified
{
    struct SdlTextEditingEventData
    {
        uint64_t reserved;
        uint64_t timestamp;                           /**< In milliseconds, populated using SDL_GetTicks() */
        uint32_t windowID;                            /**< The window with keyboard focus, if any */
        uint32_t padding;
        const char* text;                             /**< The editing text */
        int32_t start;                                /**< The start cursor of selected editing text */
        int32_t length;                               /**< The length of selected editing text */

        SdlTextEditingEventData();
        ~SdlTextEditingEventData();
    };

    constexpr uint32_t SDL_DATA_TEXTINPUTEVENT_TEXT_SIZE = 32;

    struct SdlTextInputEventData
    {
        uint64_t timestamp;                         /**< In milliseconds, populated using SDL_GetTicks() */
        uint32_t reserved;
        uint32_t windowID;                          /**< The window with keyboard focus, if any */
        const char* text;                           /**< The input text */

        SdlTextInputEventData();
        ~SdlTextInputEventData();
    };

    struct SdlTextEditingCandidatesEventData
    {
        uint64_t timestamp;                 /**< In nanoseconds, populated using SDL_GetTicksNS() */
        uint32_t reserved;
        uint32_t windowID;                  /**< The window with keyboard focus, if any */
        const char* const* candidates;      /**< The list of candidates, or NULL if there are no candidates available */
        int32_t num_candidates;             /**< The number of strings in `candidates` */
        int32_t selected_candidate;         /**< The index of the selected candidate, or -1 if no candidate is selected */
        bool horizontal;                    /**< true if the list is horizontal, false if it's vertical */
        uint8_t padding1;
        uint8_t padding2;
        uint8_t padding3;
        uint32_t padding4;

        SdlTextEditingCandidatesEventData();
        ~SdlTextEditingCandidatesEventData();
    };
}
