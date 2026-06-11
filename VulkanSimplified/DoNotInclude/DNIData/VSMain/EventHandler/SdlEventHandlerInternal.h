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
		IDObject<std::pair<SystemThemeChangeEventFunction, void*>> RegisterSystemThemeChangeEventCallback(SystemThemeChangeEventFunction function, void* data, size_t add);

		IDObject<std::pair<DisplayEventFunction, void*>> RegisterDisplayEventCallback(DisplayEventFunction function, void* data, size_t add);
		IDObject<std::pair<WindowEventFunction, void*>> RegisterWindowEventCallback(WindowEventFunction function, void* data, size_t add);

		IDObject<std::pair<KeyboardEventFunction, void*>> RegisterKeyboardEventCallback(KeyboardEventFunction function, void* data, size_t add);
		IDObject<std::pair<TextEditingEventFunction, void*>> RegisterTextEditingEventCallback(TextEditingEventFunction function, void* data, size_t add);
		IDObject<std::pair<TextInputEventFunction, void*>> RegisterTextInputEventCallback(TextInputEventFunction function, void* data, size_t add);
		IDObject<std::pair<KeymapChangeEventFunction, void*>> RegisterKeymapChangingEventCallback(KeymapChangeEventFunction function, void* data, size_t add);

		IDObject<std::pair<KeyboardDeviceEventFunction, void*>> RegisterKeyboardDeviceEventCallback(KeyboardDeviceEventFunction function, void* data, size_t add);
		IDObject<std::pair<TextEditingCandidatesEventFunction, void*>> RegisterTextCandidatesEditingEventCallback(TextEditingCandidatesEventFunction function, void* data, size_t add);
		IDObject<std::pair<ScreenKeyboardEventFunction, void*>> RegisterScreenKeyboardEventCallback(ScreenKeyboardEventFunction function, void* data, size_t add);

		IDObject<std::pair<MouseMotionEventFunction, void*>> RegisterMouseMotionEventCallback(MouseMotionEventFunction function, void* data, size_t add);
		IDObject<std::pair<MouseButtonEventFunction, void*>> RegisterMouseButtonEventCallback(MouseButtonEventFunction function, void* data, size_t add);
		IDObject<std::pair<MouseWheelEventFunction, void*>> RegisterMouseWheelEventCallback(MouseWheelEventFunction function, void* data, size_t add);
		IDObject<std::pair<MouseDeviceEventFunction, void*>> RegisterMouseDeviceEventCallback(MouseDeviceEventFunction function, void* data, size_t add);

		IDObject<std::pair<JoyAxisEventFunction, void*>> RegisterJoystickAxisEventCallback(JoyAxisEventFunction function, void* data, size_t add);
		IDObject<std::pair<JoyBallEventFunction, void*>> RegisterJoystickBallEventCallback(JoyBallEventFunction function, void* data, size_t add);
		IDObject<std::pair<JoyHatEventFunction, void*>> RegisterJoystickHatEventCallback(JoyHatEventFunction function, void* data, size_t add);
		IDObject<std::pair<JoyButtonEventFunction, void*>> RegisterJoystickButtonEventCallback(JoyButtonEventFunction function, void* data, size_t add);
		IDObject<std::pair<JoyDeviceEventFunction, void*>> RegisterJoystickDeviceEventCallback(JoyDeviceEventFunction function, void* data, size_t add);
		IDObject<std::pair<JoyBatteryEventFunction, void*>> RegisterJoystickBatteryEventCallback(JoyBatteryEventFunction function, void* data, size_t add);

		IDObject<std::pair<GamepadAxisEventFunction, void*>> RegisterGamepadAxisEventCallback(GamepadAxisEventFunction function, void* data, size_t add);
		IDObject<std::pair<GamepadButtonEventFunction, void*>> RegisterGamepadButtonEventCallback(GamepadButtonEventFunction function, void* data, size_t add);
		IDObject<std::pair<GamepadDeviceEventFunction, void*>> RegisterGamepadDeviceEventCallback(GamepadDeviceEventFunction function, void* data, size_t add);
		IDObject<std::pair<GamepadTouchpadEventFunction, void*>> RegisterGamepadTouchpadEventCallback(GamepadTouchpadEventFunction function, void* data, size_t add);
		IDObject<std::pair<GamepadSensorEventFunction, void*>> RegisterGamepadSensorEventCallback(GamepadSensorEventFunction function, void* data, size_t add);

		IDObject<std::pair<TouchFingerEventFunction, void*>> RegisterTouchFingerEventCallback(TouchFingerEventFunction function, void* data, size_t add);
		IDObject<std::pair<TouchPinchEventFunction, void*>> RegisterPinchFingerEventCallback(TouchPinchEventFunction function, void* data, size_t add);
		IDObject<std::pair<ClipboardEventFunction, void*>> RegisterClipboardEventCallback(ClipboardEventFunction function, void* data, size_t add);

		IDObject<std::pair<DropEventFunction, void*>> RegisterDropEventCallback(DropEventFunction function, void* data, size_t add);
		IDObject<std::pair<AudioDeviceEventFunction, void*>> RegisterAudioDeviceEventCallback(AudioDeviceEventFunction function, void* data, size_t add);
		IDObject<std::pair<SensorEventFunction, void*>> RegisterSensorEventCallback(SensorEventFunction function, void* data, size_t add);

		IDObject<std::pair<PenProximityEventFunction, void*>> RegisterPenProximityEventCallback(PenProximityEventFunction function, void* data, size_t add);
		IDObject<std::pair<PenTouchEventFunction, void*>> RegisterPenTouchEventCallback(PenTouchEventFunction function, void* data, size_t add);
		IDObject<std::pair<PenButtonEventFunction, void*>> RegisterPenButtonEventCallback(PenButtonEventFunction function, void* data, size_t add);
		IDObject<std::pair<PenMotionEventFunction, void*>> RegisterPenMotionEventCallback(PenMotionEventFunction function, void* data, size_t add);
		IDObject<std::pair<PenAxisEventFunction, void*>> RegisterPenAxisEventCallback(PenAxisEventFunction function, void* data, size_t add);

		IDObject<std::pair<CameraEventFunction, void*>> RegisterCameraEventCallback(CameraEventFunction function, void* data, size_t add);
		IDObject<std::pair<RenderTargetsResetEventFunction, void*>> RegisterRenderTargetsResetEventCallback(RenderTargetsResetEventFunction function, void* data, size_t add);
		IDObject<std::pair<RenderDeviceResetEventFunction, void*>> RegisterRenderDeviceResetEventCallback(RenderDeviceResetEventFunction function, void* data, size_t add);
		IDObject<std::pair<RenderDeviceLostEventFunction, void*>> RegisterRenderDeviceLostEventCallback(RenderDeviceLostEventFunction function, void* data, size_t add);

		IDObject<std::pair<UserEventFunction, void*>> RegisterUserEventCallback(UserEventFunction function, void* data, size_t add);

		bool UnRegisterQuitEventCallback(IDObject<std::pair<QuitEventFunction, void*>> ID, bool throwOnIDNotFound);

		bool UnRegisterAppTerminatingEventCallback(IDObject<std::pair<AppTerminatingEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterAppLowMemoryEventCallback(IDObject<std::pair<AppLowMemoryEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterAppWillEnterBackgroundEventCallback(IDObject<std::pair<AppWillEnterBackgroundEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterAppDidEnterBackgroundEventCallback(IDObject<std::pair<AppDidEnterBackgroundEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterAppWillEnterForegroundEventCallback(IDObject<std::pair<AppWillEnterForegroundEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterAppDidEnterForegroundEventCallback(IDObject<std::pair<AppDidEnterForegroundEventFunction, void*>> ID, bool throwOnIDNotFound);

		bool UnRegisterLocaleChangedEventCallback(IDObject<std::pair<LocaleChangedEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterSystemThemeChangeEventCallback(IDObject<std::pair<SystemThemeChangeEventFunction, void*>> ID, bool throwOnIDNotFound);

		bool UnRegisterDisplayEventCallback(IDObject<std::pair<DisplayEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterWindowEventCallback(IDObject<std::pair<WindowEventFunction, void*>> ID, bool throwOnIDNotFound);

		bool UnRegisterKeyboardEventCallback(IDObject<std::pair<KeyboardEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterTextEditingEventCallback(IDObject<std::pair<TextEditingEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterTextInputEventCallback(IDObject<std::pair<TextInputEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterKeymapChangeEventCallback(IDObject<std::pair<KeymapChangeEventFunction, void*>> ID, bool throwOnIDNotFound);

		bool UnRegisterKeyboardDeviceEventCallback(IDObject<std::pair<KeyboardDeviceEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterTextCandidatesEditingEventCallback(IDObject<std::pair<TextEditingCandidatesEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterScreenKeyboardEventCallback(IDObject<std::pair<ScreenKeyboardEventFunction, void*>> ID, bool throwOnIDNotFound);

		bool UnRegisterMouseMotionEventCallback(IDObject<std::pair<MouseMotionEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterMouseButtonEventCallback(IDObject<std::pair<MouseButtonEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterMouseWheelEventCallback(IDObject<std::pair<MouseWheelEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterMouseDeviceEventCallback(IDObject<std::pair<MouseDeviceEventFunction, void*>> ID, bool throwOnIDNotFound);

		bool UnRegisterJoyAxisEventCallback(IDObject<std::pair<JoyAxisEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterJoyBallEventCallback(IDObject<std::pair<JoyBallEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterJoyHatEventCallback(IDObject<std::pair<JoyHatEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterJoyButtonEventCallback(IDObject<std::pair<JoyButtonEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterJoyDeviceEventCallback(IDObject<std::pair<JoyDeviceEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterJoyBatteryEventCallback(IDObject<std::pair<JoyBatteryEventFunction, void*>> ID, bool throwOnIDNotFound);

		bool UnRegisterGamepadAxisEventCallback(IDObject<std::pair<GamepadAxisEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterGamepadButtonEventCallback(IDObject<std::pair<GamepadButtonEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterGamepadDeviceEventCallback(IDObject<std::pair<GamepadDeviceEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterGamepadTouchpadEventCallback(IDObject<std::pair<GamepadTouchpadEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterGamepadSensorEventCallback(IDObject<std::pair<GamepadSensorEventFunction, void*>> ID, bool throwOnIDNotFound);

		bool UnRegisterTouchFingerEventCallback(IDObject<std::pair<TouchFingerEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterTouchPinchEventCallback(IDObject<std::pair<TouchPinchEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterClipboardEventCallback(IDObject<std::pair<ClipboardEventFunction, void*>> ID, bool throwOnIDNotFound);

		bool UnRegisterDropEventCallback(IDObject<std::pair<DropEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterAudioDeviceEventCallback(IDObject<std::pair<AudioDeviceEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterSensorEventCallback(IDObject<std::pair<SensorEventFunction, void*>> ID, bool throwOnIDNotFound);

		bool UnRegisterPenProximityEventCallback(IDObject<std::pair<PenProximityEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterPenTouchEventCallback(IDObject<std::pair<PenTouchEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterPenButtonEventCallback(IDObject<std::pair<PenButtonEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterPenMotionEventCallback(IDObject<std::pair<PenMotionEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterPenAxisEventCallback(IDObject<std::pair<PenAxisEventFunction, void*>> ID, bool throwOnIDNotFound);
		
		bool UnRegisterCameraEventCallback(IDObject<std::pair<CameraEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterRenderTargetsResetEventCallback(IDObject<std::pair<RenderTargetsResetEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterRenderDeviceResetEventCallback(IDObject<std::pair<RenderDeviceResetEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterRenderDeviceLostEventCallback(IDObject<std::pair<RenderDeviceLostEventFunction, void*>> ID, bool throwOnIDNotFound);

		bool UnRegisterUserEventCallback(IDObject<std::pair<UserEventFunction, void*>> ID, bool throwOnIDNotFound);

	private:
		OrderIndependentDeletionStack<std::pair<QuitEventFunction, void*>> _quitEventFunctions;

		OrderIndependentDeletionStack<std::pair<AppTerminatingEventFunction, void*>> _appTerminatingEventFunctions;
		OrderIndependentDeletionStack<std::pair<AppLowMemoryEventFunction, void*>> _appLowMemoryEventFunctions;
		OrderIndependentDeletionStack<std::pair<AppWillEnterBackgroundEventFunction, void*>> _appWillEnterBackgroundEventFunctions;
		OrderIndependentDeletionStack<std::pair<AppDidEnterBackgroundEventFunction, void*>> _appDidEnterBackgroundEventFunctions;
		OrderIndependentDeletionStack<std::pair<AppWillEnterForegroundEventFunction, void*>> _appWillEnterForegroundEventFunctions;
		OrderIndependentDeletionStack<std::pair<AppDidEnterForegroundEventFunction, void*>> _appDidEnterForegroundEventFunctions;

		OrderIndependentDeletionStack<std::pair<LocaleChangedEventFunction, void*>> _localeChangedEventFunctions;
		OrderIndependentDeletionStack<std::pair<SystemThemeChangeEventFunction, void*>> _systemThemeChangeEventFunctions;

		OrderIndependentDeletionStack<std::pair<DisplayEventFunction, void*>> _displayEventFunctions;
		OrderIndependentDeletionStack<std::pair<WindowEventFunction, void*>> _windowEventFunctions;

		OrderIndependentDeletionStack<std::pair<KeyboardEventFunction, void*>> _keyboardEventFunctions;
		OrderIndependentDeletionStack<std::pair<TextEditingEventFunction, void*>> _textEditingEventFunctions;
		OrderIndependentDeletionStack<std::pair<TextInputEventFunction, void*>> _textInputEventFunctions;
		OrderIndependentDeletionStack<std::pair<KeymapChangeEventFunction, void*>> _keymapChangedEventFunctions;

		OrderIndependentDeletionStack<std::pair<KeyboardDeviceEventFunction, void*>> _keyboardDeviceEventFunctions;
		OrderIndependentDeletionStack<std::pair<TextEditingCandidatesEventFunction, void*>> _textEditingCandidatesEventFunctions;
		OrderIndependentDeletionStack<std::pair<ScreenKeyboardEventFunction, void*>> _screenKeyboardEventFunctions;

		OrderIndependentDeletionStack<std::pair<MouseMotionEventFunction, void*>> _mouseMotionEventFunctions;
		OrderIndependentDeletionStack<std::pair<MouseButtonEventFunction, void*>> _mouseButtonEventFunctions;
		OrderIndependentDeletionStack<std::pair<MouseWheelEventFunction, void*>> _mouseWheelEventFunctions;
		OrderIndependentDeletionStack<std::pair<MouseDeviceEventFunction, void*>> _mouseDeviceEventFunctions;

		OrderIndependentDeletionStack<std::pair<JoyAxisEventFunction, void*>> _joyAxisEventFunctions;
		OrderIndependentDeletionStack<std::pair<JoyBallEventFunction, void*>> _joyBallEventFunctions;
		OrderIndependentDeletionStack<std::pair<JoyHatEventFunction, void*>> _joyHatEventFunctions;
		OrderIndependentDeletionStack<std::pair<JoyButtonEventFunction, void*>> _joyButtonEventFunctions;
		OrderIndependentDeletionStack<std::pair<JoyDeviceEventFunction, void*>> _joyDeviceEventFunctions;
		OrderIndependentDeletionStack<std::pair<JoyBatteryEventFunction, void*>> _joyBatteryEventFunctions;

		OrderIndependentDeletionStack<std::pair<GamepadAxisEventFunction, void*>> _gamepadAxisEventFunctions;
		OrderIndependentDeletionStack<std::pair<GamepadButtonEventFunction, void*>> _gamepadButtonEventFunctions;
		OrderIndependentDeletionStack<std::pair<GamepadDeviceEventFunction, void*>> _gamepadDeviceEventFunctions;
		OrderIndependentDeletionStack<std::pair<GamepadTouchpadEventFunction, void*>> _gamepadTouchpadEventFunctions;
		OrderIndependentDeletionStack<std::pair<GamepadSensorEventFunction, void*>> _gamepadSensorEventFunctions;

		OrderIndependentDeletionStack<std::pair<TouchFingerEventFunction, void*>> _touchFingerEventFunctions;
		OrderIndependentDeletionStack<std::pair<TouchPinchEventFunction, void*>> _touchPinchEventFunctions;
		OrderIndependentDeletionStack<std::pair<ClipboardEventFunction, void*>> _clipboardEventFunctions;

		OrderIndependentDeletionStack<std::pair<DropEventFunction, void*>> _dropEventFunctions;
		OrderIndependentDeletionStack<std::pair<AudioDeviceEventFunction, void*>> _audioDeviceEventFunctions;
		OrderIndependentDeletionStack<std::pair<SensorEventFunction, void*>> _sensorEventFunctions;

		OrderIndependentDeletionStack<std::pair<PenProximityEventFunction, void*>> _penProximityEventFunctions;
		OrderIndependentDeletionStack<std::pair<PenTouchEventFunction, void*>> _penTouchEventFunctions;
		OrderIndependentDeletionStack<std::pair<PenButtonEventFunction, void*>> _penButtonEventFunctions;
		OrderIndependentDeletionStack<std::pair<PenMotionEventFunction, void*>> _penMotionEventFunctions;
		OrderIndependentDeletionStack<std::pair<PenAxisEventFunction, void*>> _penAxisEventFunctions;

		OrderIndependentDeletionStack<std::pair<CameraEventFunction, void*>> _cameraEventFunctions;
		OrderIndependentDeletionStack<std::pair<RenderTargetsResetEventFunction, void*>> _renderTargetsResetEventFunctions;
		OrderIndependentDeletionStack<std::pair<RenderDeviceResetEventFunction, void*>> _renderDeviceResetEventFunctions;
		OrderIndependentDeletionStack<std::pair<RenderDeviceLostEventFunction, void*>> _renderDeviceLostEventFunctions;

		OrderIndependentDeletionStack<std::pair<UserEventFunction, void*>> _userEventFunctions;

		void HandleEvent(const SDL_Event& event);

		void HandleQuitEvent(const SDL_Event& event);

		void HandleAppTerminatingEvent(const SDL_Event& event);
		void HandleAppLowMemoryEvent(const SDL_Event& event);
		void HandleAppWillEnterBackgroundEvent(const SDL_Event& event);
		void HandleAppDidEnterBackgroundEvent(const SDL_Event& event);
		void HandleAppWillEnterForegroundEvent(const SDL_Event& event);
		void HandleAppDidEnterForegroundEvent(const SDL_Event& event);

		void HandleLocaleChangeEvent(const SDL_Event& event);
		void HandleSystemThemeChangeEvent(const SDL_Event& event);

		void HandleDisplayEvent(const SDL_Event& event);
		void HandleWindowEvent(const SDL_Event& event);

		void HandleKeyboardEvent(const SDL_Event& event);
		void HandleTextEditingEvent(const SDL_Event& event);
		void HandleTextInputEvent(const SDL_Event& event);
		void HandleKeymapChangedEvent(const SDL_Event& event);

		void HandleKeyboardDeviceEvent(const SDL_Event& event);
		void HandleTextEditingCandidatesEvent(const SDL_Event& event);
		void HandleScreenKeyboardEvent(const SDL_Event& event);

		void HandleMouseMotionEvent(const SDL_Event& event);
		void HandleMouseButtonEvent(const SDL_Event& event);
		void HandleMouseWheelEvent(const SDL_Event& event);
		void HandleMouseDeviceEvent(const SDL_Event& event);

		void HandleJoyAxisEvent(const SDL_Event& event);
		void HandleJoyBallEvent(const SDL_Event& event);
		void HandleJoyHatEvent(const SDL_Event& event);
		void HandleJoyButtonEvent(const SDL_Event& event);
		void HandleJoyDeviceEvent(const SDL_Event& event);
		void HandleJoyBatteryEvent(const SDL_Event& event);

		void HandleGamepadAxisEvent(const SDL_Event& event);
		void HandleGamepadButtonEvent(const SDL_Event& event);
		void HandleGamepadDeviceEvent(const SDL_Event& event);
		void HandleGamepadTouchpadEvent(const SDL_Event& event);
		void HandleGamepadSensorEvent(const SDL_Event& event);

		void HandleTouchFingerEvent(const SDL_Event& event);
		void HandleTouchPinchEvent(const SDL_Event& event);
		void HandleClipboardEvent(const SDL_Event& event);

		void HandleDropEvent(const SDL_Event& event);
		void HandleAudioDeviceEvent(const SDL_Event& event);
		void HandleSensorEvent(const SDL_Event& event);

		void HandlePenProximityEvent(const SDL_Event& event);
		void HandlePenTouchEvent(const SDL_Event& event);
		void HandlePenButtonEvent(const SDL_Event& event);
		void HandlePenMotionEvent(const SDL_Event& event);
		void HandlePenAxisEvent(const SDL_Event& event);

		void HandleCameraEvent(const SDL_Event& event);
		void HandleRenderTargetsResetEvent(const SDL_Event& event);
		void HandleRenderDeviceResetEvent(const SDL_Event& event);
		void HandleRenderDeviceLostEvent(const SDL_Event& event);

		void HandleUserEvent(const SDL_Event& event);
	};
}