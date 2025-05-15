#pragma once

#include <memory>

struct VulkanBasicData;
struct VulkanSharedData;
struct VulkanInstanceDependentData;
struct VulkanDeviceDependentData;
struct VulkanRenderPassData;
struct VulkanPipelineData;
struct VulkanMemoryData;
struct VulkanSynchronizationData;
struct VulkanCommandBufferData;
struct VulkanDescriptorData;
struct VulkanFrameData;

struct VulkanData
{
	std::unique_ptr<VulkanBasicData> basicData;
	std::unique_ptr<VulkanSharedData> sharedData;
	std::unique_ptr<VulkanInstanceDependentData> instanceDependentData;
	std::unique_ptr<VulkanDeviceDependentData> deviceDependentData;
	std::unique_ptr<VulkanRenderPassData> renderPassData;
	std::unique_ptr<VulkanPipelineData> pipelineData;
	std::unique_ptr<VulkanMemoryData> memoryData;
	std::unique_ptr<VulkanSynchronizationData> synchronizationData;
	std::unique_ptr<VulkanCommandBufferData> commandBufferData;
	std::unique_ptr<VulkanDescriptorData> descriptorData;

	std::unique_ptr<VulkanFrameData> frameData;

	VulkanData();
	~VulkanData();
};