#ifndef PWM_OUTPUT_H
#define PWM_OUTPUT_H

#include <IHAL.h>

/**
 * PWM Output
 *
 * Controls a PWM output pin. Accepts normalized values (0.0-1.0) and
 * converts them to the appropriate PWM range (0-255 for Arduino).
 */

class PWMOutput {
public:
	/**
	 * Configures a pin as a PWM output.
	 *
	 * @param hal The Hardware Abstraction Layer (HAL).
	 * @param pin The pin number.
	 */
	PWMOutput(IHAL &hal, int pin);

	/**
	 * Sets the duty cycle for pulse-width modulated output on this pin.
	 *
	 * @param dutyCycle The proportion of a PWM cycle where this pin is HIGH.
	 *                  Must be in the range [0, 1].
	 */
	void analogWrite(float dutyCycle);

private:
	IHAL &m_hal;
	int m_pin;
};

#endif // PWM_OUTPUT_H
