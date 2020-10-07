#include "competition/opcontrol.h"
#include "core.h"

using namespace Hardware;

/**
 * Code for the Driver Control period is executed below.
 */
void OpControl::opcontrol()
{
  
  // OpControl Init
  while(imu.isCalibrating());

  // OpControl Loop
  while (true)
  { 
    // LEFT STICK: lateral movement   RIGHT STICK: rotational movement
    drive.drive(master.Axis3.position(), master.Axis4.position(), master.Axis1.position());


    vexDelay(50); // Small delay to allow time-sensitive functions to work properly (milliseconds)
  }
}