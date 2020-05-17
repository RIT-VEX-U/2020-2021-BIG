#include "hardware.h"

// Initialize Hardware below
// Form: [class] Hardware::[name](parameters);

brain Hardware::v5_brain;

controller Hardware::master(controllerType::primary);
controller Hardware::partner(controllerType::partner);


TankDrive Hardware::tank(new motor_group, new motor_group, new inertial(1), new TankDrive::tankdrive_config_t);
bumper Hardware::floor_sense(v5_brain.ThreeWirePort.A);
motor Hardware::arm(2);

// End Hardware Initialization