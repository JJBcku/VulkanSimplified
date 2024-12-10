#include "SdlEhNipch.h"
#include "SdlEventHandlerInternal.h"

#include "../../../Include/VSMain/EventHandler/SdlEventHandlerInitData.h"

#include "../../../Include/VSMain/EventHandler/SdlAppEventsData.h"
#include "../../../Include/VSMain/EventHandler/SdlAudioDeviceEventData.h"
#include "../../../Include/VSMain/EventHandler/SdlClipboardEventData.h"
#include "../../../Include/VSMain/EventHandler/SdlControllerEventsData.h"
#include "../../../Include/VSMain/EventHandler/SdlDisplayEventData.h"
#include "../../../Include/VSMain/EventHandler/SdlDropEventData.h"
#include "../../../Include/VSMain/EventHandler/SdlJoyEventsData.h"
#include "../../../Include/VSMain/EventHandler/SdlKeyboardEventsData.h"
#include "../../../Include/VSMain/EventHandler/SdlLocaleChangedEventData.h"
#include "../../../Include/VSMain/EventHandler/SdlMouseEventsData.h"
#include "../../../Include/VSMain/EventHandler/SdlQuitEventData.h"
#include "../../../Include/VSMain/EventHandler/SdlRenderEventsData.h"
#include "../../../Include/VSMain/EventHandler/SdlSensorEventData.h"
#include "../../../Include/VSMain/EventHandler/SdlTextEventsData.h"
#include "../../../Include/VSMain/EventHandler/SdlTouchpadEventData.h"
#include "../../../Include/VSMain/EventHandler/SdlUserEventData.h"
#include "../../../Include/VSMain/EventHandler/SdlWindowEventData.h"

namespace VulkanSimplifiedInternal
{
	SdlEventHandlerInternal::SdlEventHandlerInternal(const VulkanSimplified::SdlEventHandlerInitData& initData) : _quitEventFunctions(initData.quitEventFunctionListInitialCapacity),
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

	IDObject<std::pair<VulkanSimplified::QuitEventFunction, void*>> SdlEventHandlerInternal::RegisterQuitEventCallback(VulkanSimplified::QuitEventFunction function, void* data, size_t add)
	{
		return _quitEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<VulkanSimplified::AppTerminatingEventFunction, void*>> SdlEventHandlerInternal::RegisterAppTerminatingEventCallback(VulkanSimplified::AppTerminatingEventFunction function, void* data, size_t add)
	{
		return _appTerminatingEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<VulkanSimplified::AppLowMemoryEventFunction, void*>> SdlEventHandlerInternal::RegisterAppLowMemoryWarningEventCallback(VulkanSimplified::AppLowMemoryEventFunction function, void* data, size_t add)
	{
		return _appLowMemoryEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<VulkanSimplified::AppWillEnterBackgroundEventFunction, void*>> SdlEventHandlerInternal::RegisterAppWillEnterBackgroundWarningEventCallback(VulkanSimplified::AppWillEnterBackgroundEventFunction function, void* data, size_t add)
	{
		return _appWillEnterBackgroundEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<VulkanSimplified::AppDidEnterBackgroundEventFunction, void*>> SdlEventHandlerInternal::RegisterAppDidEnterBackgroundEventCallback(VulkanSimplified::AppDidEnterBackgroundEventFunction function, void* data, size_t add)
	{
		return _appDidEnterBackgroundEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<VulkanSimplified::AppWillEnterForegroundEventFunction, void*>> SdlEventHandlerInternal::RegisterAppWillEnterForegroundWarningEventCallback(VulkanSimplified::AppWillEnterForegroundEventFunction function, void* data, size_t add)
	{
		return _appWillEnterForegroundEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<VulkanSimplified::AppDidEnterForegroundEventFunction, void*>> SdlEventHandlerInternal::RegisterAppDidEnterForegroundEventCallback(VulkanSimplified::AppDidEnterForegroundEventFunction function, void* data, size_t add)
	{
		return _appDidEnterForegroundEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<VulkanSimplified::LocaleChangedEventFunction, void*>> SdlEventHandlerInternal::RegisterLocaleChangingEventCallback(VulkanSimplified::LocaleChangedEventFunction function, void* data, size_t add)
	{
		return _localeChangedEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<VulkanSimplified::DisplayEventFunction, void*>> SdlEventHandlerInternal::RegisterDisplayEventCallback(VulkanSimplified::DisplayEventFunction function, void* data, size_t add)
	{
		return _displayEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<VulkanSimplified::WindowEventFunction, void*>> SdlEventHandlerInternal::RegisterWindowEventCallback(VulkanSimplified::WindowEventFunction function, void* data, size_t add)
	{
		return _windowEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<VulkanSimplified::KeyboardEventFunction, void*>> SdlEventHandlerInternal::RegisterKeyboardEventCallback(VulkanSimplified::KeyboardEventFunction function, void* data, size_t add)
	{
		return _keyboardEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<VulkanSimplified::KeymapChangeEventFunction, void*>> SdlEventHandlerInternal::RegisterKeymapChangingEventCallback(VulkanSimplified::KeymapChangeEventFunction function, void* data, size_t add)
	{
		return _keymapChangedEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<VulkanSimplified::TextEditingEventFunction, void*>> SdlEventHandlerInternal::RegisterTextEditingEventCallback(VulkanSimplified::TextEditingEventFunction function, void* data, size_t add)
	{
		return _textEditingEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<VulkanSimplified::TextEditingExtendedEventFunction, void*>> SdlEventHandlerInternal::RegisterTextEditingExtendedEventCallback(VulkanSimplified::TextEditingExtendedEventFunction function, void* data, size_t add)
	{
		return _textEditingExtendedEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<VulkanSimplified::TextInputEventFunction, void*>> SdlEventHandlerInternal::RegisterTextInputEventCallback(VulkanSimplified::TextInputEventFunction function, void* data, size_t add)
	{
		return _textInputEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<VulkanSimplified::MouseMotionEventFunction, void*>> SdlEventHandlerInternal::RegisterMouseMotionEventCallback(VulkanSimplified::MouseMotionEventFunction function, void* data, size_t add)
	{
		return _mouseMotionEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<VulkanSimplified::MouseButtonEventFunction, void*>> SdlEventHandlerInternal::RegisterMouseButtonEventCallback(VulkanSimplified::MouseButtonEventFunction function, void* data, size_t add)
	{
		return _mouseButtonEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<VulkanSimplified::MouseWheelEventFunction, void*>> SdlEventHandlerInternal::RegisterMouseWheelEventCallback(VulkanSimplified::MouseWheelEventFunction function, void* data, size_t add)
	{
		return _mouseWheelEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<VulkanSimplified::JoyAxisEventFunction, void*>> SdlEventHandlerInternal::RegisterJoystickAxisEventCallback(VulkanSimplified::JoyAxisEventFunction function, void* data, size_t add)
	{
		return _joyAxisEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<VulkanSimplified::JoyBallEventFunction, void*>> SdlEventHandlerInternal::RegisterJoystickBallEventCallback(VulkanSimplified::JoyBallEventFunction function, void* data, size_t add)
	{
		return _joyBallEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<VulkanSimplified::JoyHatEventFunction, void*>> SdlEventHandlerInternal::RegisterJoystickHatEventCallback(VulkanSimplified::JoyHatEventFunction function, void* data, size_t add)
	{
		return _joyHatEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<VulkanSimplified::JoyButtonEventFunction, void*>> SdlEventHandlerInternal::RegisterJoystickButtonEventCallback(VulkanSimplified::JoyButtonEventFunction function, void* data, size_t add)
	{
		return _joyButtonEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<VulkanSimplified::JoyDeviceEventFunction, void*>> SdlEventHandlerInternal::RegisterJoystickDeviceEventCallback(VulkanSimplified::JoyDeviceEventFunction function, void* data, size_t add)
	{
		return _joyDeviceEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<VulkanSimplified::JoyBatteryEventFunction, void*>> SdlEventHandlerInternal::RegisterJoystickBatteryEventCallback(VulkanSimplified::JoyBatteryEventFunction function, void* data, size_t add)
	{
		return _joyBatteryEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<VulkanSimplified::ControllerAxisEventFunction, void*>> SdlEventHandlerInternal::RegisterControllerAxisEventCallback(VulkanSimplified::ControllerAxisEventFunction function, void* data, size_t add)
	{
		return _controllerAxisEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<VulkanSimplified::ControllerButtonEventFunction, void*>> SdlEventHandlerInternal::RegisterControllerButtonEventCallback(VulkanSimplified::ControllerButtonEventFunction function, void* data, size_t add)
	{
		return _controllerButtonEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<VulkanSimplified::ControllerDeviceEventFunction, void*>> SdlEventHandlerInternal::RegisterControllerDeviceEventCallback(VulkanSimplified::ControllerDeviceEventFunction function, void* data, size_t add)
	{
		return _controllerDeviceEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<VulkanSimplified::ControllerTouchpadEventFunction, void*>> SdlEventHandlerInternal::RegisterControllerTouchpadEventCallback(VulkanSimplified::ControllerTouchpadEventFunction function, void* data, size_t add)
	{
		return _controllerTouchpadEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<VulkanSimplified::ControllerSensorEventFunction, void*>> SdlEventHandlerInternal::RegisterControllerSensorEventCallback(VulkanSimplified::ControllerSensorEventFunction function, void* data, size_t add)
	{
		return _controllerSensorEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<VulkanSimplified::AudioDeviceEventFunction, void*>> SdlEventHandlerInternal::RegisterAudioDeviceEventCallback(VulkanSimplified::AudioDeviceEventFunction function, void* data, size_t add)
	{
		return _audioDeviceEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<VulkanSimplified::TouchFingerEventFunction, void*>> SdlEventHandlerInternal::RegisterTouchFingerEventCallback(VulkanSimplified::TouchFingerEventFunction function, void* data, size_t add)
	{
		return _touchFingerEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<VulkanSimplified::MultiGestureEventFunction, void*>> SdlEventHandlerInternal::RegisterMultiGestureEventCallback(VulkanSimplified::MultiGestureEventFunction function, void* data, size_t add)
	{
		return _multiGestureEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<VulkanSimplified::DollarGestureEventFunction, void*>> SdlEventHandlerInternal::RegisterDollarGestureEventCallback(VulkanSimplified::DollarGestureEventFunction function, void* data, size_t add)
	{
		return _dollarGestureEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<VulkanSimplified::ClipboardEventFunction, void*>> SdlEventHandlerInternal::RegisterClipboardEventCallback(VulkanSimplified::ClipboardEventFunction function, void* data, size_t add)
	{
		return _clipboardEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<VulkanSimplified::DropEventFunction, void*>> SdlEventHandlerInternal::RegisterDropEventCallback(VulkanSimplified::DropEventFunction function, void* data, size_t add)
	{
		return _dropEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<VulkanSimplified::SensorEventFunction, void*>> SdlEventHandlerInternal::RegisterSensorEventCallback(VulkanSimplified::SensorEventFunction function, void* data, size_t add)
	{
		return _sensorEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<VulkanSimplified::UserEventFunction, void*>> SdlEventHandlerInternal::RegisterUserEventCallback(VulkanSimplified::UserEventFunction function, void* data, size_t add)
	{
		return _userEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<VulkanSimplified::RenderTargetsResetEventFunction, void*>> SdlEventHandlerInternal::RegisterRenderTargetsResetEventCallback(VulkanSimplified::RenderTargetsResetEventFunction function, void* data, size_t add)
	{
		return _renderTargetsResetEventFunctions.AddObject(std::pair(function, data), add);
	}

	IDObject<std::pair<VulkanSimplified::RenderDeviceResetEventFunction, void*>> SdlEventHandlerInternal::RegisterRenderDeviceResetEventCallback(VulkanSimplified::RenderDeviceResetEventFunction function, void* data, size_t add)
	{
		return _renderDeviceResetEventFunctions.AddObject(std::pair(function, data), add);
	}

	bool SdlEventHandlerInternal::UnRegisterQuitEventCallback(IDObject<std::pair<VulkanSimplified::QuitEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _quitEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterAppTerminatingEventCallback(IDObject<std::pair<VulkanSimplified::AppTerminatingEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _appTerminatingEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterAppLowMemoryEventCallback(IDObject<std::pair<VulkanSimplified::AppLowMemoryEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _appLowMemoryEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterAppWillEnterBackgroundEventCallback(IDObject<std::pair<VulkanSimplified::AppWillEnterBackgroundEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _appWillEnterBackgroundEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterAppDidEnterBackgroundEventCallback(IDObject<std::pair<VulkanSimplified::AppDidEnterBackgroundEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _appDidEnterBackgroundEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterAppWillEnterForegroundEventCallback(IDObject<std::pair<VulkanSimplified::AppWillEnterForegroundEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _appWillEnterForegroundEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterAppDidEnterForegroundEventCallback(IDObject<std::pair<VulkanSimplified::AppDidEnterForegroundEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _appDidEnterForegroundEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterLocaleChangedEventCallback(IDObject<std::pair<VulkanSimplified::LocaleChangedEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _localeChangedEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterDisplayEventCallback(IDObject<std::pair<VulkanSimplified::DisplayEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _displayEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterWindowEventCallback(IDObject<std::pair<VulkanSimplified::WindowEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _windowEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterKeyboardEventCallback(IDObject<std::pair<VulkanSimplified::KeyboardEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _keyboardEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterKeymapChangeEventCallback(IDObject<std::pair<VulkanSimplified::KeymapChangeEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _keymapChangedEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterTextEditingEventCallback(IDObject<std::pair<VulkanSimplified::TextEditingEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _textEditingEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterTextEditingExtendedEventCallback(IDObject<std::pair<VulkanSimplified::TextEditingExtendedEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _textEditingExtendedEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterTextInputEventCallback(IDObject<std::pair<VulkanSimplified::TextInputEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _textInputEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterMouseMotionEventCallback(IDObject<std::pair<VulkanSimplified::MouseMotionEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _mouseMotionEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterMouseButtonEventCallback(IDObject<std::pair<VulkanSimplified::MouseButtonEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _mouseButtonEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterMouseWheelEventCallback(IDObject<std::pair<VulkanSimplified::MouseWheelEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _mouseWheelEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterJoyAxisEventCallback(IDObject<std::pair<VulkanSimplified::JoyAxisEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _joyAxisEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterJoyBallEventCallback(IDObject<std::pair<VulkanSimplified::JoyBallEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _joyBallEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterJoyHatEventCallback(IDObject<std::pair<VulkanSimplified::JoyHatEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _joyHatEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterJoyButtonEventCallback(IDObject<std::pair<VulkanSimplified::JoyButtonEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _joyButtonEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterJoyDeviceEventCallback(IDObject<std::pair<VulkanSimplified::JoyDeviceEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _joyDeviceEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterJoyBatteryEventCallback(IDObject<std::pair<VulkanSimplified::JoyBatteryEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _joyBatteryEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterControllerAxisEventCallback(IDObject<std::pair<VulkanSimplified::ControllerAxisEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _controllerAxisEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterControllerButtonEventCallback(IDObject<std::pair<VulkanSimplified::ControllerButtonEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _controllerButtonEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterControllerDeviceEventCallback(IDObject<std::pair<VulkanSimplified::ControllerDeviceEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _controllerDeviceEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterControllerTouchpadEventCallback(IDObject<std::pair<VulkanSimplified::ControllerTouchpadEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _controllerTouchpadEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterControllerSensorEventCallback(IDObject<std::pair<VulkanSimplified::ControllerSensorEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _controllerSensorEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterAudioDeviceEventCallback(IDObject<std::pair<VulkanSimplified::AudioDeviceEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _audioDeviceEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterTouchFingerEventCallback(IDObject<std::pair<VulkanSimplified::TouchFingerEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _touchFingerEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterMultiGestureEventCallback(IDObject<std::pair<VulkanSimplified::MultiGestureEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _multiGestureEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterDollarGestureEventCallback(IDObject<std::pair<VulkanSimplified::DollarGestureEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _dollarGestureEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterClipboardEventCallback(IDObject<std::pair<VulkanSimplified::ClipboardEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _clipboardEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterDropEventCallback(IDObject<std::pair<VulkanSimplified::DropEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _dropEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterSensorEventCallback(IDObject<std::pair<VulkanSimplified::SensorEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _sensorEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterUserEventCallback(IDObject<std::pair<VulkanSimplified::UserEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _userEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterRenderTargetsResetEventCallback(IDObject<std::pair<VulkanSimplified::RenderTargetsResetEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _renderTargetsResetEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	bool SdlEventHandlerInternal::UnRegisterRenderDeviceResetEventCallback(IDObject<std::pair<VulkanSimplified::RenderDeviceResetEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _renderDeviceResetEventFunctions.RemoveObject(ID, throwOnIDNotFound);
	}

	void SdlEventHandlerInternal::HandleEvent(SDL_Event& event)
	{
		auto& type = event.type;

		switch (type)
		{
		case SDL_FIRSTEVENT:
			break;
		case SDL_QUIT:
			HandleEvent(VulkanSimplified::SdlQuitEventData(event.quit));
			break;
		case SDL_APP_TERMINATING:
			HandleEvent(VulkanSimplified::SdlAppTerminatingEventData(event.common));
			break;
		case SDL_APP_LOWMEMORY:
			HandleEvent(VulkanSimplified::SdlAppLowMemoryEventData(event.common));
			break;
		case SDL_APP_WILLENTERBACKGROUND:
			HandleEvent(VulkanSimplified::SdlAppWillEnterBackgroundEventData(event.common));
			break;
		case SDL_APP_DIDENTERBACKGROUND:
			HandleEvent(VulkanSimplified::SdlAppDidEnterBackgroundEventData(event.common));
			break;
		case SDL_APP_WILLENTERFOREGROUND:
			HandleEvent(VulkanSimplified::SdlAppWillEnterForegroundEventData(event.common));
			break;
		case SDL_APP_DIDENTERFOREGROUND:
			HandleEvent(VulkanSimplified::SdlAppDidEnterForegroundEventData(event.common));
			break;
		case SDL_LOCALECHANGED:
			HandleEvent(VulkanSimplified::SdlLocaleChangeEventData(event.common));
			break;
		case SDL_DISPLAYEVENT:
			HandleEvent(event.display);
			break;
		case SDL_WINDOWEVENT:
			HandleEvent(event.window);
			break;
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			HandleEvent(event.key);
			break;
		case SDL_TEXTEDITING:
			HandleEvent(event.edit);
			break;
		case SDL_TEXTINPUT:
			HandleEvent(event.text);
			break;
		case SDL_KEYMAPCHANGED:
			HandleEvent(VulkanSimplified::SdlKeymapChangedEventData(event.common));
			break;
		case SDL_TEXTEDITING_EXT:
			HandleEvent(event.editExt);
			break;
		case SDL_MOUSEMOTION:
			HandleEvent(event.motion);
			break;
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			HandleEvent(event.button);
			break;
		case SDL_MOUSEWHEEL:
			HandleEvent(event.wheel);
			break;
		case SDL_JOYAXISMOTION:
			HandleEvent(event.jaxis);
			break;
		case SDL_JOYBALLMOTION:
			HandleEvent(event.jball);
			break;
		case SDL_JOYHATMOTION:
			HandleEvent(event.jhat);
			break;
		case SDL_JOYBUTTONDOWN:
		case SDL_JOYBUTTONUP:
			HandleEvent(event.jbutton);
			break;
		case SDL_JOYDEVICEADDED:
		case SDL_JOYDEVICEREMOVED:
			HandleEvent(event.jdevice);
			break;
		case SDL_JOYBATTERYUPDATED:
			HandleEvent(event.jbattery);
			break;
		case SDL_CONTROLLERAXISMOTION:
			HandleEvent(event.caxis);
			break;
		case SDL_CONTROLLERBUTTONDOWN:
		case SDL_CONTROLLERBUTTONUP:
			HandleEvent(event.cbutton);
			break;
		case SDL_CONTROLLERDEVICEADDED:
		case SDL_CONTROLLERDEVICEREMOVED:
		case SDL_CONTROLLERDEVICEREMAPPED:
			HandleEvent(event.cdevice);
			break;
		case SDL_CONTROLLERTOUCHPADDOWN:
		case SDL_CONTROLLERTOUCHPADMOTION:
		case SDL_CONTROLLERTOUCHPADUP:
			HandleEvent(event.ctouchpad);
			break;
		case SDL_CONTROLLERSENSORUPDATE:
			HandleEvent(event.csensor);
			break;
		case SDL_FINGERDOWN:
		case SDL_FINGERUP:
		case SDL_FINGERMOTION:
			HandleEvent(event.tfinger);
			break;
		case SDL_DOLLARGESTURE:
		case SDL_DOLLARRECORD:
			HandleEvent(event.dgesture);
			break;
		case SDL_MULTIGESTURE:
			HandleEvent(event.mgesture);
			break;
		case SDL_CLIPBOARDUPDATE:
			HandleEvent(VulkanSimplified::SdlClipboardEventData(event.common));
			break;
		case SDL_DROPFILE:
		case SDL_DROPTEXT:
		case SDL_DROPBEGIN:
		case SDL_DROPCOMPLETE:
			HandleEvent(event.drop);
			break;
		case SDL_AUDIODEVICEADDED:
		case SDL_AUDIODEVICEREMOVED:
			HandleEvent(event.adevice);
			break;
		case SDL_SENSORUPDATE:
			HandleEvent(event.sensor);
			break;
		case SDL_RENDER_TARGETS_RESET:
			HandleEvent(VulkanSimplified::SdlRenderTargetsResetEventData(event.common));
			break;
		case SDL_RENDER_DEVICE_RESET:
			HandleEvent(VulkanSimplified::SdlRenderDeviceResetEventData(event.common));
			break;
		case SDL_POLLSENTINEL:
			break;
		case SDL_USEREVENT:
			HandleEvent(event.user);
			break;
		case SDL_LASTEVENT:
			break;
		default:
			break;
		}
	}

	void SdlEventHandlerInternal::HandleEvent(VulkanSimplified::SdlQuitEventData event)
	{
		auto size = _quitEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _quitEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(event, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleEvent(VulkanSimplified::SdlAppTerminatingEventData event)
	{
		auto size = _appTerminatingEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _appTerminatingEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(event, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleEvent(VulkanSimplified::SdlAppLowMemoryEventData event)
	{
		auto size = _appLowMemoryEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _appLowMemoryEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(event, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleEvent(VulkanSimplified::SdlAppWillEnterBackgroundEventData event)
	{
		auto size = _appWillEnterBackgroundEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _appWillEnterBackgroundEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(event, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleEvent(VulkanSimplified::SdlAppDidEnterBackgroundEventData event)
	{
		auto size = _appDidEnterBackgroundEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _appDidEnterBackgroundEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(event, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleEvent(VulkanSimplified::SdlAppWillEnterForegroundEventData event)
	{
		auto size = _appWillEnterForegroundEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _appWillEnterForegroundEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(event, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleEvent(VulkanSimplified::SdlAppDidEnterForegroundEventData event)
	{
		auto size = _appDidEnterForegroundEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _appDidEnterForegroundEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(event, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleEvent(VulkanSimplified::SdlLocaleChangeEventData event)
	{
		auto size = _localeChangedEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _localeChangedEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(event, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleEvent(VulkanSimplified::SdlDisplayEventData event)
	{
		auto size = _displayEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _displayEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(event, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleEvent(VulkanSimplified::SdlWindowEventData event)
	{
		auto size = _windowEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _windowEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(event, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleEvent(VulkanSimplified::SdlKeyboardEventData event)
	{
		auto size = _keyboardEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _keyboardEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(event, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleEvent(VulkanSimplified::SdlKeymapChangedEventData event)
	{
		auto size = _keymapChangedEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _keymapChangedEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(event, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleEvent(VulkanSimplified::SdlTextEditingEventData event)
	{
		auto size = _textEditingEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _textEditingEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(event, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleEvent(VulkanSimplified::SdlTextEditingExtendedEventData event)
	{
		auto size = _textEditingExtendedEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _textEditingExtendedEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(event, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleEvent(VulkanSimplified::SdlTextInputEventData event)
	{
		auto size = _textInputEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _textInputEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(event, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleEvent(VulkanSimplified::SdlMouseMotionEventData event)
	{
		auto size = _mouseMotionEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _mouseMotionEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(event, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleEvent(VulkanSimplified::SdlMouseButtonEventData event)
	{
		auto size = _mouseButtonEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _mouseButtonEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(event, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleEvent(VulkanSimplified::SdlMouseWheelEventData event)
	{
		auto size = _mouseWheelEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _mouseWheelEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(event, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleEvent(VulkanSimplified::SdlJoyAxisEventData event)
	{
		auto size = _joyAxisEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _joyAxisEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(event, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleEvent(VulkanSimplified::SdlJoyBallEventData event)
	{
		auto size = _joyBallEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _joyBallEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(event, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleEvent(VulkanSimplified::SdlJoyHatEventData event)
	{
		auto size = _joyHatEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _joyHatEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(event, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleEvent(VulkanSimplified::SdlJoyButtonEventData event)
	{
		auto size = _joyButtonEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _joyButtonEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(event, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleEvent(VulkanSimplified::SdlJoyDeviceEventData event)
	{
		auto size = _joyDeviceEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _joyDeviceEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(event, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleEvent(VulkanSimplified::SdlJoyBatteryEventData event)
	{
		auto size = _joyBatteryEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _joyBatteryEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(event, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleEvent(VulkanSimplified::SdlControllerAxisEventData event)
	{
		auto size = _controllerAxisEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _controllerAxisEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(event, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleEvent(VulkanSimplified::SdlControllerButtonEventData event)
	{
		auto size = _controllerButtonEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _controllerButtonEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(event, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleEvent(VulkanSimplified::SdlControllerDeviceEventData event)
	{
		auto size = _controllerDeviceEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _controllerDeviceEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(event, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleEvent(VulkanSimplified::SdlControllerTouchpadEventData event)
	{
		auto size = _controllerTouchpadEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _controllerTouchpadEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(event, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleEvent(VulkanSimplified::SdlControllerSensorEventData event)
	{
		auto size = _controllerSensorEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _controllerSensorEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(event, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleEvent(VulkanSimplified::SdlAudioDeviceEventData event)
	{
		auto size = _audioDeviceEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _audioDeviceEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(event, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleEvent(VulkanSimplified::SdlTouchFingerEventData event)
	{
		auto size = _touchFingerEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _touchFingerEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(event, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleEvent(VulkanSimplified::SdlMultiGestureEventData event)
	{
		auto size = _multiGestureEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _multiGestureEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(event, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleEvent(VulkanSimplified::SdlDollarGestureEventData event)
	{
		auto size = _dollarGestureEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _dollarGestureEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(event, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleEvent(VulkanSimplified::SdlClipboardEventData event)
	{
		auto size = _clipboardEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _clipboardEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(event, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleEvent(VulkanSimplified::SdlDropEventData event)
	{
		auto size = _dropEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _dropEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(event, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleEvent(VulkanSimplified::SdlSensorEventData event)
	{
		auto size = _sensorEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _sensorEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(event, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleEvent(VulkanSimplified::SdlUserEventData event)
	{
		auto size = _userEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _userEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(event, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleEvent(VulkanSimplified::SdlRenderTargetsResetEventData event)
	{
		auto size = _renderTargetsResetEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _renderTargetsResetEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(event, functiondata.second);
		}
	}

	void SdlEventHandlerInternal::HandleEvent(VulkanSimplified::SdlRenderDeviceResetEventData event)
	{
		auto size = _renderDeviceResetEventFunctions.GetUsedSize();
		size_t current = 0;

		bool fallthrough = true;

		while (fallthrough)
		{
			if (current == size)
				break;

			auto& functiondata = _renderDeviceResetEventFunctions.GetConstObject(current++);

			fallthrough = functiondata.first(event, functiondata.second);
		}
	}
}
