#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4LCD lcd;
Zumo32U4ButtonA buttonA;
Zumo32U4Motors motors;

#define FRONT_SENSOR  22
#define RIGHT_SENSOR  4
#define LEFT_SENSOR  20
#define LINE_SENSOR_LED  11

int brightnessLevel = 2;
int motorSpeed = 75;
bool front_left_led_state;
bool front_right_led_state;
bool left_left_led_state;
bool right_right_led_state;

void setup()
{
  pinMode(LINE_SENSOR_LED, OUTPUT);
  digitalWrite(LINE_SENSOR_LED, LOW);

  pinMode(FRONT_SENSOR, INPUT_PULLUP);
  pinMode(RIGHT_SENSOR, INPUT_PULLUP);
  pinMode(LEFT_SENSOR, INPUT_PULLUP);
    
  lcd.clear();
  lcd.print(F("Press A"));
  buttonA.waitForButton();
  lcd.clear();
}


void loop()
{
  Zumo32U4IRPulses::start(Zumo32U4IRPulses::Left, brightnessLevel, 420);
  delayMicroseconds(421);
  front_left_led_state = digitalRead(FRONT_SENSOR);
  left_left_led_state = digitalRead(LEFT_SENSOR);
  Zumo32U4IRPulses::stop();

  Zumo32U4IRPulses::start(Zumo32U4IRPulses::Right, brightnessLevel, 420);
  delayMicroseconds(421);
  front_right_led_state = digitalRead(FRONT_SENSOR);
  right_right_led_state = digitalRead(RIGHT_SENSOR);
  Zumo32U4IRPulses::stop();

  lcd.clear();
  lcd.print(front_left_led_state);
  lcd.print(left_left_led_state);
  lcd.gotoXY(0, 1);
  lcd.print(front_right_led_state);
  lcd.print(right_right_led_state);

  if (!left_left_led_state) {
    motors.setSpeeds(-motorSpeed, motorSpeed);
  }
  else if (!right_right_led_state) {
    motors.setSpeeds(motorSpeed, -motorSpeed);
  }
  else if (!front_left_led_state & front_right_led_state) {
    motors.setSpeeds(-motorSpeed/2, motorSpeed);
  }
  else if (front_left_led_state & !front_right_led_state) {
    motors.setSpeeds(motorSpeed, -motorSpeed/2); 
  }
  else if (!front_left_led_state & !front_right_led_state) {
    motors.setSpeeds(motorSpeed, motorSpeed);
  }
  else {
     motors.setSpeeds(0, 0);
  }

  
  delay(100);
}
