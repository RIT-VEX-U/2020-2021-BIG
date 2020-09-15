#include "hardware.h"

// Initialize Hardware below
// Form: [class] Hardware::[name](parameters);

brain Hardware::v5_brain;

controller Hardware::master(controllerType::primary);
controller Hardware::partner(controllerType::partner);

motor Hardware::lf(1), Hardware::rf(2, true), Hardware::lr(3), Hardware::rr(4, true);

MecanumDrive Hardware::mec_drive(lf, rf, lr, rr);

// End Hardware Initialization