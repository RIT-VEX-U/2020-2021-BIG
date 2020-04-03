/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Copyright (c) Innovation First 2017-2019, All rights reserved.          */
/*                                                                            */
/*    Module:     vex_vision.h                                                */
/*    Author:     James Pearman                                               */
/*    Created:    30 June 2017                                                */
/*                                                                            */
/*    Revisions:                                                              */
/*                V1.00     TBD - Initial release                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef   VEX_VISION_CLASS_H
#define   VEX_VISION_CLASS_H

/*-----------------------------------------------------------------------------*/
/** @file    vex_vision.h
  * @brief   Vision sensor device class header
*//*---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------*/
/** @brief Vision sensor device class                                          */
/*-----------------------------------------------------------------------------*/
namespace vex {
  /** 
    * @prog_lang{block|cpp|pro}
    * @brief Use this class when programming the vision sensor.
  */
  class vision : public device {
    private:
      #define VISION_MAX_OBJECTS               16
      #define VISION_DEFAULT_SNAPSHOT_OBJECTS   8
      
      // Variadic template for signature setting
      void _setsig() {};
      template <typename signature, typename... Args>
      void _setsig( signature &sig, Args &... args ) {
        setSignature( sig );
        _setsig( args... );
      }
            
    public:

     /** 
      * @prog_lang{cpp|pro}
      * @drawer_cat{constructor}
      * @block_sig{vex::vision Vision = vex::vision(vex::PORT1);}
      * @brief Creates a new vision object on the port specified.
      * @param index The port index for this vision. The index is zero-based.
      */  
      vision( int32_t index );  
      ~vision();

     /** 
      * @prog_lang{cpp|pro}
      * @drawer_cat{constructor}
      * @block_sig{vex::vision Vision = vex::vision(vex::PORT1, 60, sigObj1, sigObj2, sigObj3, sigObj4, sigObj5, sigObj6, sigObj7);}
      * @brief Creates a new vision object on the port specified. Sets the brightness setting and all of the vision objects settings.
      * @param index The port index for this vision. The index is zero-based.
      * @param bright The vision sensor brightness setting. Values are 0 to 255
      * @param sigs List of signature objects used to setup the detection signatures for this sensor.
      */
      template <typename... Args>
      vision( int32_t index, uint8_t bright, Args &... sigs  ) : vision( index ) {
        setBrightness( bright );
        _setsig( sigs... );
      }
       
      bool            installed();
      int32_t         value();

      enum class detectionMode {
        objectDetect = kVisionModeNormal,
        mixedDetect  = kVisionModeMixed,
        lineDetect   = kVisionModeLineDetect,
        test         = kVisionTypeTest
      };
      
      enum class whiteBalanceMode {
        automatic    = kVisionWBNormal,
        start        = kVisionWBStart,
        manual       = kVisionWBManual
      };

      enum class ledMode {
        automatic    = kVisionLedModeAuto,
        manual       = kVisionLedModeManual
      };

      enum class wifiMode {
        off          = kVisionWifiModeOff,
        on           = kVisionWifiModeOn
      };
      
      /** 
       * @prog_lang{block|cpp|pro}
       * @brief The object class represents an object that the vision sensor detects.
      */  
      class object {          
          int     _id;
          int     _originX;
          int     _originY;
          int     _centerX;
          int     _centerY;
          int     _width;
          int     _height;
          double  _angle;
          bool    _exists;
      
        public:

          /** 
           * @prog_lang{pro}
           * @drawer_cat{constructor|none}
           * @brief Creates a new vision object with all properties set to default values.
           */
          object();
          ~object();
        
          /** 
           * @prog_lang{pro}
           * @drawer_cat{action|none}
           * @brief Copies all properties of the passed in object into this object.
           * @param obj The object whose properties are to be copied.
           */
          void      set( V5_DeviceVisionObject obj );
        
          /** 
           * @prog_lang{pro}
           * @drawer_cat{action|none}
           * @brief Inverts the angle for this object.
           */
          void      flipAngle();

          /**
           * @prog_lang{pro}
           * @drawer_cat{action|none}
           * @brief Sets all properties for this object to default values.
           */
          void      clear();
        
          object& operator=( const object &obj );
          object& operator=( int32_t signatureId );
 
           /**
           * @prog_lang{block|cpp|pro}
           * @drawer_cat{sensing}
           * @block_sig{id}
           * @brief The unique ID of the object.
           */
          const int  &id;
          /**
           * @prog_lang{block|cpp|pro}
           * @drawer_cat{sensing}
           * @block_sig{originX}
           * @brief The top left x position of the object.
           */
          const int  &originX;
          /**
           * @prog_lang{block|cpp|pro}
           * @drawer_cat{sensing}
           * @block_sig{originY}
           * @brief The top left y position of the object.
           */
          const int  &originY;
          /**
           * @prog_lang{block|cpp|pro}
           * @drawer_cat{sensing}
           * @block_sig{centerX}
           * @brief The center x position of the object.
           */
          const int  &centerX;
          /**
           * @prog_lang{block|cpp|pro}
           * @drawer_cat{sensing}
           * @block_sig{centerY}
           * @brief The center y position of the object.
           */
          const int  &centerY;
          /**
           * @prog_lang{block|cpp|pro}
           * @drawer_cat{sensing}
           * @block_sig{width}
           * @brief The width of the object.
           */
          const int  &width;
          /**
           * @prog_lang{block|cpp|pro}
           * @drawer_cat{sensing}
           * @block_sig{height}
           * @brief The height of the object.
           */
          const int  &height;
          /**
           * @prog_lang{block|cpp|pro}
           * @drawer_cat{sensing}
           * @block_sig{angle}
           * @brief The angle of the object.
           */
          const double &angle;
          /**
           * @prog_lang{block|cpp|pro}
           * @drawer_cat{sensing}
           * @block_sig{exists}
           * @brief If the vision sensor detects the object or not.
           */
          const bool &exists;
      };
        
      /**
       * @prog_lang{pro}
       * @brief Use this class when programming the vision sensor.
      */
      class signature {
        friend class vex::vision;

        private:
          #define   MAX_MAME    32

          int32_t   _id;
          int32_t   _uMin;
          int32_t   _uMax;
          int32_t   _uMean;
          int32_t   _vMin;
          int32_t   _vMax;
          int32_t   _vMean;
          float     _range;
          uint32_t  _rgb;
          uint32_t  _type;

          void      clear();
                  
          static void setTypeColorCode() {};
          template <typename signature, typename... Args>
          static void setTypeColorCode( signature &sig, Args &... args ) {
            sig._type = 1;
            setTypeColorCode( args... );
          }

        public:
          signature();
          ~signature();
          
         /** 
          * @prog_lang{cpp|pro}
          * @drawer_cat{constructor}
          * @block_sig{vex::vision::signature Signature = vex::vision::signature( id, uMin, uMax, uMean, vMin, vMax, vMean, range, type );}
          * @brief Creates a new vision signature object.
          * @param id The signature id.
          * @param uMin The signature minimum value on the u axis.
          * @param uMax The signature maximum value on the u axis.
          * @param uMean The signature mean value on the u axis.
          * @param vMin The signature minimum value on the v axis.
          * @param vMax The signature maximum value on the v axis.
          * @param vMean The signature mean value on the v axis.
          * @param range The signature range scale factor.
          * @param type The signature type, normal, or color code.
          */  
          signature( int32_t id, int32_t uMin, int32_t uMax, int32_t uMean, int32_t vMin, int32_t vMax, int32_t vMean, float range, int32_t type );


          // read only references to internal variables
          const int32_t   &id;
          const int32_t   &uMin;
          const int32_t   &uMax;
          const int32_t   &uMean;
          const int32_t   &vMin;
          const int32_t   &vMax;
          const int32_t   &vMean;
          const float     &range;
          const uint32_t  &rgb;
          const uint32_t  &type;
      };
      
    /**
     * @prog_lang{pro}
     * @brief Use this class when programming the vision sensor.
     */
    class code {
        private:
          uint32_t _code;
          bool     _flipped = false;
        
        public:
          code(int32_t sig1, int32_t sig2);
          code(int32_t sig1, int32_t sig2, int32_t sig3);
          code(int32_t sig1, int32_t sig2, int32_t sig3, int32_t sig4);
          code(int32_t sig1, int32_t sig2, int32_t sig3, int32_t sig4, int32_t sig5 );
  
         /** 
          * @prog_lang{cpp|pro}
          * @drawer_cat{constructor}
          * @block_sig{vex::vision::code Code  = vex::vision::code( sig1, sig2 );}
          * @brief Creates a new vision code object.
          * @param s1 The first signature which is part of the color code.
          * @param s2 The second signature which is part of the color code.
          */  

          code( signature &s1, signature &s2 );
          code( signature &s1, signature &s2, signature &s3 );
          code( signature &s1, signature &s2, signature &s3, signature &s4 );
          code( signature &s1, signature &s2, signature &s3, signature &s4, signature &s5 ); 
      
          uint32_t getCode()   { return _code;    }
          bool     isFlipped() { return _flipped; } 
      };      
       
      // from master spec
      /**
       * @prog_lang{cpp|pro}
       * @drawer_cat{action}
       * @block_sig{Vision.takeSnapshot(1);}
       * @brief Takes a data sample from the vision sensor.
       * @return Returns the number of objects found from the ID passed in the parameter.
       * @param id The ID of the object to look for.
       */ 
      int32_t         takeSnapshot( uint32_t id );

      /**
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{action}
       * @block_sig{Vision.takeSnapshot(codeSig);}
       * @brief Takes a data sample from the vision sensor.
       * @return Returns the number of objects found from the code signature passed in the parameter. 
       * @return_type_override{void}
       * @param cc The code signature of the object to look for.
       */
      int32_t         takeSnapshot( code &cc );

      /**
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{action}
       * @block_sig{Vision.takeSnapshot(SIG1);}
       * @brief Takes a data sample from the vision sensor. 
       * @return Returns a number of objects found from the signature passed in the parameter. 
       * @return_type_override{void}
       * @param sig The signature of the object to look for.
       */
      int32_t         takeSnapshot( signature &sig );

      /**
       * @prog_lang{cpp|pro}
       * @drawer_cat{action}
       * @block_sig{Vision.takeSnapshot(1,5);}
       * @brief Takes a data sample from the vision sensor, and only stores  the largest samples of the specified amount.
       * @return Returns a limited number of objects found from the ID passed in the parameter.
       * @param id The ID of the object to look for.
       * @param count the amount  of objects to look for. The largest of the object will be returned.
       */
      int32_t         takeSnapshot( uint32_t id, uint32_t count );

      /**
       * @prog_lang{cpp|pro}
       * @drawer_cat{action}
       * @block_sig{Vision.takeSnapshot(sigCode,5);}
       * @brief Takes a data sample from the vision sensor, and only stores  the largest samples of the specified amount.
       * @return Returns a limited number of objects found from the code signature passed in the parameter.
       * @param cc The code signature of the object to look for.
       * @param count the amount  of objects to look for. The largest of the object will be returned.
       */
      int32_t         takeSnapshot( code &cc, uint32_t count );

      /**
       * @prog_lang{cpp|pro}
       * @drawer_cat{action}
       * @block_sig{Vision.takeSnapshot(SIG1,5);}
       * @brief Takes a data sample from the vision sensor, and only stores  the largest samples of the specified amount.
       * @return Returns a limited number of objects found from the signature passed in the parameter.
       * @param sig The signature of the object to look for.
       * @param count the amount  of objects to look for. The largest of the object will be returned.
       */
      int32_t         takeSnapshot( signature &sig, uint32_t count );

      /**
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{sensing}
       * @block_sig{Vision.objectCount}
       * @brief The amount of objects found in the data sample.
       */
      int32_t         objectCount;

      /**
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{instance}
       * @block_sig{Vision.largestObject}
       * @brief The largest object found in the data sample.
       */
      object          largestObject;

      /**
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{instance}
       * @block_sig{Vision.objects[0]}
       * @brief An array containing the largest object(s) found in the data sample.
       * @type_override{object}
       * @identifier_override{objects[12]}
       */
      safearray< object, VISION_MAX_OBJECTS > objects;  

      // not part of current spec
      bool            setSignature( V5_DeviceVisionSignature *pSignature );
      bool            getSignature( uint32_t id, V5_DeviceVisionSignature *pSignature );
      bool            setSignature( signature &sig );
      bool            getSignature( uint32_t id, signature &sig );
      bool            setMode( detectionMode mode );
      detectionMode   getMode( void );
      bool            setBrightness( uint8_t value );
      uint8_t         getBrightness( void );
      bool            setWhiteBalanceMode( whiteBalanceMode mode );
      whiteBalanceMode getWhiteBalanceMode( void );
      bool            setWhiteBalanceValues( uint8_t red, uint8_t green, uint8_t blue );
      bool            getWhiteBalanceValues( uint8_t *red, uint8_t *green, uint8_t *blue );

      /**
       * @prog_lang{cpp|pro}
       * @drawer_cat{setting}
       * @block_sig{Vision.setLedMode(vex::tLedMode::manual);}
       * @brief Changes the mode of the LED on the vision sensor.
       * @param mode The LED mode. Automatic mode will cause the LED color to be controlled by the vision sensor firmware. Manual mode allows the LED color to be controlled by the user program.
       * @return Returns true if setting was successfully saved.
       */
      bool            setLedMode( ledMode mode );

      /**
       * @prog_lang{cpp|pro}
       * @drawer_cat{sensing}
       * @block_sig{Vision.getLedMode()}
       * @brief Gets the mode of the LED from the vision sensor.
       * @return Returns a tLedMode that represents the current mode of the vision sensor LED.
       */
      ledMode         getLedMode( void );

      /**
       * @prog_lang{cpp|pro}
       * @drawer_cat{setting}
       * @block_sig{Vision.setLedBrightness(50);}
       * @brief Changes the brightness of the LED on the vision sensor when LED is set to manual mode.
       * @param percent A percentage of total brightness of the vision sensor LED when in manual mode. Values are 0 to 100. 0 = LED off
       * @return Returns true if setting was successfully saved.
       */
      bool            setLedBrightness( uint8_t percent );

      /**
       * @prog_lang{cpp|pro}
       * @drawer_cat{sensing}
       * @block_sig{Vision.getLedBrightness()}
       * @brief Gets the brightness of the LED from the vision sensor.
       * @return Returns a value between 0 and 100 that represents the current brightness of the vision sensor LED.
       */
      uint8_t         getLedBrightness( void );

      /**
       * @prog_lang{cpp|pro}
       * @drawer_cat{setting}
       * @block_sig{Vision.setLedColor(0, 255, 0);}
       * @brief Changes the color of the LED on the vision sensor when LED is set to manual mode.
       * @param red A value from 0 to 255 the represents the intensity of the red color of the LED.
       * @param green A value from 0 to 255 the represents the intensity of the green color of the LED.
       * @param blue A value from 0 to 255 the represents the intensity of the blue color of the LED. 
       * @return Returns true if setting was successfully saved.
       */
      bool            setLedColor( uint8_t red, uint8_t green, uint8_t blue );

      /**
       * @prog_lang{cpp|pro}
       * @drawer_cat{sensing}
       * @block_sig{Vision.getLedColor(0, 255, 0)}
       * @brief Gets the color of the LED from the vision sensor.
       * @param red A reference to a value to store the intensity of the red color of the LED.
       * @param green A reference to a value to store the intensity of the green color of the LED.
       * @param blue A reference to a value to store the intensity of the blue color of the LED.
       * @return Returns true if values were sucessfully recived. 
       */
      bool            getLedColor( uint8_t *red, uint8_t *green, uint8_t *blue );

      
      bool            setWifiMode( wifiMode mode );
      wifiMode        getWifiMode( void );
                  
    private:
      // storage for raw data from camera
      V5_DeviceVisionObject _objects[ VISION_MAX_OBJECTS ];
      // set all objects to 0
      void               _clearObjects( void );
  };
};

typedef vex::vision::object     VexVisionObject;
typedef vex::vision::code       VisionCode;

#endif // VEX_VISION_CLASS_H