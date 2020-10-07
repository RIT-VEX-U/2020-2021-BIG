#include "initialize.h"
#include "vex.h"
#include "config.h"
#include "hardware.h"

using namespace vex;
using namespace Hardware;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 *
 * This should be called at the start of your int main function.
 */
void Init::vexcodeInit(void)
{
  // Initialize the robot configuration variables
  Config::initConfig();

  // Calibrate the IMU. Make sure robot is STILL!
  fprintf(stderr, "Calibrating Inertial...");
  imu.startCalibration();
  while(imu.isCalibrating());
  fprintf(stderr, "Done!\n");

  // Set the direction motors to be in "brake" mode
  lf_dir.setBrake(brakeType::brake);
  lr_dir.setBrake(brakeType::brake);
  rf_dir.setBrake(brakeType::brake);
  rr_dir.setBrake(brakeType::brake);

  Hardware::v5_brain.Screen.print("Robot Code Initialized.");
  Hardware::master.Screen.print("Controller Initialized.");
  Hardware::partner.Screen.print("Controller Initialized.");
}