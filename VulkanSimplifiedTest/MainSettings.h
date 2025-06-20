#pragma once

namespace VulkanSimplified
{
	struct SdlQuitEventData;
}

class MainSettings
{
public:
	MainSettings();
	~MainSettings();

	MainSettings(const MainSettings&) noexcept = delete;

	MainSettings& operator=(const MainSettings&) noexcept = delete;

	bool IsClosingRequested() const;

	static bool QuitEventCallback(const VS::SdlQuitEventData&, void* instance);

private:
	bool _quit;
	char _padding[7];

	void SetQuit();
};