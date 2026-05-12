/**
 * @file PWMOutput.h
 */

#ifndef PWM_OUTPUT_H
#define PWM_OUTPUT_H

#include <IHAL.h>
#include <IOutput.h>

/**
 * The implementation of `IOutput`
 */
class PWMOutput : public IOutput {
public:
	/**
	 * Configures a pin as a PWM output.
	 *
	 * @param hal A reference to the hardware abstraction layer.
	 * @param pin The pin number.
	 */
	PWMOutput(IHAL &hal, int pin);

	float getValue() override;
	void setValue(float value) override;

private:
	IHAL &m_hal;
	int m_pin;
	float m_value;
};

#endif // PWM_OUTPUT_H
