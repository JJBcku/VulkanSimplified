#pragma once

#include "EventHandler/SdlEventHandlerInitData.h"

struct VSMainInitData
{
	SdlEventHandlerInitData eventHandlerData;
	uint64_t stump;

	VSMainInitData();
	~VSMainInitData();
};