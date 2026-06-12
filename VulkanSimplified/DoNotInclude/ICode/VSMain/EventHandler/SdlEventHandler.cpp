#include "SdlEhIpch.h"
#include "../../../../Include/VSMain/EventHandler/SdlEventHandler.h"

#include "../../../../DoNotInclude/DNIData/VSMain/EventHandler/SdlEventHandlerInternal.h"

#include <CustomLists/IDObject.h>
#include "../../../../Include/VSDevice/VSDescriptorDataLists.h"

namespace VulkanSimplified
{
	SdlEventHandler::SdlEventHandler(SdlEventHandlerInternal& ref) : _internal(ref)
	{
	}

	SdlEventHandler::~SdlEventHandler()
	{
	}

	void SdlEventHandler::HandleEvents()
	{
		_internal.HandleEvents();
	}

	IDObject<std::pair<QuitEventFunction, void*>> SdlEventHandler::RegisterQuitEventCallback(QuitEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterQuitEventCallback(function, data, add);
	}

	IDObject<std::pair<AppTerminatingEventFunction, void*>> SdlEventHandler::RegisterAppTerminatingEventCallback(AppTerminatingEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterAppTerminatingEventCallback(function, data, add);
	}

	IDObject<std::pair<AppLowMemoryEventFunction, void*>> SdlEventHandler::RegisterAppLowMemoryWarningEventCallback(AppLowMemoryEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterAppLowMemoryWarningEventCallback(function, data, add);
	}

	IDObject<std::pair<AppWillEnterBackgroundEventFunction, void*>> SdlEventHandler::RegisterAppWillEnterBackgroundWarningEventCallback(AppWillEnterBackgroundEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterAppWillEnterBackgroundWarningEventCallback(function, data, add);
	}

	IDObject<std::pair<AppDidEnterBackgroundEventFunction, void*>> SdlEventHandler::RegisterAppDidEnterBackgroundEventCallback(AppDidEnterBackgroundEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterAppDidEnterBackgroundEventCallback(function, data, add);
	}

	IDObject<std::pair<AppWillEnterForegroundEventFunction, void*>> SdlEventHandler::RegisterAppWillEnterForegroundWarningEventCallback(AppWillEnterForegroundEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterAppWillEnterForegroundWarningEventCallback(function, data, add);
	}

	IDObject<std::pair<AppDidEnterForegroundEventFunction, void*>> SdlEventHandler::RegisterAppDidEnterForegroundEventCallback(AppDidEnterForegroundEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterAppDidEnterForegroundEventCallback(function, data, add);
	}

	IDObject<std::pair<LocaleChangedEventFunction, void*>> SdlEventHandler::RegisterLocaleChangingEventCallback(LocaleChangedEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterLocaleChangingEventCallback(function, data, add);
	}

	IDObject<std::pair<DisplayEventFunction, void*>> SdlEventHandler::RegisterDisplayEventCallback(DisplayEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterDisplayEventCallback(function, data, add);
	}

	IDObject<std::pair<WindowEventFunction, void*>> SdlEventHandler::RegisterWindowEventCallback(WindowEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterWindowEventCallback(function, data, add);
	}

	IDObject<std::pair<KeyboardEventFunction, void*>> SdlEventHandler::RegisterKeyboardEventCallback(KeyboardEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterKeyboardEventCallback(function, data, add);
	}

	IDObject<std::pair<TextEditingEventFunction, void*>> SdlEventHandler::RegisterTextEditingEventCallback(TextEditingEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterTextEditingEventCallback(function, data, add);
	}

	IDObject<std::pair<TextInputEventFunction, void*>> SdlEventHandler::RegisterTextInputEventCallback(TextInputEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterTextInputEventCallback(function, data, add);
	}

	IDObject<std::pair<KeymapChangeEventFunction, void*>> SdlEventHandler::RegisterKeymapChangingEventCallback(KeymapChangeEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterKeymapChangingEventCallback(function, data, add);
	}

	IDObject<std::pair<KeyboardDeviceEventFunction, void*>> SdlEventHandler::RegisterKeyboardDeviceEventCallback(KeyboardDeviceEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterKeyboardDeviceEventCallback(function, data, add);
	}

	IDObject<std::pair<TextEditingCandidatesEventFunction, void*>> SdlEventHandler::RegisterTextCandidatesEditingEventCallback(TextEditingCandidatesEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterTextCandidatesEditingEventCallback(function, data, add);
	}

	IDObject<std::pair<ScreenKeyboardEventFunction, void*>> SdlEventHandler::RegisterScreenKeyboardEventCallback(ScreenKeyboardEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterScreenKeyboardEventCallback(function, data, add);
	}

	IDObject<std::pair<MouseMotionEventFunction, void*>> SdlEventHandler::RegisterMouseMotionEventCallback(MouseMotionEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterMouseMotionEventCallback(function, data, add);
	}

	IDObject<std::pair<MouseButtonEventFunction, void*>> SdlEventHandler::RegisterMouseButtonEventCallback(MouseButtonEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterMouseButtonEventCallback(function, data, add);
	}

	IDObject<std::pair<MouseWheelEventFunction, void*>> SdlEventHandler::RegisterMouseWheelEventCallback(MouseWheelEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterMouseWheelEventCallback(function, data, add);
	}

	IDObject<std::pair<MouseDeviceEventFunction, void*>> SdlEventHandler::RegisterMouseDeviceEventCallback(MouseDeviceEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterMouseDeviceEventCallback(function, data, add);
	}

	IDObject<std::pair<JoyAxisEventFunction, void*>> SdlEventHandler::RegisterJoystickAxisEventCallback(JoyAxisEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterJoystickAxisEventCallback(function, data, add);
	}

	IDObject<std::pair<JoyBallEventFunction, void*>> SdlEventHandler::RegisterJoystickBallEventCallback(JoyBallEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterJoystickBallEventCallback(function, data, add);
	}

	IDObject<std::pair<JoyHatEventFunction, void*>> SdlEventHandler::RegisterJoystickHatEventCallback(JoyHatEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterJoystickHatEventCallback(function, data, add);
	}

	IDObject<std::pair<JoyButtonEventFunction, void*>> SdlEventHandler::RegisterJoystickButtonEventCallback(JoyButtonEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterJoystickButtonEventCallback(function, data, add);
	}

	IDObject<std::pair<JoyDeviceEventFunction, void*>> SdlEventHandler::RegisterJoystickDeviceEventCallback(JoyDeviceEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterJoystickDeviceEventCallback(function, data, add);
	}

	IDObject<std::pair<JoyBatteryEventFunction, void*>> SdlEventHandler::RegisterJoystickBatteryEventCallback(JoyBatteryEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterJoystickBatteryEventCallback(function, data, add);
	}

	IDObject<std::pair<GamepadAxisEventFunction, void*>> SdlEventHandler::RegisterGamepadAxisEventCallback(GamepadAxisEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterGamepadAxisEventCallback(function, data, add);
	}

	IDObject<std::pair<GamepadButtonEventFunction, void*>> SdlEventHandler::RegisterGamepadButtonEventCallback(GamepadButtonEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterGamepadButtonEventCallback(function, data, add);
	}

	IDObject<std::pair<GamepadDeviceEventFunction, void*>> SdlEventHandler::RegisterGamepadDeviceEventCallback(GamepadDeviceEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterGamepadDeviceEventCallback(function, data, add);
	}

	IDObject<std::pair<GamepadTouchpadEventFunction, void*>> SdlEventHandler::RegisterGamepadTouchpadEventCallback(GamepadTouchpadEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterGamepadTouchpadEventCallback(function, data, add);
	}

	IDObject<std::pair<GamepadSensorEventFunction, void*>> SdlEventHandler::RegisterGamepadSensorEventCallback(GamepadSensorEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterGamepadSensorEventCallback(function, data, add);
	}

	IDObject<std::pair<TouchFingerEventFunction, void*>> SdlEventHandler::RegisterTouchFingerEventCallback(TouchFingerEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterTouchFingerEventCallback(function, data, add);
	}

	IDObject<std::pair<TouchPinchEventFunction, void*>> SdlEventHandler::RegisterPinchFingerEventCallback(TouchPinchEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterPinchFingerEventCallback(function, data, add);
	}

	IDObject<std::pair<ClipboardEventFunction, void*>> SdlEventHandler::RegisterClipboardEventCallback(ClipboardEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterClipboardEventCallback(function, data, add);
	}

	IDObject<std::pair<DropEventFunction, void*>> SdlEventHandler::RegisterDropEventCallback(DropEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterDropEventCallback(function, data, add);
	}

	IDObject<std::pair<AudioDeviceEventFunction, void*>> SdlEventHandler::RegisterAudioDeviceEventCallback(AudioDeviceEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterAudioDeviceEventCallback(function, data, add);
	}

	IDObject<std::pair<SensorEventFunction, void*>> SdlEventHandler::RegisterSensorEventCallback(SensorEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterSensorEventCallback(function, data, add);
	}

	IDObject<std::pair<PenProximityEventFunction, void*>> SdlEventHandler::RegisterPenProximityEventCallback(PenProximityEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterPenProximityEventCallback(function, data, add);
	}

	IDObject<std::pair<PenTouchEventFunction, void*>> SdlEventHandler::RegisterPenTouchEventCallback(PenTouchEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterPenTouchEventCallback(function, data, add);
	}

	IDObject<std::pair<PenButtonEventFunction, void*>> SdlEventHandler::RegisterPenButtonEventCallback(PenButtonEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterPenButtonEventCallback(function, data, add);
	}

	IDObject<std::pair<PenMotionEventFunction, void*>> SdlEventHandler::RegisterPenMotionEventCallback(PenMotionEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterPenMotionEventCallback(function, data, add);
	}

	IDObject<std::pair<PenAxisEventFunction, void*>> SdlEventHandler::RegisterPenAxisEventCallback(PenAxisEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterPenAxisEventCallback(function, data, add);
	}

	IDObject<std::pair<CameraEventFunction, void*>> SdlEventHandler::RegisterCameraEventCallback(CameraEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterCameraEventCallback(function, data, add);
	}

	IDObject<std::pair<RenderTargetsResetEventFunction, void*>> SdlEventHandler::RegisterRenderTargetsResetEventCallback(RenderTargetsResetEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterRenderTargetsResetEventCallback(function, data, add);
	}

	IDObject<std::pair<RenderDeviceResetEventFunction, void*>> SdlEventHandler::RegisterRenderDeviceResetEventCallback(RenderDeviceResetEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterRenderDeviceResetEventCallback(function, data, add);
	}

	IDObject<std::pair<RenderDeviceLostEventFunction, void*>> SdlEventHandler::RegisterRenderDeviceLostEventCallback(RenderDeviceLostEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterRenderDeviceLostEventCallback(function, data, add);
	}

	IDObject<std::pair<UserEventFunction, void*>> SdlEventHandler::RegisterUserEventCallback(UserEventFunction function, void* data, size_t add)
	{
		return _internal.RegisterUserEventCallback(function, data, add);
	}

	bool SdlEventHandler::UnRegisterQuitEventCallback(IDObject<std::pair<QuitEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterQuitEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterAppTerminatingEventCallback(IDObject<std::pair<AppTerminatingEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterAppTerminatingEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterAppLowMemoryEventCallback(IDObject<std::pair<AppLowMemoryEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterAppLowMemoryEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterAppWillEnterBackgroundEventCallback(IDObject<std::pair<AppWillEnterBackgroundEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterAppWillEnterBackgroundEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterAppDidEnterBackgroundEventCallback(IDObject<std::pair<AppDidEnterBackgroundEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterAppDidEnterBackgroundEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterAppWillEnterForegroundEventCallback(IDObject<std::pair<AppWillEnterForegroundEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterAppWillEnterForegroundEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterAppDidEnterForegroundEventCallback(IDObject<std::pair<AppDidEnterForegroundEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterAppDidEnterForegroundEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterLocaleChangedEventCallback(IDObject<std::pair<LocaleChangedEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterLocaleChangedEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterDisplayEventCallback(IDObject<std::pair<DisplayEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterDisplayEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterWindowEventCallback(IDObject<std::pair<WindowEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterWindowEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterKeyboardEventCallback(IDObject<std::pair<KeyboardEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterKeyboardEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterTextEditingEventCallback(IDObject<std::pair<TextEditingEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterTextEditingEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterTextInputEventCallback(IDObject<std::pair<TextInputEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterTextInputEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterKeymapChangeEventCallback(IDObject<std::pair<KeymapChangeEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterKeymapChangeEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterMouseMotionEventCallback(IDObject<std::pair<MouseMotionEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterMouseMotionEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterMouseButtonEventCallback(IDObject<std::pair<MouseButtonEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterMouseButtonEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterMouseWheelEventCallback(IDObject<std::pair<MouseWheelEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterMouseWheelEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterMouseDeviceEventCallback(IDObject<std::pair<MouseDeviceEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterMouseDeviceEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterJoyAxisEventCallback(IDObject<std::pair<JoyAxisEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterJoyAxisEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterJoyBallEventCallback(IDObject<std::pair<JoyBallEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterJoyBallEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterJoyHatEventCallback(IDObject<std::pair<JoyHatEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterJoyHatEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterJoyButtonEventCallback(IDObject<std::pair<JoyButtonEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterJoyButtonEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterJoyDeviceEventCallback(IDObject<std::pair<JoyDeviceEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterJoyDeviceEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterJoyBatteryEventCallback(IDObject<std::pair<JoyBatteryEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterJoyBatteryEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterGamepadAxisEventCallback(IDObject<std::pair<GamepadAxisEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterGamepadAxisEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterGamepadButtonEventCallback(IDObject<std::pair<GamepadButtonEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterGamepadButtonEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterGamepadDeviceEventCallback(IDObject<std::pair<GamepadDeviceEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterGamepadDeviceEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterGamepadTouchpadEventCallback(IDObject<std::pair<GamepadTouchpadEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterGamepadTouchpadEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterGamepadSensorEventCallback(IDObject<std::pair<GamepadSensorEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterGamepadSensorEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterTouchFingerEventCallback(IDObject<std::pair<TouchFingerEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterTouchFingerEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterTouchPinchEventCallback(IDObject<std::pair<TouchPinchEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterTouchPinchEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterClipboardEventCallback(IDObject<std::pair<ClipboardEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterClipboardEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterDropEventCallback(IDObject<std::pair<DropEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterDropEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterAudioDeviceEventCallback(IDObject<std::pair<AudioDeviceEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterAudioDeviceEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterSensorEventCallback(IDObject<std::pair<SensorEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterSensorEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterPenProximityEventCallback(IDObject<std::pair<PenProximityEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterPenProximityEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterPenTouchEventCallback(IDObject<std::pair<PenTouchEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterPenTouchEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterPenButtonEventCallback(IDObject<std::pair<PenButtonEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterPenButtonEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterPenMotionEventCallback(IDObject<std::pair<PenMotionEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterPenMotionEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterPenAxisEventCallback(IDObject<std::pair<PenAxisEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterPenAxisEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterCameraEventCallback(IDObject<std::pair<CameraEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterCameraEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterRenderTargetsResetEventCallback(IDObject<std::pair<RenderTargetsResetEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterRenderTargetsResetEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterRenderDeviceResetEventCallback(IDObject<std::pair<RenderDeviceResetEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterRenderDeviceResetEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterRenderDeviceLostEventCallback(IDObject<std::pair<RenderDeviceLostEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterRenderDeviceLostEventCallback(ID, throwOnIDNotFound);
	}

	bool SdlEventHandler::UnRegisterUserEventCallback(IDObject<std::pair<UserEventFunction, void*>> ID, bool throwOnIDNotFound)
	{
		return _internal.UnRegisterUserEventCallback(ID, throwOnIDNotFound);
	}
}
