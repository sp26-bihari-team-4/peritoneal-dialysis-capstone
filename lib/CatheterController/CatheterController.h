/**
 * @file CatheterController.h
 */

#ifndef CATHER_CONTROLLER_H
#define CATHER_CONTROLLER_H

#include <Channel.h>
#include <IDisplay.h>
#include <IHAL.h>
#include <PWMOutput.h>
#include <PotentiometerInput.h>

/**
 * The main encapsulating class containing our business logic. Driven from
 * main.cpp using the `update` method.
 */
class CatheterController {
private:
	PotentiometerInput input1;
	PWMOutput output1;
	PotentiometerInput input2;
	PWMOutput output2;
	Channel channel1;
	Channel channel2;
	IDisplay &display;

public:
	/**
	 * @param hal A reference to the hardware abstraction layer
	 * @param inputPin1 The pin number of the input for channel 1
	 * @param outputPin1 The pin number of the output for channel 1
	 * @param inputPin2 The pin number of the input for channel 2
	 * @param outputPin2 The pin number of the output for channel 2
	 * @param display A reference to the display
	 */
	CatheterController(
		IHAL &hal, int inputPin1, int outputPin1, int inputPin2, int outputPin2,
		IDisplay &display
	);

	/**
	 * Update both channels and display the output duty cycles.
	 */
	void update();
};

#endif // CATHER_CONTROLLER_H
