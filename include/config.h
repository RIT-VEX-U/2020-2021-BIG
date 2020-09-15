#include "core.h"
/**
 * config.h
 * Created 4/3/2020
 * 
 * A location where all configuration variables are set for the robot, usually in the form
 * of creating Structs, and initializing their values at runtime in config.cpp
 * 
 */
namespace Config
{

// Declare configuration structs below
// Form: extern [structName] [name];

extern PID::pid_config_t swerve_drive_config;

// End Config Declarations

void initConfig();
} // namespace Config