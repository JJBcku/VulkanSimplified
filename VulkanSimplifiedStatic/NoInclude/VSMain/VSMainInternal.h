#pragma once

struct VSMainInitData;

class VSMainInternal
{
public:
	VSMainInternal(const VSMainInitData& initData);
	~VSMainInternal();

private:
	uint64_t stump;
};