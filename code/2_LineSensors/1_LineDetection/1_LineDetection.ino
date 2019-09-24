/* This example uses the line sensors on the Zumo 32U4 to follow
a black line on a white background, using a PID-based algorithm.
It works decently on courses with smooth, 6" radius curves and
has been tested with Zumos using 75:1 HP motors.  Modifications
might be required for it to work well on different courses or
with different motors.

This demo requires a Zumo 32U4 Front Sensor Array to be
connected, and jumpers on the front sensor array must be
installed in order to connect pin 4 to DN4 and pin 20 to DN2. */

#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4LineSensors lineSensors;
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4LCD lcd;

#define NUM_SENSORS 5
unsigned int lineSensorValues[NUM_SENSORS];
bool lineDetected[NUM_SENSORS];

const uint16_t maxSpeed = 100;

void setup()
{
  lineSensors.initFiveSensors();

  // Wait for button A to be pressed and released.
  lcd.clear();
  lcd.print(F("Press A"));
  lcd.gotoXY(0, 1);
  lcd.print(F("to start"));
  buttonA.waitForButton();
}

void loop()
{
  // Get the position of the line.  Note that we *must* provide
  // the "lineSensorValues" argument to readLine() here, even
  // though we are not interested in the individual sensor
  // readings.
  lineSensors.read(lineSensorValues, QTR_EMITTERS_ON);

  for (uint8_t i = 0; i < NUM_SENSORS; i++) {

    if (lineSensorValues[i] > 500) {
      lineDetected[i] = true;
    } else {
      lineDetected[i] = false;
    }
  } 

  static uint16_t lastSampleTime = 0;

  if ((uint16_t)(millis() - lastSampleTime) >= 100)
  {
    lastSampleTime = millis();
    
    lcd.clear();
    for (uint8_t i = 0; i < NUM_SENSORS; i++) {
      lcd.print(lineDetected[i]);
    }
  }

}
