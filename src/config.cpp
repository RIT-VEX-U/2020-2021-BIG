#include "config.h"
#include "hardware.h"

// Tuned Oct. 4 with 10lb mass + drivetrain
PID::pid_config_t Config::swerve_drive_config = 
  {
    .p = .035,
    .i = .001,
    .d = .003,
    .deadband = .5,
    .on_target_time = .3
  };

// Tuned Oct. 4 with 10lb mass + drivetrain
PID::pid_config_t Config::swerve_turning_config = 
{
  .p = .006,
  .d = .0001,
  .deadband = .3
};


/**
 * config.cpp
 * 
 * Initialize all hardware configurations at runtime, inside initConfig() in initialize.cpp.
 */
void Config::initConfig()
{
  Hardware::drive.set_drive_pid(swerve_drive_config);
  Hardware::drive.set_turn_pid(swerve_turning_config);
}