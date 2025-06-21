#include "SdlEhNipch.h"
#include "../EventHandler/SdlEventHandlerInternal.h"

#include "../../../../Include/VSMain/EventHandler/SdlEventHandlerInitData.h"

#include "../../../../Include/VSMain/EventHandler/SdlAppEventsData.h"
#include "../../../../Include/VSMain/EventHandler/SdlAudioDeviceEventData.h"
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
#include "../../../../Include/VSMain/EventHandler/SdlTextEventsData.h"
#include "../../../../Include/VSMain/EventHandler/SdlTouchpadEventData.h"
#include "../../../../Include/VSMain/EventHandler/SdlUserEventData.h"
#include "../../../../Include/VSMain/EventHandler/SdlWindowEventData.h"

namespace VulkanSimplified
{
	SdlEventHandlerInternal::SdlEventHandlerInternal(const SdlEventHandlerInitData& initData) : _quitEventFunctions(initData.quitEventFunctionListInitialCapacity),
		_appTerminatingEventFunctions(initData.appTerminatingEventFunctionListInitialCapacity), _appLowMemoryEventFunctions(initData.appLowMemoryEventFunctionListInitialCapacity),
		_appWillEnterBackgroundEventFunctions(initData.appWillEnterBackgroundEventFunctionListInitialCapacity),
		_appDidEnterBackgroundEventFunctions(initData.appDidEnterBackgroundEventFunctionListInitialCapacity),
		_appWillEnterForegroundEventFunctions(initData.appWillEnterForegroundEventFunctionListInitialCapacity),
		_appDidEnterForegroundEventFunctions(initData.appDidEnterForegroundEventFunctionListInitialCapacity),
		_localeChangedEventFunctions(initData.localeChangedEventFunctionListInitialCapacity), _displayEventFunctions(initData.displayEventFunctionListInitialCapacity),
		_windowEventFunctions(initData.windowEventFunctionListInitialCapacity), _keyboardEventFunctions(initData.keyboardEventFunctionListInitialCapacity),
		_keymapChangedEventFunctions(initData.keymapChangeEventFunctionListInitialCapacity), _textEditingEventFunctions(initData.textEditingEventFunctionListInitialCapacity),
		_textEditingExtendedEventFunctions(initData.textEditingExtendedEventFunctionListInitialCapacity), _textInputEventFunctions(initData.textInputEventFunctionListInitialCapacity),
		_mouseMotionEventFunctions(initData.mouseMotionEventFunctionListInitialCapacity), _mouseButtonEventFunctions(initData.mouseButtonEventFunctionListInitialCapacity),
		_mouseWheelEventFunctions(initData.mouseWheelEventFunctionListInitialCapacity), _joyAxisEventFunctions(initData.joyAxisEventFunctionListInitialCapacity),
		_joyBallEventFunctions(initData.joyBallEventFunctionListInitialCapacity), _joyHatEventFunctions(initData.joyHatEventFunctionListInitialCapacity),
		_joyButtonEventFunctions(initData.joyButtonEventFunctionListInitialCapacity), _joyDeviceEventFunctions(initData.joyDeviceEventFunctionListInitialCapacity),
		_joyBatteryEventFunctions(initData.joyBatteryEventFunctionListInitialCapacity), _controllerAxisEventFunctions(initData.controllerAxisEventFunctionListInitialCapacity),
		_controllerButtonEventFunctions(initData.controllerButtonEventFunctionListInitialCapacity), _controllerDeviceEventFunctions(initData.controllerDeviceEventFunctionListInitialCapacity),
		_controllerTouchpadEventFunctions(initData.controllerTouchpadEventFunctionListInitialCapacity), _controllerSensorEventFunctions(initData.controllerSensorEventFunctionListInitialCapacity),
		_audioDeviceEventFunctions(initData.audioDeviceEventFunctionListInitialCapacity), _touchFingerEventFunctions(initData.touchFingerEventFunctionListInitialCapacity),
		_multiGestureEventFunctions(initData.multiGestureEventFunctionListInitialCapacity), _dollarGestureEventFunctions(initData.dollarGestureEventFunctionListInitialCapacity),
		_clipboardEventFunctions(initData.clipboardEventFunctionListInitialCapacity), _dropEventFunctions(initData.dropEventFunctionListInitialCapacity),
		_sensorEventFunctions(initData.sensorEventFunctionListInitialCapacity), _userEventFunctions(initData.userEventFunctionListInitialCapacity),
		_renderTargetsResetEventFunctions(initData.renderTargetsResetEventFunctionListInitialCapacity),
		_renderDeviceResetEventFunctions(initData.renderDeviceResetEventFunctionListInitialCapacity)
	{
	}

	SdlEventHandlerInternal::~SdlEventHandlerInternal()
	{
	}

	void SdlEventHandlerInternal::HandleEvents()
	{
		SDL_Event event{};

		while (SDL_PollEvent(&event) > 0)
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

	IDObject<std::pair<DisplayEventFunction, void*>> SdlEventHandlerInternal::RegisterDisplayEventCallback(DisplayEventFunction function, void* data, size_t add)
	{
		return _displayEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<WindowEventFunction, void*>> SdlEventHandlerInternal::RegisterWindowEventCallback(WindowEventFunction function, void* data, size_t add)
	{
		return _windowEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<KeyboardEventFunction, void*>> SdlEventHandlerInternal::RegisterKeyboardEventCallback(KeyboardEventFunction function, void* data, size_t add)
	{
		return _keyboardEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<KeymapChangeEventFunction, void*>> SdlEventHandlerInternal::RegisterKeymapChangingEventCallback(KeymapChangeEventFunction function, void* data, size_t add)
	{
		return _keymapChangedEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<TextEditingEventFunction, void*>> SdlEventHandlerInternal::RegisterTextEditingEventCallback(TextEditingEventFunction function, void* data, size_t add)
	{
		return _textEditingEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<TextEditingExtendedEventFunction, void*>> SdlEventHandlerInternal::RegisterTextEditingExtendedEventCallback(TextEditingExtendedEventFunction function, void* data, size_t add)
	{
		return _textEditingExtendedEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<TextInputEventFunction, void*>> SdlEventHandlerInternal::RegisterTextInputEventCallback(TextInputEventFunction function, void* data, size_t add)
	{
		return _textInputEventFunctions.AddObject(std::pair(function, data), add);
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

	IDObject<std::pair<ControllerAxisEventFunction, void*>> SdlEventHandlerInternal::RegisterControllerAxisEventCallback(ControllerAxisEventFunction function, void* data, size_t add)
	{
		return _controllerAxisEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<ControllerButtonEventFunction, void*>> SdlEventHandlerInternal::RegisterControllerButtonEventCallback(ControllerButtonEventFunction function, void* data, size_t add)
	{
		return _controllerButtonEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<ControllerDeviceEventFunction, void*>> SdlEventHandlerInternal::RegisterControllerDeviceEventCallback(ControllerDeviceEventFunction function, void* data, size_t add)
	{
		return _controllerDeviceEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<ControllerTouchpadEventFunction, void*>> SdlEventHandlerInternal::RegisterControllerTouchpadEventCallback(ControllerTouchpadEventFunction function, void* data, size_t add)
	{
		return _controllerTouchpadEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<ControllerSensorEventFunction, void*>> SdlEventHandlerInternal::RegisterControllerSensorEventCallback(ControllerSensorEventFunction function, void* data, size_t add)
	{
		return _controllerSensorEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<AudioDeviceEventFunction, void*>> SdlEventHandlerInternal::RegisterAudioDeviceEventCallback(AudioDeviceEventFunction function, void* data, size_t add)
	{
		return _audioDeviceEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<TouchFingerEventFunction, void*>> SdlEventHandlerInternal::RegisterTouchFingerEventCallback(TouchFingerEventFunction function, void* data, size_t add)
	{
		return _touchFingerEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<MultiGestureEventFunction, void*>> SdlEventHandlerInternal::RegisterMultiGestureEventCallback(MultiGestureEventFunction function, void* data, size_t add)
	{
		return _multiGestureEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<DollarGestureEventFunction, void*>> SdlEventHandlerInternal::RegisterDollarGestureEventCallback(DollarGestureEventFunction function, void* data, size_t add)
	{
		return _dollarGestureEventFunctions.AddObject(std::pair(function, data), add);
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

	IDObject<std::pair<RenderTargetsResetEventFunction, void*>> SdlEventHandlerInternal::RegisterRenderTargetsResetEventCallback(RenderTargetsResetEventFunction function, void* data, size_t add)
	{
		return _renderTargetsResetEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<RenderDeviceResetEventFunction, void*>> SdlEventHandlerInternal::RegisterRenderDeviceResetEventCallback(RenderDeviceResetEventFunction function, void* data, size_t add)
	{
		return _renderDeviceResetEventFunctions.AddObject(std::pair(function, data), add);
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

	bool SdlEventHandlerInternal::UnRegisterDisplayEventCallback(IDObject<std::pair<DisplayEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _displayEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterWindowEventCallback(IDObject<std::pair<WindowEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _windowEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterKeyboardEventCallback(IDObject<std::pair<KeyboardEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _keyboardEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterKeymapChangeEventCallback(IDObject<std::pair<KeymapChangeEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _keymapChangedEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterTextEditingEventCallback(IDObject<std::pair<TextEditingEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _textEditingEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterTextEditingExtendedEventCallback(IDObject<std::pair<TextEditingExtendedEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _textEditingExtendedEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterTextInputEventCallback(IDObject<std::pair<TextInputEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _textInputEventFunctions.RemoveObject(ID, throwOnIDNotFound);
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

	bool SdlEventHandlerInternal::UnRegisterControllerAxisEventCallback(IDObject<std::pair<ControllerAxisEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _controllerAxisEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterControllerButtonEventCallback(IDObject<std::pair<ControllerButtonEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _controllerButtonEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterControllerDeviceEventCallback(IDObject<std::pair<ControllerDeviceEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _controllerDeviceEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterControllerTouchpadEventCallback(IDObject<std::pair<ControllerTouchpadEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _controllerTouchpadEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterControllerSensorEventCallback(IDObject<std::pair<ControllerSensorEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _controllerSensorEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterAudioDeviceEventCallback(IDObject<std::pair<AudioDeviceEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _audioDeviceEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterTouchFingerEventCallback(IDObject<std::pair<TouchFingerEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _touchFingerEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterMultiGestureEventCallback(IDObject<std::pair<MultiGestureEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _multiGestureEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterDollarGestureEventCallback(IDObject<std::pair<DollarGestureEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _dollarGestureEventFunctions.RemoveObject(ID, throwOnIDNotFound);
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

	bool SdlEventHandlerInternal::UnRegisterRenderTargetsResetEventCallback(IDObject<std::pair<RenderTargetsResetEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _renderTargetsResetEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterRenderDeviceResetEventCallback(IDObject<std::pair<RenderDeviceResetEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _renderDeviceResetEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	void SdlEventHandlerInternal::HandleEvent(const SDL_Event& event)
	{
		auto& type = event.type;

		switch (type)
		{
		case SDL_FIRSTEVENT:
			break;
		case SDL_QUIT:
			HandleQuitEvent(event);
			break;
		case SDL_APP_TERMINATING:
			HandleAppTerminatingEvent(event);
			break;
		case SDL_APP_LOWMEMORY:
			HandleAppLowMemoryEvent(event);
			break;
		case SDL_APP_WILLENTERBACKGROUND:
			HandleAppWillEnterBackgroundEvent(event);
			break;
		case SDL_APP_DIDENTERBACKGROUND:
			HandleAppDidEnterBackgroundEvent(event);
			break;
		case SDL_APP_WILLENTERFOREGROUND:
			HandleAppWillEnterForegroundEvent(event);
			break;
		case SDL_APP_DIDENTERFOREGROUND:
			HandleAppDidEnterForegroundEvent(event);
			break;
		case SDL_LOCALECHANGED:
			HandleLocaleChangeEvent(event);
			break;
		case SDL_DISPLAYEVENT:
			HandleDisplayEvent(event);
			break;
		case SDL_WINDOWEVENT:
			HandleWindowEvent(event);
			break;
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			HandleKeyboardEvent(event);
			break;
		case SDL_TEXTEDITING:
			HandleTextEditingEvent(event);
			break;
		case SDL_TEXTINPUT:
			HandleTextInputEvent(event);
			break;
		case SDL_KEYMAPCHANGED:
			HandleKeymapChangedEvent(event);
			break;
		case SDL_TEXTEDITING_EXT:
			HandleTextEditingExtendedEvent(event);
			break;
		case SDL_MOUSEMOTION:
			HandleMouseMotionEvent(event);
			break;
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			HandleMouseButtonEvent(event);
			break;
		case SDL_MOUSEWHEEL:
			HandleMouseWheelEvent(event);
			break;
		case SDL_JOYAXISMOTION:
			HandleJoyAxisEvent(event);
			break;
		case SDL_JOYBALLMOTION:
			HandleJoyBallEvent(event);
			break;
		case SDL_JOYHATMOTION:
			HandleJoyHatEvent(event);
			break;
		case SDL_JOYBUTTONDOWN:
		case SDL_JOYBUTTONUP:
			HandleJoyButtonEvent(event);
			break;
		case SDL_JOYDEVICEADDED:
		case SDL_JOYDEVICEREMOVED:
			HandleJoyDeviceEvent(event);
			break;
		case SDL_JOYBATTERYUPDATED:
			HandleJoyBatteryEvent(event);
			break;
		case SDL_CONTROLLERAXISMOTION:
			HandleControllerAxisEvent(event);
			break;
		case SDL_CONTROLLERBUTTONDOWN:
		case SDL_CONTROLLERBUTTONUP:
			HandleControllerButtonEvent(event);
			break;
		case SDL_CONTROLLERDEVICEADDED:
		case SDL_CONTROLLERDEVICEREMOVED:
		case SDL_CONTROLLERDEVICEREMAPPED:
			HandleControllerDeviceEvent(event);
			break;
		case SDL_CONTROLLERTOUCHPADDOWN:
		case SDL_CONTROLLERTOUCHPADMOTION:
		case SDL_CONTROLLERTOUCHPADUP:
			HandleControllerTouchpadEvent(event);
			break;
		case SDL_CONTROLLERSENSORUPDATE:
			HandleControllerSensorEvent(event);
			break;
		case SDL_FINGERDOWN:
		case SDL_FINGERUP:
		case SDL_FINGERMOTION:
			HandleTouchFingerEvent(event);
			break;
		case SDL_DOLLARGESTURE:
		case SDL_DOLLARRECORD:
			HandleDollarGestureEvent(event);
			break;
		case SDL_MULTIGESTURE:
			HandleMultiGestureEvent(event);
			break;
		case SDL_CLIPBOARDUPDATE:
			HandleClipboardEvent(event);
			break;
		case SDL_DROPFILE:
		case SDL_DROPTEXT:
		case SDL_DROPBEGIN:
		case SDL_DROPCOMPLETE:
			HandleDropEvent(event);
			break;
		case SDL_AUDIODEVICEADDED:
		case SDL_AUDIODEVICEREMOVED:
			HandleAudioDeviceEvent(event);
			break;
		case SDL_SENSORUPDATE:
			HandleSensorEvent(event);
			break;
		case SDL_RENDER_TARGETS_RESET:
			HandleRenderTargetsResetEvent(event);
			break;
		case SDL_RENDER_DEVICE_RESET:
			HandleRenderDeviceResetEvent(event);
			break;
		case SDL_POLLSENTINEL:
			break;
		case SDL_USEREVENT:
			HandleUserEvent(event);
			break;
		case SDL_LASTEVENT:
			break;
		default:
			break;
		}
	}

	void SdlEventHandlerInternal::HandleQuitEvent(const SDL_Event& event)
	{
		SdlQuitEventData eventData;
		eventData.timestamp = event.quit.timestamp;

		auto size = _quitEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _quitEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleAppTerminatingEvent(const SDL_Event& event)
	{
		SdlAppTerminatingEventData eventData;
		eventData.timestamp = event.common.timestamp;

		auto size = _appTerminatingEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _appTerminatingEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleAppLowMemoryEvent(const SDL_Event& event)
	{
		SdlAppLowMemoryEventData eventData;
		eventData.timestamp = event.common.timestamp;

		auto size = _appLowMemoryEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _appLowMemoryEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleAppWillEnterBackgroundEvent(const SDL_Event& event)
	{
		SdlAppWillEnterBackgroundEventData eventData;
		eventData.timestamp = event.common.timestamp;

		auto size = _appWillEnterBackgroundEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _appWillEnterBackgroundEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleAppDidEnterBackgroundEvent(const SDL_Event& event)
	{
		SdlAppDidEnterBackgroundEventData eventData;
		eventData.timestamp = event.common.timestamp;

		auto size = _appDidEnterBackgroundEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _appDidEnterBackgroundEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleAppWillEnterForegroundEvent(const SDL_Event& event)
	{
		SdlAppWillEnterForegroundEventData eventData;
		eventData.timestamp = event.common.timestamp;

		auto size = _appWillEnterForegroundEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _appWillEnterForegroundEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleAppDidEnterForegroundEvent(const SDL_Event& event)
	{
		SdlAppDidEnterForegroundEventData eventData;
		eventData.timestamp = event.common.timestamp;

		auto size = _appDidEnterForegroundEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _appDidEnterForegroundEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleLocaleChangeEvent(const SDL_Event& event)
	{
		SdlLocaleChangeEventData eventData;
		eventData.timestamp = event.common.timestamp;

		auto size = _localeChangedEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _localeChangedEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleDisplayEvent(const SDL_Event& event)
	{
		SdlDisplayEventData eventData;
		eventData.timestamp = event.display.timestamp;
		eventData.display = event.display.display;

		switch (event.display.event)
		{
		case SDL_DisplayEventID::SDL_DISPLAYEVENT_NONE:
			eventData.event = SDL_DATA_DISPLAYEVENT_NONE;
			break;
		case SDL_DisplayEventID::SDL_DISPLAYEVENT_ORIENTATION:
			eventData.event = SDL_DATA_DISPLAYEVENT_ORIENTATION;
			break;
		case SDL_DisplayEventID::SDL_DISPLAYEVENT_CONNECTED:
			eventData.event = SDL_DATA_DISPLAYEVENT_CONNECTED;
			break;
		case SDL_DisplayEventID::SDL_DISPLAYEVENT_DISCONNECTED:
			eventData.event = SDL_DATA_DISPLAYEVENT_DISCONNECTED;
			break;
		case SDL_DisplayEventID::SDL_DISPLAYEVENT_MOVED:
			eventData.event = SDL_DATA_DISPLAYEVENT_MOVED;
			break;
		default:
			throw std::runtime_error("SdlEventHandlerInternal::HandleDisplayEvent Error: Wrong display event subtype was passed to the function!");
		}

		eventData.padding1 = event.display.padding1;
		eventData.padding2 = event.display.padding2;
		eventData.padding3 = event.display.padding3;
		eventData.data1 = event.display.data1;

		auto size = _displayEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _displayEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleWindowEvent(const SDL_Event& event)
	{
		SdlWindowEventData eventData;
		eventData.timestamp = event.window.timestamp;
		eventData.windowID = event.window.windowID;
		eventData.event = event.window.event;
		eventData.padding1 = event.window.padding1;
		eventData.padding2 = event.window.padding2;
		eventData.padding3 = event.window.padding3;
		eventData.data1 = event.window.data1;
		eventData.data2 = event.window.data2;
		eventData.padding = 0;

		auto size = _windowEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _windowEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleKeyboardEvent(const SDL_Event& event)
	{
		SdlKeyboardEventData eventData;
		eventData.timestamp = event.key.timestamp;
		eventData.windowID = event.key.windowID;
		eventData.state = event.key.state;
		eventData.repeat = event.key.repeat;
		eventData.padding2 = event.key.padding2;
		eventData.padding3 = event.key.padding3;
		eventData.padding = 0;

		eventData.keysym.scancode = static_cast<SdlScancode>(event.key.keysym.scancode);
		eventData.keysym.sym = static_cast<SdlKeycode>(event.key.keysym.sym);
		eventData.keysym.mod = event.key.keysym.mod;
		eventData.keysym.padding = 0;
		eventData.keysym.unused = event.key.keysym.unused;

		auto size = _keyboardEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _keyboardEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleKeymapChangedEvent(const SDL_Event& event)
	{
		SdlKeymapChangedEventData eventData;
		eventData.timestamp = event.common.timestamp;

		auto size = _keymapChangedEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _keymapChangedEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleTextEditingEvent(const SDL_Event& event)
	{
		SdlTextEditingEventData eventData;
		eventData.timestamp = event.edit.timestamp;
		eventData.windowID = event.edit.windowID;
		for (size_t i = 0; i < SDL_DATA_TEXTEDITINGEVENT_TEXT_SIZE; i++)
			eventData.text[i] = event.edit.text[i];
		eventData.start = event.edit.start;
		eventData.length = event.edit.length;

		auto size = _textEditingEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _textEditingEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleTextEditingExtendedEvent(const SDL_Event& event)
	{
		SdlTextEditingExtendedEventData eventData;
		eventData.timestamp = event.editExt.timestamp;
		eventData.windowID = event.editExt.windowID;
		eventData.text = event.editExt.text;
		eventData.start = event.editExt.start;
		eventData.length = event.editExt.length;

		auto size = _textEditingExtendedEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _textEditingExtendedEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleTextInputEvent(const SDL_Event& event)
	{
		SdlTextInputEventData eventData;
		eventData.timestamp = event.text.timestamp;
		eventData.windowID = event.text.windowID;
		for (size_t i = 0; i < SDL_DATA_TEXTINPUTEVENT_TEXT_SIZE; i++)
			eventData.text[i] = event.text.text[i];

		auto size = _textInputEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _textInputEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleMouseMotionEvent(const SDL_Event& event)
	{
		SdlMouseMotionEventData eventData;
		eventData.timestamp = event.motion.timestamp;
		eventData.windowID = event.motion.windowID;
		eventData.which = event.motion.which;
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

			auto& functiondata = _mouseMotionEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleMouseButtonEvent(const SDL_Event& event)
	{
		SdlMouseButtonEventData eventData;
		eventData.timestamp = event.button.timestamp;
		eventData.windowID = event.button.windowID;
		eventData.which = event.button.which;
		eventData.button = event.button.button;
		eventData.state = event.button.state;
		eventData.clicks = event.button.clicks;
		eventData.padding1 = event.button.padding1;
		eventData.x = event.button.x;
		eventData.y = event.button.y;

		auto size = _mouseButtonEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _mouseButtonEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleMouseWheelEvent(const SDL_Event& event)
	{
		SdlMouseWheelEventData eventData;
		eventData.timestamp = event.wheel.timestamp;
		eventData.windowID = event.wheel.windowID;
		eventData.which = event.wheel.which;
		eventData.x = event.wheel.x;
		eventData.y = event.wheel.y;
		eventData.direction = event.wheel.direction;
		eventData.preciseX = event.wheel.preciseX;
		eventData.preciseY = event.wheel.preciseY;
		eventData.mouseX = event.wheel.mouseX;
		eventData.mouseY = event.wheel.mouseY;

		auto size = _mouseWheelEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _mouseWheelEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleJoyAxisEvent(const SDL_Event& event)
	{
		SdlJoyAxisEventData eventData;
		eventData.timestamp = event.jaxis.timestamp;
		eventData.which = event.jaxis.which;
		eventData.axis = event.jaxis.axis;
		eventData.padding1 = event.jaxis.padding1;
		eventData.padding2 = event.jaxis.padding2;
		eventData.padding3 = event.jaxis.padding3;
		eventData.value = event.jaxis.value;
		eventData.padding4 = 0;

		auto size = _joyAxisEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _joyAxisEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleJoyBallEvent(const SDL_Event& event)
	{
		SdlJoyBallEventData eventData;
		eventData.timestamp = event.jball.timestamp;
		eventData.which = event.jball.which;
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

			auto& functiondata = _joyBallEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleJoyHatEvent(const SDL_Event& event)
	{
		SdlJoyHatEventData eventData;
		eventData.timestamp = event.jhat.timestamp;
		eventData.which = event.jhat.which;
		eventData.hat = event.jhat.hat;
		eventData.value = event.jhat.value;
		eventData.padding1 = event.jhat.padding1;
		eventData.padding2 = event.jhat.padding2;
		eventData.padding3 = 0;

		auto size = _joyHatEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _joyHatEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleJoyButtonEvent(const SDL_Event& event)
	{
		SdlJoyButtonEventData eventData;
		eventData.timestamp = event.jbutton.timestamp;
		eventData.which = event.jbutton.which;
		eventData.button = event.jbutton.button;
		eventData.state = event.jbutton.state;
		eventData.padding1 = event.jbutton.padding1;
		eventData.padding2 = event.jbutton.padding2;
		eventData.padding3 = 0;

		auto size = _joyButtonEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _joyButtonEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleJoyDeviceEvent(const SDL_Event& event)
	{
		SdlJoyDeviceEventData eventData;

		if (event.type == static_cast<uint32_t>(SDL_EventType::SDL_JOYDEVICEADDED))
			eventData.type = 1;
		else
			eventData.type = 0;

		eventData.timestamp = event.jdevice.timestamp;
		eventData.which = event.jdevice.which;

		auto size = _joyDeviceEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _joyDeviceEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleJoyBatteryEvent(const SDL_Event& event)
	{
		SdlJoyBatteryEventData eventData;
		eventData.timestamp = event.jbattery.timestamp;
		eventData.which = event.jbattery.which;
		eventData.level = static_cast<SdlJoystickPowerLevel>(event.jbattery.level);

		auto size = _joyBatteryEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _joyBatteryEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleControllerAxisEvent(const SDL_Event& event)
	{
		SdlControllerAxisEventData eventData;
		eventData.timestamp = event.caxis.timestamp;
		eventData.which = event.caxis.which;
		eventData.axis = event.caxis.axis;
		eventData.padding1 = event.caxis.padding1;
		eventData.padding2 = event.caxis.padding2;
		eventData.padding3 = event.caxis.padding3;
		eventData.value = event.caxis.value;
		eventData.padding4 = 0;

		auto size = _controllerAxisEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _controllerAxisEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleControllerButtonEvent(const SDL_Event& event)
	{
		SdlControllerButtonEventData eventData;
		eventData.timestamp = event.cbutton.timestamp;
		eventData.which = event.cbutton.which;
		eventData.button = event.cbutton.button;
		eventData.state = event.cbutton.state;
		eventData.padding1 = event.cbutton.padding1;
		eventData.padding2 = event.cbutton.padding2;
		eventData.padding3 = 0;

		auto size = _controllerButtonEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _controllerButtonEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleControllerDeviceEvent(const SDL_Event& event)
	{
		SdlControllerDeviceEventData eventData;
		switch (event.type)
		{
		case SDL_CONTROLLERDEVICEADDED:
			eventData.type = SdlControllerDeviceEventType::DEVICE_ADDED;
			break;
		case SDL_CONTROLLERDEVICEREMOVED:
			eventData.type = SdlControllerDeviceEventType::DEVICE_REMOVED;
			break;
		case SDL_CONTROLLERDEVICEREMAPPED:
			eventData.type = SdlControllerDeviceEventType::DEVICE_REMMAPED;
			break;
		default:
			throw std::runtime_error("SdlEventHandlerInternal::HandleControllerDeviceEvent error: Wrong event type was passed to the function!");
		}
		eventData.timestamp = event.cdevice.timestamp;
		eventData.which = event.cdevice.which;
		eventData.padding = 0;

		auto size = _controllerDeviceEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _controllerDeviceEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleControllerTouchpadEvent(const SDL_Event& event)
	{
		SdlControllerTouchpadEventData eventData;

		switch (event.type)
		{
		case SDL_CONTROLLERTOUCHPADDOWN:
			eventData.type = SdlControllerTouchpadEventType::TOUCHPAD_DOWN;
			break;
		case SDL_CONTROLLERTOUCHPADMOTION:
			eventData.type = SdlControllerTouchpadEventType::TOUCHPAD_MOTION;
			break;
		case SDL_CONTROLLERTOUCHPADUP:
			eventData.type = SdlControllerTouchpadEventType::TOUCHPAD_DOWN;
			break;
		default:
			throw std::runtime_error("SdlEventHandlerInternal::HandleControllerTouchpadEvent Error: Wrong event type was passed to the function!");
		}

		eventData.timestamp = event.ctouchpad.timestamp;
		eventData.which = event.ctouchpad.which;
		eventData.touchpad = event.ctouchpad.touchpad;
		eventData.finger = event.ctouchpad.finger;
		eventData.x = event.ctouchpad.x;
		eventData.y = event.ctouchpad.y;
		eventData.pressure = event.ctouchpad.pressure;

		auto size = _controllerTouchpadEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _controllerTouchpadEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleControllerSensorEvent(const SDL_Event& event)
	{
		SdlControllerSensorEventData eventData;
		eventData.timestamp = event.csensor.timestamp;
		eventData.which = event.csensor.which;
		eventData.sensor = event.csensor.sensor;
		eventData.data[0] = event.csensor.data[0];
		eventData.data[1] = event.csensor.data[1];
		eventData.data[2] = event.csensor.data[2];
		eventData.timestamp_us = event.csensor.timestamp_us;

		auto size = _controllerSensorEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _controllerSensorEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleAudioDeviceEvent(const SDL_Event& event)
	{
		SdlAudioDeviceEventData eventData;
		if (event.type == SDL_AUDIODEVICEADDED)
			eventData.type = 1;
		else
			eventData.type = 0;

		eventData.timestamp = event.adevice.timestamp;
		eventData.which = event.adevice.which;
		eventData.iscapture = event.adevice.iscapture;
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

			auto& functiondata = _audioDeviceEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleTouchFingerEvent(const SDL_Event& event)
	{
		SdlTouchFingerEventData eventData;

		switch (event.type)
		{
		case SDL_FINGERDOWN:
			eventData.type = SdlTouchFingerEventType::FINGER_DOWN;
			break;
		case SDL_FINGERUP:
			eventData.type = SdlTouchFingerEventType::FINGER_UP;
			break;
		case SDL_FINGERMOTION:
			eventData.type = SdlTouchFingerEventType::FINGER_MOTION;
			break;
		default:
			throw std::runtime_error("SdlEventHandlerInternal::HandleTouchFingerEvent Error: Wrong event type was passed to the function!");
		}

		eventData.timestamp = event.tfinger.timestamp;
		eventData.touchId = event.tfinger.touchId;
		eventData.fingerId = event.tfinger.fingerId;
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

			auto& functiondata = _touchFingerEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleMultiGestureEvent(const SDL_Event& event)
	{
		SdlMultiGestureEventData eventData;
		eventData.timestamp = event.mgesture.timestamp;
		eventData.padding2 = 0;
		eventData.touchId = event.mgesture.touchId;
		eventData.dTheta = event.mgesture.dTheta;
		eventData.dDist = event.mgesture.dDist;
		eventData.x = event.mgesture.x;
		eventData.y = event.mgesture.y;
		eventData.numFingers = event.mgesture.numFingers;
		eventData.padding = event.mgesture.padding;
		eventData.padding3 = 0;

		auto size = _multiGestureEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _multiGestureEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleDollarGestureEvent(const SDL_Event& event)
	{
		SdlDollarGestureEventData eventData;

		if (event.type == SDL_DOLLARGESTURE)
			eventData.type = 1;
		else
			eventData.type = 0;

		eventData.timestamp = event.dgesture.timestamp;
		eventData.touchId = event.dgesture.touchId;
		eventData.gestureId = event.dgesture.gestureId;
		eventData.numFingers = event.dgesture.numFingers;
		eventData.error = event.dgesture.error;
		eventData.x = event.dgesture.x;
		eventData.y = event.dgesture.y;

		auto size = _dollarGestureEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _dollarGestureEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleClipboardEvent(const SDL_Event& event)
	{
		SdlClipboardEventData eventData;
		eventData.timestamp = event.common.timestamp;

		auto size = _clipboardEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _clipboardEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleDropEvent(const SDL_Event& event)
	{
		SdlDropEventData eventData;

		switch (event.type)
		{
		case SDL_DROPBEGIN:
			eventData.type = SdlDropEventType::DROPEVENT_BEGIN;
			break;
		case SDL_DROPFILE:
			eventData.type = SdlDropEventType::DROPEVENT_FILE;
			break;
		case SDL_DROPTEXT:
			eventData.type = SdlDropEventType::DROPEVENT_TEXT;
			break;
		case SDL_DROPCOMPLETE:
			eventData.type = SdlDropEventType::DROPEVENT_COMPLETE;
			break;
		default:
			throw std::runtime_error("SdlEventHandlerInternal::HandleDropEvent Error: Wrong event type was passed to the function!");
		}

		eventData.timestamp = event.drop.timestamp;
		eventData.file = event.drop.file;
		eventData.windowID = event.drop.windowID;
		eventData.padding = 0;

		auto size = _dropEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _dropEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}

		if (eventData.file != nullptr)
			SDL_free(eventData.file);
	}

	void SdlEventHandlerInternal::HandleSensorEvent(const SDL_Event& event)
	{
		SdlSensorEventData eventData;
		eventData.timestamp = event.sensor.timestamp;
		eventData.which = event.sensor.which;
		eventData.data[0] = event.sensor.data[0];
		eventData.data[1] = event.sensor.data[1];
		eventData.data[2] = event.sensor.data[2];
		eventData.data[3] = event.sensor.data[3];
		eventData.data[4] = event.sensor.data[4];
		eventData.data[5] = event.sensor.data[5];
		eventData.timestamp_us = event.sensor.timestamp_us;

		auto size = _sensorEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _sensorEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleUserEvent(const SDL_Event& event)
	{
		SdlUserEventData eventData;
		eventData.timestamp = event.user.timestamp;
		eventData.windowID = event.user.windowID;
		eventData.code = event.user.code;
		eventData.padding = 0;
		eventData.data1 = event.user.data1;
		eventData.data2 = event.user.data2;

		auto size = _userEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _userEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleRenderTargetsResetEvent(const SDL_Event& event)
	{
		SdlRenderTargetsResetEventData eventData;
		eventData.timestamp = event.common.timestamp;

		auto size = _renderTargetsResetEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _renderTargetsResetEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleRenderDeviceResetEvent(const SDL_Event& event)
	{
		SdlRenderDeviceResetEventData eventData;
		eventData.timestamp = event.common.timestamp;

		auto size = _renderDeviceResetEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _renderDeviceResetEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(eventData, functiondata.second);
		}
	}
}
