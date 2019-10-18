/* This program displays the value sensed by the front proximity sensor
 *  
 * This demo does not use the dedicated library so you can see what it is doing under the hood
 * 
 * The "problem" here is that the sensor can only return a digital state: 
 * - it is either 0 if something is sensed
 * - or 1 if nothing is sensed
 * 
 * Thus to compute the distance of an object, 
 * we test the state of the sensor for different intensity/birgthness of the infrared LED 
 *  
 * Also, there is only one such sensor in the front of the robot
 * So to get LEFT/RIGHT information, we use two LED, one on the LEFT, one on the RIGHT
 * And we only turn one ON at a time
 *  
 * Another details is that the sensor is responsible to signals at only 38kHZ
 * and it needs to receive a signal for at least 7 to 15 cycles before turning ON.
 * More details in the code bellow
 * 
 * Because of the above, we need to manually deactivate the line sensor led 
 * to not have it polute our reading from the LEFT and RIGHT top leds.
 * This comes from hardware configuration that are usually taken care of in the ain library
 * 
 * See https://pololu.github.io/zumo-32u4-arduino-library/class_zumo32_u4_proximity_sensors.html
 * for the dedicated library
 * Check the FaceTowardOpponent to see how the library can be used:
 * 
 * proxSensors.read();
 * int leftValue = proxSensors.countsFrontWithLeftLeds();
 * int rightValue = proxSensors.countsFrontWithRightLeds();
 * 
 * More about proximity sensor https://www.pololu.com/docs/0J63/3.6
 */
 
#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4LCD lcd;
Zumo32U4ButtonA buttonA;

// Line sensor led pin, with is an IR emitting diode
// We will just turn it off to avoid noisy reading
#define LINE_SENSOR_LED  11

// Proximity sensor PIN
#define FRONT_SENSOR  22

// these are the brightnessLevels levels we will test
// the values correspond to the PWM high state duration relative to the period of the signal (that we set later in the program)
// I choose values arbitrarily and following code I found in the libraries
int brightnessLevels[] = { 1, 2, 4, 15, 32, 55, 85, 120 };
// This simply computes the lenght of the list above.
// We compute the size of brightnessLevels in memory and divide by the size of a single integer element
// So nLevels should be 8 here
int nLevels = sizeof(brightnessLevels) /sizeof(int);

int leftState;
int rightState;
  
void setup()
{
  // Turing off the line sensor LED, set to OUTPUT, and turn to LOW state
  pinMode(LINE_SENSOR_LED, OUTPUT);
  digitalWrite(LINE_SENSOR_LED, LOW);

  // Setting pin mode of proximity sensor to INPUT
  // The INPUT_PULLUP means that by defaut, if nothing is connected to the pin, 
  // then the returned value is 1 (it is pulled towards 1 by default)
  pinMode(FRONT_SENSOR, INPUT_PULLUP);

  lcd.clear();
  lcd.print(F("Press A"));
  buttonA.waitForButton();
  lcd.clear();
}


void loop()
{
  // Go to the origin on screen
  lcd.gotoXY(0, 0);


  // LEFT LED

  // for each level in brightnessLevels
  // we turn the IR LED on
  // we wait a bit so the sensor can react to the light
  // we read the state of the sensor
  // we turn the IR LED off
  // we print the value on the screen
  for (int i = 0; i < nLevels; i++) {
    // We start sending a PWM pulsing signal on the LEFT LED
    // We use the Zumo32U4IRPulses class from the library
    // See the start function in https://github.com/pololu/zumo-32u4-arduino-library/blob/master/Zumo32U4IRPulses.cpp
    // It takes three arguments:
    // - the LED, we need to use their variable for it called: Zumo32U4IRPulses::Left, look for it in https://github.com/pololu/zumo-32u4-arduino-library/blob/master/Zumo32U4IRPulses.h
    // - the brightness level, which is proportional the duty cylce of the PWM. It can not be higher that the period of the signal (which is set by the next parameter)
    // - the period of the signal in a weird unit, see comments in https://github.com/pololu/zumo-32u4-arduino-library/blob/master/Zumo32U4IRPulses.h
    // The interval between consecutive the rising edges of pulses will be (1 + period) / (16 MHz).
    // The default value is 420, which results in a period very close to 38 kHz.
    // Indeed: 16000000 / (420 + 1) = 38.005 kHz
    // That is why we use 420 here, because the sensor reacts only to signal at 38kHZ frequency, the 420 is to set that frequency
    Zumo32U4IRPulses::start(Zumo32U4IRPulses::Left, brightnessLevels[i], 420);

    // Now we need to wait for the sensor to change state if it is receiving the light back
    // We do not wait for the light to come back, become this is much faster that the timescale our processor operates at
    // We wait for the sensor to have the time to react to the light
    // In the library: https://github.com/pololu/zumo-32u4-arduino-library/blob/master/Zumo32U4ProximitySensors.h#L205
    // They explain that, according to the TSSP77038 datasheet, the delay between the start of the
    // IR pulses and the start of the sensor output pulse could be anywhere between 7 cycles /(38 kHz) and 15 cycles /(38 kHz).
    // The default pulse on time of 16/(38 kHz) = 421us guarantees we are not missing output pulses by reading the sensor too soon.
    // This is why we pause for 421us. It is unrelated to the 420 period parameter we used above
    delayMicroseconds(421);

    // we read the sensor
    // we use ! the value just to store it in a way that is easy for a human to interpret
    // 0 for nothing detected
    // 1 for something detected
    leftState = !digitalRead(FRONT_SENSOR);

    // we can now stop the pulse on the IR LED
    Zumo32U4IRPulses::stop();

    // print on lcd
    lcd.print(leftState);
  }

  // Go to the next line
  lcd.gotoXY(0, 1);

  // same as above but for right LED
  for (int i = 0; i < nLevels; i++) {
    Zumo32U4IRPulses::start(Zumo32U4IRPulses::Right, brightnessLevels[i], 420);
    delayMicroseconds(421);
    rightState = !digitalRead(FRONT_SENSOR);
    Zumo32U4IRPulses::stop();
    lcd.print(rightState);
  }
}
