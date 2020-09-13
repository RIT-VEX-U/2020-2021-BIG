#ifndef _HARDWARE_
#define _HARDWARE_

#include "vex.h"
#include "core.h"

using namespace vex;

/**
 * hardware.h
 * created 4/3/2020
 * 
 * Contains all the "hardware" objects (motors, sensors, controllers, etc)
 * to be initialized in hardware.cpp
 * 
 */
namespace Hardware
{
// Hardware Declared Below
// Form: extern [class_name] [name];

extern brain v5_brain;

extern controller master;
extern controller partner;

extern motor lf_drive;
extern motor rf_drive;
extern motor lr_drive;
extern motor rr_drive;

extern motor lf_dir;
extern motor rf_dir;
extern motor lr_dir;
extern motor rr_dir;

extern SwerveModule lf_mod;
extern SwerveModule rf_mod;
extern SwerveModule lr_mod;
extern SwerveModule rr_mod;

extern SwerveDrive drive;

//End Hardware Declarations
} // namespace Hardware

#endif