#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4LCD lcd;
Zumo32U4ButtonA buttonA;

#define YELLOW_LED  13

void setup()
{
  pinMode(YELLOW_LED, OUTPUT);

  lcd.clear();
  lcd.print(F("Press A"));
  buttonA.waitForButton();
  lcd.clear();
}


void loop()
{
  for (uint8_t i = 0; i < 255; i++) {
    analogWrite(YELLOW_LED, i);
    delay(1);
  } 

  for (uint8_t i = 255; i > 0; i--) {
    analogWrite(YELLOW_LED, i);
    delay(1);
  } 

}
