#include "VSDeviceIpch.h"
#include "VSImagesMemoryBarrierData.h"

#include "../VSCommon/VSBool64.h"
#include "../VSCommon/VSImageLayoutFlags.h"

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