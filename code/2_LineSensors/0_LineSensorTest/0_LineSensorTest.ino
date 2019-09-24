/** This example shows how to read the raw values from the five
line sensors on the Zumo32U4 Front Sensor Array.  This example is
useful if you are having trouble with the sensors or just want to
characterize their behavior.

The raw (uncalibrated) values are reported to the serial monitor,
and also displayed on the LCD.  The first line of the LCD
displays a bar graph of all five readings.  The upper right
corner shows a an "E" if the IR emitters are being used (the
default) or an "e" if they are not being used.  The second line
displays the raw reading for the currently-selected sensor.

You can press the "A" and "B" buttons to change which sensor is
selected.

You can press the "C" button to toggle whether the IR emitters
are on during the reading.

In order for the second and forth sensors to work, jumpers on the
front sensor array must be installed in order to connect pin 4 to
DN4 and pin 20 to DN2. */

#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4LCD lcd;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4LineSensors lineSensors;

#define NUM_SENSORS 5
uint16_t lineSensorValues[NUM_SENSORS];

uint8_t selectedSensorIndex = 0;

void setup()
{
  lineSensors.initFiveSensors();
}


void loop()
{
  static uint16_t lastSampleTime = 0;

  if ((uint16_t)(millis() - lastSampleTime) >= 100)
  {
    lastSampleTime = millis();

    // Read the line sensors.
    lineSensors.read(lineSensorValues, QTR_EMITTERS_ON);

    lcd.clear();
    lcd.print(selectedSensorIndex);
    lcd.gotoXY(0, 1);
    lcd.print(lineSensorValues[selectedSensorIndex]);
  }

  // If button A is pressed, select the previous sensor.
  if (buttonA.getSingleDebouncedPress())
  {
    selectedSensorIndex = (selectedSensorIndex + NUM_SENSORS - 1) % NUM_SENSORS;
  }

  // If button B is pressed, select the next sensor.
  if (buttonB.getSingleDebouncedPress())
  {
    selectedSensorIndex = (selectedSensorIndex + 1) % NUM_SENSORS;
  }

  
}
