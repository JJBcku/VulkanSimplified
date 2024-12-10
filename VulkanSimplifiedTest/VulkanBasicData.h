#pragma once

#include <optional>

#include "VSMain.h"

struct VulkanBasicData
{
	std::optional<VulkanSimplified::VSMain> vsmain;

	VulkanBasicData();
	~VulkanBasicData();
};