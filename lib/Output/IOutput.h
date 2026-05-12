/**
 * @file IOutput.h
 */

#ifndef IOUTPUT_H
#define IOUTPUT_H

/**
 * An analog output interface
 *
 * Mainly exists so that `PWMOutput` can be mocked in unit tests.
 */
class IOutput {
public:
	virtual ~IOutput() = default;

	/**
	 * Returns the last value written to this output.
	 */
	virtual float getValue() = 0;

	/**
	 * Writes a value to this output.
	 *
	 * @param value The floating-point value to set. Must be in the range [0, 1].
	 */
	virtual void setValue(float value) = 0;
};

#endif // IOUTPUT_H
