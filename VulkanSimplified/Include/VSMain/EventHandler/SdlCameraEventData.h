#pragma once

#include <stdint.h>

namespace VulkanSimplified
{
	enum class SdlCameraDeviceEventSubtype : uint64_t
	{
		CAMERA_DEVICE_EVENT_UNSET = 0x0,

		CAMERA_DEVICE_EVENT_ADDED = 0x1,
		CAMERA_DEVICE_EVENT_REMOVED = 0x2,
		CAMERA_DEVICE_EVENT_APPROVED = 0x4,
		CAMERA_DEVICE_EVENT_DENIED = 0x8,
	};

	struct SdlCameraEventData
	{
		SdlCameraDeviceEventSubtype eventSubtype;
		uint64_t timestamp;								/**< In nanoseconds, populated using SDL_GetTicksNS() */
		uint32_t reserved;
		uint32_t cameraID;								/**< SDL_CameraID for the device being added or removed or changing */

		SdlCameraEventData();
		~SdlCameraEventData();
	};
}