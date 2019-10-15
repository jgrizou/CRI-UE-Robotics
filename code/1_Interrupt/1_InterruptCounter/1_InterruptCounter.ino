#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4LCD lcd;

#define PIN_RIGHT_XOR  7

int count;
  
void interrupt()
{
  count += 1;
}

void setup()
{
  count = 0;
  
  attachInterrupt(digitalPinToInterrupt(PIN_RIGHT_XOR), interrupt, CHANGE);
}


void loop()
{
  lcd.clear();
  lcd.print(count);
  delay(100);
}
