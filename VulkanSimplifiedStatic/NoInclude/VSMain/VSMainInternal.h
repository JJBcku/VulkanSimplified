#pragma once

#include "EventHandler/SdlEventHandlerInternal.h"

struct VSMainInitData;

class VSMainInternal
{
public:
	VSMainInternal(const VSMainInitData& initData);
	~VSMainInternal();

	SdlEventHandlerInternal& GetSdlEventHandler();

	const SdlEventHandlerInternal& GetSdlEventHandler() const;

private:
	SdlEventHandlerInternal _eventHandler;

	uint64_t stump;
};