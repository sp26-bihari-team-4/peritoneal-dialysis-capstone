/**
 * @file IInput.h
 */

#ifndef IINPUT_H
#define IINPUT_H

/**
 * An analog input interface
 *
 * Mainly exists so that `PotentiometerInput` can be mocked in unit tests.
 */
class IInput {
public:
	virtual ~IInput() = default;

	/**
	 * Samples this input.
	 *
	 * @return The floating-point value of this input, normalized to
	 * the range [0, 1].
	 */
	virtual float getValue() = 0;
};

#endif // IINPUT_H
