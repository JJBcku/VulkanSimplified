#pragma once

#include <memory>

struct VulkanBasicData;
struct VulkanSharedData;
struct VulkanInstanceDependentData;
struct VulkanDeviceDependentData;
struct VulkanRenderPassData;
struct VulkanPipelineData;

struct VulkanData
{
	std::unique_ptr<VulkanBasicData> basicData;
	std::unique_ptr<VulkanSharedData> sharedData;
	std::unique_ptr<VulkanInstanceDependentData> instanceDependentData;
	std::unique_ptr<VulkanDeviceDependentData> deviceDependentData;
	std::unique_ptr<VulkanRenderPassData> renderPassData;
	std::unique_ptr<VulkanPipelineData> pipelineData;

	VulkanData();
	~VulkanData();
};