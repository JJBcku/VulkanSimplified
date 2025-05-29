#include "VSDeviceIpch.h"
#include "VSImageDataListsInitialCapacities.h"

namespace VulkanSimplified
{
	ImageDataListsInitialCapacities::ImageDataListsInitialCapacities()
	{
		colorRenderTargetsListInitialCapacity = 0;
		twoDTexturesListInitialCapacity = 0;

		framebufferListInitialCapacity = 0;
	}
}