#include "SdlEhIpch.h"
#include "../../../../Include/VSMain/EventHandler/SdlEventHandlerInitData.h"

namespace VulkanSimplified
{
	SdlEventHandlerInitData::SdlEventHandlerInitData(size_t commonReserveSize)
	{
		quitEventFunctionListInitialCapacity = commonReserveSize;

		appTerminatingEventFunctionListInitialCapacity = commonReserveSize;
		appLowMemoryEventFunctionListInitialCapacity = commonReserveSize;
		appWillEnterBackgroundEventFunctionListInitialCapacity = commonReserveSize;
		appDidEnterBackgroundEventFunctionListInitialCapacity = commonReserveSize;
		appWillEnterForegroundEventFunctionListInitialCapacity = commonReserveSize;
		appDidEnterForegroundEventFunctionListInitialCapacity = commonReserveSize;

		localeChangedEventFunctionListInitialCapacity = commonReserveSize;
		systemThemeChangeEventFunctionListInitialCapacity = commonReserveSize;

		displayEventFunctionListInitialCapacity = commonReserveSize;
		windowEventFunctionListInitialCapacity = commonReserveSize;

		keyboardDeviceEventFunctionListInitialCapacity = commonReserveSize;
		keyboardEventFunctionListInitialCapacity = commonReserveSize;
		keymapChangeEventFunctionListInitialCapacity = commonReserveSize;
		screenKeyboardEventFunctionListInitialCapacity = commonReserveSize;
		textEditingEventFunctionListInitialCapacity = commonReserveSize;
		textEditingCandidatesEventFunctionListInitialCapacity = commonReserveSize;
		textInputEventFunctionListInitialCapacity = commonReserveSize;

		mouseDeviceEventFunctionListInitialCapacity = commonReserveSize;
		mouseMotionEventFunctionListInitialCapacity = commonReserveSize;
		mouseButtonEventFunctionListInitialCapacity = commonReserveSize;
		mouseWheelEventFunctionListInitialCapacity = commonReserveSize;

		joyAxisEventFunctionListInitialCapacity = commonReserveSize;
		joyBallEventFunctionListInitialCapacity = commonReserveSize;
		joyHatEventFunctionListInitialCapacity = commonReserveSize;
		joyButtonEventFunctionListInitialCapacity = commonReserveSize;
		joyDeviceEventFunctionListInitialCapacity = commonReserveSize;
		joyBatteryEventFunctionListInitialCapacity = commonReserveSize;

		gamepadAxisEventFunctionListInitialCapacity = commonReserveSize;
		gamepadButtonEventFunctionListInitialCapacity = commonReserveSize;
		gamepadDeviceEventFunctionListInitialCapacity = commonReserveSize;
		gamepadTouchpadEventFunctionListInitialCapacity = commonReserveSize;
		gamepadSensorEventFunctionListInitialCapacity = commonReserveSize;

		audioDeviceEventFunctionListInitialCapacity = commonReserveSize;
		touchFingerEventFunctionListInitialCapacity = commonReserveSize;
		touchPinchEventFunctionListInitialCapacity = commonReserveSize;
		cameraEventFunctionListInitialCapacity = commonReserveSize;
		clipboardEventFunctionListInitialCapacity = commonReserveSize;

		dropEventFunctionListInitialCapacity = commonReserveSize;
		sensorEventFunctionListInitialCapacity = commonReserveSize;
		userEventFunctionListInitialCapacity = commonReserveSize;

		penAxisEventFunctionListInitialCapacity = commonReserveSize;
		penButtonEventFunctionListInitialCapacity = commonReserveSize;
		penMotionEventFunctionListInitialCapacity = commonReserveSize;
		penTouchEventFunctionListInitialCapacity = commonReserveSize;
		penProximityEventFunctionListInitialCapacity = commonReserveSize;

		renderTargetsResetEventFunctionListInitialCapacity = commonReserveSize;
		renderDeviceResetEventFunctionListInitialCapacity = commonReserveSize;
		renderDeviceLostEventFunctionListInitialCapacity = commonReserveSize;
	}
}