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

#include <VSWindow.h>
#include <VSSwapchainCreationData.h>

#include <VSShaderLists.h>
#include <VSImageDataLists.h>

#include <fstream>

std::vector<char> LoadShader(std::string filename)
{
	std::vector<char> ret;

	std::ifstream file;
	file.open(filename, std::ios_base::binary | std::ios_base::in | std::ios_base::ate);

	if (!file.is_open())
		throw std::runtime_error("LoadShader Error: Program failed to open the file " + filename);

	std::streampos size = file.tellg();

	ret.resize(static_cast<size_t>(size));

	file.seekg(0, std::ios_base::_Seekbeg);

	file.read(ret.data(), size);

	if (!file.good())
		throw std::runtime_error("LoadShader Error: Program failed to read the file " + filename);

	file.close();

	return ret;
}

void CreateDeviceDependentData(VulkanData& data)
{
	auto& base = *data.basicData->vsmain;
	auto instance = base.GetInstance();
	auto device = instance.GetChoosenDevicesMainClass();

	auto windowList = device.GetWindowList();

	data.deviceDependentData = std::make_unique<VulkanDeviceDependentData>();

	VS::WindowCreationData windowCreationData;
	windowCreationData.width = 800;
	windowCreationData.height = 600;
	windowCreationData.windowTitle = "Test Window";
	windowCreationData.settings = VS::WindowSettings::RESIZABLE;

	data.deviceDependentData->windowID = windowList.CreateWindow(windowCreationData);

	auto window = windowList.GetWindow(data.deviceDependentData->windowID);

	VS::SwapchainCreationData swapchainCreationData;

	swapchainCreationData.compositeAlphaMode = VS::COMPOSITE_ALPHA_OPAQUE;
	swapchainCreationData.surfaceTranformMode = VS::SURFACE_TRASFORM_IDENTITY;
	swapchainCreationData.surfacePresentMode = VS::PRESENT_MODE_FIFO_STRICT;
	swapchainCreationData.format = data.instanceDependentData->supportedColorFormat;

	swapchainCreationData.imageAmount = std::min(data.instanceDependentData->minSwapchainImageAmount + 1, data.instanceDependentData->maxSwapchainImageAmount);

	window.CreateSwapchain(swapchainCreationData, true);

	std::string shaderFolder = "shaders\\";

	std::string fragmentName = "basicFragmentShader";
	std::string vertexName = "basicVertexShader";

	std::string fragmentExt = ".frag";
	std::string vertexExt = ".vert";
	std::string fileExt = ".spv";

	std::string fragmentFullName = shaderFolder + fragmentName;
	std::string vertexFullName = shaderFolder + vertexName;

#if defined(_DEBUG) || defined(DEBUG) || defined(DEBUG_UTILS)
	std::string debugExt = ".debug";
	fragmentFullName += debugExt;
	vertexFullName += debugExt;
#endif

	fragmentFullName += fragmentExt + fileExt;
	vertexFullName += vertexExt + fileExt;

	auto fragmentData = LoadShader(fragmentFullName);
	auto vertexData = LoadShader(vertexFullName);

	auto shaderLists = device.GetShaderLists();

	data.deviceDependentData->fragmentShadersID = shaderLists.CreateFragmentShaderModule(*fragmentData.data(), fragmentData.size());
	data.deviceDependentData->vertexShadersID = shaderLists.CreateVertexShaderModule(*vertexData.data(), vertexData.size());

	auto imageList = device.GetImageDataLists();

	data.deviceDependentData->sampler = imageList.AddSampler(true, true, false, false, false, false, 0.0f, data.instanceDependentData->maxAnisotropy, 0.0f, {});
}
