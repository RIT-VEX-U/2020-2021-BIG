/**
 * core.h
 * Ryan McGee
 *
 * Include all files from the 'core' library
 */

//Subsystems
#include "../core/include/subsystems/rgb_controller.h"
#include "../core/include/subsystems/tank_drive.h"
#include "../core/include/subsystems/swerve_module.h"
#include "../core/include/subsystems/swerve_drive.h"
#include "../core/include/subsystems/mecanum_drive.h"

//Utils
#include "../core/include/utils/pid.h"
#include "../core/include/utils/spline_path.h"
#include "../core/include/utils/generic_auto.h"

//Top Level
#include "../core/include/pathfinder.h"
