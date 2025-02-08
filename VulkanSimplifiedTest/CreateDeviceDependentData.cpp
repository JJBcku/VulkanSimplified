#include "pch.h"
#include "CreateDeviceDependentData.h"

#include "VulkanData.h"
#include "VulkanBasicData.h"
#include "VulkanInstanceDependentData.h"
#include "VulkanDeviceDependentData.h"

#include <VSMain.h>
#include <VSInstance.h>
#include <VSDeviceMain.h>

#include <VSWindowList.h>
#include <VSWindowCreationData.h>

void CreateDeviceDependentData(VulkanData& data)
{
	auto& base = data.basicData->vsmain.value();
	auto instance = base.GetInstance();
	auto device = instance.GetChoosenDevicesMainClass();

	auto windowList = device.GetWindowList();

	data.deviceDependentData = std::make_unique<VulkanDeviceDependentData>();

	VulkanSimplified::WindowCreationData windowCreationData;
	windowCreationData.width = 800;
	windowCreationData.height = 600;
	windowCreationData.windowTitle = "Test Window";

	data.deviceDependentData->windowID = windowList.CreateWindow(windowCreationData);
}
