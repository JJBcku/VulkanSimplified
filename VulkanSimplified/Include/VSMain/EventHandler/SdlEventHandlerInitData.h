#pragma once

namespace VulkanSimplified
{
	struct SdlEventHandlerInitData
	{
		size_t quitEventFunctionListInitialCapacity;

		size_t appTerminatingEventFunctionListInitialCapacity;
		size_t appLowMemoryEventFunctionListInitialCapacity;
		size_t appWillEnterBackgroundEventFunctionListInitialCapacity;
		size_t appDidEnterBackgroundEventFunctionListInitialCapacity;
		size_t appWillEnterForegroundEventFunctionListInitialCapacity;
		size_t appDidEnterForegroundEventFunctionListInitialCapacity;

		size_t localeChangedEventFunctionListInitialCapacity;

		size_t displayEventFunctionListInitialCapacity;
		size_t windowEventFunctionListInitialCapacity;

		size_t keyboardEventFunctionListInitialCapacity;
		size_t keymapChangeEventFunctionListInitialCapacity;
		size_t textEditingEventFunctionListInitialCapacity;
		size_t textInputEventFunctionListInitialCapacity;

		size_t mouseMotionEventFunctionListInitialCapacity;
		size_t mouseButtonEventFunctionListInitialCapacity;
		size_t mouseWheelEventFunctionListInitialCapacity;

		size_t joyAxisEventFunctionListInitialCapacity;
		size_t joyBallEventFunctionListInitialCapacity;
		size_t joyHatEventFunctionListInitialCapacity;
		size_t joyButtonEventFunctionListInitialCapacity;
		size_t joyDeviceEventFunctionListInitialCapacity;
		size_t joyBatteryEventFunctionListInitialCapacity;

		size_t gamepadAxisEventFunctionListInitialCapacity;
		size_t gamepadButtonEventFunctionListInitialCapacity;
		size_t gamepadDeviceEventFunctionListInitialCapacity;
		size_t gamepadTouchpadEventFunctionListInitialCapacity;
		size_t gamepadSensorEventFunctionListInitialCapacity;

		size_t audioDeviceEventFunctionListInitialCapacity;
		size_t touchFingerEventFunctionListInitialCapacity;
		size_t clipboardEventFunctionListInitialCapacity;

		size_t dropEventFunctionListInitialCapacity;
		size_t sensorEventFunctionListInitialCapacity;
		size_t userEventFunctionListInitialCapacity;

		size_t renderTargetsResetEventFunctionListInitialCapacity;
		size_t renderDeviceResetEventFunctionListInitialCapacity;

		SdlEventHandlerInitData(size_t commonReserveSize = 0);
	};
}
