#include <CatheterController.h>
#include <SerialDisplay.h>
#include <PotentiometerInput.h>
#include <PWMOutput.h>

/**
 * CatheterController Implementation
 */

CatheterController::CatheterController(IHAL &hal)
    : input1(hal, 14),
      output1(hal, 9),
      input2(hal, 15),
      output2(hal, 10),
      channel1(input1, output1),
      channel2(input2, output2),
      display(hal) {}

void CatheterController::update() {
    channel1.update();
    channel2.update();
    float output1 = channel1.getOutputValue();
    float output2 = channel2.getOutputValue();
    display.update(output1, output2);
}
