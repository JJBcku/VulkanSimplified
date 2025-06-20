#pragma once

#include <CustomLists/IDObject.h>

#include <VSCommandPoolMainListDef.h>
#include <VSCommandPoolQFGroupListDef.h>
#include <VSIRCommandPoolDef.h>

struct VulkanCommandBufferData
{
	IDObject<VS::CommandPoolQFGroupPointer> graphicGroup;
	std::optional<IDObject<VS::CommandPoolQFGroupPointer>> transferGroup;
	std::optional<IDObject<VS::CommandPoolQFGroupPointer>> presentGroup;

	IDObject<VS::IRPoolPointer> graphicPool;
	std::optional<IDObject<VS::IRPoolPointer>> transferPool;
	std::optional<IDObject<VS::IRPoolPointer>> presentPool;

	std::vector<IDObject<VS::PrimaryIRPointer>> graphicBuffers;
	std::vector<IDObject<VS::PrimaryIRPointer>> transferBuffers;
	std::vector<IDObject<VS::PrimaryIRPointer>> presentBuffers;

	VulkanCommandBufferData() = default;
};