#include <Arduino.h>
#include <ArduinoHAL.h>
#include <CatheterController.h>
#include <SerialDisplay.h>

#define INPUT_PIN_1 A0
#define INPUT_PIN_2 A2
#define OUTPUT_PIN_1 10
#define OUTPUT_PIN_2 11

#define BAUD_RATE 9600
#define DELAY_MS 100

ArduinoHAL hal(BAUD_RATE);
SerialDisplay display(hal);
CatheterController controller(
	hal, INPUT_PIN_1, OUTPUT_PIN_1, INPUT_PIN_2, OUTPUT_PIN_2, display
);

void setup() {
	pinMode(INPUT_PIN_1, INPUT);
	pinMode(INPUT_PIN_2, INPUT);
	pinMode(OUTPUT_PIN_1, OUTPUT);
	pinMode(OUTPUT_PIN_2, OUTPUT);

	display.initialize();
}

void loop() {
	controller.update();
	hal.delayMs(DELAY_MS);
}
