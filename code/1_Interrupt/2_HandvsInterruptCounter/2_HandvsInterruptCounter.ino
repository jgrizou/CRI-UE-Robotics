#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4LCD lcd;
Zumo32U4Motors motors;

#define PIN_RIGHT_XOR  7
#define PIN_LEFT_XOR  8

int count_left;
int count_right;
int previous_state_left;
int current_state_left;

static void interrupt_right()
{
  count_right += 1;
}


void setup()
{
  pinMode(PIN_LEFT_XOR, INPUT);
  
  count_left = 0;
  count_right = 0;
  previous_state_left = digitalRead(PIN_LEFT_XOR);

  attachInterrupt(digitalPinToInterrupt(PIN_RIGHT_XOR), interrupt_right, CHANGE);
}

void loop()
{
  current_state_left = digitalRead(PIN_LEFT_XOR);

  if (current_state_left != previous_state_left) {
    count_left += 1;
    previous_state_left = current_state_left;
  }

  lcd.gotoXY(0, 0);
  lcd.print(count_left);
  lcd.gotoXY(0, 1);
  lcd.print(count_right);
    
  motors.setSpeeds(75, -75);
  delay(500);
  motors.setSpeeds(-75, 75);
  delay(500);
  
}
