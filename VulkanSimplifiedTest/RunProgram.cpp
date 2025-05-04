#include "pch.h"
#include "RunProgram.h"

#include "VulkanData.h"
#include "MainSettings.h"

#include "CreateBasicData.h"
#include "CreateInstanceDependentData.h"
#include "CreateDeviceDependentData.h"
#include "CreateSharedData.h"
#include "CreateRenderPassData.h"
#include "CreatePipelineData.h"
#include "CreateMemoryData.h"
#include "CreateSynchronizationData.h"

#include "MiscFunctions.h"

#include <thread>

void RunProgram()
{
	VulkanData data;
	MainSettings settings;

	CreateBasicData(data, settings);
	CreateSharedData(data);
	CreateInstanceDependentData(data);
	CreateDeviceDependentData(data);
	CreateRenderPassData(data);
	CreatePipelineData(data);
	CreateMemoryData(data);
	CreateSynchronizationData(data);

	while (!settings.IsClosingRequested())
	{
		HandleEvents(data);

		std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(10));
	}

	WaitIdle(data);
}
