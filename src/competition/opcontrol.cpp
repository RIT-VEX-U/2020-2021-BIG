#include "competition/opcontrol.h"
#include "core.h"

using namespace Hardware;

/**
 * Code for the Driver Control period is executed below.
 */
void OpControl::opcontrol()
{
  // OpControl Init
  lf_dir.setBrake(brakeType::brake);
  lr_dir.setBrake(brakeType::brake);
  rf_dir.setBrake(brakeType::brake);
  rr_dir.setBrake(brakeType::brake);

  drive.set_drive_pid(Config::swerve_drive_config);

  GenericAuto auto1;

  auto1.add([](){return drive.auto_drive(0, .3, 24);});
  auto1.add([](){return drive.auto_drive(90, .3, 24);});
  auto1.add([](){return drive.auto_drive(180, .3, 24);});
  auto1.add([](){return drive.auto_drive(270, .3, 24);});

  auto1.run(true);

  fprintf(stderr, "Done!");
  return;

  // OpControl Loop
  while (true)
  { 
    // drive.drive(master.Axis3.position(), master.Axis4.position(), master.Axis1.position());

   



    // master.LCD.clearScreen();
    // master.LCD.setCursor(1,1);
    // master.LCD.print("RightX: %d", master.Axis1.position());

    vexDelay(100); // Small delay to allow time-sensitive functions to work properly.
  }
}