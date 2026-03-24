/**
 * @file SerialDisplay.h
 */

#ifndef SERIAL_DISPLAY_H
#define SERIAL_DISPLAY_H

#include <IDisplay.h>
#include <IHAL.h>

/**
 * Serial display
 *
 * Implementation of `IDisplay` that uses the HAL to write text messages to
 * serial output.
 */
class SerialDisplay : public IDisplay {
private:
    IHAL &m_hal;

public:
    /**
     * @param hal The Hardware Abstraction Layer.
     */
    SerialDisplay(IHAL &hal);

    /**
     * Update the display with the given values.
     *
     * @param value1 The first value to display.
     * @param value2 The second value to display.
     */
    void update(float value1, float value2) override;
};

#endif // SERIAL_DISPLAY_H
