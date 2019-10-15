#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4LineSensors lineSensors;
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4LCD lcd;

#define NUM_SENSORS 5
int lineSensorValues[NUM_SENSORS];
bool lineDetected[NUM_SENSORS];

int lastSampleTime = 0;
int maxSpeed = 100;

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
  lineSensors.read(lineSensorValues, QTR_EMITTERS_ON);

  for (int i = 0; i < NUM_SENSORS; i++) {

    if (lineSensorValues[i] > 500) {
      lineDetected[i] = true;
    } else {
      lineDetected[i] = false;
    }
  } 

  if ((int)(millis() - lastSampleTime) >= 100)
  {
    lastSampleTime = millis();
    
    lcd.clear();
    for (int i = 0; i < NUM_SENSORS; i++) {
      lcd.print(lineDetected[i]);
    }
  }

}
