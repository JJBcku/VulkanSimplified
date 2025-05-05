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
#include "CreateCommandBufferData.h"

#include "MiscFunctions.h"
#include "RunFrame.h"
#include "SwapchainSizes.h"

#include "VulkanBasicData.h"
#include "VulkanDeviceDependentData.h"

#include <VSMain.h>
#include <VSInstance.h>
#include <VSDeviceMain.h>
#include <VSWindowList.h>
#include <VSWindow.h>

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
	CreateCommandBufferData(data);

	uint32_t frameIndex = 0;

	auto windowList = data.basicData->vsmain->GetInstance().GetChoosenDevicesMainClass().GetWindowList();
	auto window = windowList.GetWindow(data.deviceDependentData->windowID);

	while (!settings.IsClosingRequested())
	{
		HandleEvents(data);

		if (window.IsHidden() || window.IsMinimized())
		{
			std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(10));
		}
		else
		{
			RunFrame(data, frameIndex);

			if (++frameIndex >= framesInFlight)
				frameIndex = 0;
		}
	}

	WaitIdle(data);
}
