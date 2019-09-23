#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4LCD lcd;
Zumo32U4ButtonA buttonA;

#define FRONT_SENSOR  22
#define LINE_SENSOR_LED  11

void setup()
{
  pinMode(LINE_SENSOR_LED, OUTPUT);
  digitalWrite(LINE_SENSOR_LED, LOW);

  pinMode(FRONT_SENSOR, INPUT_PULLUP);
    
  lcd.clear();
  lcd.print(F("Press A"));
  buttonA.waitForButton();
  lcd.clear();
}


void loop()
{
  lcd.clear();

  const static uint16_t brightnessLevels[] = { 1, 2, 4, 15, 32, 55, 85, 120 };
  static int nLevels = sizeof(brightnessLevels) /sizeof(uint16_t);

  for (uint8_t i = 0; i < nLevels; i++) {
    Zumo32U4IRPulses::start(Zumo32U4IRPulses::Left, brightnessLevels[i], 420);
    delayMicroseconds(421);
    lcd.print(digitalRead(FRONT_SENSOR));
    Zumo32U4IRPulses::stop();
  }

  // Go to the next line
  lcd.gotoXY(0, 1);
  
  for (uint8_t i = 0; i < nLevels; i++) {
    Zumo32U4IRPulses::start(Zumo32U4IRPulses::Right, brightnessLevels[i], 420);
    delayMicroseconds(421);
    lcd.print(digitalRead(FRONT_SENSOR));
    Zumo32U4IRPulses::stop();
  }
  
  delay(100);
}
