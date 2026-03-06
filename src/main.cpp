#if defined(ARDUINO_AVR_UNO)

#include <Arduino.h>

void setup() {
	short test = (int)3;
}

void loop() {}

#else

#include <iostream>

int main() {
	std::cout << "Hello, World!\n";
}

#endif
