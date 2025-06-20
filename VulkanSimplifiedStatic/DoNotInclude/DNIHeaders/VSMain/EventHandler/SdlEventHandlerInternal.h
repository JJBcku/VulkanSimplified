#pragma once

#include "CustomLists/OrderIndependentDeletionStack.h"

#include "../../../../Include/VSMain/EventHandler/SdlEventHandlerTypedefs.h"

#include <functional>
#include <utility>

union SDL_Event;

namespace VulkanSimplified
{
	class SdlEventHandlerInternal
	{
	public:
		SdlEventHandlerInternal(const SdlEventHandlerInitData& initData);
		~SdlEventHandlerInternal();

		SdlEventHandlerInternal(const SdlEventHandlerInternal&) noexcept = delete;
		SdlEventHandlerInternal(SdlEventHandlerInternal&&) noexcept = delete;

		SdlEventHandlerInternal& operator=(const SdlEventHandlerInternal&) noexcept = delete;
		SdlEventHandlerInternal& operator=(SdlEventHandlerInternal&&) noexcept = delete;

		void HandleEvents();

		IDObject<std::pair<QuitEventFunction, void*>> RegisterQuitEventCallback(QuitEventFunction function, void* data, size_t add);

		IDObject<std::pair<AppTerminatingEventFunction, void*>> RegisterAppTerminatingEventCallback(AppTerminatingEventFunction function, void* data, size_t add);
		IDObject<std::pair<AppLowMemoryEventFunction, void*>> RegisterAppLowMemoryWarningEventCallback(AppLowMemoryEventFunction function, void* data, size_t add);
		IDObject<std::pair<AppWillEnterBackgroundEventFunction, void*>> RegisterAppWillEnterBackgroundWarningEventCallback(AppWillEnterBackgroundEventFunction function, void* data, size_t add);
		IDObject<std::pair<AppDidEnterBackgroundEventFunction, void*>> RegisterAppDidEnterBackgroundEventCallback(AppDidEnterBackgroundEventFunction function, void* data, size_t add);
		IDObject<std::pair<AppWillEnterForegroundEventFunction, void*>> RegisterAppWillEnterForegroundWarningEventCallback(AppWillEnterForegroundEventFunction function, void* data, size_t add);
		IDObject<std::pair<AppDidEnterForegroundEventFunction, void*>> RegisterAppDidEnterForegroundEventCallback(AppDidEnterForegroundEventFunction function, void* data, size_t add);

		IDObject<std::pair<LocaleChangedEventFunction, void*>> RegisterLocaleChangingEventCallback(LocaleChangedEventFunction function, void* data, size_t add);

		IDObject<std::pair<DisplayEventFunction, void*>> RegisterDisplayEventCallback(DisplayEventFunction function, void* data, size_t add);
		IDObject<std::pair<WindowEventFunction, void*>> RegisterWindowEventCallback(WindowEventFunction function, void* data, size_t add);

		IDObject<std::pair<KeyboardEventFunction, void*>> RegisterKeyboardEventCallback(KeyboardEventFunction function, void* data, size_t add);
		IDObject<std::pair<KeymapChangeEventFunction, void*>> RegisterKeymapChangingEventCallback(KeymapChangeEventFunction function, void* data, size_t add);
		IDObject<std::pair<TextEditingEventFunction, void*>> RegisterTextEditingEventCallback(TextEditingEventFunction function, void* data, size_t add);
		IDObject<std::pair<TextEditingExtendedEventFunction, void*>> RegisterTextEditingExtendedEventCallback(TextEditingExtendedEventFunction function, void* data, size_t add);
		IDObject<std::pair<TextInputEventFunction, void*>> RegisterTextInputEventCallback(TextInputEventFunction function, void* data, size_t add);

		IDObject<std::pair<MouseMotionEventFunction, void*>> RegisterMouseMotionEventCallback(MouseMotionEventFunction function, void* data, size_t add);
		IDObject<std::pair<MouseButtonEventFunction, void*>> RegisterMouseButtonEventCallback(MouseButtonEventFunction function, void* data, size_t add);
		IDObject<std::pair<MouseWheelEventFunction, void*>> RegisterMouseWheelEventCallback(MouseWheelEventFunction function, void* data, size_t add);

		IDObject<std::pair<JoyAxisEventFunction, void*>> RegisterJoystickAxisEventCallback(JoyAxisEventFunction function, void* data, size_t add);
		IDObject<std::pair<JoyBallEventFunction, void*>> RegisterJoystickBallEventCallback(JoyBallEventFunction function, void* data, size_t add);
		IDObject<std::pair<JoyHatEventFunction, void*>> RegisterJoystickHatEventCallback(JoyHatEventFunction function, void* data, size_t add);
		IDObject<std::pair<JoyButtonEventFunction, void*>> RegisterJoystickButtonEventCallback(JoyButtonEventFunction function, void* data, size_t add);
		IDObject<std::pair<JoyDeviceEventFunction, void*>> RegisterJoystickDeviceEventCallback(JoyDeviceEventFunction function, void* data, size_t add);
		IDObject<std::pair<JoyBatteryEventFunction, void*>> RegisterJoystickBatteryEventCallback(JoyBatteryEventFunction function, void* data, size_t add);

		IDObject<std::pair<ControllerAxisEventFunction, void*>> RegisterControllerAxisEventCallback(ControllerAxisEventFunction function, void* data, size_t add);
		IDObject<std::pair<ControllerButtonEventFunction, void*>> RegisterControllerButtonEventCallback(ControllerButtonEventFunction function, void* data, size_t add);
		IDObject<std::pair<ControllerDeviceEventFunction, void*>> RegisterControllerDeviceEventCallback(ControllerDeviceEventFunction function, void* data, size_t add);
		IDObject<std::pair<ControllerTouchpadEventFunction, void*>> RegisterControllerTouchpadEventCallback(ControllerTouchpadEventFunction function, void* data, size_t add);
		IDObject<std::pair<ControllerSensorEventFunction, void*>> RegisterControllerSensorEventCallback(ControllerSensorEventFunction function, void* data, size_t add);

		IDObject<std::pair<AudioDeviceEventFunction, void*>> RegisterAudioDeviceEventCallback(AudioDeviceEventFunction function, void* data, size_t add);
		IDObject<std::pair<TouchFingerEventFunction, void*>> RegisterTouchFingerEventCallback(TouchFingerEventFunction function, void* data, size_t add);
		IDObject<std::pair<MultiGestureEventFunction, void*>> RegisterMultiGestureEventCallback(MultiGestureEventFunction function, void* data, size_t add);
		IDObject<std::pair<DollarGestureEventFunction, void*>> RegisterDollarGestureEventCallback(DollarGestureEventFunction function, void* data, size_t add);
		IDObject<std::pair<ClipboardEventFunction, void*>> RegisterClipboardEventCallback(ClipboardEventFunction function, void* data, size_t add);

		IDObject<std::pair<DropEventFunction, void*>> RegisterDropEventCallback(DropEventFunction function, void* data, size_t add);
		IDObject<std::pair<SensorEventFunction, void*>> RegisterSensorEventCallback(SensorEventFunction function, void* data, size_t add);
		IDObject<std::pair<UserEventFunction, void*>> RegisterUserEventCallback(UserEventFunction function, void* data, size_t add);

		IDObject<std::pair<RenderTargetsResetEventFunction, void*>> RegisterRenderTargetsResetEventCallback(RenderTargetsResetEventFunction function, void* data, size_t add);
		IDObject<std::pair<RenderDeviceResetEventFunction, void*>> RegisterRenderDeviceResetEventCallback(RenderDeviceResetEventFunction function, void* data, size_t add);

		bool UnRegisterQuitEventCallback(IDObject<std::pair<QuitEventFunction, void*>> ID, bool throwOnIDNotFound);

		bool UnRegisterAppTerminatingEventCallback(IDObject<std::pair<AppTerminatingEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterAppLowMemoryEventCallback(IDObject<std::pair<AppLowMemoryEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterAppWillEnterBackgroundEventCallback(IDObject<std::pair<AppWillEnterBackgroundEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterAppDidEnterBackgroundEventCallback(IDObject<std::pair<AppDidEnterBackgroundEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterAppWillEnterForegroundEventCallback(IDObject<std::pair<AppWillEnterForegroundEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterAppDidEnterForegroundEventCallback(IDObject<std::pair<AppDidEnterForegroundEventFunction, void*>> ID, bool throwOnIDNotFound);

		bool UnRegisterLocaleChangedEventCallback(IDObject<std::pair<LocaleChangedEventFunction, void*>> ID, bool throwOnIDNotFound);

		bool UnRegisterDisplayEventCallback(IDObject<std::pair<DisplayEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterWindowEventCallback(IDObject<std::pair<WindowEventFunction, void*>> ID, bool throwOnIDNotFound);

		bool UnRegisterKeyboardEventCallback(IDObject<std::pair<KeyboardEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterKeymapChangeEventCallback(IDObject<std::pair<KeymapChangeEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterTextEditingEventCallback(IDObject<std::pair<TextEditingEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterTextEditingExtendedEventCallback(IDObject<std::pair<TextEditingExtendedEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterTextInputEventCallback(IDObject<std::pair<TextInputEventFunction, void*>> ID, bool throwOnIDNotFound);

		bool UnRegisterMouseMotionEventCallback(IDObject<std::pair<MouseMotionEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterMouseButtonEventCallback(IDObject<std::pair<MouseButtonEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterMouseWheelEventCallback(IDObject<std::pair<MouseWheelEventFunction, void*>> ID, bool throwOnIDNotFound);

		bool UnRegisterJoyAxisEventCallback(IDObject<std::pair<JoyAxisEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterJoyBallEventCallback(IDObject<std::pair<JoyBallEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterJoyHatEventCallback(IDObject<std::pair<JoyHatEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterJoyButtonEventCallback(IDObject<std::pair<JoyButtonEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterJoyDeviceEventCallback(IDObject<std::pair<JoyDeviceEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterJoyBatteryEventCallback(IDObject<std::pair<JoyBatteryEventFunction, void*>> ID, bool throwOnIDNotFound);

		bool UnRegisterControllerAxisEventCallback(IDObject<std::pair<ControllerAxisEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterControllerButtonEventCallback(IDObject<std::pair<ControllerButtonEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterControllerDeviceEventCallback(IDObject<std::pair<ControllerDeviceEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterControllerTouchpadEventCallback(IDObject<std::pair<ControllerTouchpadEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterControllerSensorEventCallback(IDObject<std::pair<ControllerSensorEventFunction, void*>> ID, bool throwOnIDNotFound);

		bool UnRegisterAudioDeviceEventCallback(IDObject<std::pair<AudioDeviceEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterTouchFingerEventCallback(IDObject<std::pair<TouchFingerEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterMultiGestureEventCallback(IDObject<std::pair<MultiGestureEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterDollarGestureEventCallback(IDObject<std::pair<DollarGestureEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterClipboardEventCallback(IDObject<std::pair<ClipboardEventFunction, void*>> ID, bool throwOnIDNotFound);

		bool UnRegisterDropEventCallback(IDObject<std::pair<DropEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterSensorEventCallback(IDObject<std::pair<SensorEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterUserEventCallback(IDObject<std::pair<UserEventFunction, void*>> ID, bool throwOnIDNotFound);

		bool UnRegisterRenderTargetsResetEventCallback(IDObject<std::pair<RenderTargetsResetEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterRenderDeviceResetEventCallback(IDObject<std::pair<RenderDeviceResetEventFunction, void*>> ID, bool throwOnIDNotFound);

	private:
		OrderIndependentDeletionStack<std::pair<QuitEventFunction, void*>> _quitEventFunctions;

		OrderIndependentDeletionStack<std::pair<AppTerminatingEventFunction, void*>> _appTerminatingEventFunctions;
		OrderIndependentDeletionStack<std::pair<AppLowMemoryEventFunction, void*>> _appLowMemoryEventFunctions;
		OrderIndependentDeletionStack<std::pair<AppWillEnterBackgroundEventFunction, void*>> _appWillEnterBackgroundEventFunctions;
		OrderIndependentDeletionStack<std::pair<AppDidEnterBackgroundEventFunction, void*>> _appDidEnterBackgroundEventFunctions;
		OrderIndependentDeletionStack<std::pair<AppWillEnterForegroundEventFunction, void*>> _appWillEnterForegroundEventFunctions;
		OrderIndependentDeletionStack<std::pair<AppDidEnterForegroundEventFunction, void*>> _appDidEnterForegroundEventFunctions;

		OrderIndependentDeletionStack<std::pair<LocaleChangedEventFunction, void*>> _localeChangedEventFunctions;

		OrderIndependentDeletionStack<std::pair<DisplayEventFunction, void*>> _displayEventFunctions;
		OrderIndependentDeletionStack<std::pair<WindowEventFunction, void*>> _windowEventFunctions;

		OrderIndependentDeletionStack<std::pair<KeyboardEventFunction, void*>> _keyboardEventFunctions;
		OrderIndependentDeletionStack<std::pair<KeymapChangeEventFunction, void*>> _keymapChangedEventFunctions;
		OrderIndependentDeletionStack<std::pair<TextEditingEventFunction, void*>> _textEditingEventFunctions;
		OrderIndependentDeletionStack<std::pair<TextEditingExtendedEventFunction, void*>> _textEditingExtendedEventFunctions;
		OrderIndependentDeletionStack<std::pair<TextInputEventFunction, void*>> _textInputEventFunctions;

		OrderIndependentDeletionStack<std::pair<MouseMotionEventFunction, void*>> _mouseMotionEventFunctions;
		OrderIndependentDeletionStack<std::pair<MouseButtonEventFunction, void*>> _mouseButtonEventFunctions;
		OrderIndependentDeletionStack<std::pair<MouseWheelEventFunction, void*>> _mouseWheelEventFunctions;

		OrderIndependentDeletionStack<std::pair<JoyAxisEventFunction, void*>> _joyAxisEventFunctions;
		OrderIndependentDeletionStack<std::pair<JoyBallEventFunction, void*>> _joyBallEventFunctions;
		OrderIndependentDeletionStack<std::pair<JoyHatEventFunction, void*>> _joyHatEventFunctions;
		OrderIndependentDeletionStack<std::pair<JoyButtonEventFunction, void*>> _joyButtonEventFunctions;
		OrderIndependentDeletionStack<std::pair<JoyDeviceEventFunction, void*>> _joyDeviceEventFunctions;
		OrderIndependentDeletionStack<std::pair<JoyBatteryEventFunction, void*>> _joyBatteryEventFunctions;

		OrderIndependentDeletionStack<std::pair<ControllerAxisEventFunction, void*>> _controllerAxisEventFunctions;
		OrderIndependentDeletionStack<std::pair<ControllerButtonEventFunction, void*>> _controllerButtonEventFunctions;
		OrderIndependentDeletionStack<std::pair<ControllerDeviceEventFunction, void*>> _controllerDeviceEventFunctions;
		OrderIndependentDeletionStack<std::pair<ControllerTouchpadEventFunction, void*>> _controllerTouchpadEventFunctions;
		OrderIndependentDeletionStack<std::pair<ControllerSensorEventFunction, void*>> _controllerSensorEventFunctions;

		OrderIndependentDeletionStack<std::pair<AudioDeviceEventFunction, void*>> _audioDeviceEventFunctions;
		OrderIndependentDeletionStack<std::pair<TouchFingerEventFunction, void*>> _touchFingerEventFunctions;
		OrderIndependentDeletionStack<std::pair<MultiGestureEventFunction, void*>> _multiGestureEventFunctions;
		OrderIndependentDeletionStack<std::pair<DollarGestureEventFunction, void*>> _dollarGestureEventFunctions;
		OrderIndependentDeletionStack<std::pair<ClipboardEventFunction, void*>> _clipboardEventFunctions;

		OrderIndependentDeletionStack<std::pair<DropEventFunction, void*>> _dropEventFunctions;
		OrderIndependentDeletionStack<std::pair<SensorEventFunction, void*>> _sensorEventFunctions;
		OrderIndependentDeletionStack<std::pair<UserEventFunction, void*>> _userEventFunctions;

		OrderIndependentDeletionStack<std::pair<RenderTargetsResetEventFunction, void*>> _renderTargetsResetEventFunctions;
		OrderIndependentDeletionStack<std::pair<RenderDeviceResetEventFunction, void*>> _renderDeviceResetEventFunctions;

		void HandleEvent(const SDL_Event& event);

		void HandleQuitEvent(const SDL_Event& event);

		void HandleAppTerminatingEvent(const SDL_Event& event);
		void HandleAppLowMemoryEvent(const SDL_Event& event);
		void HandleAppWillEnterBackgroundEvent(const SDL_Event& event);
		void HandleAppDidEnterBackgroundEvent(const SDL_Event& event);
		void HandleAppWillEnterForegroundEvent(const SDL_Event& event);
		void HandleAppDidEnterForegroundEvent(const SDL_Event& event);

		void HandleLocaleChangeEvent(const SDL_Event& event);

		void HandleDisplayEvent(const SDL_Event& event);
		void HandleWindowEvent(const SDL_Event& event);

		void HandleKeyboardEvent(const SDL_Event& event);
		void HandleKeymapChangedEvent(const SDL_Event& event);
		void HandleTextEditingEvent(const SDL_Event& event);
		void HandleTextEditingExtendedEvent(const SDL_Event& event);
		void HandleTextInputEvent(const SDL_Event& event);

		void HandleMouseMotionEvent(const SDL_Event& event);
		void HandleMouseButtonEvent(const SDL_Event& event);
		void HandleMouseWheelEvent(const SDL_Event& event);

		void HandleJoyAxisEvent(const SDL_Event& event);
		void HandleJoyBallEvent(const SDL_Event& event);
		void HandleJoyHatEvent(const SDL_Event& event);
		void HandleJoyButtonEvent(const SDL_Event& event);
		void HandleJoyDeviceEvent(const SDL_Event& event);
		void HandleJoyBatteryEvent(const SDL_Event& event);

		void HandleControllerAxisEvent(const SDL_Event& event);
		void HandleControllerButtonEvent(const SDL_Event& event);
		void HandleControllerDeviceEvent(const SDL_Event& event);
		void HandleControllerTouchpadEvent(const SDL_Event& event);
		void HandleControllerSensorEvent(const SDL_Event& event);

		void HandleAudioDeviceEvent(const SDL_Event& event);
		void HandleTouchFingerEvent(const SDL_Event& event);
		void HandleMultiGestureEvent(const SDL_Event& event);
		void HandleDollarGestureEvent(const SDL_Event& event);
		void HandleClipboardEvent(const SDL_Event& event);

		void HandleDropEvent(const SDL_Event& event);
		void HandleSensorEvent(const SDL_Event& event);
		void HandleUserEvent(const SDL_Event& event);

		void HandleRenderTargetsResetEvent(const SDL_Event& event);
		void HandleRenderDeviceResetEvent(const SDL_Event& event);
	};
}