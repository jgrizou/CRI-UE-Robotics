/* This program uses the line detected information to follow the line
 *  
 *  The ligical is as follows:
 *  - if the line is centered according tot he robot, go straight
 *  - if the line is a bit on the right, turn right
 *  - if the line is a bit on the left, turn left
 *  
 * WARNING: You need to place the jumper on the bottom PCB on the DN4 and DN2 position.
 * See https://www.pololu.com/docs/0J63/3.5
 * 
 * We use the library Zumo32U4LineSensors
 * See https://pololu.github.io/zumo-32u4-arduino-library/class_zumo32_u4_line_sensors.html
 */

#include <Wire.h>
#include <Zumo32U4.h>


Zumo32U4LCD lcd;
Zumo32U4ButtonA buttonA;
Zumo32U4Motors motors;
Zumo32U4LineSensors lineSensors;

#define NUM_SENSORS 5
int lineSensorValues[NUM_SENSORS];

int lineDetectionThreshold = 500;
bool lineDetected[NUM_SENSORS];

// default speed of the motors
//useful when debugging you can make it slow to understand the behavior better
int motorSpeed = 200; 

int lastSampleTime = 0;

void setup()
{
  // init sensors
  lineSensors.initFiveSensors();

  // Wait for button A to be pressed and released.
  lcd.clear();
  lcd.print(F("Press A"));
  lcd.gotoXY(0, 1);
  lcd.print(F("to start"));
  buttonA.waitForButton();
  lcd.clear();
}

void loop()
{
  // read sensors
  lineSensors.read(lineSensorValues, QTR_EMITTERS_ON);

  // convert to boolean, line or no line
  for (int i = 0; i < NUM_SENSORS; i++) {
    if (lineSensorValues[i] > lineDetectionThreshold) {
      lineDetected[i] = true;
    } else {
      lineDetected[i] = false;
    }
  } 

  // we print 0 if there is not line, 1 if a line, for each sensor in order
  lcd.gotoXY(0,0);
  for (int i = 0; i < NUM_SENSORS; i++) {
    lcd.print(lineDetected[i]);
  }

  // the feedback control starts here

  // if the middle sensor is activated
  if (lineDetected[2]) {
    // go straight
    motors.setSpeeds(motorSpeed, motorSpeed);

  } else {
    // middle sensor not activated

    // and left sensor activated
    if (lineDetected[1]) {
      // turn left
      motors.setSpeeds(-motorSpeed, motorSpeed);
    } else if (lineDetected[3]) {
      // and right sensor activated
      // turn right
      motors.setSpeeds(motorSpeed, -motorSpeed);
    }
  }
}
