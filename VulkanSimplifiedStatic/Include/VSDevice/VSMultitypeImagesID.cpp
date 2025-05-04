#include "VSDeviceIpch.h"
#include "VSMultitypeImagesID.h"

VulkanSimplified::MultitypeImagesID::MultitypeImagesID()
{
	type = ImageIDType::UNKNOWN;
}

VulkanSimplified::MultitypeImagesID::MultitypeImagesID(const IDObject<VulkanSimplifiedInternal::AutoCleanupColorRenderTargetImage>& ID)
{
	colorRenderTarget.type = ImageIDType::COLOR_RENDER_TARGET;
	colorRenderTarget.ID = ID;
}
