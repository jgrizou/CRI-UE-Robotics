#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4LCD lcd;
Zumo32U4ButtonA buttonA;

Zumo32U4Motors motors;
Zumo32U4Encoders encoders;


void setup()
{
  lcd.clear();
  lcd.print(F("Press A"));
  buttonA.waitForButton();
  lcd.clear();
  delay(1000);
}


void loop()
{

  while (encoders.getCountsLeft() < 761) {
    motors.setSpeeds(100, 100);
  }

  lcd.clear();
  lcd.print(encoders.getCountsLeft());
  motors.setSpeeds(0, 0);

  delay(100);
}
