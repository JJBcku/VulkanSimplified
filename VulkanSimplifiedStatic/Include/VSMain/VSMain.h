#pragma once

#include <memory>

class VSMainInternal;
struct VSMainInitData;

class SdlEventHandler;

class VSMain
{
public:
	VSMain(const VSMainInitData& initData);
	~VSMain();

	SdlEventHandler GetSdlEventHandler();

	const SdlEventHandler GetSdlEventHandler() const;

private:
	std::unique_ptr<VSMainInternal> _internal;
};