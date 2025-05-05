#pragma once

#include <CustomLists/IDObject.h>

#include <VSCommandPoolMainListDef.h>
#include <VSCommandPoolQFGroupListDef.h>
#include <VSIRCommandPoolDef.h>

struct VulkanCommandBufferData
{
	IDObject<VulkanSimplified::CommandPoolQFGroupPointer> graphicGroup;
	std::optional<IDObject<VulkanSimplified::CommandPoolQFGroupPointer>> transferGroup;
	std::optional<IDObject<VulkanSimplified::CommandPoolQFGroupPointer>> presentGroup;

	IDObject<VulkanSimplified::IRPoolPointer> graphicPool;
	std::optional<IDObject<VulkanSimplified::IRPoolPointer>> transferPool;
	std::optional<IDObject<VulkanSimplified::IRPoolPointer>> presentPool;

	std::vector<IDObject<VulkanSimplified::PrimaryIRPointer>> graphicBuffers;
	std::optional<std::vector<IDObject<VulkanSimplified::PrimaryIRPointer>>> transferBuffers;
	std::optional<std::vector<IDObject<VulkanSimplified::PrimaryIRPointer>>> presentBuffers;

	VulkanCommandBufferData() = default;
};