#pragma once

#include <optional>

#include "VSMain.h"

struct VulkanBasicData
{
	std::optional<VSMain> vsmain;

	VulkanBasicData();
	~VulkanBasicData();
};