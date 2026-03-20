#include <CatheterController.h>

/**
 * CatheterController Implementation
 * 
 * Manages two control channels and updates them.
 */

class CatheterController {
private:
    Channel &channel1;
    Channel &channel2;
    IDisplay &display;

public:
    CatheterController(Channel &channel1, Channel &channel2, IDisplay &display)
        : channel1(channel1), channel2(channel2), display(display) {}

    void update() {
        channel1.update();
        channel2.update();
        display.update();
    }
};