/* This program compares the two method to count the number of state change of a sensor
 *  
 *  The hand method fails if we try to do too many things in the loop
 *  The interrupt method never fails  
 */

#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4LCD lcd;
Zumo32U4Motors motors;

#define PIN_RIGHT_SENSOR  7
#define PIN_LEFT_SENSOR  8

int count_left;
int previous_state_left;
int current_state_left;

int count_right;

void interrupt_right()
{
  count_right += 1;
}

void setup()
{
  pinMode(PIN_LEFT_SENSOR, INPUT);
  count_left = 0;
  previous_state_left = digitalRead(PIN_LEFT_SENSOR);

  count_right = 0;
  attachInterrupt(digitalPinToInterrupt(PIN_RIGHT_SENSOR), interrupt_right, CHANGE);
}

void loop()
{

  // manual counting
  current_state_left = digitalRead(PIN_LEFT_SENSOR);

  if (current_state_left != previous_state_left) {
    count_left += 1;  
  }
  
  previous_state_left = current_state_left;

  // print left counter on top line
  lcd.gotoXY(0, 0);
  lcd.print("L: ");
  lcd.print(count_left);
  // print right counter on bottom line
  lcd.gotoXY(0, 1);
  lcd.print("R: ");
  lcd.print(count_right);

  // The hand counter and the interrupt will vary greatly in accuracy if you do something else in the loop

  // use for example delay(50) to play by hand
  delay(50);

  // turn on motors to see more drastic effects.
//  motors.setSpeeds(75, 75);
//  delay(500);
//  motors.setSpeeds(-75, -75);
//  delay(500);
}
