#ifndef ARDUINO_HAL_H
#define ARDUINO_HAL_H

#include <IHAL.h>

/**
 * Arduino Hardware Abstraction Layer
 *
 * Implementation of the HAL for Arduino. This class provides Arduino-specific
 * implementations of all hardware operations defined in the IHAL interface.
 */

class ArduinoHAL : public IHAL {
public:
	ArduinoHAL();

	AnalogValue analogRead(int pin) override;
	void analogWrite(int pin, AnalogValue value) override;
	AnalogValue getMaxAnalogReadQuant() const override;
	AnalogValue getMaxAnalogWriteQuant() const override;

	DigitalValue digitalRead(int pin) override;
	void digitalWrite(int pin, DigitalValue value) override;

	void print(const char *s) override;
	void println(const char *s) override;

	void delayMs(unsigned long durationMs) override;
	unsigned long getTimeMs() override;
};

#endif // ARDUINO_HAL_H
