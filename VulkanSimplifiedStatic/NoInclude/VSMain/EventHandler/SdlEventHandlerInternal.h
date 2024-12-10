#pragma once

#include "CustomLists/OrderIndependentDeletionStack.h"

#include "../../../Include/VSMain/EventHandler/SdlEventHandlerTypedefs.h"

#include <functional>
#include <utility>

namespace VulkanSimplifiedInternal
{
	class SdlEventHandlerInternal
	{
	public:
		SdlEventHandlerInternal(const VulkanSimplified::SdlEventHandlerInitData& initData);
		~SdlEventHandlerInternal();

		SdlEventHandlerInternal(const SdlEventHandlerInternal&) noexcept = delete;
		SdlEventHandlerInternal(SdlEventHandlerInternal&&) noexcept = delete;

		SdlEventHandlerInternal& operator=(const SdlEventHandlerInternal&) noexcept = delete;
		SdlEventHandlerInternal& operator=(SdlEventHandlerInternal&&) noexcept = delete;

		void HandleEvents();

		IDObject<std::pair<VulkanSimplified::QuitEventFunction, void*>> RegisterQuitEventCallback(VulkanSimplified::QuitEventFunction function, void* data, size_t add);

		IDObject<std::pair<VulkanSimplified::AppTerminatingEventFunction, void*>> RegisterAppTerminatingEventCallback(VulkanSimplified::AppTerminatingEventFunction function, void* data, size_t add);
		IDObject<std::pair<VulkanSimplified::AppLowMemoryEventFunction, void*>> RegisterAppLowMemoryWarningEventCallback(VulkanSimplified::AppLowMemoryEventFunction function, void* data, size_t add);
		IDObject<std::pair<VulkanSimplified::AppWillEnterBackgroundEventFunction, void*>> RegisterAppWillEnterBackgroundWarningEventCallback(VulkanSimplified::AppWillEnterBackgroundEventFunction function, void* data, size_t add);
		IDObject<std::pair<VulkanSimplified::AppDidEnterBackgroundEventFunction, void*>> RegisterAppDidEnterBackgroundEventCallback(VulkanSimplified::AppDidEnterBackgroundEventFunction function, void* data, size_t add);
		IDObject<std::pair<VulkanSimplified::AppWillEnterForegroundEventFunction, void*>> RegisterAppWillEnterForegroundWarningEventCallback(VulkanSimplified::AppWillEnterForegroundEventFunction function, void* data, size_t add);
		IDObject<std::pair<VulkanSimplified::AppDidEnterForegroundEventFunction, void*>> RegisterAppDidEnterForegroundEventCallback(VulkanSimplified::AppDidEnterForegroundEventFunction function, void* data, size_t add);

		IDObject<std::pair<VulkanSimplified::LocaleChangedEventFunction, void*>> RegisterLocaleChangingEventCallback(VulkanSimplified::LocaleChangedEventFunction function, void* data, size_t add);

		IDObject<std::pair<VulkanSimplified::DisplayEventFunction, void*>> RegisterDisplayEventCallback(VulkanSimplified::DisplayEventFunction function, void* data, size_t add);
		IDObject<std::pair<VulkanSimplified::WindowEventFunction, void*>> RegisterWindowEventCallback(VulkanSimplified::WindowEventFunction function, void* data, size_t add);

		IDObject<std::pair<VulkanSimplified::KeyboardEventFunction, void*>> RegisterKeyboardEventCallback(VulkanSimplified::KeyboardEventFunction function, void* data, size_t add);
		IDObject<std::pair<VulkanSimplified::KeymapChangeEventFunction, void*>> RegisterKeymapChangingEventCallback(VulkanSimplified::KeymapChangeEventFunction function, void* data, size_t add);
		IDObject<std::pair<VulkanSimplified::TextEditingEventFunction, void*>> RegisterTextEditingEventCallback(VulkanSimplified::TextEditingEventFunction function, void* data, size_t add);
		IDObject<std::pair<VulkanSimplified::TextEditingExtendedEventFunction, void*>> RegisterTextEditingExtendedEventCallback(VulkanSimplified::TextEditingExtendedEventFunction function, void* data, size_t add);
		IDObject<std::pair<VulkanSimplified::TextInputEventFunction, void*>> RegisterTextInputEventCallback(VulkanSimplified::TextInputEventFunction function, void* data, size_t add);

		IDObject<std::pair<VulkanSimplified::MouseMotionEventFunction, void*>> RegisterMouseMotionEventCallback(VulkanSimplified::MouseMotionEventFunction function, void* data, size_t add);
		IDObject<std::pair<VulkanSimplified::MouseButtonEventFunction, void*>> RegisterMouseButtonEventCallback(VulkanSimplified::MouseButtonEventFunction function, void* data, size_t add);
		IDObject<std::pair<VulkanSimplified::MouseWheelEventFunction, void*>> RegisterMouseWheelEventCallback(VulkanSimplified::MouseWheelEventFunction function, void* data, size_t add);

		IDObject<std::pair<VulkanSimplified::JoyAxisEventFunction, void*>> RegisterJoystickAxisEventCallback(VulkanSimplified::JoyAxisEventFunction function, void* data, size_t add);
		IDObject<std::pair<VulkanSimplified::JoyBallEventFunction, void*>> RegisterJoystickBallEventCallback(VulkanSimplified::JoyBallEventFunction function, void* data, size_t add);
		IDObject<std::pair<VulkanSimplified::JoyHatEventFunction, void*>> RegisterJoystickHatEventCallback(VulkanSimplified::JoyHatEventFunction function, void* data, size_t add);
		IDObject<std::pair<VulkanSimplified::JoyButtonEventFunction, void*>> RegisterJoystickButtonEventCallback(VulkanSimplified::JoyButtonEventFunction function, void* data, size_t add);
		IDObject<std::pair<VulkanSimplified::JoyDeviceEventFunction, void*>> RegisterJoystickDeviceEventCallback(VulkanSimplified::JoyDeviceEventFunction function, void* data, size_t add);
		IDObject<std::pair<VulkanSimplified::JoyBatteryEventFunction, void*>> RegisterJoystickBatteryEventCallback(VulkanSimplified::JoyBatteryEventFunction function, void* data, size_t add);

		IDObject<std::pair<VulkanSimplified::ControllerAxisEventFunction, void*>> RegisterControllerAxisEventCallback(VulkanSimplified::ControllerAxisEventFunction function, void* data, size_t add);
		IDObject<std::pair<VulkanSimplified::ControllerButtonEventFunction, void*>> RegisterControllerButtonEventCallback(VulkanSimplified::ControllerButtonEventFunction function, void* data, size_t add);
		IDObject<std::pair<VulkanSimplified::ControllerDeviceEventFunction, void*>> RegisterControllerDeviceEventCallback(VulkanSimplified::ControllerDeviceEventFunction function, void* data, size_t add);
		IDObject<std::pair<VulkanSimplified::ControllerTouchpadEventFunction, void*>> RegisterControllerTouchpadEventCallback(VulkanSimplified::ControllerTouchpadEventFunction function, void* data, size_t add);
		IDObject<std::pair<VulkanSimplified::ControllerSensorEventFunction, void*>> RegisterControllerSensorEventCallback(VulkanSimplified::ControllerSensorEventFunction function, void* data, size_t add);

		IDObject<std::pair<VulkanSimplified::AudioDeviceEventFunction, void*>> RegisterAudioDeviceEventCallback(VulkanSimplified::AudioDeviceEventFunction function, void* data, size_t add);
		IDObject<std::pair<VulkanSimplified::TouchFingerEventFunction, void*>> RegisterTouchFingerEventCallback(VulkanSimplified::TouchFingerEventFunction function, void* data, size_t add);
		IDObject<std::pair<VulkanSimplified::MultiGestureEventFunction, void*>> RegisterMultiGestureEventCallback(VulkanSimplified::MultiGestureEventFunction function, void* data, size_t add);
		IDObject<std::pair<VulkanSimplified::DollarGestureEventFunction, void*>> RegisterDollarGestureEventCallback(VulkanSimplified::DollarGestureEventFunction function, void* data, size_t add);
		IDObject<std::pair<VulkanSimplified::ClipboardEventFunction, void*>> RegisterClipboardEventCallback(VulkanSimplified::ClipboardEventFunction function, void* data, size_t add);

		IDObject<std::pair<VulkanSimplified::DropEventFunction, void*>> RegisterDropEventCallback(VulkanSimplified::DropEventFunction function, void* data, size_t add);
		IDObject<std::pair<VulkanSimplified::SensorEventFunction, void*>> RegisterSensorEventCallback(VulkanSimplified::SensorEventFunction function, void* data, size_t add);
		IDObject<std::pair<VulkanSimplified::UserEventFunction, void*>> RegisterUserEventCallback(VulkanSimplified::UserEventFunction function, void* data, size_t add);

		IDObject<std::pair<VulkanSimplified::RenderTargetsResetEventFunction, void*>> RegisterRenderTargetsResetEventCallback(VulkanSimplified::RenderTargetsResetEventFunction function, void* data, size_t add);
		IDObject<std::pair<VulkanSimplified::RenderDeviceResetEventFunction, void*>> RegisterRenderDeviceResetEventCallback(VulkanSimplified::RenderDeviceResetEventFunction function, void* data, size_t add);

		bool UnRegisterQuitEventCallback(IDObject<std::pair<VulkanSimplified::QuitEventFunction, void*>> ID, bool throwOnIDNotFound);

		bool UnRegisterAppTerminatingEventCallback(IDObject<std::pair<VulkanSimplified::AppTerminatingEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterAppLowMemoryEventCallback(IDObject<std::pair<VulkanSimplified::AppLowMemoryEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterAppWillEnterBackgroundEventCallback(IDObject<std::pair<VulkanSimplified::AppWillEnterBackgroundEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterAppDidEnterBackgroundEventCallback(IDObject<std::pair<VulkanSimplified::AppDidEnterBackgroundEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterAppWillEnterForegroundEventCallback(IDObject<std::pair<VulkanSimplified::AppWillEnterForegroundEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterAppDidEnterForegroundEventCallback(IDObject<std::pair<VulkanSimplified::AppDidEnterForegroundEventFunction, void*>> ID, bool throwOnIDNotFound);

		bool UnRegisterLocaleChangedEventCallback(IDObject<std::pair<VulkanSimplified::LocaleChangedEventFunction, void*>> ID, bool throwOnIDNotFound);

		bool UnRegisterDisplayEventCallback(IDObject<std::pair<VulkanSimplified::DisplayEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterWindowEventCallback(IDObject<std::pair<VulkanSimplified::WindowEventFunction, void*>> ID, bool throwOnIDNotFound);

		bool UnRegisterKeyboardEventCallback(IDObject<std::pair<VulkanSimplified::KeyboardEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterKeymapChangeEventCallback(IDObject<std::pair<VulkanSimplified::KeymapChangeEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterTextEditingEventCallback(IDObject<std::pair<VulkanSimplified::TextEditingEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterTextEditingExtendedEventCallback(IDObject<std::pair<VulkanSimplified::TextEditingExtendedEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterTextInputEventCallback(IDObject<std::pair<VulkanSimplified::TextInputEventFunction, void*>> ID, bool throwOnIDNotFound);

		bool UnRegisterMouseMotionEventCallback(IDObject<std::pair<VulkanSimplified::MouseMotionEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterMouseButtonEventCallback(IDObject<std::pair<VulkanSimplified::MouseButtonEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterMouseWheelEventCallback(IDObject<std::pair<VulkanSimplified::MouseWheelEventFunction, void*>> ID, bool throwOnIDNotFound);

		bool UnRegisterJoyAxisEventCallback(IDObject<std::pair<VulkanSimplified::JoyAxisEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterJoyBallEventCallback(IDObject<std::pair<VulkanSimplified::JoyBallEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterJoyHatEventCallback(IDObject<std::pair<VulkanSimplified::JoyHatEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterJoyButtonEventCallback(IDObject<std::pair<VulkanSimplified::JoyButtonEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterJoyDeviceEventCallback(IDObject<std::pair<VulkanSimplified::JoyDeviceEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterJoyBatteryEventCallback(IDObject<std::pair<VulkanSimplified::JoyBatteryEventFunction, void*>> ID, bool throwOnIDNotFound);

		bool UnRegisterControllerAxisEventCallback(IDObject<std::pair<VulkanSimplified::ControllerAxisEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterControllerButtonEventCallback(IDObject<std::pair<VulkanSimplified::ControllerButtonEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterControllerDeviceEventCallback(IDObject<std::pair<VulkanSimplified::ControllerDeviceEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterControllerTouchpadEventCallback(IDObject<std::pair<VulkanSimplified::ControllerTouchpadEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterControllerSensorEventCallback(IDObject<std::pair<VulkanSimplified::ControllerSensorEventFunction, void*>> ID, bool throwOnIDNotFound);

		bool UnRegisterAudioDeviceEventCallback(IDObject<std::pair<VulkanSimplified::AudioDeviceEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterTouchFingerEventCallback(IDObject<std::pair<VulkanSimplified::TouchFingerEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterMultiGestureEventCallback(IDObject<std::pair<VulkanSimplified::MultiGestureEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterDollarGestureEventCallback(IDObject<std::pair<VulkanSimplified::DollarGestureEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterClipboardEventCallback(IDObject<std::pair<VulkanSimplified::ClipboardEventFunction, void*>> ID, bool throwOnIDNotFound);

		bool UnRegisterDropEventCallback(IDObject<std::pair<VulkanSimplified::DropEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterSensorEventCallback(IDObject<std::pair<VulkanSimplified::SensorEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterUserEventCallback(IDObject<std::pair<VulkanSimplified::UserEventFunction, void*>> ID, bool throwOnIDNotFound);

		bool UnRegisterRenderTargetsResetEventCallback(IDObject<std::pair<VulkanSimplified::RenderTargetsResetEventFunction, void*>> ID, bool throwOnIDNotFound);
		bool UnRegisterRenderDeviceResetEventCallback(IDObject<std::pair<VulkanSimplified::RenderDeviceResetEventFunction, void*>> ID, bool throwOnIDNotFound);

	private:
		OrderIndependentDeletionStack<std::pair<VulkanSimplified::QuitEventFunction, void*>> _quitEventFunctions;

		OrderIndependentDeletionStack<std::pair<VulkanSimplified::AppTerminatingEventFunction, void*>> _appTerminatingEventFunctions;
		OrderIndependentDeletionStack<std::pair<VulkanSimplified::AppLowMemoryEventFunction, void*>> _appLowMemoryEventFunctions;
		OrderIndependentDeletionStack<std::pair<VulkanSimplified::AppWillEnterBackgroundEventFunction, void*>> _appWillEnterBackgroundEventFunctions;
		OrderIndependentDeletionStack<std::pair<VulkanSimplified::AppDidEnterBackgroundEventFunction, void*>> _appDidEnterBackgroundEventFunctions;
		OrderIndependentDeletionStack<std::pair<VulkanSimplified::AppWillEnterForegroundEventFunction, void*>> _appWillEnterForegroundEventFunctions;
		OrderIndependentDeletionStack<std::pair<VulkanSimplified::AppDidEnterForegroundEventFunction, void*>> _appDidEnterForegroundEventFunctions;

		OrderIndependentDeletionStack<std::pair<VulkanSimplified::LocaleChangedEventFunction, void*>> _localeChangedEventFunctions;

		OrderIndependentDeletionStack<std::pair<VulkanSimplified::DisplayEventFunction, void*>> _displayEventFunctions;
		OrderIndependentDeletionStack<std::pair<VulkanSimplified::WindowEventFunction, void*>> _windowEventFunctions;

		OrderIndependentDeletionStack<std::pair<VulkanSimplified::KeyboardEventFunction, void*>> _keyboardEventFunctions;
		OrderIndependentDeletionStack<std::pair<VulkanSimplified::KeymapChangeEventFunction, void*>> _keymapChangedEventFunctions;
		OrderIndependentDeletionStack<std::pair<VulkanSimplified::TextEditingEventFunction, void*>> _textEditingEventFunctions;
		OrderIndependentDeletionStack<std::pair<VulkanSimplified::TextEditingExtendedEventFunction, void*>> _textEditingExtendedEventFunctions;
		OrderIndependentDeletionStack<std::pair<VulkanSimplified::TextInputEventFunction, void*>> _textInputEventFunctions;

		OrderIndependentDeletionStack<std::pair<VulkanSimplified::MouseMotionEventFunction, void*>> _mouseMotionEventFunctions;
		OrderIndependentDeletionStack<std::pair<VulkanSimplified::MouseButtonEventFunction, void*>> _mouseButtonEventFunctions;
		OrderIndependentDeletionStack<std::pair<VulkanSimplified::MouseWheelEventFunction, void*>> _mouseWheelEventFunctions;

		OrderIndependentDeletionStack<std::pair<VulkanSimplified::JoyAxisEventFunction, void*>> _joyAxisEventFunctions;
		OrderIndependentDeletionStack<std::pair<VulkanSimplified::JoyBallEventFunction, void*>> _joyBallEventFunctions;
		OrderIndependentDeletionStack<std::pair<VulkanSimplified::JoyHatEventFunction, void*>> _joyHatEventFunctions;
		OrderIndependentDeletionStack<std::pair<VulkanSimplified::JoyButtonEventFunction, void*>> _joyButtonEventFunctions;
		OrderIndependentDeletionStack<std::pair<VulkanSimplified::JoyDeviceEventFunction, void*>> _joyDeviceEventFunctions;
		OrderIndependentDeletionStack<std::pair<VulkanSimplified::JoyBatteryEventFunction, void*>> _joyBatteryEventFunctions;

		OrderIndependentDeletionStack<std::pair<VulkanSimplified::ControllerAxisEventFunction, void*>> _controllerAxisEventFunctions;
		OrderIndependentDeletionStack<std::pair<VulkanSimplified::ControllerButtonEventFunction, void*>> _controllerButtonEventFunctions;
		OrderIndependentDeletionStack<std::pair<VulkanSimplified::ControllerDeviceEventFunction, void*>> _controllerDeviceEventFunctions;
		OrderIndependentDeletionStack<std::pair<VulkanSimplified::ControllerTouchpadEventFunction, void*>> _controllerTouchpadEventFunctions;
		OrderIndependentDeletionStack<std::pair<VulkanSimplified::ControllerSensorEventFunction, void*>> _controllerSensorEventFunctions;

		OrderIndependentDeletionStack<std::pair<VulkanSimplified::AudioDeviceEventFunction, void*>> _audioDeviceEventFunctions;
		OrderIndependentDeletionStack<std::pair<VulkanSimplified::TouchFingerEventFunction, void*>> _touchFingerEventFunctions;
		OrderIndependentDeletionStack<std::pair<VulkanSimplified::MultiGestureEventFunction, void*>> _multiGestureEventFunctions;
		OrderIndependentDeletionStack<std::pair<VulkanSimplified::DollarGestureEventFunction, void*>> _dollarGestureEventFunctions;
		OrderIndependentDeletionStack<std::pair<VulkanSimplified::ClipboardEventFunction, void*>> _clipboardEventFunctions;

		OrderIndependentDeletionStack<std::pair<VulkanSimplified::DropEventFunction, void*>> _dropEventFunctions;
		OrderIndependentDeletionStack<std::pair<VulkanSimplified::SensorEventFunction, void*>> _sensorEventFunctions;
		OrderIndependentDeletionStack<std::pair<VulkanSimplified::UserEventFunction, void*>> _userEventFunctions;

		OrderIndependentDeletionStack<std::pair<VulkanSimplified::RenderTargetsResetEventFunction, void*>> _renderTargetsResetEventFunctions;
		OrderIndependentDeletionStack<std::pair<VulkanSimplified::RenderDeviceResetEventFunction, void*>> _renderDeviceResetEventFunctions;

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