/**
 * @file IDisplay.h
 */

#ifndef IDISPLAY_H
#define IDISPLAY_H

/**
 * An interface for displaying important values related to the system
 *
 * Currently, it supports displaying the duty cycle on each channel output.
 */
class IDisplay {
public:
	virtual ~IDisplay() = default;

	/**
	 * Initialize the display. In general, must be called before any calls to
	 * `update`.
	 */
	virtual void initialize() = 0;

	/**
	 * Update the display with all relevant values.
	 *
	 * @param channel1Power The output duty cycle for channel 1 (between 0 and 1)
	 * @param channel2Power The output duty cycle for channel 2 (between 0 and 1)
	 */
	virtual void update(float channel1Power, float channel2Power) = 0;
};

#endif // IDISPLAY_H
