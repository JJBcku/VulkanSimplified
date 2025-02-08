#include "VSDeviceIpch.h"
#include "VSWindowCreationData.h"

namespace VulkanSimplified
{
	WindowCreationData::WindowCreationData()
	{
		windowTitle = "";
		width = 0;
		height = 0;
		settings = WindowSettings::STANDARD;
	}
}