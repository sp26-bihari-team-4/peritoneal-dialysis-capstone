#include "PWMOutput.h"

#include <assert.h>

#define MAX_QUANT 255

PWMOutput::PWMOutput(IHAL &hal, int pin) : m_hal{hal}, m_pin{pin} {}

void PWMOutput::analogWrite(float dutyCycle) {
	// TODO: Should these be preconditions, or should we normalize
	//       `dutyCycle` ourselves?
	assert(dutyCycle >= 0.f);
	assert(dutyCycle <= 1.f);

	int quant = (int)(dutyCycle * (float)MAX_QUANT);

	m_hal.analogWrite(m_pin, quant);
}
