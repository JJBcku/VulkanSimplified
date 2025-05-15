#pragma once

namespace VulkanSimplifiedInternal
{
	struct DescriptorPoolTypeCapacities
	{
		size_t samplerCapacity;
		size_t combinedImageSamplerCapacity;
		size_t sampledImageCapacity;
		size_t storageImageCapacity;
		size_t uniformTexelBufferCapacity;
		size_t storageTexelBufferCapacity;
		size_t uniformBufferCapacity;
		size_t storageBufferCapacity;
		size_t dynamicUniformBufferCapacity;
		size_t dynamicStorageBufferCapacity;
		size_t inputAttachmentCapacity;

		DescriptorPoolTypeCapacities();
	};
}