/**
 * @file CatheterController.h
 */

#ifndef CATHER_CONTROLLER_H
#define CATHER_CONTROLLER_H

#include <Channel.h>
#include <IDisplay.h>

/**
 * Catheter Controller
 *
 * Owns the two channels and a display. Has an update method to update
 * those. This class is what main.cpp will interact with.
 */

class CatheterController {
private:
    Channel &channel1;
    Channel &channel2;  
    IDisplay &display;
    
public:
    /**
     * @param channel1 First control channel
     * @param channel2 Second control channel
     */
    CatheterController(Channel &channel1, Channel &channel2, IDisplay &display)
        : channel1(channel1), channel2(channel2), display(display) {};

    /**
     * Update both channels
     */
    void update();
};

#endif // CATHER_CONTROLLER_H
