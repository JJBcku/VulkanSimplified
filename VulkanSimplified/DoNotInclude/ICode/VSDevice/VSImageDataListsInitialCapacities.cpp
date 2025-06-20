#include "VSDeviceIpch.h"
#include "../../../Include/VSDevice/VSImageDataListsInitialCapacities.h"

namespace VulkanSimplified
{
	ImageDataListsInitialCapacities::ImageDataListsInitialCapacities()
	{
		colorRenderTargetsListInitialCapacity = 0;
		depthStencilRenderTargetsListInitialCapacity = 0;
		resolveRenderTargetsListInitialCapacity = 0;

		twoDTexturesListInitialCapacity = 0;

		framebufferListInitialCapacity = 0;
		samplerListInitialCapacity = 0;
	}
}