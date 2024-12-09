#include "VSMainIpch.h"
#include "VSMain.h"

#include "../../NoInclude/VSMain/VSMainInternal.h"

#include "VSMainInitData.h"

VSMain::VSMain(const VSMainInitData& initData)
{
	_internal = std::make_unique<VSMainInternal>(initData);
}

VSMain::~VSMain()
{
}
