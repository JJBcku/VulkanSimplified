#include "SdlEhIpch.h"
#include "../../../../Include/VSMain/EventHandler/SdlCameraEventData.h"

namespace VulkanSimplified
{
	SdlCameraEventData::SdlCameraEventData()
	{
		eventSubtype = SdlCameraDeviceEventSubtype::CAMERA_DEVICE_EVENT_UNSET;
		timestamp = 0;
		reserved = 0;
		cameraID = 0;
	}

	SdlCameraEventData::~SdlCameraEventData()
	{
	}

}