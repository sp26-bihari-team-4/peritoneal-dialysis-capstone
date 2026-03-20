/**
 * @file CatheterController.h
 */

#ifndef CATHER_CONTROLLER_H
#define CATHER_CONTROLLER_H

#include <Channel.h>
#include <IDisplay.h>
#include <IHAL.h>
#include <PotentiometerInput.h>
#include <PWMOutput.h>
#include <SerialDisplay.h>

/**
 * Catheter Controller
 *
 * Owns the two channels and a display. Has an update method to update
 * those. This class is what main.cpp will interact with.
 */

class CatheterController {
private:
    PotentiometerInput input1;
    PWMOutput output1;
    PotentiometerInput input2;
    PWMOutput output2;
    Channel channel1;
    Channel channel2;
    SerialDisplay display;

public:
    /**
     * @param hal The Hardware Abstraction Layer.
     */
    CatheterController(IHAL &hal);
    /**
     * Update both channels
     */
    void update();
};

#endif // CATHER_CONTROLLER_H
