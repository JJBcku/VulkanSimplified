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
#include "CreateDescriptorData.h"
#include "CreateTextureData.h"

#include "CreateFrameData.h"

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
#include <iostream>

void RunProgram()
{
	VulkanData data;
	MainSettings settings;

	CreateBasicData(data, settings);
	CreateInstanceDependentData(data);
	CreateSharedData(data);
	CreateDeviceDependentData(data);
	CreateRenderPassData(data);
	CreatePipelineData(data);
	CreateMemoryData(data);
	CreateSynchronizationData(data);
	CreateCommandBufferData(data);
	CreateDescriptorData(data);

	CreateFrameData(data);
	CreateTextureData(data);

	uint32_t frameIndex = 0;
	size_t framesThisSecond = 0;

	float lastSecond = 0.0;

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

			framesThisSecond++;

			static const auto startTime = std::chrono::high_resolution_clock::now();

			auto currentTime = std::chrono::high_resolution_clock::now();

			float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

			if (time - lastSecond >= 1.0f)
			{
				lastSecond = time;
				std::cout << "FPS: " << framesThisSecond << std::endl;
				framesThisSecond = 0;
			}
		}
	}

	WaitIdle(data);
}
