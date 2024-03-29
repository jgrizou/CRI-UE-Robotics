/* This program toggles the motors ON and OFF
 * with a pause in between each toggling event
 */

// Include necessary for using Zumo32u4 libraries
#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4LCD lcd;  // Instanciate the lcd class
Zumo32U4ButtonA buttonA; // Instanciate the buttonA class


// We use #define to give names to each PIN required to move the motors
// See explanation of define at https://www.techonthenet.com/c_language/constants/create_define.php
// See PIN mappping for motors at https://www.pololu.com/docs/0J63/3.3

#define MOTOR_SPEED_RIGHT  9
#define MOTOR_DIR_RIGHT  15

#define MOTOR_SPEED_LEFT 10
#define MOTOR_DIR_LEFT  16

int pause_duration = 100; // this is the duration of the pause, try different values


// the setup function is executed only once
void setup()
{
  // We want to send commands so we set all PINs as OUTPUT
  // See https://www.arduino.cc/reference/en/language/functions/digital-io/pinmode/
  pinMode(MOTOR_SPEED_RIGHT, OUTPUT);
  pinMode(MOTOR_DIR_RIGHT, OUTPUT);
  pinMode(MOTOR_SPEED_LEFT, OUTPUT);
  pinMode(MOTOR_DIR_LEFT, OUTPUT);

  // We set the direction to LOW which is forward
  // See https://www.arduino.cc/reference/en/language/functions/digital-io/digitalwrite/
  digitalWrite(MOTOR_DIR_RIGHT, LOW);
  digitalWrite(MOTOR_DIR_LEFT, LOW);

  lcd.clear();  // clear the lcd 
  lcd.print("Press A");  // ask user to press button A
  buttonA.waitForButton(); // wait for the button A to be pressed
  lcd.clear(); // clear the lcd again
}

// the loop function is executed in an infinite loop
// as soon as we reach the end of the loop() function, it starts again.
void loop()
{

  // Turn both motors ON
  digitalWrite(MOTOR_SPEED_RIGHT, HIGH);
  digitalWrite(MOTOR_SPEED_LEFT, HIGH);

  // pause for some time
  delay(pause_duration);  // see https://www.arduino.cc/reference/en/language/functions/time/delay/
  // you can even do shorter pauses in us
//  delayMicroseconds(pause_duration);  //  see https://www.arduino.cc/reference/en/language/functions/time/delaymicroseconds/

  // Turn both motors OFF
  digitalWrite(MOTOR_SPEED_RIGHT, LOW);
  digitalWrite(MOTOR_SPEED_LEFT, LOW);

  // pause for some time in ms
  // Try changing the duration of this second pause, for example using delay(2*pause_duration);
  // What happens to the speed, why?
  delay(pause_duration);
  // you can even do shorter pauses in us
//  delayMicroseconds(pause_duration);


  // If you do very short pauses of 1us (pause_duration = 1 and use delayMicroseconds(pause_duration) )
  // Uncomment below to try it out
  // The speed of the robot decreases, why?
//  lcd.gotoXY(0, 0); // reset printing position to top-left corner
//  lcd.print(random(100)); // we print random numbers just to be able to see it is plotting very fast different things in each loop
}
