#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4LCD lcd;

#define PIN_RIGHT_XOR  7
#define PIN_RIGHT_B    23

static volatile bool lastRightA;
static volatile bool lastRightB;
static volatile int16_t countRight;

static void interrupt()
{
    bool newRightB = digitalRead(PIN_RIGHT_B);
    bool newRightA = digitalRead(PIN_RIGHT_XOR) ^ newRightB;

    countRight += (newRightA ^ lastRightB) - (lastRightA ^ newRightB);

    lastRightA = newRightA;
    lastRightB = newRightB;
}

void setup()
{
  pinMode(PIN_RIGHT_B, INPUT);
  pinMode(PIN_RIGHT_XOR, INPUT);

  lastRightB = digitalRead(PIN_RIGHT_B);
  lastRightA = digitalRead(PIN_RIGHT_XOR) ^ lastRightB;
  
  countRight = 0;

  attachInterrupt(digitalPinToInterrupt(PIN_RIGHT_XOR), interrupt, CHANGE);
}


void loop()
{
  lcd.clear();
  lcd.print(countRight);
  delay(100);
}
