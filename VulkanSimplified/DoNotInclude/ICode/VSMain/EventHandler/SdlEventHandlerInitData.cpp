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

		keyboardEventFunctionListInitialCapacity = commonReserveSize;
		textEditingEventFunctionListInitialCapacity = commonReserveSize;
		textInputEventFunctionListInitialCapacity = commonReserveSize;
		keymapChangeEventFunctionListInitialCapacity = commonReserveSize;

		keyboardDeviceEventFunctionListInitialCapacity = commonReserveSize;
		textEditingCandidatesEventFunctionListInitialCapacity = commonReserveSize;
		screenKeyboardEventFunctionListInitialCapacity = commonReserveSize;

		mouseMotionEventFunctionListInitialCapacity = commonReserveSize;
		mouseButtonEventFunctionListInitialCapacity = commonReserveSize;
		mouseWheelEventFunctionListInitialCapacity = commonReserveSize;
		mouseDeviceEventFunctionListInitialCapacity = commonReserveSize;

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

		touchFingerEventFunctionListInitialCapacity = commonReserveSize;
		touchPinchEventFunctionListInitialCapacity = commonReserveSize;
		clipboardEventFunctionListInitialCapacity = commonReserveSize;

		dropEventFunctionListInitialCapacity = commonReserveSize;
		audioDeviceEventFunctionListInitialCapacity = commonReserveSize;
		sensorEventFunctionListInitialCapacity = commonReserveSize;

		penProximityEventFunctionListInitialCapacity = commonReserveSize;
		penTouchEventFunctionListInitialCapacity = commonReserveSize;
		penButtonEventFunctionListInitialCapacity = commonReserveSize;
		penMotionEventFunctionListInitialCapacity = commonReserveSize;
		penAxisEventFunctionListInitialCapacity = commonReserveSize;

		cameraEventFunctionListInitialCapacity = commonReserveSize;
		renderTargetsResetEventFunctionListInitialCapacity = commonReserveSize;
		renderDeviceResetEventFunctionListInitialCapacity = commonReserveSize;
		renderDeviceLostEventFunctionListInitialCapacity = commonReserveSize;

		userEventFunctionListInitialCapacity = commonReserveSize;
	}
}