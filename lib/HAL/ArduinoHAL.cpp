#include <ArduinoHAL.h>

#include <Arduino.h>

#include <assert.h>

static constexpr int SERIAL_BAUD = 9600;

static constexpr AnalogValue MAX_ANALOG_READ_QUANT = 1023;
static constexpr AnalogValue MAX_ANALOG_WRITE_QUANT = 255;

// Analog I/O

static void setupSerial() {
	Serial.begin(SERIAL_BAUD);
}

ArduinoHAL::ArduinoHAL() {
	setupSerial();
}

AnalogValue ArduinoHAL::analogRead(int pin) {
	return analogRead(pin);
}

void ArduinoHAL::analogWrite(int pin, AnalogValue value) {
	assert(value <= MAX_ANALOG_WRITE_QUANT);
	analogWrite(pin, value);
}

AnalogValue ArduinoHAL::getMaxAnalogReadQuant() const {
	return MAX_ANALOG_READ_QUANT;
}

AnalogValue ArduinoHAL::getMaxAnalogWriteQuant() const {
	return MAX_ANALOG_WRITE_QUANT;
}

// Digital I/O

DigitalValue ArduinoHAL::digitalRead(int pin) {
	return digitalRead(pin);
}

void ArduinoHAL::digitalWrite(int pin, DigitalValue value) {
	assert(value == LOW || value == HIGH);
	digitalWrite(pin, value);
}

// Serial print functions

void ArduinoHAL::print(const char *s) {
	Serial.print(s);
}

void ArduinoHAL::println(const char *s) {
	Serial.println(s);
}

// Timing

void ArduinoHAL::delayMs(unsigned long durationMs) {
	delay(durationMs);
}

unsigned long ArduinoHAL::getTimeMs() {
	return millis();
}
