#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4LCD lcd;
Zumo32U4Motors motors;

#define PIN_LEFT_XOR  8

int count;
int previous_state;
int current_state;

void setup()
{
  pinMode(PIN_LEFT_XOR, INPUT);
  
  count = 0;
  previous_state = digitalRead(PIN_LEFT_XOR);
}


void loop()
{
  current_state = digitalRead(PIN_LEFT_XOR);

  if (current_state != previous_state) {
    count += 1;
    previous_state = current_state;
  }

  lcd.gotoXY(0, 0);
  lcd.print(count);
  lcd.gotoXY(0, 1);
  lcd.print(sqrt(pow(10, 4)));
  
//  motors.setSpeeds(75, 0);
//  delay(500);
//  motors.setSpeeds(-75, 0);
//  delay(500);
  
}
