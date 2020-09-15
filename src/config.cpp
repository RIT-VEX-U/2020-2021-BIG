#include "config.h"

PID::pid_config_t Config::swerve_drive_config = 
  {
    .p = .1,
    .deadband = .5,
    .on_target_time = .3
  };

/**
 * config.cpp
 * 
 * Initialize all hardware configurations at runtime, inside initConfig() in initialize.cpp.
 */
void Config::initConfig()
{
}