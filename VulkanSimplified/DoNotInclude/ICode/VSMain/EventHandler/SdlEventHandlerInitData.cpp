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

		displayEventFunctionListInitialCapacity = commonReserveSize;
		windowEventFunctionListInitialCapacity = commonReserveSize;

		keyboardEventFunctionListInitialCapacity = commonReserveSize;
		keymapChangeEventFunctionListInitialCapacity = commonReserveSize;
		textEditingEventFunctionListInitialCapacity = commonReserveSize;
		textInputEventFunctionListInitialCapacity = commonReserveSize;

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
		clipboardEventFunctionListInitialCapacity = commonReserveSize;

		dropEventFunctionListInitialCapacity = commonReserveSize;
		sensorEventFunctionListInitialCapacity = commonReserveSize;
		userEventFunctionListInitialCapacity = commonReserveSize;

		renderTargetsResetEventFunctionListInitialCapacity = commonReserveSize;
		renderDeviceResetEventFunctionListInitialCapacity = commonReserveSize;
	}
}