# Automatic Watering System

This is an automatic watering system project for Arduino. The project includes a water pump, a button, an LED, and a scheduler for automatic watering.

## Features

* The watering interval and duration can be set in the code.
* The button supports two types of presses: short press (to turn on/off the scheduler) and long press (to start watering immediately).
* If the scheduler is on, the LED will blink every 30 seconds for one second.

## Hardware Setup

* Connect the water pump to pin 5 of the Arduino.
* Connect the button to pin 10 of the Arduino.
* Connect the LED to pin 9 of the Arduino.

## Code Explanation

* `MAIN_PERIOD` and `BUTTON_PERIOD` are the periods for checking the main loop and the button state, respectively.
* `pumpPin`, `buttonPin`, and `statusLedPin` are the pins for the water pump, button, and LED, respectively.
* `BUTTON_PRESSED_LONG_DURATION_MILLIS`, `BUTTON_PRESSED_SHORT_DURATION_MILLIS`, and `BUTTON_PRESSED_DELAY` are the durations for long press, short press, and button press delay, respectively.
* `LED_BLINK_PERIOD` and `LED_BLINK_DURATION` are the periods for LED blinking and LED blinking duration, respectively.
* `WATERING_DURATION_MILLIS` is the duration for each watering.
* `wateringIntervalMillis` is the interval between each watering.
* The timers are used to keep track of the time for each event.
* The flags are used to indicate the state of the system.
* The methods are used to handle the events in the system.

## Usage

1. Upload the code to the Arduino.
2. Set the watering interval and duration in the code.
3. Turn on the system.
4. Press the button shortly to turn on/off the scheduler.
5. Press the button for a long time to start watering immediately.
6. The LED will blink every 30 seconds for one second if the scheduler is on.

## Note

* The default watering interval is set to two days (2 \* 86400000 milliseconds).
* The default watering duration is set to 9 seconds (1000 \* 9 milliseconds).

## License

This project is open-source and licensed under the [MIT License](https://opensource.org/licenses/MIT).

Feel free to modify and distribute the project as you like.
