#include "competition/auto1.h"

// STATE NUMBER 1
bool drive_forward_1()
{
  return Hardware::tank.drive_forward(12, .5);
}

// STATE NUMBER 2
bool turn_right()
{
  return Hardware::tank.turn_degrees(45, 1);
}

// STATE NUMBER 3
// Move until bump sensor is triggered
// while moving arm 90 degrees
bool drive_to_bump_move_arm()
{
  Hardware::arm.spinToPosition(90, rotationUnits::deg);
  if(Hardware::floor_sense.pressing())
    return true;

  return false;
}

GenericAuto auto1 = {drive_forward_1, turn_right, drive_to_bump_move_arm};
