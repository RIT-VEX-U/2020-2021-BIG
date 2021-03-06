#include "competition/autonomous.h"
#include "core.h"

using namespace Hardware;

/**
 * Code for the autonomous period is executed below.
 */
void Auto::autonomous()
{
  //Autonomous Init
  while(imu.isCalibrating());

  //Autonomous Loop
  while (true)
  {

    vexDelay(20); // Small delay to allow time-sensitive functions to work properly.
  }
}