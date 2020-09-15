#include "competition/opcontrol.h"
#include "core.h"

using namespace Hardware;

/**
 * Code for the Driver Control period is executed below.
 */
void OpControl::opcontrol()
{
  // OpControl Init

  // OpControl Loop
  while (true)
  { 
    mec_drive.drive(master.Axis3.position(), master.Axis4.position(), master.Axis1.position());

    vexDelay(100); // Small delay to allow time-sensitive functions to work properly.
  }
}