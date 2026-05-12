/**
 * @file PotentiometerInput.h
 */

#ifndef POTENTIOMETER_INPUT_H
#define POTENTIOMETER_INPUT_H

#include <IHAL.h>
#include <IInput.h>

/**
 * The implementation of `IInput`
 */
class PotentiometerInput : public IInput {
public:
	/**
	 * Configures a pin as a potentiometer input.
	 *
	 * @param hal A reference to the hardware abstraction layer.
	 * @param pin The pin number.
	 */
	PotentiometerInput(IHAL &hal, int pin);

	float getValue() override;

private:
	IHAL &m_hal;
	int m_pin;
};

#endif // POTENTIOMETER_INPUT_H
