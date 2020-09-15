#include "../core/include/subsystems/swerve_drive.h"

/**
 * Construct the SwerveDrive object.
 */
SwerveDrive::SwerveDrive(SwerveModule &left_front, SwerveModule &left_rear, SwerveModule &right_front, SwerveModule &right_rear)
:left_front(left_front), left_rear(left_rear), right_front(right_front), right_rear(right_rear)
{

}

/**
 * Drive the robot using controller inputs. Deadbands are automatically taken into
 * account before passing to the main control method.
 * 
 * @param leftY Left joystick, Y axis (-100 -> 100)
 * @param leftX Left joystick, X axis (-100 -> 100) 
 * @param rightX Right joystick, X axis(-100 -> 100)
 */
void SwerveDrive::drive(int32_t leftY, int32_t leftX, int32_t rightX)
{
    Vector::point_t p = {.x=(leftX / 100.0), .y=(leftY / 100.0)};

    Vector input_lat(p);

    // Lateral Deadband
    if(fabs(input_lat.get_mag()) < LAT_DEADBAND)
        Vector input_lat(0,0);

    // Rotational Deadband
    if(fabs(rightX / 100.0) < LAT_DEADBAND)
        rightX = 0;

    // Convert input to a vector, and pass into main control method
    this->drive(input_lat, rightX / 100.0);    
}

/**
 * The main control method. Takes a vector and a rotation, and performs vector math to
 * calculate the position/speed for each wheel.
 */
void SwerveDrive::drive(Vector lateral, double rotation)
{
    // Each wheel has a different rotation vector
    Vector rot_lf(deg2rad(45), rotation);
    Vector rot_rf(deg2rad(45+90), rotation);
    Vector rot_rr(deg2rad(45+180), rotation);
    Vector rot_lr(deg2rad(45+270), rotation);

    // Perform vector addition between the rotation vector and lateral vectors
    Vector lf_out = rot_lf + lateral;
    Vector rf_out = rot_rf + lateral;
    Vector rr_out = rot_rr + lateral;
    Vector lr_out = rot_lr + lateral;

    // Set each swerve module to the respective direction / speed
    left_front.set(rad2deg(lf_out.get_dir()), lf_out.get_mag());
    right_front.set(rad2deg(rf_out.get_dir()), rf_out.get_mag());
    right_rear.set(rad2deg(rr_out.get_dir()), rr_out.get_mag());
    left_rear.set(rad2deg(lr_out.get_dir()), lr_out.get_mag());
}

/**
 * Set the PID configuration for the "auto_drive" function
 */
void SwerveDrive::set_drive_pid(PID::pid_config_t &config) 
{
  if(drive_pid != NULL)
    delete drive_pid;

  this->drive_pid = new PID(config);
}

/**
 * Set the PID configuration for the "auto_turn" function
 */
void SwerveDrive::set_turn_pid(PID::pid_config_t &config) 
{ 
  if(turn_pid != NULL)
    delete turn_pid;

  this->turn_pid = new PID(config);
}

/**
 * Autonomously drive the robot in (degrees) direction, at (-1.0 -> 1.0) speed, for (inches) distance.
 * Indicate a negative speed or distance, or (preferably) a direction of +-180 degrees for backwards.
 */
bool SwerveDrive::auto_drive(double direction, double speed, double distance)
{
  // Null check the PID config
  if(drive_pid == NULL)
  {
    fprintf(stderr, "Failed to run auto_drive: Missing PID config\n");
    return true; // true to indicate 'finished'
  }

  // INITIALIZATION
  if(auto_drive_init)
  {
    // Turn all the wheels in the correct direction before running
    bool all_wheels_done = true;
    all_wheels_done = all_wheels_done & left_front.set_direction(direction);
    all_wheels_done = all_wheels_done & right_front.set_direction(direction);
    all_wheels_done = all_wheels_done & left_rear.set_direction(direction);
    all_wheels_done = all_wheels_done & right_rear.set_direction(direction);

    // Setting the speed of all wheels to zero will still slowly run the motor, to make sure the wheel is stopped.
    // (running the direction motor affects the speed of the wheel due to how it's geared together)
    left_front.set_speed(0);
    right_front.set_speed(0);
    left_rear.set_speed(0);
    right_rear.set_speed(0);

    // Make sure all the wheels are done turning before continuing with the 'init' phase
    if(!all_wheels_done)
      return false;

    // We're using the left front encoder for distance travelled.
    auto_drive_enc_reset = left_front.get_distance_driven();

    // set up the PID
    drive_pid->reset();
    drive_pid->set_target(distance);
    drive_pid->set_limits(-fabs(speed), fabs(speed));

    auto_drive_init = false;
  }

  // PERIODIC

  drive_pid->update( left_front.get_distance_driven() - auto_drive_enc_reset );
  this->drive(Vector(deg2rad(direction), drive_pid->get()), 0);

  // Check if the driving is complete
  if(drive_pid->is_on_target())
  {
    this->drive(Vector(0,0), 0); // stop the robot
    auto_drive_init = true;
    return true;
  }

  return false;
}