/* This program displays the value sensed by each of the line sensors
 *  
 * Because the screen is of limited size, we only print one value at a time and use the 
 *  
 * WARNING: You need to place the jumper on the bottom PCB on the DN4 and DN2 position.
 * See https://www.pololu.com/docs/0J63/3.5
 * 
 * We use the library Zumo32U4LineSensors
 * See https://pololu.github.io/zumo-32u4-arduino-library/class_zumo32_u4_line_sensors.html
 */

#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4LCD lcd;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4LineSensors lineSensors; // this is the tools for reading the sensors values

// there is 5 sensors, we just #define NUM_SENSORS 5 to not have to use directly the number 5 all along the program
#define NUM_SENSORS 5

// this creates a list of 5 integer
// see https://www.tutorialspoint.com/cplusplus/cpp_arrays.htm
// we are going to store the sensors values in that list
int lineSensorValues[NUM_SENSORS];

// this is to keep track of which sensor we display on the lcd screen
int selectedSensorIndex = 0;

// we will only read sensors value every 100ms
// this variable is to store the time we last read the sensors
int lastSampleTime = 0;

void setup()
{
  // this initialize the sensors and various memory space used by the library
  // see https://pololu.github.io/zumo-32u4-arduino-library/class_zumo32_u4_line_sensors.html#a3873997ed35fbc1c6c57411f6cee1f2d
  lineSensors.initFiveSensors();
}


void loop()
{

  // once 100ms have elapsed, we enter this if statement
  // we do that because we need to keep monitoring the buttons below, so we need the loop to be as fats a possible
  // however if we go too fast we cannot see what is printed on the screen
  // that is why we only read and print on the screen every 100 ms, but check the buttons state all the time
  if ((millis() - lastSampleTime) >= 100)
  {

    // update lastSampleTime to now, so we enter this function again in 100ms
    lastSampleTime = millis();

    // Read all line sensors and put the values in lineSensorValues
    // This turns the emitters on at the same time
    lineSensors.read(lineSensorValues, QTR_EMITTERS_ON);
    // for curious students, the actual function that reads from the sensors is
    // https://github.com/pololu/zumo-32u4-arduino-library/blob/master/QTRSensors.cpp#L424
    // The reason why the values are low for white and high for black is that 
    // our measure is the time it takes for the sensor to come back to the state LOW after being pulled to HIGH
    // this depends on the amount of infrared light coming back to the sensor
    // which depends on the color of the surface, 
    // black surfaces absorb more light, so less is light is coming back to the sensor, 
    // so it takes more time to go back to a LOW state
    //
    // from https://www.pololu.com/docs/0J63/3.5: 
    // The reflectance sensors operate on the same principles as our QTR-1RC sensor: 
    // the AVR uses an I/O line to drive the sensor output high, and then measures the time for the output voltage to decay.


    // We print the sensor value currently selected
    lcd.clear();
    lcd.print("Index: ");
    lcd.print(selectedSensorIndex);
    lcd.gotoXY(0, 1);
    lcd.print("Val:");
    lcd.print(lineSensorValues[selectedSensorIndex]);
  }

  // If button A is pressed, select the previous sensor.
  if (buttonA.getSingleDebouncedPress())
  {
    selectedSensorIndex = (selectedSensorIndex + NUM_SENSORS - 1) % NUM_SENSORS;
    // if curious read more about modulo: https://en.wikipedia.org/wiki/Modulo_operation
    // and in c++ it is the % operator: https://www.cprogramming.com/tutorial/modulus.html
  }

  // If button B is pressed, select the next sensor.
  if (buttonB.getSingleDebouncedPress())
  {
    selectedSensorIndex = (selectedSensorIndex + 1) % NUM_SENSORS;
  }

  
}
