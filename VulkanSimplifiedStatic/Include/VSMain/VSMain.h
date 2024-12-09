#pragma once

#include <memory>

class VSMainInternal;
struct VSMainInitData;

class VSMain
{
public:
	VSMain(const VSMainInitData& initData);
	~VSMain();

private:
	std::unique_ptr<VSMainInternal> _internal;
};