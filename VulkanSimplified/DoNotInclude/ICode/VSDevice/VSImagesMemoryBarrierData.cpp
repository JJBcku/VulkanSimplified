#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSImagesMemoryBarrierData.h"

#include "../../../Include/VSCommon/VSBool64.h"
#include "../../../Include/VSCommon/VSImageLayoutFlags.h"

namespace VulkanSimplified
{
	ImagesMemoryBarrierData::ImagesMemoryBarrierData()
	{
		srcAccess = 0;
		dstAccess = 0;
		oldLayout = ImageLayoutFlags::UNDEFINED;
		newLayout = ImageLayoutFlags::UNDEFINED;
	}
}