#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4LCD lcd;
Zumo32U4ButtonA buttonA;

#define MOTOR_SPEED_RIGHT  9
#define MOTOR_DIR_RIGHT  15

#define MOTOR_SPEED_LEFT 10
#define MOTOR_DIR_LEFT  16

int high_muliptlier = 100;
int low_muliptlier = 100;
int pause_us = 1;

void setup()
{
  pinMode(MOTOR_SPEED_RIGHT, OUTPUT);
  pinMode(MOTOR_DIR_RIGHT, OUTPUT);
  pinMode(MOTOR_SPEED_LEFT, OUTPUT);
  pinMode(MOTOR_DIR_LEFT, OUTPUT);

  digitalWrite(MOTOR_DIR_RIGHT, LOW);
  digitalWrite(MOTOR_DIR_LEFT, LOW);

  lcd.clear();
  lcd.print(F("Press A"));
  buttonA.waitForButton();
  lcd.clear();
}


void loop()
{
  digitalWrite(MOTOR_SPEED_RIGHT, HIGH);
  digitalWrite(MOTOR_SPEED_LEFT, HIGH);
  delayMicroseconds(high_muliptlier * pause_us);
  digitalWrite(MOTOR_SPEED_RIGHT, LOW);
  digitalWrite(MOTOR_SPEED_LEFT, LOW);
  delayMicroseconds(low_muliptlier * pause_us);

//  lcd.print(random(100));
}
