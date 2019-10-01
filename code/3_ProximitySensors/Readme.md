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
