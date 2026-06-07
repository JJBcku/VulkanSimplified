#pragma once

#include <stdint.h>

namespace VulkanSimplified
{
    enum class SdlAudioDeviceEventSubtype : uint32_t
    {
        AUDIO_DEVICE_EVENT_UNSET = 0,

        AUDIO_DEVICE_EVENT_ADDED = 1,
        AUDIO_DEVICE_EVENT_REMOVED = 2,
        AUDIO_DEVICE_EVENT_FORMAT_CHANGED = 4,
    };

    struct SdlAudioDeviceEventData
    {
        SdlAudioDeviceEventSubtype type;
        uint32_t reserved;
        uint64_t timestamp;                     /**< In milliseconds, populated using SDL_GetTicks() */
        uint32_t which;                         /**< The audio device index for the ADDED event (valid until next SDL_GetNumAudioDevices() call), SDL_AudioDeviceID for the REMOVED event */
        bool recording;
        uint8_t padding1;
        uint8_t padding2;
        uint8_t padding3;

        SdlAudioDeviceEventData();
        ~SdlAudioDeviceEventData();
    };
}