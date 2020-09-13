#include "hardware.h"

// Initialize Hardware below
// Form: [class] Hardware::[name](parameters);

brain Hardware::v5_brain;

controller Hardware::master(controllerType::primary);
controller Hardware::partner(controllerType::partner);

motor Hardware::lf_dir(PORT2, true);
motor Hardware::rf_dir(PORT9, true);
motor Hardware::lr_dir(PORT12, true);
motor Hardware::rr_dir(PORT19, true);

motor Hardware::lf_drive(PORT1);
motor Hardware::rf_drive(PORT10);
motor Hardware::lr_drive(PORT11);
motor Hardware::rr_drive(PORT20);

SwerveModule Hardware::lf_mod(Hardware::lf_drive, gearSetting::ratio36_1, Hardware::lf_dir, gearSetting::ratio36_1);
SwerveModule Hardware::rf_mod(Hardware::rf_drive, gearSetting::ratio36_1, Hardware::rf_dir, gearSetting::ratio36_1);
SwerveModule Hardware::lr_mod(Hardware::lr_drive, gearSetting::ratio36_1, Hardware::lr_dir, gearSetting::ratio36_1);
SwerveModule Hardware::rr_mod(Hardware::rr_drive, gearSetting::ratio36_1, Hardware::rr_dir, gearSetting::ratio36_1);

SwerveDrive Hardware::drive(lf_mod, lr_mod, rf_mod, rr_mod);

// End Hardware Initialization