/**
 * @file IDisplay.h
 */

#ifndef IDISPLAY_H
#define IDISPLAY_H

/**
 * Display Interface
 *
 * Has an update method that takes in values to be shown on the display.
 */

class IDisplay {

public:
    
    /**
     * Update the display with the current values. This will be called after
     * each update of the channels.
     *
     * @param value1 The value from channel 1 to display (between 0 and 1).
     * @param value2 The value from channel 2 to display (between 0 and 1).
     */
    virtual void update(float value1, float value2) = 0;
};
#endif // IDISPLAY_H
