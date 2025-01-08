#pragma once

namespace VulkanSimplified
{
	struct Vulkan10MaxImageSizeLimits
	{
		std::uint64_t maxImageDimension1D;
		std::uint64_t maxImageDimension2D;
		std::uint64_t maxImageDimension3D;
		std::uint64_t maxImageArrayLayers;

		Vulkan10MaxImageSizeLimits();
	};

	struct Vulkan10DescriptorSetBindingLimits
	{
		std::uint64_t maxBoundDescriptorSets;
		std::uint64_t maxPerStageDescriptorSamplers;
		std::uint64_t maxPerStageDescriptorUniformBuffers;
		std::uint64_t maxPerStageDescriptorStorageBuffers;
		std::uint64_t maxPerStageDescriptorSampledImages;
		std::uint64_t maxPerStageDescriptorStorageImages;
		std::uint64_t maxPerStageDescriptorInputAttachments;
		std::uint64_t maxPerStageResources;

		Vulkan10DescriptorSetBindingLimits();
	};

	struct Vulkan10DescriptorSetLimits
	{
		Vulkan10DescriptorSetBindingLimits descriptorSetBindingsLimit;

		std::uint64_t maxDescriptorSetSamplers;
		std::uint64_t maxDescriptorSetUniformBuffers;
		std::uint64_t maxDescriptorSetUniformBuffersDynamic;
		std::uint64_t maxDescriptorSetStorageBuffers;
		std::uint64_t maxDescriptorSetStorageBuffersDynamic;
		std::uint64_t maxDescriptorSetSampledImages;
		std::uint64_t maxDescriptorSetStorageImages;
		std::uint64_t maxDescriptorSetInputAttachments;

		Vulkan10DescriptorSetLimits();
	};

	struct Vulkan10VertexShaderLimits
	{
		std::uint64_t maxVertexInputAttributes;
		std::uint64_t maxVertexInputBindings;
		std::uint64_t maxVertexInputAttributeOffset;
		std::uint64_t maxVertexInputBindingStride;
		std::uint64_t maxVertexOutputComponents;

		Vulkan10VertexShaderLimits();
	};

	struct Vulkan10FragmentShaderLimits
	{
		std::uint64_t maxFragmentInputComponents;
		std::uint64_t maxFragmentOutputAttachments;
		std::uint64_t maxFragmentDualSrcAttachments;
		std::uint64_t maxFragmentCombinedOutputResources;

		Vulkan10FragmentShaderLimits();
	};

	struct Vulkan10ViewportLimits
	{
		std::uint64_t maxViewports;
		std::uint64_t maxViewportDimensionsX;
		std::uint64_t maxViewportDimensionsY;
		float viewportBoundsRangeMin;
		float viewportBoundsRangeMax;
		std::uint64_t viewportSubPixelBits;

		Vulkan10ViewportLimits();
	};

	struct Vulkan10FramebufferLimits
	{
		std::uint64_t maxFramebufferWidth;
		std::uint64_t maxFramebufferHeight;
		std::uint64_t maxFramebufferLayers;
		std::uint64_t framebufferColorSampleCounts;
		std::uint64_t framebufferDepthSampleCounts;
		std::uint64_t framebufferStencilSampleCounts;
		std::uint64_t framebufferNoAttachmentsSampleCounts;

		Vulkan10FramebufferLimits();
	};

	struct Vulkan10SamplingLimits
	{
		std::uint64_t sampledImageColorSampleCounts;
		std::uint64_t sampledImageIntegerSampleCounts;
		std::uint64_t sampledImageDepthSampleCounts;
		std::uint64_t sampledImageStencilSampleCounts;
		std::uint64_t storageImageSampleCounts;

		Vulkan10SamplingLimits();
	};

	struct DeviceVulkan10Limits
	{
		Vulkan10MaxImageSizeLimits maxImageSizes;

		std::uint64_t maxUniformBufferRange;
		std::uint64_t maxStorageBufferRange;
		std::uint64_t maxPushConstantsSize;

		std::uint64_t maxMemoryAllocationCount;
		std::uint64_t maxSamplerAllocationCount;

		Vulkan10DescriptorSetLimits descriptorSetLimits;

		Vulkan10VertexShaderLimits vertexShaderLimit;
		Vulkan10FragmentShaderLimits fragmentShaderLimit;

		std::uint64_t subPixelPrecisionBits;
		std::uint64_t mipmapPrecisionBits;

		std::uint64_t maxDrawIndexedIndexValue;

		float maxSamplerLodBias;
		float maxSamplerAnisotropy;

		Vulkan10ViewportLimits viewportLimits;
		Vulkan10FramebufferLimits framebufferLimits;

		std::uint64_t maxColorAttachments;

		Vulkan10SamplingLimits samplingLimits;

		DeviceVulkan10Limits();
	};
}