#include "VSInstanceIpch.h"
#include "../../../Include/VSInstance/VSDeviceQueueFamilyData.h"

namespace VulkanSimplified
{
	QueueFamilyData::QueueFamilyData()
	{
		queueTypes = 0;
		queueCount = 0;
		timespampValidBits = 0;
		minImageTransferGranularityWidth = 0;
		minImageTransferGranularityHeight = 0;
		minImageTransferGranularityDepth = 0;

		presentationSupport = BOOL64_FALSE;
	}

	QueueFamilyData::~QueueFamilyData()
	{
	}
}