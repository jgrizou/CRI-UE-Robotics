#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4LCD lcd;
Zumo32U4ButtonA buttonA;
Zumo32U4Motors motors;
L3G gyro;

void setup()
{
  Wire.begin();
  gyro.init();
  // 800 Hz output data rate,
  // low-pass filter cutoff 100 Hz
  gyro.writeReg(L3G::CTRL1, 0b11111111);
  // 2000 dps full scale
  gyro.writeReg(L3G::CTRL4, 0b00100000);
  // High-pass filter disabled
  gyro.writeReg(L3G::CTRL5, 0b00000000);
}


void loop()
{
  gyro.read();
  
  lcd.clear();
  lcd.print(gyro.g.z);
  delay(100);
}
