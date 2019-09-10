#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4LCD lcd;
Zumo32U4ButtonA buttonA;
Zumo32U4Motors motors;
L3G gyro;

unsigned long current_measured_time;
unsigned long last_measured_time;
unsigned long dt;

int offset_gyro;
int current_gyro;

double delta_angle;
double current_angle;


// The conversion from gyro digits to
// degrees per second (dps) is determined by the sensitivity of
// the gyro: 0.07 degrees per second per digit.
double convertion_ratio = 0.07 / 1000000;


const int maxSpeed = 200;
int target_angle;
int error_angle;
int turnSpeed;



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


  lcd.clear();
  lcd.print(F("Press A"));
  buttonA.waitForButton();
  
  // Turn on the yellow LED in case the LCD is not available.
  ledYellow(1);

  // Delay to give the user time to remove their finger.
  lcd.clear();
  lcd.print(F("Cal Gyro"));
  delay(1000);

  // Calibrate the gyro.
  int total = 0;
  int n_samples = 1000;
  for (int i = 0; i < n_samples; i++)
  {
    // Wait for new data to be available, then read it.
    while(!gyro.readReg(L3G::STATUS_REG) & 0x08);
    gyro.read();

    // Add the Z axis reading to the total.
    total += gyro.g.z;
  }
  ledYellow(0);
  offset_gyro = total / n_samples;


  //
  current_angle = 0;
  target_angle = current_angle;
  gyro.read();
  last_measured_time = micros();
}


void loop()
{
  gyro.read();
  current_gyro = gyro.g.z - offset_gyro;

  current_measured_time = micros();
  dt = current_measured_time - last_measured_time;
  last_measured_time = current_measured_time;
  
  delta_angle = (double)dt * (double)current_gyro * convertion_ratio;
  current_angle += delta_angle;


  error_angle = current_angle - target_angle;
  turnSpeed = -error_angle * 100 - current_gyro/20;
  turnSpeed = constrain(turnSpeed, -maxSpeed, maxSpeed);
  motors.setSpeeds(-turnSpeed, turnSpeed);

  
  static uint16_t lastSampleTime = 0;
  if ((uint16_t)(millis() - lastSampleTime) >= 100)
  {
    lastSampleTime = millis();
    lcd.clear();
    lcd.gotoXY(0, 0);
    lcd.print(current_angle);
    lcd.gotoXY(0, 1);
    lcd.print(error_angle);
  }  
}
