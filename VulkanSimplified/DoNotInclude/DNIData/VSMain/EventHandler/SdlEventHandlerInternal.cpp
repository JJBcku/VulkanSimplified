#include "SdlEhDNIpch.h"
#include "../EventHandler/SdlEventHandlerInternal.h"

#include "../../../../Include/VSMain/EventHandler/SdlEventHandlerInitData.h"

#include "../../../../Include/VSMain/EventHandler/SdlAppEventsData.h"
#include "../../../../Include/VSMain/EventHandler/SdlAudioDeviceEventData.h"
#include "../../../../Include/VSMain/EventHandler/SdlCameraEventData.h"
#include "../../../../Include/VSMain/EventHandler/SdlClipboardEventData.h"
#include "../../../../Include/VSMain/EventHandler/SdlControllerEventsData.h"
#include "../../../../Include/VSMain/EventHandler/SdlDisplayEventData.h"
#include "../../../../Include/VSMain/EventHandler/SdlDropEventData.h"
#include "../../../../Include/VSMain/EventHandler/SdlJoyEventsData.h"
#include "../../../../Include/VSMain/EventHandler/SdlKeyboardEventsData.h"
#include "../../../../Include/VSMain/EventHandler/SdlLocaleChangedEventData.h"
#include "../../../../Include/VSMain/EventHandler/SdlMouseEventsData.h"
#include "../../../../Include/VSMain/EventHandler/SdlQuitEventData.h"
#include "../../../../Include/VSMain/EventHandler/SdlRenderEventsData.h"
#include "../../../../Include/VSMain/EventHandler/SdlSensorEventData.h"
#include "../../../../Include/VSMain/EventHandler/SdlSystemThemeChangeEventData.h"
#include "../../../../Include/VSMain/EventHandler/SdlTextEventsData.h"
#include "../../../../Include/VSMain/EventHandler/SdlTouchpadEventsData.h"
#include "../../../../Include/VSMain/EventHandler/SdlUserEventData.h"
#include "../../../../Include/VSMain/EventHandler/SdlPenEventsData.h"
#include "../../../../Include/VSMain/EventHandler/SdlWindowEventData.h"

namespace VulkanSimplified
{
	SdlEventHandlerInternal::SdlEventHandlerInternal(const SdlEventHandlerInitData& initData) : _quitEventFunctions(initData.quitEventFunctionListInitialCapacity),
		_appTerminatingEventFunctions(initData.appTerminatingEventFunctionListInitialCapacity), _appLowMemoryEventFunctions(initData.appLowMemoryEventFunctionListInitialCapacity),
		_appWillEnterBackgroundEventFunctions(initData.appWillEnterBackgroundEventFunctionListInitialCapacity),
		_appDidEnterBackgroundEventFunctions(initData.appDidEnterBackgroundEventFunctionListInitialCapacity),
		_appWillEnterForegroundEventFunctions(initData.appWillEnterForegroundEventFunctionListInitialCapacity),
		_appDidEnterForegroundEventFunctions(initData.appDidEnterForegroundEventFunctionListInitialCapacity),
		_localeChangedEventFunctions(initData.localeChangedEventFunctionListInitialCapacity),
		_systemThemeChangeEventFunctions(initData.systemThemeChangeEventFunctionListInitialCapacity),
		_displayEventFunctions(initData.displayEventFunctionListInitialCapacity),
		_windowEventFunctions(initData.windowEventFunctionListInitialCapacity),
		_keyboardEventFunctions(initData.keyboardEventFunctionListInitialCapacity),
		_textEditingEventFunctions(initData.textEditingEventFunctionListInitialCapacity),
		_keymapChangedEventFunctions(initData.keymapChangeEventFunctionListInitialCapacity),
		_textInputEventFunctions(initData.textInputEventFunctionListInitialCapacity),
		_keyboardDeviceEventFunctions(initData.keyboardDeviceEventFunctionListInitialCapacity),
		_textEditingCandidatesEventFunctions(initData.textEditingCandidatesEventFunctionListInitialCapacity),
		_screenKeyboardEventFunctions(initData.screenKeyboardEventFunctionListInitialCapacity),
		_mouseMotionEventFunctions(initData.mouseMotionEventFunctionListInitialCapacity),
		_mouseButtonEventFunctions(initData.mouseButtonEventFunctionListInitialCapacity),
		_mouseWheelEventFunctions(initData.mouseWheelEventFunctionListInitialCapacity),
		_mouseDeviceEventFunctions(initData.mouseDeviceEventFunctionListInitialCapacity),
		_joyAxisEventFunctions(initData.joyAxisEventFunctionListInitialCapacity),
		_joyBallEventFunctions(initData.joyBallEventFunctionListInitialCapacity),
		_joyHatEventFunctions(initData.joyHatEventFunctionListInitialCapacity),
		_joyButtonEventFunctions(initData.joyButtonEventFunctionListInitialCapacity),
		_joyDeviceEventFunctions(initData.joyDeviceEventFunctionListInitialCapacity),
		_joyBatteryEventFunctions(initData.joyBatteryEventFunctionListInitialCapacity),
		_gamepadAxisEventFunctions(initData.gamepadAxisEventFunctionListInitialCapacity),
		_gamepadButtonEventFunctions(initData.gamepadButtonEventFunctionListInitialCapacity),
		_gamepadDeviceEventFunctions(initData.gamepadDeviceEventFunctionListInitialCapacity),
		_gamepadTouchpadEventFunctions(initData.gamepadTouchpadEventFunctionListInitialCapacity),
		_gamepadSensorEventFunctions(initData.gamepadSensorEventFunctionListInitialCapacity),
		_touchFingerEventFunctions(initData.touchFingerEventFunctionListInitialCapacity),
		_touchPinchEventFunctions(initData.touchPinchEventFunctionListInitialCapacity),
		_clipboardEventFunctions(initData.clipboardEventFunctionListInitialCapacity),
		_dropEventFunctions(initData.dropEventFunctionListInitialCapacity),
		_audioDeviceEventFunctions(initData.audioDeviceEventFunctionListInitialCapacity),
		_sensorEventFunctions(initData.sensorEventFunctionListInitialCapacity),
		_penProximityEventFunctions(initData.penProximityEventFunctionListInitialCapacity),
		_penTouchEventFunctions(initData.penTouchEventFunctionListInitialCapacity),
		_penButtonEventFunctions(initData.penButtonEventFunctionListInitialCapacity),
		_penMotionEventFunctions(initData.penMotionEventFunctionListInitialCapacity),
		_penAxisEventFunctions(initData.penAxisEventFunctionListInitialCapacity),
		_cameraEventFunctions(initData.cameraEventFunctionListInitialCapacity),
		_renderTargetsResetEventFunctions(initData.renderTargetsResetEventFunctionListInitialCapacity),
		_renderDeviceResetEventFunctions(initData.renderDeviceResetEventFunctionListInitialCapacity),
		_renderDeviceLostEventFunctions(initData.renderDeviceLostEventFunctionListInitialCapacity),
		_userEventFunctions(initData.userEventFunctionListInitialCapacity)
	{
	}

	SdlEventHandlerInternal::~SdlEventHandlerInternal()
	{
	}

	void SdlEventHandlerInternal::HandleEvents()
	{
		SDL_Event event{};

		while (SDL_PollEvent(&event))
		{
			HandleEvent(event);
		}
	}

	IDObject<std::pair<QuitEventFunction, void*>> SdlEventHandlerInternal::RegisterQuitEventCallback(QuitEventFunction function, void* data, size_t add)
	{
		return _quitEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<AppTerminatingEventFunction, void*>> SdlEventHandlerInternal::RegisterAppTerminatingEventCallback(AppTerminatingEventFunction function, void* data, size_t add)
	{
		return _appTerminatingEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<AppLowMemoryEventFunction, void*>> SdlEventHandlerInternal::RegisterAppLowMemoryWarningEventCallback(AppLowMemoryEventFunction function, void* data, size_t add)
	{
		return _appLowMemoryEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<AppWillEnterBackgroundEventFunction, void*>> SdlEventHandlerInternal::RegisterAppWillEnterBackgroundWarningEventCallback(AppWillEnterBackgroundEventFunction function, void* data, size_t add)
	{
		return _appWillEnterBackgroundEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<AppDidEnterBackgroundEventFunction, void*>> SdlEventHandlerInternal::RegisterAppDidEnterBackgroundEventCallback(AppDidEnterBackgroundEventFunction function, void* data, size_t add)
	{
		return _appDidEnterBackgroundEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<AppWillEnterForegroundEventFunction, void*>> SdlEventHandlerInternal::RegisterAppWillEnterForegroundWarningEventCallback(AppWillEnterForegroundEventFunction function, void* data, size_t add)
	{
		return _appWillEnterForegroundEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<AppDidEnterForegroundEventFunction, void*>> SdlEventHandlerInternal::RegisterAppDidEnterForegroundEventCallback(AppDidEnterForegroundEventFunction function, void* data, size_t add)
	{
		return _appDidEnterForegroundEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<LocaleChangedEventFunction, void*>> SdlEventHandlerInternal::RegisterLocaleChangingEventCallback(LocaleChangedEventFunction function, void* data, size_t add)
	{
		return _localeChangedEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<SystemThemeChangeEventFunction, void*>> SdlEventHandlerInternal::RegisterSystemThemeChangeEventCallback(SystemThemeChangeEventFunction function, void* data, size_t add)
	{
		return _systemThemeChangeEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<DisplayEventFunction, void*>> SdlEventHandlerInternal::RegisterDisplayEventCallback(DisplayEventFunction function, void* data, size_t add)
	{
		return _displayEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<WindowEventFunction, void*>> SdlEventHandlerInternal::RegisterWindowEventCallback(WindowEventFunction function, void* data, size_t add)
	{
		return _windowEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<KeyboardDeviceEventFunction, void*>> SdlEventHandlerInternal::RegisterKeyboardDeviceEventCallback(KeyboardDeviceEventFunction function, void* data, size_t add)
	{
		return _keyboardDeviceEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<KeyboardEventFunction, void*>> SdlEventHandlerInternal::RegisterKeyboardEventCallback(KeyboardEventFunction function, void* data, size_t add)
	{
		return _keyboardEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<KeymapChangeEventFunction, void*>> SdlEventHandlerInternal::RegisterKeymapChangingEventCallback(KeymapChangeEventFunction function, void* data, size_t add)
	{
		return _keymapChangedEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<ScreenKeyboardEventFunction, void*>> SdlEventHandlerInternal::RegisterScreenKeyboardEventCallback(ScreenKeyboardEventFunction function, void* data, size_t add)
	{
		return _screenKeyboardEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<TextEditingCandidatesEventFunction, void*>> SdlEventHandlerInternal::RegisterTextCandidatesEditingEventCallback(TextEditingCandidatesEventFunction function,
		void* data, size_t add)
	{
		return _textEditingCandidatesEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<TextEditingEventFunction, void*>> SdlEventHandlerInternal::RegisterTextEditingEventCallback(TextEditingEventFunction function, void* data, size_t add)
	{
		return _textEditingEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<TextInputEventFunction, void*>> SdlEventHandlerInternal::RegisterTextInputEventCallback(TextInputEventFunction function, void* data, size_t add)
	{
		return _textInputEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<MouseDeviceEventFunction, void*>> SdlEventHandlerInternal::RegisterMouseDeviceEventCallback(MouseDeviceEventFunction function, void* data, size_t add)
	{
		return _mouseDeviceEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<MouseMotionEventFunction, void*>> SdlEventHandlerInternal::RegisterMouseMotionEventCallback(MouseMotionEventFunction function, void* data, size_t add)
	{
		return _mouseMotionEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<MouseButtonEventFunction, void*>> SdlEventHandlerInternal::RegisterMouseButtonEventCallback(MouseButtonEventFunction function, void* data, size_t add)
	{
		return _mouseButtonEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<MouseWheelEventFunction, void*>> SdlEventHandlerInternal::RegisterMouseWheelEventCallback(MouseWheelEventFunction function, void* data, size_t add)
	{
		return _mouseWheelEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<JoyAxisEventFunction, void*>> SdlEventHandlerInternal::RegisterJoystickAxisEventCallback(JoyAxisEventFunction function, void* data, size_t add)
	{
		return _joyAxisEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<JoyBallEventFunction, void*>> SdlEventHandlerInternal::RegisterJoystickBallEventCallback(JoyBallEventFunction function, void* data, size_t add)
	{
		return _joyBallEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<JoyHatEventFunction, void*>> SdlEventHandlerInternal::RegisterJoystickHatEventCallback(JoyHatEventFunction function, void* data, size_t add)
	{
		return _joyHatEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<JoyButtonEventFunction, void*>> SdlEventHandlerInternal::RegisterJoystickButtonEventCallback(JoyButtonEventFunction function, void* data, size_t add)
	{
		return _joyButtonEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<JoyDeviceEventFunction, void*>> SdlEventHandlerInternal::RegisterJoystickDeviceEventCallback(JoyDeviceEventFunction function, void* data, size_t add)
	{
		return _joyDeviceEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<JoyBatteryEventFunction, void*>> SdlEventHandlerInternal::RegisterJoystickBatteryEventCallback(JoyBatteryEventFunction function, void* data, size_t add)
	{
		return _joyBatteryEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<GamepadAxisEventFunction, void*>> SdlEventHandlerInternal::RegisterGamepadAxisEventCallback(GamepadAxisEventFunction function, void* data, size_t add)
	{
		return _gamepadAxisEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<GamepadButtonEventFunction, void*>> SdlEventHandlerInternal::RegisterGamepadButtonEventCallback(GamepadButtonEventFunction function, void* data, size_t add)
	{
		return _gamepadButtonEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<GamepadDeviceEventFunction, void*>> SdlEventHandlerInternal::RegisterGamepadDeviceEventCallback(GamepadDeviceEventFunction function, void* data, size_t add)
	{
		return _gamepadDeviceEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<GamepadTouchpadEventFunction, void*>> SdlEventHandlerInternal::RegisterGamepadTouchpadEventCallback(GamepadTouchpadEventFunction function, void* data, size_t add)
	{
		return _gamepadTouchpadEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<GamepadSensorEventFunction, void*>> SdlEventHandlerInternal::RegisterGamepadSensorEventCallback(GamepadSensorEventFunction function, void* data, size_t add)
	{
		return _gamepadSensorEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<AudioDeviceEventFunction, void*>> SdlEventHandlerInternal::RegisterAudioDeviceEventCallback(AudioDeviceEventFunction function, void* data, size_t add)
	{
		return _audioDeviceEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<TouchFingerEventFunction, void*>> SdlEventHandlerInternal::RegisterTouchFingerEventCallback(TouchFingerEventFunction function, void* data, size_t add)
	{
		return _touchFingerEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<TouchPinchEventFunction, void*>> SdlEventHandlerInternal::RegisterPinchFingerEventCallback(TouchPinchEventFunction function, void* data, size_t add)
	{
		return _touchPinchEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<CameraEventFunction, void*>> SdlEventHandlerInternal::RegisterCameraEventCallback(CameraEventFunction function, void* data, size_t add)
	{
		return _cameraEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<ClipboardEventFunction, void*>> SdlEventHandlerInternal::RegisterClipboardEventCallback(ClipboardEventFunction function, void* data, size_t add)
	{
		return _clipboardEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<DropEventFunction, void*>> SdlEventHandlerInternal::RegisterDropEventCallback(DropEventFunction function, void* data, size_t add)
	{
		return _dropEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<SensorEventFunction, void*>> SdlEventHandlerInternal::RegisterSensorEventCallback(SensorEventFunction function, void* data, size_t add)
	{
		return _sensorEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<UserEventFunction, void*>> SdlEventHandlerInternal::RegisterUserEventCallback(UserEventFunction function, void* data, size_t add)
	{
		return _userEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<PenAxisEventFunction, void*>> SdlEventHandlerInternal::RegisterPenAxisEventCallback(PenAxisEventFunction function, void* data, size_t add)
	{
		return _penAxisEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<PenButtonEventFunction, void*>> SdlEventHandlerInternal::RegisterPenButtonEventCallback(PenButtonEventFunction function, void* data, size_t add)
	{
		return _penButtonEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<PenMotionEventFunction, void*>> SdlEventHandlerInternal::RegisterPenMotionEventCallback(PenMotionEventFunction function, void* data, size_t add)
	{
		return _penMotionEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<PenTouchEventFunction, void*>> SdlEventHandlerInternal::RegisterPenTouchEventCallback(PenTouchEventFunction function, void* data, size_t add)
	{
		return _penTouchEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<PenProximityEventFunction, void*>> SdlEventHandlerInternal::RegisterPenProximityEventCallback(PenProximityEventFunction function, void* data, size_t add)
	{
		return _penProximityEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<RenderTargetsResetEventFunction, void*>> SdlEventHandlerInternal::RegisterRenderTargetsResetEventCallback(RenderTargetsResetEventFunction function, void* data, size_t add)
	{
		return _renderTargetsResetEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<RenderDeviceResetEventFunction, void*>> SdlEventHandlerInternal::RegisterRenderDeviceResetEventCallback(RenderDeviceResetEventFunction function, void* data, size_t add)
	{
		return _renderDeviceResetEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<RenderDeviceLostEventFunction, void*>> SdlEventHandlerInternal::RegisterRenderDeviceLostEventCallback(RenderDeviceLostEventFunction function, void* data, size_t add)
	{
		return _renderDeviceLostEventFunctions.AddObject(std::pair(function, data), add);
	}

	bool SdlEventHandlerInternal::UnRegisterQuitEventCallback(IDObject<std::pair<QuitEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _quitEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterAppTerminatingEventCallback(IDObject<std::pair<AppTerminatingEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _appTerminatingEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterAppLowMemoryEventCallback(IDObject<std::pair<AppLowMemoryEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _appLowMemoryEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterAppWillEnterBackgroundEventCallback(IDObject<std::pair<AppWillEnterBackgroundEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _appWillEnterBackgroundEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterAppDidEnterBackgroundEventCallback(IDObject<std::pair<AppDidEnterBackgroundEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _appDidEnterBackgroundEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterAppWillEnterForegroundEventCallback(IDObject<std::pair<AppWillEnterForegroundEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _appWillEnterForegroundEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterAppDidEnterForegroundEventCallback(IDObject<std::pair<AppDidEnterForegroundEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _appDidEnterForegroundEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterLocaleChangedEventCallback(IDObject<std::pair<LocaleChangedEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _localeChangedEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterSystemThemeChangeEventCallback(IDObject<std::pair<SystemThemeChangeEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _systemThemeChangeEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterDisplayEventCallback(IDObject<std::pair<DisplayEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _displayEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterWindowEventCallback(IDObject<std::pair<WindowEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _windowEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterKeyboardDeviceEventCallback(IDObject<std::pair<KeyboardDeviceEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _keyboardDeviceEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterKeyboardEventCallback(IDObject<std::pair<KeyboardEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _keyboardEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterKeymapChangeEventCallback(IDObject<std::pair<KeymapChangeEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _keymapChangedEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterScreenKeyboardEventCallback(IDObject<std::pair<ScreenKeyboardEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _screenKeyboardEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterTextEditingEventCallback(IDObject<std::pair<TextEditingEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _textEditingEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterTextCandidatesEditingEventCallback(IDObject<std::pair<TextEditingCandidatesEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _textEditingCandidatesEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterTextInputEventCallback(IDObject<std::pair<TextInputEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _textInputEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterMouseDeviceEventCallback(IDObject<std::pair<MouseDeviceEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _mouseDeviceEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterMouseMotionEventCallback(IDObject<std::pair<MouseMotionEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _mouseMotionEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterMouseButtonEventCallback(IDObject<std::pair<MouseButtonEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _mouseButtonEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterMouseWheelEventCallback(IDObject<std::pair<MouseWheelEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _mouseWheelEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterJoyAxisEventCallback(IDObject<std::pair<JoyAxisEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _joyAxisEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterJoyBallEventCallback(IDObject<std::pair<JoyBallEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _joyBallEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterJoyHatEventCallback(IDObject<std::pair<JoyHatEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _joyHatEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterJoyButtonEventCallback(IDObject<std::pair<JoyButtonEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _joyButtonEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterJoyDeviceEventCallback(IDObject<std::pair<JoyDeviceEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _joyDeviceEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterJoyBatteryEventCallback(IDObject<std::pair<JoyBatteryEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _joyBatteryEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterGamepadAxisEventCallback(IDObject<std::pair<GamepadAxisEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _gamepadAxisEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterGamepadButtonEventCallback(IDObject<std::pair<GamepadButtonEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _gamepadButtonEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterGamepadDeviceEventCallback(IDObject<std::pair<GamepadDeviceEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _gamepadDeviceEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterGamepadTouchpadEventCallback(IDObject<std::pair<GamepadTouchpadEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _gamepadTouchpadEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterGamepadSensorEventCallback(IDObject<std::pair<GamepadSensorEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _gamepadSensorEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterAudioDeviceEventCallback(IDObject<std::pair<AudioDeviceEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _audioDeviceEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterTouchFingerEventCallback(IDObject<std::pair<TouchFingerEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _touchFingerEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterTouchPinchEventCallback(IDObject<std::pair<TouchPinchEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _touchPinchEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterCameraEventCallback(IDObject<std::pair<CameraEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _cameraEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterClipboardEventCallback(IDObject<std::pair<ClipboardEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _clipboardEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterDropEventCallback(IDObject<std::pair<DropEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _dropEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterSensorEventCallback(IDObject<std::pair<SensorEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _sensorEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterUserEventCallback(IDObject<std::pair<UserEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _userEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterPenAxisEventCallback(IDObject<std::pair<PenAxisEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _penAxisEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterPenButtonEventCallback(IDObject<std::pair<PenButtonEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _penButtonEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterPenMotionEventCallback(IDObject<std::pair<PenMotionEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _penMotionEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterPenTouchEventCallback(IDObject<std::pair<PenTouchEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _penTouchEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterPenProximityEventCallback(IDObject<std::pair<PenProximityEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _penProximityEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterRenderTargetsResetEventCallback(IDObject<std::pair<RenderTargetsResetEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _renderTargetsResetEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterRenderDeviceResetEventCallback(IDObject<std::pair<RenderDeviceResetEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _renderDeviceResetEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterRenderDeviceLostEventCallback(IDObject<std::pair<RenderDeviceLostEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _renderDeviceLostEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	void SdlEventHandlerInternal::HandleEvent(const SDL_Event& event)
	{
		auto& type = event.type;

		switch (type)
		{
		case SDL_EVENT_FIRST:
			break;
		case SDL_EVENT_QUIT:
			HandleQuitEvent(event);
			break;
		case SDL_EVENT_TERMINATING:
			HandleAppTerminatingEvent(event);
			break;
		case SDL_EVENT_LOW_MEMORY:
			HandleAppLowMemoryEvent(event);
			break;
		case SDL_EVENT_WILL_ENTER_BACKGROUND:
			HandleAppWillEnterBackgroundEvent(event);
			break;
		case SDL_EVENT_DID_ENTER_BACKGROUND:
			HandleAppDidEnterBackgroundEvent(event);
			break;
		case SDL_EVENT_WILL_ENTER_FOREGROUND:
			HandleAppWillEnterForegroundEvent(event);
			break;
		case SDL_EVENT_DID_ENTER_FOREGROUND:
			HandleAppDidEnterForegroundEvent(event);
			break;
		case SDL_EVENT_LOCALE_CHANGED:
			HandleLocaleChangeEvent(event);
			break;
		case  SDL_EVENT_SYSTEM_THEME_CHANGED:
			HandleSystemThemeChangeEvent(event);
			break;
		case SDL_EVENT_DISPLAY_ORIENTATION:
		case SDL_EVENT_DISPLAY_ADDED:
		case SDL_EVENT_DISPLAY_REMOVED:
		case SDL_EVENT_DISPLAY_MOVED:
		case SDL_EVENT_DISPLAY_DESKTOP_MODE_CHANGED:
		case SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED:
		case SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED:
		case SDL_EVENT_DISPLAY_USABLE_BOUNDS_CHANGED:
			HandleDisplayEvent(event);
			break;
		case SDL_EVENT_WINDOW_SHOWN:
		case SDL_EVENT_WINDOW_HIDDEN:
		case SDL_EVENT_WINDOW_EXPOSED:
		case SDL_EVENT_WINDOW_MOVED:
		case SDL_EVENT_WINDOW_RESIZED:
		case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
		case SDL_EVENT_WINDOW_METAL_VIEW_RESIZED:
		case SDL_EVENT_WINDOW_MINIMIZED:
		case SDL_EVENT_WINDOW_MAXIMIZED:
		case SDL_EVENT_WINDOW_RESTORED:
		case SDL_EVENT_WINDOW_MOUSE_ENTER:
		case SDL_EVENT_WINDOW_MOUSE_LEAVE:
		case SDL_EVENT_WINDOW_FOCUS_GAINED:
		case SDL_EVENT_WINDOW_FOCUS_LOST:
		case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
		case SDL_EVENT_WINDOW_HIT_TEST:
		case SDL_EVENT_WINDOW_ICCPROF_CHANGED:
		case SDL_EVENT_WINDOW_DISPLAY_CHANGED:
		case SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED:
		case SDL_EVENT_WINDOW_SAFE_AREA_CHANGED:
		case SDL_EVENT_WINDOW_OCCLUDED:
		case SDL_EVENT_WINDOW_ENTER_FULLSCREEN:
		case SDL_EVENT_WINDOW_LEAVE_FULLSCREEN:
		case SDL_EVENT_WINDOW_DESTROYED:
		case SDL_EVENT_WINDOW_HDR_STATE_CHANGED:
			HandleWindowEvent(event);
			break;
		case SDL_EVENT_KEY_DOWN:
		case SDL_EVENT_KEY_UP:
			HandleKeyboardEvent(event);
			break;
		case SDL_EVENT_TEXT_EDITING:
			HandleTextEditingEvent(event);
			break;
		case SDL_EVENT_TEXT_INPUT:
			HandleTextInputEvent(event);
			break;
		case SDL_EVENT_KEYMAP_CHANGED:
			HandleKeymapChangedEvent(event);
			break;
		case SDL_EVENT_KEYBOARD_ADDED:
		case SDL_EVENT_KEYBOARD_REMOVED:
			HandleKeyboardDeviceEvent(event);
			break;
		case SDL_EVENT_TEXT_EDITING_CANDIDATES:
			HandleTextEditingCandidatesEvent(event);
			break;
		case SDL_EVENT_SCREEN_KEYBOARD_SHOWN:
		case SDL_EVENT_SCREEN_KEYBOARD_HIDDEN:
			HandleScreenKeyboardEvent(event);
			break;
		case SDL_EVENT_MOUSE_ADDED:
		case SDL_EVENT_MOUSE_REMOVED:
			HandleMouseDeviceEvent(event);
			break;
		case SDL_EVENT_MOUSE_MOTION:
			HandleMouseMotionEvent(event);
			break;
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
		case SDL_EVENT_MOUSE_BUTTON_UP:
			HandleMouseButtonEvent(event);
			break;
		case SDL_EVENT_MOUSE_WHEEL:
			HandleMouseWheelEvent(event);
			break;
		case SDL_EVENT_JOYSTICK_AXIS_MOTION:
			HandleJoyAxisEvent(event);
			break;
		case SDL_EVENT_JOYSTICK_BALL_MOTION:
			HandleJoyBallEvent(event);
			break;
		case SDL_EVENT_JOYSTICK_HAT_MOTION:
			HandleJoyHatEvent(event);
			break;
		case SDL_EVENT_JOYSTICK_BUTTON_DOWN:
		case SDL_EVENT_JOYSTICK_BUTTON_UP:
			HandleJoyButtonEvent(event);
			break;
		case SDL_EVENT_JOYSTICK_ADDED:
		case SDL_EVENT_JOYSTICK_REMOVED:
		case SDL_EVENT_JOYSTICK_UPDATE_COMPLETE:
			HandleJoyDeviceEvent(event);
			break;
		case SDL_EVENT_JOYSTICK_BATTERY_UPDATED:
			HandleJoyBatteryEvent(event);
			break;
		case SDL_EVENT_GAMEPAD_AXIS_MOTION:
			HandleGamepadAxisEvent(event);
			break;
		case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
		case SDL_EVENT_GAMEPAD_BUTTON_UP:
			HandleGamepadButtonEvent(event);
			break;
		case SDL_EVENT_GAMEPAD_ADDED:
		case SDL_EVENT_GAMEPAD_REMOVED:
		case SDL_EVENT_GAMEPAD_REMAPPED:
		case SDL_EVENT_GAMEPAD_UPDATE_COMPLETE:
		case SDL_EVENT_GAMEPAD_STEAM_HANDLE_UPDATED:
			HandleGamepadDeviceEvent(event);
			break;
		case SDL_EVENT_GAMEPAD_TOUCHPAD_DOWN:
		case SDL_EVENT_GAMEPAD_TOUCHPAD_MOTION:
		case SDL_EVENT_GAMEPAD_TOUCHPAD_UP:
			HandleGamepadTouchpadEvent(event);
			break;
		case SDL_EVENT_GAMEPAD_SENSOR_UPDATE:
			HandleGamepadSensorEvent(event);
			break;
		case SDL_EVENT_FINGER_DOWN:
		case SDL_EVENT_FINGER_UP:
		case SDL_EVENT_FINGER_MOTION:
		case SDL_EVENT_FINGER_CANCELED:
			HandleTouchFingerEvent(event);
			break;
		case SDL_EVENT_PINCH_BEGIN:
		case SDL_EVENT_PINCH_UPDATE:
		case SDL_EVENT_PINCH_END:
			HandleTouchPinchEvent(event);
			break;
		case SDL_EVENT_CLIPBOARD_UPDATE:
			HandleClipboardEvent(event);
			break;
		case SDL_EVENT_DROP_FILE:
		case SDL_EVENT_DROP_TEXT:
		case SDL_EVENT_DROP_BEGIN:
		case SDL_EVENT_DROP_COMPLETE:
		case SDL_EVENT_DROP_POSITION:
			HandleDropEvent(event);
			break;
		case SDL_EVENT_AUDIO_DEVICE_ADDED:
		case SDL_EVENT_AUDIO_DEVICE_REMOVED:
		case SDL_EVENT_AUDIO_DEVICE_FORMAT_CHANGED:
			HandleAudioDeviceEvent(event);
			break;
		case SDL_EVENT_SENSOR_UPDATE:
			HandleSensorEvent(event);
			break;
		case SDL_EVENT_PEN_AXIS:
			HandlePenAxisEvent(event);
			break;
		case SDL_EVENT_PEN_BUTTON_DOWN:
		case SDL_EVENT_PEN_BUTTON_UP:
			HandlePenButtonEvent(event);
			break;
		case SDL_EVENT_PEN_MOTION:
			HandlePenMotionEvent(event);
			break;
		case SDL_EVENT_PEN_DOWN:
		case SDL_EVENT_PEN_UP:
			HandlePenTouchEvent(event);
			break;
		case SDL_EVENT_CAMERA_DEVICE_ADDED:
		case SDL_EVENT_CAMERA_DEVICE_REMOVED:
		case SDL_EVENT_CAMERA_DEVICE_APPROVED:
		case SDL_EVENT_CAMERA_DEVICE_DENIED:
			HandleCameraEvent(event);
			break;
		case SDL_EVENT_RENDER_TARGETS_RESET:
			HandleRenderTargetsResetEvent(event);
			break;
		case SDL_EVENT_RENDER_DEVICE_RESET:
			HandleRenderDeviceResetEvent(event);
			break;
		case SDL_EVENT_RENDER_DEVICE_LOST:
			break;
		case SDL_EVENT_USER:
			HandleUserEvent(event);
			break;
		case SDL_EVENT_LAST:
			break;
		default:
			break;
		}
	}

	void SdlEventHandlerInternal::HandleQuitEvent(const SDL_Event& event)
	{
		if (event.type != SDL_EVENT_QUIT)
			throw std::runtime_error("SdlEventHandlerInternal::HandleQuitEvent Error: Wrong event type was passed to this function!");

		SdlQuitEventData eventData;
		eventData.reserved = event.quit.reserved;
		eventData.timestamp = event.quit.timestamp;

		auto size = _quitEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _quitEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleAppTerminatingEvent(const SDL_Event& event)
	{
		if (event.type != SDL_EVENT_TERMINATING)
			throw std::runtime_error("SdlEventHandlerInternal::HandleAppTerminatingEvent Error: Wrong event type was passed to this function!");

		SdlAppTerminatingEventData eventData;
		eventData.reserved = event.quit.reserved;
		eventData.timestamp = event.quit.timestamp;

		auto size = _appTerminatingEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _appTerminatingEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleAppLowMemoryEvent(const SDL_Event& event)
	{
		if (event.type != SDL_EVENT_LOW_MEMORY)
			throw std::runtime_error("SdlEventHandlerInternal::HandleAppLowMemoryEvent Error: Wrong event type was passed to this function!");

		SdlAppLowMemoryEventData eventData;
		eventData.reserved = event.quit.reserved;
		eventData.timestamp = event.quit.timestamp;

		auto size = _appLowMemoryEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _appLowMemoryEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleAppWillEnterBackgroundEvent(const SDL_Event& event)
	{
		if (event.type != SDL_EVENT_WILL_ENTER_BACKGROUND)
			throw std::runtime_error("SdlEventHandlerInternal::HandleAppWillEnterBackgroundEvent Error: Wrong event type was passed to this function!");

		SdlAppWillEnterBackgroundEventData eventData;
		eventData.reserved = event.quit.reserved;
		eventData.timestamp = event.quit.timestamp;

		auto size = _appWillEnterBackgroundEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _appWillEnterBackgroundEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleAppDidEnterBackgroundEvent(const SDL_Event& event)
	{
		if (event.type != SDL_EVENT_DID_ENTER_BACKGROUND)
			throw std::runtime_error("SdlEventHandlerInternal::HandleAppDidEnterBackgroundEvent Error: Wrong event type was passed to this function!");

		SdlAppDidEnterBackgroundEventData eventData;
		eventData.reserved = event.quit.reserved;
		eventData.timestamp = event.quit.timestamp;

		auto size = _appDidEnterBackgroundEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _appDidEnterBackgroundEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleAppWillEnterForegroundEvent(const SDL_Event& event)
	{
		if (event.type != SDL_EVENT_WILL_ENTER_FOREGROUND)
			throw std::runtime_error("SdlEventHandlerInternal::HandleAppWillEnterForegroundEvent Error: Wrong event type was passed to this function!");

		SdlAppWillEnterForegroundEventData eventData;
		eventData.reserved = event.quit.reserved;
		eventData.timestamp = event.quit.timestamp;

		auto size = _appWillEnterForegroundEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _appWillEnterForegroundEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleAppDidEnterForegroundEvent(const SDL_Event& event)
	{
		if (event.type != SDL_EVENT_DID_ENTER_FOREGROUND)
			throw std::runtime_error("SdlEventHandlerInternal::HandleAppDidEnterForegroundEvent Error: Wrong event type was passed to this function!");

		SdlAppDidEnterForegroundEventData eventData;
		eventData.reserved = event.quit.reserved;
		eventData.timestamp = event.quit.timestamp;

		auto size = _appDidEnterForegroundEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _appDidEnterForegroundEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleLocaleChangeEvent(const SDL_Event& event)
	{
		if (event.type != SDL_EVENT_LOCALE_CHANGED)
			throw std::runtime_error("SdlEventHandlerInternal::HandleLocaleChangeEvent Error: Wrong event type was passed to this function!");

		SdlLocaleChangeEventData eventData;
		eventData.reserved = event.quit.reserved;
		eventData.timestamp = event.quit.timestamp;

		auto size = _localeChangedEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _localeChangedEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleSystemThemeChangeEvent(const SDL_Event& event)
	{
		if (event.type != SDL_EVENT_SYSTEM_THEME_CHANGED)
			throw std::runtime_error("SdlEventHandlerInternal::HandleSystemThemeChangeEvent Error: Wrong event type was passed to this function!");

		SdlSystemThemeChangeEventData eventData;
		eventData.reserved = event.quit.reserved;
		eventData.timestamp = event.quit.timestamp;

		auto size = _systemThemeChangeEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _systemThemeChangeEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleDisplayEvent(const SDL_Event& event)
	{
		SdlDisplayEventData eventData;
		eventData.timestamp = event.display.timestamp;
		eventData.reserved = event.display.reserved;
		eventData.display = event.display.displayID;

		switch (event.type)
		{
		case SDL_EVENT_DISPLAY_ORIENTATION:
			eventData.event = SdlDisplayEventID::SDL_DATA_DISPLAYEVENT_ORIENTATION;
			break;
		case SDL_EVENT_DISPLAY_ADDED:
			eventData.event = SdlDisplayEventID::SDL_DATA_DISPLAYEVENT_ADDED;
			break;
		case SDL_EVENT_DISPLAY_REMOVED:
			eventData.event = SdlDisplayEventID::SDL_DATA_DISPLAYEVENT_REMOVED;
			break;
		case SDL_EVENT_DISPLAY_MOVED:
			eventData.event = SdlDisplayEventID::SDL_DATA_DISPLAYEVENT_MOVED;
			break;
		case SDL_EVENT_DISPLAY_DESKTOP_MODE_CHANGED:
			eventData.event = SdlDisplayEventID::SDL_DATA_DISPLAYEVENT_DESKTOP_MODE_CHANGED;
			break;
		case SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED:
			eventData.event = SdlDisplayEventID::SDL_DATA_DISPLAYEVENT_CURRENT_MODE_CHANGED;
			break;
		case SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED:
			eventData.event = SdlDisplayEventID::SDL_DATA_DISPLAYEVENT_CONTENT_SCALE_CHANGED;
			break;
		case SDL_EVENT_DISPLAY_USABLE_BOUNDS_CHANGED:
			eventData.event = SdlDisplayEventID::SDL_DATA_DISPLAYEVENT_USABLE_BOUNDS_CHANGED;
			break;
		default:
			throw std::runtime_error("SdlEventHandlerInternal::HandleDisplayEvent Error: Wrong event type was passed to this function!");
		}

		eventData.data1 = event.display.data1;
		eventData.data2 = event.display.data2;

		auto size = _displayEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _displayEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleWindowEvent(const SDL_Event& event)
	{
		SdlWindowEventData eventData;
		eventData.timestamp = event.window.timestamp;
		eventData.reserved = event.window.reserved;
		eventData.windowID = event.window.windowID;
		switch (event.type)
		{
		case SDL_EVENT_WINDOW_SHOWN:
			eventData.subtype = SdlWindowEventSubType::SDL_DATA_WINDOWEVENT_SHOWN;
			break;
		case SDL_EVENT_WINDOW_HIDDEN:
			eventData.subtype = SdlWindowEventSubType::SDL_DATA_WINDOWEVENT_HIDDEN;
			break;
		case SDL_EVENT_WINDOW_EXPOSED:
			eventData.subtype = SdlWindowEventSubType::SDL_DATA_WINDOWEVENT_EXPOSED;
			break;
		case SDL_EVENT_WINDOW_MOVED:
			eventData.subtype = SdlWindowEventSubType::SDL_DATA_WINDOWEVENT_MOVED;
			break;
		case SDL_EVENT_WINDOW_RESIZED:
			eventData.subtype = SdlWindowEventSubType::SDL_DATA_WINDOWEVENT_RESIZED;
			break;
		case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
			eventData.subtype = SdlWindowEventSubType::SDL_DATA_WINDOWEVENT_PIXEL_SIZE_CHANGED;
			break;
		case SDL_EVENT_WINDOW_METAL_VIEW_RESIZED:
			eventData.subtype = SdlWindowEventSubType::SDL_DATA_WINDOWEVENT_METAL_VIEW_RESIZED;
			break;
		case SDL_EVENT_WINDOW_MINIMIZED:
			eventData.subtype = SdlWindowEventSubType::SDL_DATA_WINDOWEVENT_MINIMIZED;
			break;
		case SDL_EVENT_WINDOW_MAXIMIZED:
			eventData.subtype = SdlWindowEventSubType::SDL_DATA_WINDOWEVENT_MAXIMIZED;
			break;
		case SDL_EVENT_WINDOW_RESTORED:
			eventData.subtype = SdlWindowEventSubType::SDL_DATA_WINDOWEVENT_RESTORED;
			break;
		case SDL_EVENT_WINDOW_MOUSE_ENTER:
			eventData.subtype = SdlWindowEventSubType::SDL_DATA_WINDOWEVENT_MOUSE_ENTER;
			break;
		case SDL_EVENT_WINDOW_MOUSE_LEAVE:
			eventData.subtype = SdlWindowEventSubType::SDL_DATA_WINDOWEVENT_MOUSE_LEAVE;
			break;
		case SDL_EVENT_WINDOW_FOCUS_GAINED:
			eventData.subtype = SdlWindowEventSubType::SDL_DATA_WINDOWEVENT_FOCUS_GAINED;
			break;
		case SDL_EVENT_WINDOW_FOCUS_LOST:
			eventData.subtype = SdlWindowEventSubType::SDL_DATA_WINDOWEVENT_FOCUS_LOST;
			break;
		case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
			eventData.subtype = SdlWindowEventSubType::SDL_DATA_WINDOWEVENT_CLOSE_REQUESTED;
			break;
		case SDL_EVENT_WINDOW_HIT_TEST:
			eventData.subtype = SdlWindowEventSubType::SDL_DATA_WINDOWEVENT_HIT_TEST;
			break;
		case SDL_EVENT_WINDOW_ICCPROF_CHANGED:
			eventData.subtype = SdlWindowEventSubType::SDL_DATA_WINDOWEVENT_ICCPROF_CHANGED;
			break;
		case SDL_EVENT_WINDOW_DISPLAY_CHANGED:
			eventData.subtype = SdlWindowEventSubType::SDL_DATA_WINDOWEVENT_DISPLAY_CHANGED;
			break;
		case SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED:
			eventData.subtype = SdlWindowEventSubType::SDL_DATA_WINDOWEVENT_DISPLAY_SCALE_CHANGED;
			break;
		case SDL_EVENT_WINDOW_SAFE_AREA_CHANGED:
			eventData.subtype = SdlWindowEventSubType::SDL_DATA_WINDOWEVENT_SAFE_AREA_CHANGED;
			break;
		case SDL_EVENT_WINDOW_OCCLUDED:
			eventData.subtype = SdlWindowEventSubType::SDL_DATA_WINDOWEVENT_OCCLUDED;
			break;
		case SDL_EVENT_WINDOW_ENTER_FULLSCREEN:
			eventData.subtype = SdlWindowEventSubType::SDL_DATA_WINDOWEVENT_ENTER_FULLSCREEN;
			break;
		case SDL_EVENT_WINDOW_LEAVE_FULLSCREEN:
			eventData.subtype = SdlWindowEventSubType::SDL_DATA_WINDOWEVENT_LEAVE_FULLSCREEN;
			break;
		case SDL_EVENT_WINDOW_DESTROYED:
			eventData.subtype = SdlWindowEventSubType::SDL_DATA_WINDOWEVENT_WINDOW_DESTROYED;
			break;
		case SDL_EVENT_WINDOW_HDR_STATE_CHANGED:
			eventData.subtype = SdlWindowEventSubType::SDL_DATA_WINDOWEVENT_HDR_STATE_CHANGED;
			break;
		default:
			throw std::runtime_error("SdlEventHandlerInternal::HandleWindowEvent Error: Wrong event type was passed to this function!");
		}
		eventData.data1 = event.window.data1;
		eventData.data2 = event.window.data2;

		auto size = _windowEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _windowEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleKeyboardDeviceEvent(const SDL_Event& event)
	{
		SdlKeyboardDeviceEvent eventData;

		switch (event.type)
		{
		case SDL_EVENT_KEYBOARD_ADDED:
			eventData.subtype = SdlKeyboardDeviceEventSubType::KEYBOARD_DEVICE_ADDED;
			break;
		case SDL_EVENT_KEYBOARD_REMOVED:
			eventData.subtype = SdlKeyboardDeviceEventSubType::KEYBOARD_DEVICE_REMOWED;
			break;
		default:
			throw std::runtime_error("SdlEventHandlerInternal::HandleKeyboardDeviceEvent Error: Wrong event type was passed to this function!");
		}

		eventData.reserved = event.kdevice.reserved;
		eventData.timestamp = event.kdevice.timestamp;
		eventData.keyboardID = event.kdevice.which;

		auto size = _keyboardDeviceEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _keyboardDeviceEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleKeyboardEvent(const SDL_Event& event)
	{
		if (event.type != SDL_EVENT_KEY_UP && event.type != SDL_EVENT_KEY_DOWN)
			throw std::runtime_error("SdlEventHandlerInternal::HandleKeyboardEvent Error: Wrong event type was passed to this function!");

		SdlKeyboardEventData eventData;
		eventData.timestamp = event.key.timestamp;
		eventData.reserved = event.key.reserved;
		eventData.windowID = event.key.windowID;
		eventData.keyboardID = event.key.which;

		eventData.keysym.scancode = static_cast<SdlScancode>(event.key.scancode);
		eventData.keysym.keycode = static_cast<SdlKeycode>(event.key.key);
		eventData.keysym.mod = event.key.mod;
		eventData.keysym.rawData = event.key.raw;
		eventData.down = event.key.down;
		eventData.repeat = event.key.repeat;

		auto size = _keyboardEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _keyboardEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleKeymapChangedEvent(const SDL_Event& event)
	{
		if (event.type != SDL_EVENT_KEYMAP_CHANGED)
			throw std::runtime_error("SdlEventHandlerInternal::HandleKeymapChangedEvent Error: Wrong event type was passed to this function!");

		SdlKeymapChangedEventData eventData;
		eventData.reserved = event.common.reserved;
		eventData.timestamp = event.common.timestamp;

		auto size = _keymapChangedEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _keymapChangedEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleScreenKeyboardEvent(const SDL_Event& event)
	{
		SdlScreenKeyboardEventData eventData;
		switch (event.type)
		{
		case SDL_EVENT_SCREEN_KEYBOARD_SHOWN:
			eventData.subtype = SdlScreenKeyboardEventSubtype::SCREEN_KEYBOARD_SHOWN;
			break;
		case SDL_EVENT_SCREEN_KEYBOARD_HIDDEN:
			eventData.subtype = SdlScreenKeyboardEventSubtype::SCREEN_KEYBOARD_HIDDEN;
			break;
		default:
			throw std::runtime_error("SdlEventHandlerInternal::HandleScreenKeyboardEvent Error: Wrong event type was passed to this function!");
		}
		eventData.reserved = event.common.reserved;
		eventData.timestamp = event.common.timestamp;

		auto size = _screenKeyboardEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _screenKeyboardEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleTextEditingEvent(const SDL_Event& event)
	{
		if (event.type != SDL_EVENT_TEXT_EDITING)
			throw std::runtime_error("SdlEventHandlerInternal::HandleTextEditingEvent Error: Wrong event type was passed to this function!");

		SdlTextEditingEventData eventData;
		eventData.reserved = event.edit.reserved;
		eventData.timestamp = event.edit.timestamp;
		eventData.windowID = event.edit.windowID;
		eventData.text = event.edit.text;
		eventData.start = event.edit.start;
		eventData.length = event.edit.length;

		auto size = _textEditingEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _textEditingEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleTextEditingCandidatesEvent(const SDL_Event& event)
	{
		if (event.type != SDL_EVENT_TEXT_EDITING_CANDIDATES)
			throw std::runtime_error("SdlEventHandlerInternal::HandleTextEditingEvent Error: Wrong event type was passed to this function!");

		SdlTextEditingCandidatesEventData eventData;
		eventData.timestamp = event.edit_candidates.timestamp;
		eventData.reserved = event.edit_candidates.reserved;
		eventData.windowID = event.edit_candidates.windowID;
		eventData.candidates = event.edit_candidates.candidates;
		eventData.num_candidates = event.edit_candidates.num_candidates;
		eventData.selected_candidate = event.edit_candidates.selected_candidate;
		eventData.horizontal = event.edit_candidates.horizontal;
		eventData.padding1 = event.edit_candidates.padding1;
		eventData.padding2 = event.edit_candidates.padding2;
		eventData.padding3 = event.edit_candidates.padding3;

		auto size = _textEditingCandidatesEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _textEditingCandidatesEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleTextInputEvent(const SDL_Event& event)
	{
		if (event.type != SDL_EVENT_TEXT_INPUT)
			throw std::runtime_error("SdlEventHandlerInternal::HandleTextInputEvent Error: Wrong event type was passed to this function!");

		SdlTextInputEventData eventData;
		eventData.timestamp = event.text.timestamp;
		eventData.reserved = event.text.reserved;
		eventData.windowID = event.text.windowID;
		eventData.text = event.text.text;

		auto size = _textInputEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _textInputEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleMouseDeviceEvent(const SDL_Event& event)
	{
		SdlMouseDeviceEventData eventData;

		switch (event.type)
		{
		case SDL_EVENT_MOUSE_ADDED:
			eventData.subtype = SdlMouseDeviceEventSubType::MOUSE_DEVICE_ADDED;
			break;
		case SDL_EVENT_MOUSE_REMOVED:
			eventData.subtype = SdlMouseDeviceEventSubType::MOUSE_DEVICE_REMOVED;
			break;
		default:
			throw std::runtime_error("SdlEventHandlerInternal::HandleMouseDeviceEvent Error: Wrong event type was passed to this function!");
		}

		eventData.reserved = event.mdevice.reserved;
		eventData.timestamp = event.mdevice.timestamp;
		eventData.mouseID = event.mdevice.which;

		auto size = _mouseDeviceEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _mouseDeviceEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleMouseMotionEvent(const SDL_Event& event)
	{
		if (event.type != SDL_EVENT_MOUSE_MOTION)
			throw std::runtime_error("SdlEventHandlerInternal::HandleMouseMotionEvent Error: Wrong event type was passed to this function!");

		SdlMouseMotionEventData eventData;
		eventData.timestamp = event.motion.timestamp;
		eventData.reserved = event.motion.reserved;
		eventData.windowID = event.motion.windowID;
		eventData.mouseID = event.motion.which;
		eventData.state = event.motion.state;
		eventData.x = event.motion.x;
		eventData.y = event.motion.y;
		eventData.xrel = event.motion.xrel;
		eventData.yrel = event.motion.yrel;

		auto size = _mouseMotionEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _mouseMotionEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleMouseButtonEvent(const SDL_Event& event)
	{
		if (event.type != SDL_EVENT_MOUSE_BUTTON_DOWN && event.type != SDL_EVENT_MOUSE_BUTTON_UP)
			throw std::runtime_error("SdlEventHandlerInternal::HandleMouseButtonEvent Error: Wrong event type was passed to this function!");

		SdlMouseButtonEventData eventData;
		eventData.timestamp = event.button.timestamp;
		eventData.reserved = event.button.reserved;
		eventData.windowID = event.button.windowID;
		eventData.mouseID = event.button.which;
		eventData.button = event.button.button;
		eventData.down = event.button.down;
		eventData.clicks = event.button.clicks;
		eventData.x = event.button.x;
		eventData.y = event.button.y;

		auto size = _mouseButtonEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _mouseButtonEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleMouseWheelEvent(const SDL_Event& event)
	{
		if (event.type != SDL_EVENT_MOUSE_WHEEL)
			throw std::runtime_error("SdlEventHandlerInternal::HandleMouseWheelEvent Error: Wrong event type was passed to this function!");

		SdlMouseWheelEventData eventData;
		eventData.reserved = event.wheel.reserved;
		eventData.timestamp = event.wheel.timestamp;
		eventData.windowID = event.wheel.windowID;
		eventData.mouseID = event.wheel.which;
		eventData.x = event.wheel.x;
		eventData.y = event.wheel.y;
		eventData.direction = event.wheel.direction;
		eventData.mouse_x = event.wheel.mouse_x;
		eventData.mouse_y = event.wheel.mouse_y;
		eventData.int_x = event.wheel.integer_x;
		eventData.int_y = event.wheel.integer_y;

		auto size = _mouseWheelEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _mouseWheelEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleJoyAxisEvent(const SDL_Event& event)
	{
		if (event.type != SDL_EVENT_JOYSTICK_AXIS_MOTION)
			throw std::runtime_error("SdlEventHandlerInternal::HandleJoyAxisEvent Error: Wrong event type was passed to this function!");

		SdlJoyAxisEventData eventData;
		eventData.reserved = event.jaxis.reserved;
		eventData.timestamp = event.jaxis.timestamp;
		eventData.joystickID = event.jaxis.which;
		eventData.axis = event.jaxis.axis;
		eventData.padding1 = event.jaxis.padding1;
		eventData.padding2 = event.jaxis.padding2;
		eventData.padding3 = event.jaxis.padding3;
		eventData.value = event.jaxis.value;
		eventData.padding4 = event.jaxis.padding4;

		auto size = _joyAxisEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _joyAxisEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleJoyBallEvent(const SDL_Event& event)
	{
		if (event.type != SDL_EVENT_JOYSTICK_BALL_MOTION)
			throw std::runtime_error("SdlEventHandlerInternal::HandleJoyBallEvent Error: Wrong event type was passed to this function!");

		SdlJoyBallEventData eventData;
		eventData.timestamp = event.jball.timestamp;
		eventData.reserved = event.jball.reserved;
		eventData.joystickID = event.jball.which;
		eventData.ball = event.jball.ball;
		eventData.padding1 = event.jball.padding1;
		eventData.padding2 = event.jball.padding2;
		eventData.padding3 = event.jball.padding3;
		eventData.xrel = event.jball.xrel;
		eventData.yrel = event.jball.yrel;

		auto size = _joyBallEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _joyBallEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleJoyHatEvent(const SDL_Event& event)
	{
		if (event.type != SDL_EVENT_JOYSTICK_HAT_MOTION)
			throw std::runtime_error("SdlEventHandlerInternal::HandleJoyHatEvent Error: Wrong event type was passed to this function!");

		SdlJoyHatEventData eventData;
		eventData.timestamp = event.jhat.timestamp;
		eventData.reserved = event.jhat.reserved;
		eventData.joystickID = event.jhat.which;
		eventData.hat = event.jhat.hat;
		eventData.value = event.jhat.value;
		eventData.padding1 = event.jhat.padding1;
		eventData.padding2 = event.jhat.padding2;

		auto size = _joyHatEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _joyHatEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleJoyButtonEvent(const SDL_Event& event)
	{
		if (event.type != SDL_EVENT_JOYSTICK_BUTTON_DOWN && event.type != SDL_EVENT_JOYSTICK_BUTTON_UP)
			throw std::runtime_error("SdlEventHandlerInternal::HandleJoyButtonEvent Error: Wrong event type was passed to this function!");

		SdlJoyButtonEventData eventData;
		eventData.timestamp = event.jbutton.timestamp;
		eventData.reserved = event.jbutton.reserved;
		eventData.joystickID = event.jbutton.which;
		eventData.button = event.jbutton.button;
		eventData.down = event.jbutton.down;
		eventData.padding1 = event.jbutton.padding1;
		eventData.padding2 = event.jbutton.padding2;

		auto size = _joyButtonEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _joyButtonEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleJoyDeviceEvent(const SDL_Event& event)
	{
		SdlJoyDeviceEventData eventData;

		switch (event.type)
		{
		case SDL_EVENT_JOYSTICK_ADDED:
			eventData.subtype = SDL_JOYSTICK_DEVICE_SUBEVENT_DEVICE_ADDED;
			break;
		case SDL_EVENT_JOYSTICK_REMOVED:
			eventData.subtype = SDL_JOYSTICK_DEVICE_SUBEVENT_DEVICE_REMOVED;
			break;
		case SDL_EVENT_JOYSTICK_UPDATE_COMPLETE:
			eventData.subtype = SDL_JOYSTICK_DEVICE_SUBEVENT_DEVICE_UPDATE_COMPLETE;
			break;
		default:
			throw std::runtime_error("SdlEventHandlerInternal::HandleJoyDeviceEvent Error: Wrong event type was passed to this function!");
		}

		eventData.timestamp = event.jdevice.timestamp;
		eventData.reserved = event.jdevice.reserved;
		eventData.joystickID = event.jdevice.which;

		auto size = _joyDeviceEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _joyDeviceEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleJoyBatteryEvent(const SDL_Event& event)
	{
		if (event.type != SDL_EVENT_JOYSTICK_BATTERY_UPDATED)
			throw std::runtime_error("SdlEventHandlerInternal::HandleJoyBatteryEvent Error: Wrong event type was passed to this function!");

		SdlJoyBatteryEventData eventData;
		eventData.timestamp = event.jbattery.timestamp;
		eventData.reserved = event.jbattery.reserved;
		eventData.joystickID = event.jbattery.which;
		eventData.powerState = static_cast<SdlJoystickPowerState>(event.jbattery.state);
		eventData.powerPercentage = event.jbattery.percent;

		auto size = _joyBatteryEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _joyBatteryEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleGamepadAxisEvent(const SDL_Event& event)
	{
		if (event.type != SDL_EVENT_GAMEPAD_AXIS_MOTION)
			throw std::runtime_error("SdlEventHandlerInternal::HandleGamepadAxisEvent Error: Wrong event type was passed to this function!");

		SdlGamepadAxisEventData eventData;
		eventData.timestamp = event.gaxis.timestamp;
		eventData.reserved = event.gaxis.reserved;
		eventData.which = event.gaxis.which;
		eventData.axis = event.gaxis.axis;
		eventData.padding1 = event.gaxis.padding1;
		eventData.padding2 = event.gaxis.padding2;
		eventData.padding3 = event.gaxis.padding3;
		eventData.value = event.gaxis.value;
		eventData.padding4 = 0;

		auto size = _gamepadAxisEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _gamepadAxisEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleGamepadButtonEvent(const SDL_Event& event)
	{
		if (event.type != SDL_EVENT_GAMEPAD_BUTTON_DOWN && event.type != SDL_EVENT_GAMEPAD_BUTTON_UP)
			throw std::runtime_error("SdlEventHandlerInternal::HandleGamepadButtonEvent Error: Wrong event type was passed to this function!");

		SdlGamepadButtonEventData eventData;
		eventData.timestamp = event.gbutton.timestamp;
		eventData.reserved = event.gbutton.reserved;
		eventData.which = event.gbutton.which;
		eventData.button = event.gbutton.button;
		eventData.down = event.gbutton.down;
		eventData.padding1 = event.gbutton.padding1;
		eventData.padding2 = event.gbutton.padding2;

		auto size = _gamepadButtonEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _gamepadButtonEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleGamepadDeviceEvent(const SDL_Event& event)
	{
		SdlGamepadDeviceEventData eventData;
		switch (event.type)
		{
		case SDL_EVENT_GAMEPAD_ADDED:
			eventData.subtype = SdlGamepadDeviceSubEventType::DEVICE_ADDED;
			break;
		case SDL_EVENT_GAMEPAD_REMOVED:
			eventData.subtype = SdlGamepadDeviceSubEventType::DEVICE_REMOVED;
			break;
		case SDL_EVENT_GAMEPAD_REMAPPED:
			eventData.subtype = SdlGamepadDeviceSubEventType::DEVICE_REMAPPED;
			break;
		case SDL_EVENT_GAMEPAD_UPDATE_COMPLETE:
			eventData.subtype = SdlGamepadDeviceSubEventType::DEVICE_UPDATE_COMPLETE;
			break;
		case SDL_EVENT_GAMEPAD_STEAM_HANDLE_UPDATED:
			eventData.subtype = SdlGamepadDeviceSubEventType::DEVICE_STEAM_HANDLE_UPDATED;
			break;
		default:
			throw std::runtime_error("SdlEventHandlerInternal::HandleGamepadDeviceEvent Error: Wrong event type was passed to this function!");
		}
		eventData.timestamp = event.gdevice.timestamp;
		eventData.reserved = event.gdevice.reserved;
		eventData.which = event.gdevice.which;

		auto size = _gamepadDeviceEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _gamepadDeviceEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleGamepadTouchpadEvent(const SDL_Event& event)
	{
		SdlGamepadTouchpadEventData eventData;

		switch (event.type)
		{
		case SDL_EVENT_GAMEPAD_TOUCHPAD_DOWN:
			eventData.subtype = SdlGamepadTouchpadEventType::TOUCHPAD_DOWN;
			break;
		case SDL_EVENT_GAMEPAD_TOUCHPAD_MOTION:
			eventData.subtype = SdlGamepadTouchpadEventType::TOUCHPAD_MOTION;
			break;
		case SDL_EVENT_GAMEPAD_TOUCHPAD_UP:
			eventData.subtype = SdlGamepadTouchpadEventType::TOUCHPAD_UP;
			break;
		default:
			throw std::runtime_error("SdlEventHandlerInternal::HandleGamepadTouchpadEvent Error: Wrong event type was passed to this function!");
		}

		eventData.timestamp = event.gtouchpad.timestamp;
		eventData.reserved = event.gtouchpad.reserved;
		eventData.which = event.gtouchpad.which;
		eventData.touchpad = event.gtouchpad.touchpad;
		eventData.finger = event.gtouchpad.finger;
		eventData.x = event.gtouchpad.x;
		eventData.y = event.gtouchpad.y;
		eventData.pressure = event.gtouchpad.pressure;

		auto size = _gamepadTouchpadEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _gamepadTouchpadEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleGamepadSensorEvent(const SDL_Event& event)
	{
		if (event.type != SDL_EVENT_GAMEPAD_SENSOR_UPDATE)
			throw std::runtime_error("SdlEventHandlerInternal::HandleGamepadSensorEvent Error: Wrong event type was passed to this function!");

		SdlGamepadSensorEventData eventData;
		eventData.timestamp = event.gsensor.timestamp;
		eventData.reserved = event.gsensor.reserved;
		eventData.which = event.gsensor.which;
		eventData.sensor = event.gsensor.sensor;
		eventData.data[0] = event.gsensor.data[0];
		eventData.data[1] = event.gsensor.data[1];
		eventData.data[2] = event.gsensor.data[2];
		eventData.sensor_timestamp = event.gsensor.sensor_timestamp;

		auto size = _gamepadSensorEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _gamepadSensorEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleAudioDeviceEvent(const SDL_Event& event)
	{
		SdlAudioDeviceEventData eventData;

		switch (event.type)
		{
		case SDL_EVENT_AUDIO_DEVICE_ADDED:
			eventData.subtype = SdlAudioDeviceEventSubtype::AUDIO_DEVICE_EVENT_ADDED;
			break;
		case SDL_EVENT_AUDIO_DEVICE_REMOVED:
			eventData.subtype = SdlAudioDeviceEventSubtype::AUDIO_DEVICE_EVENT_REMOVED;
			break;
		case SDL_EVENT_AUDIO_DEVICE_FORMAT_CHANGED:
			eventData.subtype = SdlAudioDeviceEventSubtype::AUDIO_DEVICE_EVENT_FORMAT_CHANGED;
			break;
		default:
			throw std::runtime_error("SdlEventHandlerInternal::HandleAudioDeviceEvent Error: Wrong event type was passed to this function!");
		}
		eventData.reserved = event.adevice.reserved;
		eventData.timestamp = event.adevice.timestamp;
		eventData.which = event.adevice.which;
		eventData.recording = event.adevice.recording;
		eventData.padding1 = event.adevice.padding1;
		eventData.padding2 = event.adevice.padding2;
		eventData.padding3 = event.adevice.padding3;

		auto size = _audioDeviceEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _audioDeviceEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleTouchFingerEvent(const SDL_Event& event)
	{
		SdlTouchFingerEventData eventData;

		switch (event.type)
		{
		case SDL_EVENT_FINGER_DOWN:
			eventData.subtype = SdlTouchFingerEventType::FINGER_DOWN;
			break;
		case SDL_EVENT_FINGER_UP:
			eventData.subtype = SdlTouchFingerEventType::FINGER_UP;
			break;
		case SDL_EVENT_FINGER_MOTION:
			eventData.subtype = SdlTouchFingerEventType::FINGER_MOTION;
			break;
		case SDL_EVENT_FINGER_CANCELED:
			eventData.subtype = SdlTouchFingerEventType::FINGER_CANCELLED;
			break;
		default:
			throw std::runtime_error("SdlEventHandlerInternal::HandleTouchFingerEvent Error: Wrong event type was passed to this function!");
		}
		eventData.reserved = event.tfinger.reserved;
		eventData.timestamp = event.tfinger.timestamp;
		eventData.touchId = event.tfinger.touchID;
		eventData.fingerId = event.tfinger.fingerID;
		eventData.x = event.tfinger.x;
		eventData.y = event.tfinger.y;
		eventData.dx = event.tfinger.dx;
		eventData.dy = event.tfinger.dy;
		eventData.pressure = event.tfinger.pressure;
		eventData.windowID = event.tfinger.windowID;

		auto size = _touchFingerEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _touchFingerEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleTouchPinchEvent(const SDL_Event& event)
	{
		SdlTouchPinchEventData eventData;

		switch (event.type)
		{
		case SDL_EVENT_PINCH_BEGIN:
			eventData.subtype = SdlTouchPinchEventType::PINCH_BEGIN;
			break;
		case SDL_EVENT_PINCH_UPDATE:
			eventData.subtype = SdlTouchPinchEventType::PINCH_UPDATE;
			break;
		case SDL_EVENT_PINCH_END:
			eventData.subtype = SdlTouchPinchEventType::PINCH_END;
			break;
		default:
			throw std::runtime_error("SdlEventHandlerInternal::HandleTouchPinchEvent Error: Wrong event type was passed to this function!");
		}

		eventData.reserved = event.pinch.reserved;
		eventData.timestamp = event.pinch.timestamp;
		eventData.scale = event.pinch.scale;
		eventData.windowID = event.pinch.windowID;

		auto size = _touchPinchEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _touchPinchEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleCameraEvent(const SDL_Event& event)
	{
		SdlCameraEventData eventData;

		switch (event.type)
		{
		case SDL_EVENT_CAMERA_DEVICE_ADDED:
			eventData.subtype = SdlCameraDeviceEventSubtype::CAMERA_DEVICE_EVENT_ADDED;
			break;
		case SDL_EVENT_CAMERA_DEVICE_REMOVED:
			eventData.subtype = SdlCameraDeviceEventSubtype::CAMERA_DEVICE_EVENT_REMOVED;
			break;
		case SDL_EVENT_CAMERA_DEVICE_APPROVED:
			eventData.subtype = SdlCameraDeviceEventSubtype::CAMERA_DEVICE_EVENT_APPROVED;
			break;
		case SDL_EVENT_CAMERA_DEVICE_DENIED:
			eventData.subtype = SdlCameraDeviceEventSubtype::CAMERA_DEVICE_EVENT_DENIED;
			break;
		default:
			throw std::runtime_error("SdlEventHandlerInternal::HandleCameraEvent Error: Wrong event type was passed to this function!");
		}

		eventData.timestamp = event.cdevice.timestamp;
		eventData.reserved = event.cdevice.reserved;
		eventData.cameraID = event.cdevice.which;

		auto size = _cameraEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _cameraEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleClipboardEvent(const SDL_Event& event)
	{
		SdlClipboardEventData eventData;
		eventData.timestamp = event.clipboard.timestamp;
		eventData.reserved = event.clipboard.reserved;
		eventData.owner = event.clipboard.owner;
		eventData.mime_types_number = event.clipboard.num_mime_types;
		eventData.mime_types = event.clipboard.mime_types;

		auto size = _clipboardEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _clipboardEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleDropEvent(const SDL_Event& event)
	{
		SdlDropEventData eventData;

		switch (event.type)
		{
		case SDL_EVENT_DROP_BEGIN:
			eventData.subtype = SdlDropEventType::DROPEVENT_BEGIN;
			break;
		case SDL_EVENT_DROP_FILE:
			eventData.subtype = SdlDropEventType::DROPEVENT_FILE;
			break;
		case SDL_EVENT_DROP_TEXT:
			eventData.subtype = SdlDropEventType::DROPEVENT_TEXT;
			break;
		case SDL_EVENT_DROP_COMPLETE:
			eventData.subtype = SdlDropEventType::DROPEVENT_COMPLETE;
			break;
		case SDL_EVENT_DROP_POSITION:
			eventData.subtype = SdlDropEventType::DROPEVENT_POSITION;
			break;
		default:
			throw std::runtime_error("SdlEventHandlerInternal::HandleDropEvent Error: Wrong event type was passed to the function!");
		}
		eventData.reserved = event.drop.reserved;
		eventData.timestamp = event.drop.timestamp;
		eventData.windowID = event.drop.windowID;
		eventData.x = event.drop.x;
		eventData.y = event.drop.y;
		eventData.source = event.drop.source;
		eventData.data = event.drop.data;

		auto size = _dropEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _dropEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleSensorEvent(const SDL_Event& event)
	{
		if (event.type != SDL_EVENT_SENSOR_UPDATE)
			throw std::runtime_error("SdlEventHandlerInternal::HandleSensorEvent Error: Wrong event type was passed to this function!");

		SdlSensorEventData eventData;
		eventData.timestamp = event.sensor.timestamp;
		eventData.reserved = event.sensor.reserved;
		eventData.which = event.sensor.which;
		eventData.data[0] = event.sensor.data[0];
		eventData.data[1] = event.sensor.data[1];
		eventData.data[2] = event.sensor.data[2];
		eventData.data[3] = event.sensor.data[3];
		eventData.data[4] = event.sensor.data[4];
		eventData.data[5] = event.sensor.data[5];
		eventData.sensor_timestamp = event.sensor.sensor_timestamp;

		auto size = _sensorEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _sensorEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleUserEvent(const SDL_Event& event)
	{
		if (event.type < SDL_EVENT_USER || event.type >= SDL_EVENT_LAST)
			throw std::runtime_error("SdlEventHandlerInternal::HandleUserEvent Error: Wrong event type was passed to this function!");

		SdlUserEventData eventData;
		eventData.userEventType = event.type;
		eventData.reserved = event.user.reserved;
		eventData.timestamp = event.user.timestamp;
		eventData.windowID = event.user.windowID;
		eventData.code = event.user.code;
		eventData.data1 = event.user.data1;
		eventData.data2 = event.user.data2;

		auto size = _userEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _userEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandlePenAxisEvent(const SDL_Event& event)
	{
		if (event.type != SDL_EVENT_PEN_AXIS)
			throw std::runtime_error("SdlEventHandlerInternal::HandlePenAxisEvent Error: Wrong event type was passed to this function!");

		SdlPenAxisEventData eventData;
		eventData.timestamp = event.paxis.timestamp;
		eventData.reserved = event.paxis.reserved;
		eventData.windowID = event.paxis.windowID;
		eventData.penID = event.paxis.which;
		eventData.pen_state = event.paxis.pen_state;
		eventData.x = event.paxis.x;
		eventData.y = event.paxis.y;
		eventData.axis = event.paxis.axis;
		eventData.value = event.paxis.value;

		auto size = _penAxisEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _penAxisEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandlePenButtonEvent(const SDL_Event& event)
	{
		SdlPenButtonEventData eventData;
		switch (event.type)
		{
		case SDL_EVENT_PEN_BUTTON_DOWN:
			eventData.subtype = SdlPenButtonEventSubtype::PEN_BUTTON_DOWN;
			break;
		case SDL_EVENT_PEN_BUTTON_UP:
			eventData.subtype = SdlPenButtonEventSubtype::PEN_BUTTON_UP;
			break;
		default:
			throw std::runtime_error("SdlEventHandlerInternal::HandlePenButtonEvent Error: Wrong event type was passed to this function!");
		}
		eventData.reserved = event.pbutton.reserved;
		eventData.timestamp = event.pbutton.timestamp;
		eventData.windowID = event.pbutton.windowID;
		eventData.penID = event.pbutton.which;
		eventData.pen_state = event.pbutton.pen_state;
		eventData.x = event.pbutton.x;
		eventData.y = event.pbutton.y;
		eventData.button = event.pbutton.button;
		eventData.down = event.pbutton.down;

		auto size = _penButtonEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _penButtonEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandlePenMotionEvent(const SDL_Event& event)
	{
		if (event.type != SDL_EVENT_PEN_MOTION)
			throw std::runtime_error("SdlEventHandlerInternal::HandlePenMotionEvent Error: Wrong event type was passed to this function!");

		SdlPenMotionEventData eventData;
		eventData.timestamp = event.pmotion.timestamp;
		eventData.reserved = event.pmotion.reserved;
		eventData.windowID = event.pmotion.windowID;
		eventData.penID = event.pmotion.which;
		eventData.pen_state = event.pmotion.pen_state;
		eventData.x = event.pmotion.x;
		eventData.y = event.pmotion.y;

		auto size = _penMotionEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _penMotionEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandlePenTouchEvent(const SDL_Event& event)
	{
		SdlPenTouchEventData eventData;
		switch (event.type)
		{
		case SDL_EVENT_PEN_DOWN:
			eventData.subtype = SdlPenTouchEventSubtype::PEN_TOUCH_DOWN;
			break;
		case SDL_EVENT_PEN_UP:
			eventData.subtype = SdlPenTouchEventSubtype::PEN_TOUCH_UP;
			break;
		default:
			throw std::runtime_error("SdlEventHandlerInternal::HandlePenTouchEvent Error: Wrong event type was passed to this function!");
		}
		eventData.reserved = event.ptouch.reserved;
		eventData.timestamp = event.ptouch.timestamp;
		eventData.windowID = event.ptouch.windowID;
		eventData.penID = event.ptouch.which;
		eventData.pen_state = event.ptouch.pen_state;
		eventData.x = event.ptouch.x;
		eventData.y = event.ptouch.y;
		eventData.eraser = event.ptouch.eraser;
		eventData.down = event.ptouch.down;

		auto size = _penTouchEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _penTouchEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandlePenProximityEvent(const SDL_Event& event)
	{
		SdlPenProximityEventData eventData;
		switch (event.type)
		{
		case SDL_EVENT_PEN_PROXIMITY_IN:
			eventData.subtype = SdlPenProximityEventSubtype::PEN_PROXIMITY_IN;
			break;
		case SDL_EVENT_PEN_PROXIMITY_OUT:
			eventData.subtype = SdlPenProximityEventSubtype::PEN_PROXIMITY_OUT;
			break;
		default:
			throw std::runtime_error("SdlEventHandlerInternal::HandlePenProximityEvent Error: Wrong event type was passed to this function!");
		}
		eventData.reserved = event.pproximity.reserved;
		eventData.timestamp = event.pproximity.timestamp;
		eventData.windowID = event.pproximity.windowID;
		eventData.penID = event.pproximity.which;

		auto size = _penProximityEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _penProximityEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleRenderTargetsResetEvent(const SDL_Event& event)
	{
		if (event.type != SDL_EVENT_RENDER_TARGETS_RESET)
			throw std::runtime_error("SdlEventHandlerInternal::HandleRenderTargetsResetEvent Error: Wrong event type was passed to this function!");

		SdlRenderTargetsResetEventData eventData;
		eventData.reserved = event.common.reserved;
		eventData.timestamp = event.common.timestamp;

		auto size = _renderTargetsResetEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _renderTargetsResetEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleRenderDeviceResetEvent(const SDL_Event& event)
	{
		if (event.type != SDL_EVENT_RENDER_DEVICE_RESET)
			throw std::runtime_error("SdlEventHandlerInternal::HandleRenderDeviceResetEvent Error: Wrong event type was passed to this function!");

		SdlRenderDeviceResetEventData eventData;
		eventData.reserved = event.common.reserved;
		eventData.timestamp = event.common.timestamp;

		auto size = _renderDeviceResetEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _renderDeviceResetEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleRenderDeviceLostEvent(const SDL_Event& event)
	{
		if (event.type != SDL_EVENT_RENDER_DEVICE_LOST)
			throw std::runtime_error("SdlEventHandlerInternal::HandleRenderDeviceLostEvent Error: Wrong event type was passed to this function!");

		SdlRenderDeviceLostEventData eventData;
		eventData.reserved = event.common.reserved;
		eventData.timestamp = event.common.timestamp;

		auto size = _renderDeviceLostEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _renderDeviceLostEventFunctions.GetObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

}
