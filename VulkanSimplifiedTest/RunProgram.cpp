#include "pch.h"
#include "RunProgram.h"

#include "VulkanData.h"
#include "MainSettings.h"

#include "CreateBasicData.h"

void RunProgram()
{
	VulkanData data;
	MainSettings settings;

	CreateBasicData(data, settings);
}
