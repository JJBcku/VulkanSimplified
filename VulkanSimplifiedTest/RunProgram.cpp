#include "pch.h"
#include "RunProgram.h"

#include "VulkanData.h"
#include "MainSettings.h"

#include "CreateBasicData.h"
#include "CreateInstanceDependentData.h"
#include "CreateDeviceDependentData.h"

#include "MiscFunctions.h"

#include <thread>

void RunProgram()
{
	VulkanData data;
	MainSettings settings;

	CreateBasicData(data, settings);
	CreateInstanceDependentData(data);
	CreateDeviceDependentData(data);

	while (!settings.IsClosingRequested())
	{
		HandleEvents(data);

		std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(10));
	}

	WaitIdle(data);
}
