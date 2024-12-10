#pragma once

class SdlEventHandlerInternal;

struct SdlAppTerminatingEventData;
struct SdlAppLowMemoryEventData;
struct SdlAppWillEnterBackgroundEventData;
struct SdlAppDidEnterBackgroundEventData;
struct SdlAppWillEnterForegroundEventData;
struct SdlAppDidEnterForegroundEventData;

struct SdlAudioDeviceEventData;

struct SdlClipboardEventData;

struct SdlControllerAxisEventData;
struct SdlControllerButtonEventData;
struct SdlControllerDeviceEventData;
struct SdlControllerTouchpadEventData;
struct SdlControllerSensorEventData;

struct SdlDisplayEventData;

struct SdlDropEventData;

struct SdlJoyAxisEventData;
struct SdlJoyBallEventData;
struct SdlJoyHatEventData;
struct SdlJoyButtonEventData;
struct SdlJoyDeviceEventData;
struct SdlJoyBatteryEventData;

struct SdlKeyboardEventData;
struct SdlKeymapChangedEventData;

struct SdlLocaleChangeEventData;

struct SdlMouseMotionEventData;
struct SdlMouseButtonEventData;
struct SdlMouseWheelEventData;

struct SdlQuitEventData;

struct SdlRenderTargetsResetEventData;
struct SdlRenderDeviceResetEventData;

struct SdlSensorEventData;

struct SdlTextEditingEventData;
struct SdlTextEditingExtendedEventData;
struct SdlTextInputEventData;

struct SdlTouchFingerEventData;
struct SdlMultiGestureEventData;
struct SdlDollarGestureEventData;

struct SdlUserEventData;

struct SdlWindowEventData;

namespace std
{
	template<class T>
	class function;
}

typedef std::function<bool(const SdlAppTerminatingEventData&, void*)> AppTerminatingEventFunction;
typedef std::function<bool(const SdlAppLowMemoryEventData&, void*)> AppLowMemoryEventFunction;
typedef std::function<bool(const SdlAppWillEnterBackgroundEventData&, void*)> AppWillEnterBackgroundEventFunction;
typedef std::function<bool(const SdlAppDidEnterBackgroundEventData&, void*)> AppDidEnterBackgroundEventFunction;
typedef std::function<bool(const SdlAppWillEnterForegroundEventData&, void*)> AppWillEnterForegroundEventFunction;
typedef std::function<bool(const SdlAppDidEnterForegroundEventData&, void*)> AppDidEnterForegroundEventFunction;

typedef std::function<bool(const SdlAudioDeviceEventData&, void*)> AudioDeviceEventFunction;

typedef std::function<bool(const SdlClipboardEventData&, void*)> ClipboardEventFunction;

typedef std::function<bool(const SdlControllerAxisEventData&, void*)> ControllerAxisEventFunction;
typedef std::function<bool(const SdlControllerButtonEventData&, void*)> ControllerButtonEventFunction;
typedef std::function<bool(const SdlControllerDeviceEventData&, void*)> ControllerDeviceEventFunction;
typedef std::function<bool(const SdlControllerTouchpadEventData&, void*)> ControllerTouchpadEventFunction;
typedef std::function<bool(const SdlControllerSensorEventData&, void*)> ControllerSensorEventFunction;

typedef std::function<bool(const SdlDisplayEventData&, void*)> DisplayEventFunction;

typedef std::function<bool(const SdlDropEventData&, void*)> DropEventFunction;

typedef std::function<bool(const SdlJoyAxisEventData&, void*)> JoyAxisEventFunction;
typedef std::function<bool(const SdlJoyBallEventData&, void*)> JoyBallEventFunction;
typedef std::function<bool(const SdlJoyHatEventData&, void*)> JoyHatEventFunction;
typedef std::function<bool(const SdlJoyButtonEventData&, void*)> JoyButtonEventFunction;
typedef std::function<bool(const SdlJoyDeviceEventData&, void*)> JoyDeviceEventFunction;
typedef std::function<bool(const SdlJoyBatteryEventData&, void*)> JoyBatteryEventFunction;

typedef std::function<bool(const SdlKeyboardEventData&, void*)> KeyboardEventFunction;
typedef std::function<bool(const SdlKeymapChangedEventData&, void*)> KeymapChangeEventFunction;

typedef std::function<bool(const SdlLocaleChangeEventData&, void*)> LocaleChangedEventFunction;

typedef std::function<bool(const SdlMouseMotionEventData&, void*)> MouseMotionEventFunction;
typedef std::function<bool(const SdlMouseButtonEventData&, void*)> MouseButtonEventFunction;
typedef std::function<bool(const SdlMouseWheelEventData&, void*)> MouseWheelEventFunction;

typedef std::function<bool(const SdlQuitEventData&, void*)> QuitEventFunction;

typedef std::function<bool(const SdlRenderTargetsResetEventData&, void*)> RenderTargetsResetEventFunction;
typedef std::function<bool(const SdlRenderDeviceResetEventData&, void*)> RenderDeviceResetEventFunction;

typedef std::function<bool(const SdlSensorEventData&, void*)> SensorEventFunction;

typedef std::function<bool(const SdlTextEditingEventData&, void*)> TextEditingEventFunction;
typedef std::function<bool(const SdlTextEditingExtendedEventData&, void*)> TextEditingExtendedEventFunction;
typedef std::function<bool(const SdlTextInputEventData&, void*)> TextInputEventFunction;

typedef std::function<bool(const SdlTouchFingerEventData&, void*)> TouchFingerEventFunction;
typedef std::function<bool(const SdlMultiGestureEventData&, void*)> MultiGestureEventFunction;
typedef std::function<bool(const SdlDollarGestureEventData&, void*)> DollarGestureEventFunction;

typedef std::function<bool(const SdlUserEventData&, void*)> UserEventFunction;

typedef std::function<bool(const SdlWindowEventData&, void*)> WindowEventFunction;

template<class T>
class IDObject;

class SdlEventHandler
{
public:
	SdlEventHandler(SdlEventHandlerInternal& ref);
	~SdlEventHandler();

	SdlEventHandler(const SdlEventHandler&) noexcept = default;
	SdlEventHandler(SdlEventHandler&&) noexcept = default;

	SdlEventHandler& operator=(const SdlEventHandler&) noexcept = delete;
	SdlEventHandler& operator=(SdlEventHandler&&) noexcept = delete;

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
	SdlEventHandlerInternal& _internal;
};