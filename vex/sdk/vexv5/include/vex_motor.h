/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Copyright (c) Innovation First 2017-2019, All rights reserved.          */
/*                                                                            */
/*    Module:     vex_motor.h                                                 */
/*    Author:     James Pearman                                               */
/*    Created:    2 June 2017                                                 */
/*                                                                            */
/*    Revisions:                                                              */
/*                V1.00     TBD - Initial release                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef   VEX_MOTOR_CLASS_H
#define   VEX_MOTOR_CLASS_H

/*-----------------------------------------------------------------------------*/
/** @file    vex_motor.h
  * @brief   Motor device class header
*//*---------------------------------------------------------------------------*/

namespace vex {
  /** 
    * @prog_lang{block|cpp|pro}
    * @brief Use the motor class to control motor devices.
  */
  class motor : public device {
    public:
     /** 
     * @prog_lang{cpp|pro}
     * @drawer_cat{constructor}
     * @block_sig{vex::motor Motor = vex::motor(vex::PORT1);}     
     * @brief Creates a new motor object on the port specified.
     * @param index The port index for this motor. The index is zero-based.
     */
      motor( int32_t index );  
      ~motor();
    
      bool            installed();
      int32_t         value();

     /** 
      * @prog_lang{cpp|pro}
      * @drawer_cat{constructor}
      * @block_sig{vex::motor Motor = vex::motor(vex::PORT1, false);}
      * @brief Creates a new motor object on the port specified and sets the reversed flag.
      * @param index The port index for this motor. The index is zero-based.
      * @param reverse Sets the reverse flag for the new motor object.
      */
      motor( int32_t index, bool reverse );

     /** 
      * @prog_lang{cpp|pro}
      * @drawer_cat{constructor}
      * @block_sig{vex::motor Motor = vex::motor(vex::PORT1, vex::gearSetting::ratio18_1);}
      * @brief Creates a new motor object on the port specified and sets the gear setting
      * @param index The port index for this motor. The index is zero-based.
      * @param gears Sets the gear's setting for the new motor object.
      */  
      motor( int32_t index, gearSetting gears );

     /** 
      * @prog_lang{cpp|pro}
      * @drawer_cat{constructor}
      * @block_sig{vex::motor Motor = vex::motor(vex::PORT1, vex::gearSetting::ratio18_1, false);}
      * @brief Creates a new motor object on the port specified Sets the reversed flag and the gear setting for the new motor object.
      * @param index The port index for this motor. The index is zero-based.
      * @param gears Sets the gear's setting for the new motor object.
      * @param reverse Sets the reverse flag for the new motor object.
      */  
      motor( int32_t index, gearSetting gears, bool reverse );
      
      /** 
       * @prog_lang{cpp|pro}
       * @drawer_cat{setting}
       * @block_sig{Motor.setReversed(true);}
       * @brief Sets the motor mode to "reverse", which will make motor commands spin the motor in the opposite direction.
       * @param value If set to true, motor commands spin the motor in the opposite direction.
       */
      void            setReversed( bool value );

      /** 
       * @prog_lang{cpp|pro}
       * @drawer_cat{setting}
       * @block_sig{Motor.setVelocity(50, vex::velocityUnits::rpm);}
       * @brief Sets the velocity of the motor based on the parameters set in the command. This command will not run the motor.  Any subsequent call that does not contain a specified motor velocity will use this value.
       * @param velocity Sets the amount of velocity.
       * @param units The measurement unit for the velocity value. 
       */
      void            setVelocity( double velocity, velocityUnits units );

      /** 
       * @prog_lang{block}
       * @drawer_cat{setting}
       * @block_sig{Motor.setVelocity(50, percent);}
       * @brief Sets the velocity of the motor based on the parameters set in the command. This command will not run the motor.  Any subsequent call that does not contain a specified motor velocity will use this value.
       * @param velocity Sets the amount of velocity.
       * @param units The measurement unit for the velocity value.
       */
      void            setVelocity( double velocity, percentUnits units ){
          setVelocity( velocity, static_cast<velocityUnits>(units) );
      };

      //Legacy 
      void            setBrake( brakeType mode );

      /** 
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{setting}
       * @block_sig{Motor.setStopping(coast);}
       * @cpp_sig{Motor.setStopping(vex::brakeType::coast);}
       * @brief Sets the stopping mode of the motor by passing a brake mode as a parameter.
       * @param mode The stopping mode can be set to coast, brake, or hold.  
       */
      void            setStopping( brakeType mode );

      /** 
       * @prog_lang{cpp|pro}
       * @drawer_cat{setting}
       * @block_sig{Motor.resetRotation();}
       * @brief Resets the motor's encoder to the value of zero. 
       */   
      void            resetRotation( void );

      /** 
       * @prog_lang{cpp|pro}
       * @drawer_cat{setting}
       * @block_sig{Motor.resetPosition();}
       * @brief Resets the motor's encoder to the value of zero. 
       */   
      void            resetPosition( void );

      /** 
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{setting}
       * @block_sig{Motor.setRotation(90, degrees);}
       * @cpp_sig{Motor.setRotation(90,vex::rotationUnits::deg);}
       * @brief Sets the value of the motor's encoder to the value specified in the parameter.
       * @param value Sets the amount of rotation.
       * @param units The measurement unit for the rotation value.
       */
      void            setRotation( double value, rotationUnits units );

      /** 
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{setting}
       * @block_sig{Motor.setPosition(90, degrees);}
       * @cpp_sig{Motor.setPosition(90,vex::rotationUnits::deg);}
       * @brief Sets the value of the motor's encoder to the value specified in the parameter.
       * @param value Sets the current position of the motor.
       * @param units The measurement unit for the position value.
       */
      void            setPosition( double value, rotationUnits units );

      /** 
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{setting}
       * @block_sig{Motor.setTimeout(30, seconds);}
       * @cpp_sig{Motor.setTimeout(30, vex::timeUnits::sec);}
       * @brief Sets the timeout for the motor. If the motor does not reach its' commanded position prior to the completion of the timeout, the motor will stop.
       * @param time Sets the amount of time.
       * @param units The measurement unit for the time value.
       */
      void            setTimeout( int32_t time, timeUnits units );

      //Actions
      
      /** 
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{action}
       * @block_sig{Motor.spin(forward);}
       * @cpp_sig{Motor.spin(vex::directionType::fwd);}
       * @brief Turns the motor on, and spins it in the specified direction.
       * @param dir The direction to spin the motor.
       */
      void            spin( directionType dir );

      /**
       * @prog_lang{cpp|pro}
       * @drawer_cat{action}
       * @block_sig{Motor.spin(vex::directionType::fwd,50,vex::velocityUnits::rpm);}
       * @brief Turns on the motor and spins it in a specified direction and a specified velocity.
       * @param dir The direction to spin the motor. 
       * @param velocity Sets the amount of velocity.
       * @param units The measurement unit for the velocity value. 
      */
      void            spin( directionType dir, double velocity, velocityUnits units );

      void            spin( directionType dir, double velocity, percentUnits units ){
          spin( dir, velocity, static_cast<velocityUnits>(units) );
      }

      /**
       * @prog_lang{pro}
       * @drawer_cat{action}
       * @block_sig{Motor.spin(vex::directionType::fwd,6,vex::voltageUnits::volt);}
       * @brief Turns on the motor and spins it in a specified direction and a specified voltage.
       * @param dir The direction to spin the motor. 
       * @param voltage Sets the amount of volts.
       * @param units The measurement unit for the voltage value. 
      */
      void            spin( directionType dir, double voltage, voltageUnits units );

       /**
       * @prog_lang{cpp|pro}
       * @drawer_cat{action}
       * @block_sig{Motor.rotateTo(90, vex::rotationUnits::deg, 50, vex::velocityUnits::pct);}
       * @brief Turns on the motor and spins it to an absolute target rotation value at a specified velocity.
       * @return Returns a Boolean that signifies when the motor has reached the target rotation value.
       * @param rotation Sets the amount of rotation.
       * @param units The measurement unit for the rotation value.
       * @param velocity Sets the amount of velocity.
       * @param units_v The measurement unit for the velocity value. 
       * @param waitForCompletion (Optional) If true, your program will wait until the motor reaches the target rotational value. If false, the program will continue after calling this function. By default, this parameter is true.
      */
      bool            rotateTo( double rotation, rotationUnits units, double velocity, velocityUnits units_v, bool waitForCompletion=true );
      bool            spinTo( double rotation, rotationUnits units, double velocity, velocityUnits units_v, bool waitForCompletion=true );

      bool            spinToPosition( double rotation, rotationUnits units, double velocity, velocityUnits units_v, bool waitForCompletion=true );

      /**
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{action}
       * @block_sig{Motor.rotateTo(90, degrees);}
       * @cpp_sig{Motor.rotateTo(90,vex::rotationUnits::deg);}
       * @brief Turns on the motor and spins it to an absolute target rotation value.
       * @return Returns a Boolean that signifies when the motor has reached the target rotation value.
       * @parameter_number_override{2}
       * @return_type_override{void}
       * @param rotation Sets the amount of rotation.
       * @param units The measurement unit for the rotation value.        
       * @param waitForCompletion (Optional) If true, your program will wait until the motor reaches the target rotational value. If false, the program will continue after calling this function. By default, this parameter is true.
      */
      bool            rotateTo( double rotation, rotationUnits units, bool waitForCompletion=true );
      bool            spinTo( double rotation, rotationUnits units, bool waitForCompletion=true );

      bool            spinToPosition( double rotation, rotationUnits units, bool waitForCompletion=true );

      /**
       * @prog_lang{cpp|pro}
       * @drawer_cat{action}
       * @block_sig{Motor.rotateFor(90,vex::rotationUnits::deg,50,vex::velocityUnits::pct);}
       * @brief Turns on the motor and spins it to a relative target rotation value at a specified velocity.
       * @return Returns a Boolean that signifies when the motor has reached the target rotation value.
       * @param rotation Sets the amount of rotation.
       * @param units The measurement unit for the rotation value.
       * @param velocity Sets the amount of velocity.
       * @param units_v The measurement unit for the velocity value.
       * @param waitForCompletion (Optional) If true, your program will wait until the motor reaches the target rotational value. If false, the program will continue after calling this function. By default, this parameter is true.
      */
      bool            rotateFor( double rotation, rotationUnits units, double velocity, velocityUnits units_v, bool waitForCompletion=true );
      bool            spinFor( double rotation, rotationUnits units, double velocity, velocityUnits units_v, bool waitForCompletion=true );

      bool            rotateFor( directionType dir, double rotation, rotationUnits units, double velocity, velocityUnits units_v, bool waitForCompletion=true );
      bool            spinFor( directionType dir, double rotation, rotationUnits units, double velocity, velocityUnits units_v, bool waitForCompletion=true );

      /**
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{action}
       * @block_sig{Motor.rotateFor(90, degrees);}
       * @cpp_sig{Motor.rotateFor(90,vex::rotationUnits::deg);}
       * @brief Turns on the motor and spins it to a relative target rotation value.
       * @return Returns a Boolean that signifies when the motor has reached the target rotation value.
       * @parameter_number_override{2}
       * @return_type_override{void}
       * @param rotation Sets the amount of rotation.
       * @param units The measurement unit for the rotation value.        
       * @param waitForCompletion (Optional) If true, your program will wait until the motor reaches the target rotational value. If false, the program will continue after calling this function. By default, this parameter is true.
      */
      bool            rotateFor( double rotation, rotationUnits units, bool waitForCompletion=true );
      bool            spinFor( double rotation, rotationUnits units, bool waitForCompletion=true );

      bool            rotateFor( directionType dir, double rotation, rotationUnits units, bool waitForCompletion=true );
      bool            spinFor( directionType dir, double rotation, rotationUnits units, bool waitForCompletion=true );
      
      /**
       * @prog_lang{cpp|pro}
       * @drawer_cat{action}
       * @block_sig{Motor.rotateFor(2.5, vex::timeUnits::sec, 50, vex::velocityUnits::pct);}
       * @brief Turns on the motor and spins it to a relative target time value at a specified velocity.
       * @return true on success, false if parameter error
       * @param time Sets the amount of time.
       * @param units The measurement unit for the time value.
       * @param velocity Sets the amount of velocity.
       * @param units_v The measurement unit for the velocity value.       
      */
      bool            rotateFor( double time, timeUnits units, double velocity, velocityUnits units_v );
      bool            spinFor( double time, timeUnits units, double velocity, velocityUnits units_v );

      bool            rotateFor( directionType dir, double time, timeUnits units, double velocity, velocityUnits units_v );
      bool            spinFor( directionType dir, double time, timeUnits units, double velocity, velocityUnits units_v );

      /**
       * @prog_lang{cpp|pro}
       * @drawer_cat{action}
       * @block_sig{Motor.rotateFor(2.5, vex::timeUnits::sec);}
       * @brief Turns on the motor and spins it to a relative target time value.
       * @return true on success, false if parameter error
       * @param time Sets the amount of time.
       * @param units The measurement unit for the time value.              
      */
      bool            rotateFor( double time, timeUnits units );
      bool            spinFor( double time, timeUnits units );

      bool            rotateFor( directionType dir, double time, timeUnits units );
      bool            spinFor( directionType dir, double time, timeUnits units );

      /** 
       * @prog_lang{cpp|pro}
       * @drawer_cat{action}
       * @block_sig{Motor.startRotateTo(90,vex::rotationUnits::deg,50,vex::velocityUnits::pct);}
       * @brief Starts spinning a motor to an absolute target rotation but does not wait for the motor to reach that target.
       * @param rotation Sets the amount of rotation.
       * @param units The measurement unit for the rotation value.
       * @param velocity Sets the amount of velocity.
       * @param units_v The measurement unit for the velocity value.
       */
      void            startRotateTo( double rotation, rotationUnits units, double velocity, velocityUnits units_v );
      void            startSpinTo( double rotation, rotationUnits units, double velocity, velocityUnits units_v );

      /** 
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{action}
       * @block_sig{Motor.startRotateTo(90,degrees);}
       * @cpp_sig{Motor.startRotateTo(90,vex::rotationUnits::deg);}
       * @brief Starts spinning a motor to an absolute target rotation but does not wait for the motor to reach that target.
       * @param rotation Sets the amount of rotation.
       * @param units The measurement unit for the rotation value.        
       */
      void            startRotateTo( double rotation, rotationUnits units );
      void            startSpinTo( double rotation, rotationUnits units );

      /** 
       * @prog_lang{cpp|pro}
       * @drawer_cat{action}
       * @block_sig{Motor.startRotateFor(90,vex::rotationUnits::deg,50,vex::velocityUnits::pct);}
       * @brief Starts spinning a motor to a relative target rotation but does not wait for the motor to reach that target.
       * @param rotation Sets the amount of rotation.
       * @param units The measurement unit for the rotation value. 
       * @param velocity Sets the amount of velocity.
       * @param units_v The measurement unit for the velocity value.
       */
      void            startRotateFor( double rotation, rotationUnits units, double velocity, velocityUnits units_v );     
      void            startSpinFor( double rotation, rotationUnits units, double velocity, velocityUnits units_v );

      void            startRotateFor( directionType dir, double rotation, rotationUnits units, double velocity, velocityUnits units_v );     
      void            startSpinFor( directionType dir, double rotation, rotationUnits units, double velocity, velocityUnits units_v );     
      
      /** 
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{action}
       * @block_sig{Motor.startRotateFor(90,degrees);}
       * @cpp_sig{Motor.startRotateFor(90,vex::rotationUnits::deg);}
       * @brief Starts spinning a motor to a relative target but does not wait for the motor to reach that target.
       * @param rotation Sets the amount of rotation.
       * @param units The measurement unit for the rotation value.        
       */
      void            startRotateFor( double rotation, rotationUnits units );
      void            startSpinFor( double rotation, rotationUnits units );

      void            startRotateFor( directionType dir, double rotation, rotationUnits units );
      void            startSpinFor( directionType dir, double rotation, rotationUnits units );

      /** 
       * @prog_lang{cpp|pro|block}
       * @drawer_cat{sensing}
       * @block_sig{Motor.isSpinning()}
       * @brief Checks to see if the motor is rotating to a specific target.
       * @return Returns a true Boolean if the motor is on and is rotating to a target. Returns a false Boolean if the motor is done rotating to a target.
       */
      bool            isSpinning( void );

      /** 
       * @prog_lang{block}
       * @drawer_cat{sensing}
       * @block_sig{Motor.isDone()}
       * @brief Checks to see if the motor is done rotating to a specific target.
       * @return Returns a false Boolean if the motor is on and is rotating to a target. Returns a true Boolean if the motor is done rotating to a target.
       */
      bool            isDone( void );

      /** 
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{action}
       * @block_sig{Motor.stop();}
       * @brief Stops the motor using the default brake mode.
       */
      void            stop( void );

      /** 
       * @prog_lang{cpp|pro}
       * @drawer_cat{action}
       * @block_sig{Motor.stop(vex::brakeType::coast);}
       * @brief Stops the motor using a specified brake mode.
       * @param mode The brake mode can be set to coast, brake, or hold. 
       */
      void            stop( brakeType mode );

      /** 
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{setting}
       * @block_sig{Motor.setMaxTorque(50,percent);}
       * @cpp_sig{Motor.setMaxTorque(50,vex::percentUnits::pct);}
       * @brief Sets the max torque of the motor.
       * @param value Sets the amount of torque.
       * @param units The measurement unit for the torque value.
       */
      void            setMaxTorque( double value, percentUnits units );

      /** 
       * @prog_lang{pro}
       * @drawer_cat{setting}
       * @block_sig{Motor.setMaxTorque(1,vex::torqueUnits::Nm);}
       * @brief Sets the max torque of the motor.
       * @param value Sets the amount of torque.
       * @param units The measurement unit for the torque value.
       */
      void            setMaxTorque( double value, torqueUnits units );
      
      /** 
       * @prog_lang{pro}
       * @drawer_cat{setting}
       * @block_sig{Motor.setMaxTorque(1.25,vex::currentUnits::amps);}
       * @brief Sets the max torque of the motor.
       * @param value Sets the amount of torque.
       * @param units The measurement unit for the torque value.
       */
      void            setMaxTorque( double value, currentUnits units );
      
      // sensing

      /** 
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{sensing}
       * @block_sig{Motor.direction()}
       * @brief Gets which direction the motor is spinning.
       * @return Returns the direction that the motor is spinning.
       */
      directionType   direction( void );

      /** 
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{sensing}
       * @block_sig{Motor.rotation(degrees)}
       * @cpp_sig{Motor.rotation(vex::rotationUnits::deg)}
       * @brief Gets the current rotation of the motor's encoder.
       * @returns Returns a double that represents the current rotation of the motor in the units defined in the parameter.
       * @param units The measurement unit for the rotation.
       */
      double          rotation( rotationUnits units );

      /** 
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{sensing}
       * @block_sig{Motor.position(degrees)}
       * @cpp_sig{Motor.position(vex::rotationUnits::deg)}
       * @brief Gets the current position of the motor's encoder.
       * @returns Returns a double that represents the current position of the motor in the units defined in the parameter.
       * @param units The measurement unit for the position.
       */
      double          position( rotationUnits units );

       /** 
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{sensing}
       * @block_sig{Motor.velocity(rpm)}
       * @cpp_sig{Motor.velocity(vex::velocityUnits::pct)}
       * @brief Gets the current velocity of the motor.
       * @return Returns a double that represents the current velocity of the motor in the units defined in the parameter.
       * @param units The measurement unit for the velocity.
       */
      double          velocity( velocityUnits units );

      double          velocity( percentUnits units ) {
          return velocity( static_cast<velocityUnits>(units) );
      };

      /** 
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{sensing}
       * @block_sig{Motor.current(amp)}
       * @cpp_sig{Motor.current(vex::currentUnits::amp)}
       * @brief Gets the electrical current of the motor.
       * @return Returns a double that represents the electrical current of the motor in the units defined in the parameter.
       * @param units The measurement unit for the current.
       */
      double          current( currentUnits units = currentUnits::amp );

      /** 
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{sensing}
       * @block_sig{Motor.current(percent)}
       * @cpp_sig{Motor.current(vex::percentUnits::pct)}
       * @brief Gets the electrical current of the motor in percentage of maximum.
       * @return Returns a double that represents the electrical current of the motor as percentage of max current.
       * @param units The measurement unit for the current.
       */
      double          current( percentUnits units );

      /** 
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{sensing}
       * @block_sig{Motor.power(watt);}
       * @cpp_sig{Motor.power(vex::powerUnits::watt)}
       * @brief Gets the power of the motor.
       * @return Returns a double that represents the power of the motor in the units defined in the parameter.
       * @param units The measurement unit for the power.
       */
      double          power( powerUnits units = powerUnits::watt );

      /** 
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{sensing}
       * @block_sig{Motor.torque(newtonMeters)}
       * @cpp_sig{Motor.torque(vex::torqueUnits::Nm)}
       * @brief Gets the torque of the motor.
       * @return Returns a double that represents the torque of the motor in the units defined in the parameter.
       * @param units The measurement unit for the torque.
       */
      double          torque( torqueUnits units = torqueUnits::Nm );

      /** 
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{sensing}
       * @block_sig{Motor.efficiency(percent)}
       * @cpp_sig{Motor.efficiency(vex::percentUnits::pct)}
       * @brief Gets the efficiency of the motor.
       * @return Returns the efficiency of the motor in the units defined in the parameter.
       * @param units (Optional) The measurement unit for the efficiency. By default, this parameter is a percentage.
       */
      double          efficiency( percentUnits units = percentUnits::pct );

      /** 
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{sensing}
       * @block_sig{Motor.temperature(percent)}
       * @cpp_sig{Motor.temperature(vex::percentUnits::pct)}
       * @brief Gets the temperature  of the motor.
       * @return Returns the temperature of the motor in the units defined in the parameter.
       * @param units The measurement unit for the temperature.
       */
      double          temperature( percentUnits units = percentUnits::pct );
      
      /** 
       * @prog_lang{cpp|pro}
       * @drawer_cat{sensing}
       * @block_sig{Motor.temperature(vex::temperatureUnits::celsius)}
       * @brief Gets the temperature  of the motor.
       * @return Returns the temperature of the motor in the units defined in the parameter.
       * @param units The measurement unit for the temperature.
       */
      double          temperature( temperatureUnits units );
            
    protected:
      int32_t         getTimeout();
    
    private:
      int32_t         _timeout;
      int32_t         _velocity;
      brakeType       _mode;
      brakeType       _brakeMode;
      bool            _spinMode;
            
      void            defaultStopping( brakeType mode );

      void            setRotationUnits( rotationUnits units );
      double          velocityToScaled( double velocity, velocityUnits units );
      int32_t         scaledToVelocity( double value, velocityUnits units );
      double          torqueToCurrent( double torque );
  };
};

#endif // VEX_MOTOR_CLASS_H