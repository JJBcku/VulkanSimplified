#include "VSMainIpch.h"
#include "VSMain.h"

#include "../../NoInclude/VSMain/VSMainInternal.h"

VSMain::VSMain()
{
	_internal = std::make_unique<VSMainInternal>();
}

VSMain::~VSMain()
{
}
