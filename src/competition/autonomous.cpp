#include "competition/autonomous.h"
#include "core.h"
#include "competition/auto1.h"

/**
 * Code for the autonomous period is executed below.
 */
void Auto::autonomous()
{
  // Only one of the "run" methods below would actually be implemented.

  //EXAMPLE FOR BLOCKING MODE
  auto1.run(true);

  //Autonomous Loop
  while (true)
  {
    //EXAMPLE FOR NON-BLOCKING
    auto1.run(false);
    
    // other stuff can now be run concurrently

    vexDelay(20); // Small delay to allow time-sensitive functions to work properly.
  }
}