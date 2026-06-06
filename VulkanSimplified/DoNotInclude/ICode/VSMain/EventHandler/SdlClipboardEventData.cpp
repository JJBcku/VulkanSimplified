#include "SdlEhIpch.h"
#include "../../../../Include/VSMain/EventHandler/SdlClipboardEventData.h"

namespace VulkanSimplified
{
	SdlClipboardEventData::SdlClipboardEventData()
	{
		timestamp = 0;
		reserved = 0;
		owner = false;
		padding1 = 0;
		padding2 = 0;
		mime_types_number = 0;
		padding3 = 0;
		mime_types = nullptr;
	}

	SdlClipboardEventData::~SdlClipboardEventData()
	{
	}
}
