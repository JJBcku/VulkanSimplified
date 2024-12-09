#pragma once

#include <memory>

class VSMainInternal;

class VSMain
{
public:
	VSMain();
	~VSMain();

private:
	std::unique_ptr<VSMainInternal> _internal;
};