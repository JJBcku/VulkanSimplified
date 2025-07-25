#include "VSInstanceIpch.h"
#include "../../../Include/VSInstance/VSDeviceQueueFamilyData.h"

#include <Miscellaneous/Bool64.h>

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

		presentationSupport = Misc::BOOL64_FALSE;
	}

	QueueFamilyData::~QueueFamilyData()
	{
	}
}