#include "competition/autonomous.h"
#include "core.h"

enum state
{
  init, driving_forwards, turning, drive_to_bump
};

state current_state = init;

/**
  * Task that controls all driving on the robot
  * Runs in it's separate thread
  *
  * (This is all assuming the drive_forward function is blocking, which right now it is not.)
  */
int driving_task_func()
{
  current_state = driving_forwards;
    Hardware::tank.drive_forward(12, .5);

  current_state = turning;
    Hardware::tank.turn_degrees(45, 1.0);
  
  current_state = drive_to_bump;
    while(!Hardware::floor_sense.pressing())
      Hardware::tank.drive_tank(.5, .5);

  return 0;
}

/**
* Task that controls an arm on the robot, separate of the drivetrain.
* When the driving has reached a certain "state", move the arm 90 deg
* at the same time as driving.
*/
int arm_task_func(void* driving_state)
{
  while (*(state*)driving_state != drive_to_bump); //sleep until trigger
  
  Hardware::arm.spinToPosition(90, rotationUnits::deg);

  return 0;
}

/**
 * Code for the autonomous period is executed below.
 */
void Auto::autonomous()
{
  //Autonomous Init
  task driving_task(driving_task_func);
  task arm_task(arm_task_func, &current_state);

  //Autonomous Loop
  while (true)
  {
    
    vexDelay(20); // Small delay to allow time-sensitive functions to work properly.
  }
}