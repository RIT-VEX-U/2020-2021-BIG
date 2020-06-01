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

//End Hardware Declarations
} // namespace Hardware

#endif