#include "competition/opcontrol.h"
#include "core.h"

using namespace Hardware;

/**
 * Code for the Driver Control period is executed below.
 */
void OpControl::opcontrol()
{
  fprintf(stderr, "Calibrating...");
  imu.startCalibration();
  while(imu.isCalibrating());
  fprintf(stderr, "Done!\n");
  // OpControl Init
  lf_dir.setBrake(brakeType::brake);
  lr_dir.setBrake(brakeType::brake);
  rf_dir.setBrake(brakeType::brake);
  rr_dir.setBrake(brakeType::brake);

  drive.set_drive_pid(Config::swerve_drive_config);
  drive.set_turn_pid(Config::swerve_turning_config);

  GenericAuto auto1;

  auto1.add([](){return drive.auto_drive(-50, .5, 39);});
  auto1.add([](){return drive.auto_drive(180, .5, 12);});
  auto1.add([](){return drive.auto_turn(180, 1);});
  auto1.add([](){return drive.auto_drive(0, .5, 38);});
  auto1.add([](){return drive.auto_drive(180, .5, 26);});
  auto1.add([](){return drive.auto_turn(90, 1);});
  auto1.add([](){return drive.auto_drive(0, .5, 24);});
  auto1.add([](){return drive.auto_drive(180, .5, 50);});

  auto1.run(true);

  fprintf(stderr, "Done!");
  return;

  // OpControl Loop
  while (true)
  { 
    drive.drive(master.Axis3.position(), master.Axis4.position(), master.Axis1.position());

    // fprintf(stderr, "gyro: %f\n", imu.rotation());

    fprintf(stderr, "LF: %f, RF: %f, LR: %f, RR: %f\n", lf_mod.get_distance_driven(), rf_mod.get_distance_driven(), lr_mod.get_distance_driven(), rr_mod.get_distance_driven());

    // master.LCD.clearScreen();
    // master.LCD.setCursor(1,1);
    // master.LCD.print("RightX: %d", master.Axis1.position());

    vexDelay(100); // Small delay to allow time-sensitive functions to work properly.
  }
}