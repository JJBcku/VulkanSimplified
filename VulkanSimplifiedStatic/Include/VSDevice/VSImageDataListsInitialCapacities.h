#pragma once

namespace VulkanSimplified
{
	struct ImageDataListsInitialCapacities
	{
		size_t colorRenderTargetsListInitialCapacity;
		size_t twoDTexturesListInitialCapacity;

		size_t framebufferListInitialCapacity;

		ImageDataListsInitialCapacities();
	};
}