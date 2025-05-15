#include "VSDeviceNIpch.h"
#include "VSDescriptorPoolTypeCapacities.h"

namespace VulkanSimplifiedInternal
{
	DescriptorPoolTypeCapacities::DescriptorPoolTypeCapacities()
	{
		samplerCapacity = 0;
		combinedImageSamplerCapacity = 0;
		sampledImageCapacity = 0;
		storageImageCapacity = 0;
		uniformTexelBufferCapacity = 0;
		storageTexelBufferCapacity = 0;
		uniformBufferCapacity = 0;
		storageBufferCapacity = 0;
		dynamicUniformBufferCapacity = 0;
		dynamicStorageBufferCapacity = 0;
		inputAttachmentCapacity = 0;
	}
}