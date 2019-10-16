/* Preivous program could not get the direction of the rotation, the counter kept increasing
 *  
 *  This program counts both up and down according to the direction of rotation, 
 *  so we have an aboslute rotation position of the motor.
 *  
 *  To do so, we need to have two sensors and we detect the ordering in state change for each sensors
 *  In one direction sensor A is triggered before sensor B
 *  In the other direction, it is B before A
 *  
 *  We do it only for the RIGHT motor only
 *  
 *  See https://www.pololu.com/docs/0J63/3.4 for how the encoder is mapped out on the PIN
 *  Notice that, because the processor is limited in PIN that can do interrupt, 
 *  they use a XOR function to be able to only use one interrupt PIN for the two sensors A and B
 */

#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4LCD lcd;
Zumo32U4Motors motors;

#define PIN_RIGHT_XOR  7
#define PIN_RIGHT_B    23

int count_right;

// last values of A and B sensors
bool last_right_A;
bool last_right_B;

// new values of A and B sensors
bool new_right_B;
bool new_right_A;

// define interrupt function
void on_interrupt()
{
    // see https://www.pololu.com/docs/0J63/3.4 to understand the signals A and B
    
    // read B directly
    new_right_B = digitalRead(PIN_RIGHT_B);
    // reconstruct A from PIN_RIGHT_XOR and B. 
    // We follow the logic that (A^B)^B = A, where (A^B) = digitalRead(PIN_RIGHT_XOR)
    new_right_A = digitalRead(PIN_RIGHT_XOR) ^ new_right_B;

    // fancy way to recover the direction
    // (new_right_A ^ last_right_B) is 1 if the motor turns forward, and 0 otherwise
    // (last_right_A ^ new_right_B) is 0 if the motor turns forward, and 1 otherwise    
    count_right += (new_right_A ^ last_right_B) - (last_right_A ^ new_right_B);

    // update last values with current values to get ready for next time on_interrupt() is called
    last_right_A = new_right_A;
    last_right_B = new_right_B;
}

void setup()
{
  // pinMode is input as we sense
  pinMode(PIN_RIGHT_B, INPUT);
  pinMode(PIN_RIGHT_XOR, INPUT);

  // init last values, see on_interrupt() for explanation
  last_right_B = digitalRead(PIN_RIGHT_B);
  last_right_A = digitalRead(PIN_RIGHT_XOR) ^ last_right_B;

  // init counter to 0
  count_right = 0;

  // inittialise the interrupt
  attachInterrupt(digitalPinToInterrupt(PIN_RIGHT_XOR), on_interrupt, CHANGE);
}


void loop()
{
  // We do not have to do anything in the loop, we can just print
  // Try moving the right wheel to see the counter going up and down
  lcd.gotoXY(0, 0);
  lcd.print(count_right);
}
