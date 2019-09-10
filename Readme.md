Sumo competition

https://www.youtube.com/watch?v=GIv4jWB2158


Library to help interface with the on-board hardware of the Pololu Zumo 32U4 robot.

https://github.com/pololu/zumo-32u4-arduino-library


User Guide

https://www.pololu.com/docs/0J63


Install libraries: https://github.com/pololu/zumo-32u4-arduino-library#installing-the-library
Install board: https://www.pololu.com/docs/0J63/5.2


## Robot discovery

How does it works
Buttons
Screen
Buzzer
Led


## Hand coding motion - PWM

Explain how motors works
Explain motor control (use a motor found in class)
Explain H-bridge
Explain PWM

- pin connection: https://www.pololu.com/docs/0J63/3.3
- delayus: https://www.arduino.cc/reference/en/language/functions/time/delaymicroseconds/

Explain PWM are hardware dedicated to do that because that would take your full program. Try printing something on the screen for example: lcd.print(random(100)).

- library: https://pololu.github.io/zumo-32u4-arduino-library/class_zumo32_u4_motors.html


## PWM work with LED too

Same as motors!

## Proximity sensors

Explain how it works
Sensor is boolean (HIGH or LOW)
So we modulate the light
Light need to be at 38kHz
Intensity is done using PWM


Zumo32U4IRPulses::start(Zumo32U4IRPulses::Left, brightnessLevels[i], 420);

/** \brief Starts emitting IR pulses.
 *
 * \param direction Specifies which set of LEDs to turn on.
 * \param brightness A number that specifies
 *   how long each pulse is.  The pulse length will be
 *   (1 + brightness) / (16 MHz).
 *   If \c brightness is greater than or equal to \c period, then the LEDs
 *   will just be on constantly.
 * \param period A number that specifies the frequency of the pulses.
 *   The interval between consecutive the rising edges of pulses will be
 *   (1 + period) / (16 MHz).
 *   The default value is 420, which results in a period very close to
 *   38 kHz. */



/** The default frequency is 16000000 / (420 + 1) = 38.005 kHz */
static const uint16_t defaultPeriod = 420;


delayMicroseconds(421);

/** \brief The default duration of the bursts of infrared pulses emitted, in
 * microseconds.
 *
 * According to the TSSP77038 datasheet, the delay between the start of the
 * IR pulses and the start of the sensor output pulse could be anywhere
 * between 7/(38 kHz) and 15/(38 kHz).
 *
 * The default pulse on time of 16/(38 kHz) = 421 us guarantees we are not
 * missing output pulses by reading the sensor too soon.

Apply this with motors
Obstacle Avoidance + Follow


## Line Following

TODO

## Hand coding encoders

Explain how hall effect sensors work
Explain principle of encoders

Use piece of paper showing only two windows of what happened

Explain implementation with XOR
Explain interrupts
Play with interrupts -> increment counter on each interrupt
Prediction: How much ticks for 1 turn of the wheel -> 12*75

Resources:
- https://www.pololu.com/docs/0J63/3.4
- https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
- https://www.arduino.cc/reference/en/

^ (bitwise xor)

Problem of slipping, drift, etc -> need calibration




In competition, people use a free wheel system to solve that problem, more accurate (point contact, passive, etc)



## Gyroscope

Read Gyro -> observe change and default value offset
From Gyro to position
Using position to control heading
RotationResist demo
