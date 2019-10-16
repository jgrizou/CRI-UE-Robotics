/* This program count the number of time PIN 7 changes state using interruption
 * PIN 7 is connected to the HALL effect sensor of the RIGHT motor
 * 
 * We use interrupt in this demo
 */
 
#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4LCD lcd;
Zumo32U4Motors motors;

#define PIN_RIGHT_SENSOR  7

int count;

void setup()
{
  // initialise count to 0 at start
  count = 0;

  // See https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
  // we tell the processor to initiate an interrupt worker that:
  // - monitor constantly PIN_RIGHT_SENSOR, we need to use digitalPinToInterrupt(PIN_RIGHT_SENSOR) which is a nice helper from Arduino to do that
  // - call the function on_interrupt() (see below the loop function) when it sees a CHANGE on PIN_RIGHT_SENSOR 
  attachInterrupt(digitalPinToInterrupt(PIN_RIGHT_SENSOR), on_interrupt, CHANGE);
}

void loop()
{
  // we simply print count
  lcd.gotoXY(0, 0);
  lcd.print(count);

  // This time we can move the robot and the counter does not fail
  motors.setSpeeds(75, -75);
  delay(500);
  motors.setSpeeds(-75, 75);
  delay(500);
}

// the on_interrupt() function is called automatically using the interrupt mechanism 
// that we defined in setup using the attachInterrupt() function
//
void on_interrupt()
{
  count += 1;

// This function need to be very quick to execute because it can be called hundreds of times per seconds
// If you do something too time consuming, like waiting, or printing on the screen, your program might stop working or miss events.
}
