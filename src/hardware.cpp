#include "hardware.h"

// Initialize Hardware below
// Form: [class] Hardware::[name](parameters);

brain Hardware::v5_brain;

controller Hardware::master(controllerType::primary);
controller Hardware::partner(controllerType::partner);

inertial Hardware::imu(PORT6);

motor Hardware::lf_dir(PORT2, true);
motor Hardware::rf_dir(PORT9, true);
motor Hardware::lr_dir(PORT12, true);
motor Hardware::rr_dir(PORT19, true);

motor Hardware::lf_drive(PORT1, gearSetting::ratio6_1);
motor Hardware::rf_drive(PORT10, gearSetting::ratio6_1);
motor Hardware::lr_drive(PORT11, gearSetting::ratio6_1);
motor Hardware::rr_drive(PORT20, gearSetting::ratio6_1);

SwerveModule Hardware::lf_mod(Hardware::lf_drive, gearSetting::ratio18_1, Hardware::lf_dir, gearSetting::ratio18_1);
SwerveModule Hardware::rf_mod(Hardware::rf_drive, gearSetting::ratio18_1, Hardware::rf_dir, gearSetting::ratio18_1);
SwerveModule Hardware::lr_mod(Hardware::lr_drive, gearSetting::ratio18_1, Hardware::lr_dir, gearSetting::ratio18_1);
SwerveModule Hardware::rr_mod(Hardware::rr_drive, gearSetting::ratio18_1, Hardware::rr_dir, gearSetting::ratio18_1);

SwerveDrive Hardware::drive(lf_mod, lr_mod, rf_mod, rr_mod, imu);

// End Hardware Initialization