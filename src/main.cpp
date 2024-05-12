#include <Arduino.h>

#define MAIN_PERIOD 1
#define BUTTON_PERIOD 20

#define pumpPin 5
#define buttonPin 10
#define statusLedPin 9

#define BUTTON_PRESSED_LONG_DURATION_MILLIS 1000 * 3
#define BUTTON_PRESSED_SHORT_DURATION_MILLIS 100
#define BUTTON_PRESSED_DELAY 1000

#define LED_BLINK_PERIOD 1000 * 30
#define LED_BLINK_DURATION 1000

#define WATERING_DURATION_MILLIS 1000 * 9

unsigned long wateringIntervalMillis = 2 * 86400000;

// TIMERS
uint32_t mainTimer = 0;
uint32_t buttonCheckTimer = 0;
uint32_t wateringIntervalTimer = 0;
uint32_t wateringDurationTimer = 0;
uint32_t buttonPressedLongTimer = 0;
uint32_t buttonDelayTimer = 0;
uint32_t ledBLinkTimer = 0;
uint32_t ledBLinkDurationTimer = 0;

// FLAGS
bool isWateringLogicOn = false;
bool isWateringInProgress = false;
bool isButtonPressedLongStartCounter = false;
bool isLedEnabled = false;

// METHODS
void enableWatering();
void disableWatering();
void startWatering();
void stopWatering();
void onButtonLongPress();
void onButtonShortPress();

void setup()
{
  Serial.begin(9600);
  Serial.println("Start programm");
  Serial.print("Watering duration. ");
  Serial.println(WATERING_DURATION_MILLIS);
  Serial.print("Watering interval ");
  Serial.println(wateringIntervalMillis);
  pinMode(pumpPin, OUTPUT);
  pinMode(statusLedPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop()
{
  long currentMillis = millis();
  if (currentMillis - mainTimer >= MAIN_PERIOD)
  {
    if ((currentMillis - buttonCheckTimer) >= BUTTON_PERIOD)
    {
      bool isButtonPressed = digitalRead(buttonPin) == 0;
      if (isButtonPressed && isButtonPressedLongStartCounter == false && currentMillis - buttonDelayTimer >= BUTTON_PRESSED_DELAY)
      {
        isButtonPressedLongStartCounter = true;
        buttonPressedLongTimer = currentMillis;
      }
      if (isButtonPressed == false && isButtonPressedLongStartCounter)
      {
        buttonDelayTimer = currentMillis;
        uint32_t buttonWasPressed = currentMillis - buttonPressedLongTimer;
        if (buttonWasPressed >= BUTTON_PRESSED_LONG_DURATION_MILLIS)
        {
          onButtonLongPress();
        }
        else
        {
          onButtonShortPress();
        }
        isButtonPressedLongStartCounter = false;
      }
      buttonCheckTimer = currentMillis;
    }

    if (isWateringLogicOn && isWateringInProgress == false && currentMillis - wateringIntervalTimer >= wateringIntervalMillis)
    {
      startWatering();
    }
    if (isWateringInProgress && currentMillis - wateringDurationTimer >= WATERING_DURATION_MILLIS)
    {
      stopWatering();
    }

    if (isWateringLogicOn && currentMillis - ledBLinkTimer >= LED_BLINK_PERIOD)
    {
      digitalWrite(statusLedPin, HIGH);
      ledBLinkDurationTimer = currentMillis;
      isLedEnabled = true;
      ledBLinkTimer = currentMillis;
    }
    if (isLedEnabled && currentMillis - ledBLinkDurationTimer >= LED_BLINK_DURATION)
    {
      isLedEnabled = false;
      digitalWrite(statusLedPin, LOW);
    }
    mainTimer = currentMillis;
  }
}

void onButtonShortPress()
{
  Serial.println("SHORT PRESS");
  if (isWateringLogicOn == false)
  {
    enableWatering();
  }
  else
  {
    disableWatering();
  }
}
void enableWatering()
{
  Serial.println("Enable watering");
  wateringIntervalTimer = millis();
  isWateringLogicOn = true;
}

void disableWatering()
{
  Serial.println("Disable watering");
  isWateringLogicOn = false;
  stopWatering();
}

void onButtonLongPress()
{
  Serial.println("LONG PRESS");
  startWatering();
}

void startWatering()
{
  Serial.println("Start watering");
  digitalWrite(pumpPin, HIGH);
  wateringDurationTimer = millis();
  isWateringInProgress = true;
}

void stopWatering()
{
  Serial.println("Stop watering");
  digitalWrite(pumpPin, LOW);
  wateringIntervalTimer = millis();
  isWateringInProgress = false;
}