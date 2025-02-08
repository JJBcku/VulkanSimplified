#pragma once

#include <memory>

struct VulkanBasicData;
struct VulkanInstanceDependentData;
struct VulkanDeviceDependentData;

struct VulkanData
{
	std::unique_ptr<VulkanBasicData> basicData;
	std::unique_ptr<VulkanInstanceDependentData> instanceDependentData;
	std::unique_ptr<VulkanDeviceDependentData> deviceDependentData;

	VulkanData();
	~VulkanData();
};