#include "VSInstanceIpch.h"
#include "VSDeviceVulkan10Limits.h"

namespace VulkanSimplified
{
	Vulkan10MaxImageSizeLimits::Vulkan10MaxImageSizeLimits()
	{
		maxImageDimension1D = 0;
		maxImageDimension2D = 0;
		maxImageDimension3D = 0;
		maxImageArrayLayers = 0;
	}

	Vulkan10DescriptorSetBindingLimits::Vulkan10DescriptorSetBindingLimits()
	{
		maxBoundDescriptorSets = 0;
		maxPerStageDescriptorSamplers = 0;
		maxPerStageDescriptorUniformBuffers = 0;
		maxPerStageDescriptorStorageBuffers = 0;
		maxPerStageDescriptorSampledImages = 0;
		maxPerStageDescriptorStorageImages = 0;
		maxPerStageDescriptorInputAttachments = 0;
		maxPerStageResources = 0;
	}

	Vulkan10DescriptorSetLimits::Vulkan10DescriptorSetLimits()
	{
		maxDescriptorSetSamplers = 0;
		maxDescriptorSetUniformBuffers = 0;
		maxDescriptorSetUniformBuffersDynamic = 0;
		maxDescriptorSetStorageBuffers = 0;
		maxDescriptorSetStorageBuffersDynamic = 0;
		maxDescriptorSetSampledImages = 0;
		maxDescriptorSetStorageImages = 0;
		maxDescriptorSetInputAttachments = 0;
	}

	Vulkan10VertexShaderLimits::Vulkan10VertexShaderLimits()
	{
		maxVertexInputAttributes = 0;
		maxVertexInputBindings = 0;
		maxVertexInputAttributeOffset = 0;
		maxVertexInputBindingStride = 0;
		maxVertexOutputComponents = 0;
	}

	Vulkan10FragmentShaderLimits::Vulkan10FragmentShaderLimits()
	{
		maxFragmentInputComponents = 0;
		maxFragmentOutputAttachments = 0;
		maxFragmentDualSrcAttachments = 0;
		maxFragmentCombinedOutputResources = 0;
	}

	Vulkan10ViewportLimits::Vulkan10ViewportLimits()
	{
		maxViewports = 0;
		maxViewportDimensionsX = 0;
		maxViewportDimensionsY = 0;
		viewportBoundsRangeMin = 0.0f;
		viewportBoundsRangeMax = 0.0f;
		viewportSubPixelBits = 0;
	}

	Vulkan10FramebufferLimits::Vulkan10FramebufferLimits()
	{
		maxFramebufferWidth = 0;
		maxFramebufferHeight = 0;
		maxFramebufferLayers = 0;
		framebufferColorSampleCounts = 0;
		framebufferDepthSampleCounts = 0;
		framebufferStencilSampleCounts = 0;
		framebufferNoAttachmentsSampleCounts = 0;
	}

	Vulkan10SamplingLimits::Vulkan10SamplingLimits()
	{
		sampledImageColorSampleCounts = 0;
		sampledImageIntegerSampleCounts = 0;
		sampledImageDepthSampleCounts = 0;
		sampledImageStencilSampleCounts = 0;
		storageImageSampleCounts = 0;
	}

	DeviceVulkan10Limits::DeviceVulkan10Limits()
	{
		maxUniformBufferRange = 0;
		maxStorageBufferRange = 0;
		maxPushConstantsSize = 0;

		maxMemoryAllocationCount = 0;
		maxSamplerAllocationCount = 0;

		subPixelPrecisionBits = 0;
		mipmapPrecisionBits = 0;

		maxDrawIndexedIndexValue = 0;

		maxSamplerLodBias = 0.0f;
		maxSamplerAnisotropy = 0.0f;

		maxColorAttachments = 0;
	}
}