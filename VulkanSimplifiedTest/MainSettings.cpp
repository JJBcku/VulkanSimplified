#include "pch.h"
#include "MainSettings.h"

#include "EventHandler/SdlQuitEventData.h"

MainSettings::MainSettings()
{
	_quit = false;
	for (size_t i = 0; i < sizeof(_padding); i++)
		_padding[i] = 0;
}

MainSettings::~MainSettings()
{
}

bool MainSettings::IsClosingRequested() const
{
	return _quit;
}

bool MainSettings::QuitEventCallback(const VS::SdlQuitEventData&, void* instance)
{
	if (instance != nullptr)
	{
		MainSettings* pointer = static_cast<MainSettings*>(instance);
		pointer->SetQuit();
		return false;
	}

	return true;
}

void MainSettings::SetQuit()
{
	_quit = true;
}