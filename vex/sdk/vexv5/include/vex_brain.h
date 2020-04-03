/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Copyright (c) Innovation First 2017-2019, All rights reserved.          */
/*                                                                            */
/*    Module:     vex_brain.h                                                 */
/*    Author:     James Pearman                                               */
/*    Created:    8 July 2017                                                 */
/*                                                                            */
/*    Revisions:                                                              */
/*                V1.00     TBD - Initial release                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef   VEX_BRAIN_CLASS_H
#define   VEX_BRAIN_CLASS_H

#include "vex_triport.h"
#include "vex_timer.h"
#include "vex_global.h"

/*-----------------------------------------------------------------------------*/
/** @file    vex_brain.h
  * @brief   V5 brain class header
*//*---------------------------------------------------------------------------*/

namespace vex {
  /** 
    * @prog_lang{block|cpp|pro}
    * @brief Use the brain class to see battery information, SD card information, or write to the Screen.
  */
  class brain {
    friend class competition;
    
    private:

    protected:
      static int32_t _getIndex();
      
    public:

    /** 
      * @prog_lang{cpp|pro}
      * @drawer_cat{constructor}
      * @block_sig{vex::brain Brain = vex::brain();}
      * @brief Creates a new brain object.
    */
      brain();
      ~brain();

      enum class tEventType {
        EVENT_LCD_PRESSED    = 0,
        EVENT_LCD_RELEASED   = 1
      };
      /** 
        * @prog_lang{block|cpp|pro}
        * @brief Use this class to write or draw to the brain's LCD screen.
      */      
      class lcd {
        private:
          int32_t   _row;
          int32_t   _maxrows;
          int32_t   _rowheight;

          int32_t   _col;
          int32_t   _maxcols;
          int32_t   _colwidth;

          int32_t   _penWidth;

          uint32_t  _textbase;
                    
          char      _textStr[256];

          int32_t   rowToPixel( int32_t row );
          int32_t   colToPixel( int32_t col );

          bool      _transparent;
          
          int       _origin_x;
          int       _origin_y;
          
          #define   FONT_MONO_CELL_WIDTH   10    
          #define   FONT_MONO_CELL_HEIGHT  20
          #define   FONT_MONO_CELL_BASE     4         
            
          // Not sure what to do with this yet
          // does not make much sense with proportional font 
          // but we need to specify a location somehow
          #define   FONT_PROP_CELL_WIDTH   10    
          #define   FONT_PROP_CELL_HEIGHT  20
          #define   FONT_PROP_CELL_BASE     4         
                    
        public:
          lcd();
          ~lcd() {};
                  
          /** 
           * @prog_lang{block|cpp|pro}
           * @drawer_cat{setting}
           * @block_sig{setCursor(1,1);}
           * @brief Sets the cursor to the row and column number set in the parameters.
           * @param row Sets the row number for where the cursor is placed.
           * @param col Sets the column number for where the cursor is placed. 
          */
          void     setCursor( int32_t row, int32_t col );
          
          /** 
           * @prog_lang{block|cpp|pro}
           * @drawer_cat{setting}
           * @block_sig{setFont(mono20);}
           * @cpp_sig{setFont(vex::fontType::mono20);}
           * @brief Sets the font type to be displayed on the Screen that is determined by the parameter.
           * @param font The type of font that is displayed.
          */
          void     setFont( fontType font );

          /** 
           * @prog_lang{block|cpp|pro}
           * @drawer_cat{setting}
           * @block_sig{setPenWidth(5);}
           * @brief Sets the pen's width.
           * @param width This represents the width of the pen when drawing. A larger width equals a wider pen stroke.
          */
          void     setPenWidth( uint32_t width ); 

          /** 
           * @prog_lang{cpp|pro}
           * @drawer_cat{setting}
           * @block_sig{setOrigin(1,1);}
           * @brief Sets the origin of the screen to the parameters defined in the function.
           * @param x The x location of the origin.
           * @param y The y location of the origin.
          */
          void     setOrigin( int32_t x, int32_t y );


          /** 
           * @prog_lang{block|cpp|pro}
           * @drawer_cat{sensing}
           * @block_sig{column()}
           * @brief An integer that tracks the current cursor position's column, starting at 1.
           * @return Returns an integer that tracks the current cursor position's column, starting at 1.
          */
          int32_t  column();

          /** 
           * @prog_lang{block|cpp|pro}
           * @drawer_cat{sensing}
           * @block_sig{row()}
           * @brief An integer that tracks the current cursor position's row, starting at 1.
           * @return Returns an integer that tracks the current cursor position's row, starting at 1.
          */
          int32_t  row();


          
          template <class T>
          void     setPenColor( T color ) {
              _setPenColor( (uint32_t)color );
          }

          /** 
           * @prog_lang{block|cpp|pro}
           * @drawer_cat{setting}
           * @block_sig{setPenColor(red);}
           * @cpp_sig{setPenColor(vex::color::red);}
           * @brief Sets the color of the pen to a specified color.
           * @param color A color unit where colors can be defined as names.
          */          
          void     setPenColor( const color& color );

          /** 
           * @prog_lang{pro}
           * @drawer_cat{setting}
           * @block_sig{setPenColor("#FF0000");}
           * @brief Sets the color of the pen to a specified color using a hex value.
           * @param color A hexadecimal value that represents color.
          */ 
          void     setPenColor( const char *color );

          /** 
           * @prog_lang{pro}
           * @drawer_cat{setting}
           * @block_sig{setPenColor(50);}
           * @brief Sets the color of the pen to a specified color.
           * @param hue The integer represents the hue of the color.
          */ 
          void     setPenColor( int hue ); 


          // not part of spec, may be removed
          template <class T>
          void     setFillColor( T color ) {
              _setFillColor( (uint32_t)color );
          }

          /** 
           * @prog_lang{block|cpp|pro}
           * @drawer_cat{setting}
           * @block_sig{setFillColor(red);}
           * @cpp_sig{setFillColor(vex::color::red);}
           * @brief Sets the default fill color for any subsequent draw command.
           * @param color In a color unit, colors can be defined as names.
          */          
          void     setFillColor( const color& color );

          /** 
           * @prog_lang{pro}
           * @drawer_cat{setting}
           * @block_sig{setFillColor("#FF0000");}
           * @brief Sets the default fill color for any subsequent draw command..
           * @param color A hexadecimal value that represents color.
          */ 
          void     setFillColor( const char *color ); 

          /** 
           * @prog_lang{pro}
           * @drawer_cat{setting}
           * @block_sig{setFillColor(50);}
           * @brief Sets the default fill color for any subsequent draw command.
           * @param hue The integer represents the hue of the color.
          */
          void     setFillColor( int hue );

          /** 
           * @prog_lang{pro}
           * @drawer_cat{sensing}
           * @block_sig{getStringWidth("Hello World")}
           * @brief Gets the width in pixels of the given string.
           * @return Returns an integer that represents the width of the string in pixels.
          */
          int32_t  getStringWidth( const char *cstr );

          /** 
           * @prog_lang{pro}
           * @drawer_cat{sensing}
           * @block_sig{getStringHeight("Hello World")}
           * @brief Gets the height in pixels of the given string.
           * @return Returns an integer that represents the height of the string in pixels.
          */
          int32_t  getStringHeight( const char *cstr );
          
          /** 
           * @prog_lang{block}
           * @drawer_cat{action}
           * @block_sig{print("Hello");}
           * @brief Prints a number, string, or Boolean.
           * @param value Information to display on the screen.
           * @parameter_defaults_overrides{"Hello"|1|true}
           * @parameter_type_overrides{string|number|boolean}
           * @parameter_identifier_overrides{value|value|value}
          */  
          template <class T>
          void     print( T value ) {
            if( std::is_same< T, int >::value )
              print( "%d", (int)value );
            else
            if( std::is_same< T, double >::value )
              print( "%.2f", (double)value );
            else {
              // primarily to handle modkit number
              if( (int)value == value )
                print( "%d", (int)value );
              else
                print( "%.2f", (double)value );
            }
          }

          /** 
           * @prog_lang{cpp|pro}
           * @drawer_cat{action}
           * @block_sig{print("Hello");}
           * @brief Prints a number, string, or Boolean.
           * @param format This is a reference to a char format that prints the value of variables.
           * @param ... A variable list of parameters to insert into format string.
          */          
          void     print( const char *format, ... );
          void     print( char *format, ... );

          /** 
           * @prog_lang{cpp|pro}
           * @drawer_cat{action}
           * @block_sig{printAt(1,40,"Hello");}
           * @brief Prints a number, string, or Boolean at an x, y pixel location.
           * @param x The x-coordinate at which to print a message on the screen.
           * @param y The y-coordinate at which to print a message on the screen.
           * @param format A reference to a char format to print the value of variables.
           * @param ... A variable list of parameters to insert into format string.
          */
          void     printAt( int32_t x, int32_t y, const char *format, ... );

          /** 
           * @prog_lang{pro}
           * @drawer_cat{action}
           * @block_sig{printAt(1,40,true,"Hello");}
           * @brief Prints a number, string, or Boolean at an x, y pixel location with the ability to be transparent.
           * @param x The x pixel location where the print should start
           * @param y The y pixel location where the print should start
           * @param bOpaque If set to false, the print will be transparent.
           * @param format A reference to a char format to print the value of variables.
           * @param ... A variable list of parameters to insert into format string. 
          */
          void     printAt( int32_t x, int32_t y, bool bOpaque, const char *format, ... );
          
          template <class T>
          void     clearScreen( T color ) {
              _clearScreen( (uint32_t)color );
          }

          /** 
           * @prog_lang{block|cpp|pro}
           * @drawer_cat{action}
           * @block_sig{clearScreen();}
           * @brief Clears the whole Screen to a default color or otherwise specified color.
          */          
          void     clearScreen( void );

          /** 
           * @prog_lang{cpp|pro}
           * @drawer_cat{action}
           * @block_sig{clearScreen(vex::color::red);}
           * @brief Clears the whole Screen to a default color or otherwise specified color.
           * @param color In a color unit, colors can be defined as names. 
          */
          void     clearScreen( const color& color );

          /** 
           * @prog_lang{pro}
           * @drawer_cat{action}
           * @block_sig{clearScreen("#FF0000");}
           * @brief Clears the whole Screen to a default color or otherwise specified color.
           * @param color A hexadecimal value that represents color.
          */
          void     clearScreen( const char *color );

          /** 
           * @prog_lang{pro}
           * @drawer_cat{action}
           * @block_sig{clearScreen(50);}
           * @brief Clears the whole Screen to a default color or otherwise specified color.
           * @param hue The integer represents the hue of the color.
          */
          void     clearScreen( int hue );
          
          template <class T1, class C>
          void     clearLine( T1 number, C color ) {
            if( std::is_same< C, vex::color >::value ) 
              clearLine( (int)number, color );
            else
            if( std::is_same< C, const char * >::value )
              clearLine( (int)number, color );
            else
            if( std::is_same< C, int >::value )
              clearLine( (int)number, color );
            else
              _clearLine( (int)number, (uint32_t)color );
          }

          /** 
           * @prog_lang{cpp|pro}
           * @drawer_cat{action}
           * @block_sig{clearLine(1,vex::color::red);}
           * @brief Clears the specified line and sets it to a specified color.
           * @param number The integer sets the line that is to be cleared.
           * @param color A color unit where colors can be defined as names.
          */          
          void     clearLine( int number, const color& color );

          /** 
           * @prog_lang{pro}
           * @drawer_cat{action}
           * @block_sig{clearLine(1,"#FF0000");}
           * @brief Clears the specified line and sets it to a specified color.
           * @param number The integer sets the line that is to be cleared.
           * @param color A hexadecimal value that represents color.
          */
          void     clearLine( int number, const char *color );

          /** 
           * @prog_lang{pro}
           * @drawer_cat{action}
           * @block_sig{clearLine(1, 50);}
           * @brief Clears the specified line and sets it to a specified color.
           * @param number The integer sets the line that is to be cleared.
           * @param hue An integer that represents the hue of the color.
          */
          void     clearLine( int number, int hue );

          /** 
           * @prog_lang{pro}
           * @drawer_cat{action}
           * @block_sig{clearLine(1);}
           * @brief Clears the specified line and sets it to the background color.
           * @param number The integer sets the line that is to be cleared.
          */
          void     clearLine( int number );

          /** 
           * @prog_lang{block|cpp|pro}
           * @drawer_cat{action}
           * @block_sig{clearLine();}
           * @brief Clears the rest of the line from where the cursor is located. 
          */
          void     clearLine( void );

          /** 
           * @prog_lang{block|cpp|pro}
           * @drawer_cat{action}
           * @block_sig{newLine();}
           * @brief Clears the rest of the line from where the cursor is located and then moves the cursor to the beginning of the next line.
          */
          void     newLine( void );
          
          
          /** 
           * @prog_lang{block|cpp|pro}
           * @drawer_cat{action}
           * @block_sig{drawPixel(50,50);}
           * @brief Draws a single pixel to the screen in the specified x and y location.
           * @param x The x location of where to draw the pixel.
           * @param y The y location of where to draw the pixel.
          */
          void     drawPixel( int x, int y );

          /** 
           * @prog_lang{block|cpp|pro}
           * @drawer_cat{action}
           * @block_sig{drawLine(1,1,50,50);}
           * @brief Draws a line connecting the two specified points in the parameters.
           * @param x1 The x location of the first point.
           * @param y1 The y location of the first point.
           * @param x2 The x location of the second point.
           * @param y2 The y location of the second point.
          */
          void     drawLine( int x1, int y1, int x2, int y2 );

          // Rectangle
          template <class T1, class T2, class T3, class T4, class C>
          void     drawRectangle( T1 x, T2 y, T3 width, T4 height, C color ) {
            if( std::is_same< C, vex::color >::value ) 
              drawRectangle( (int)x, (int)y, (int)width, (int)height, color );
            else
            if( std::is_same< C, const char * >::value )
              drawRectangle( (int)x, (int)y, (int)width, (int)height, color );
            else
            if( std::is_same< C, int >::value )
              drawRectangle( (int)x, (int)y, (int)width, (int)height, color );
            else
              _drawRectangle( (int)x, (int)y, (int)width, (int)height, (uint32_t)color );
          }

          /** 
           * @prog_lang{block|cpp|pro}
           * @drawer_cat{action}
           * @block_sig{drawRectangle(1,1, 50, 20);}
           * @brief Draws a rectangle using the specified points and attributes set in the parameters. Fills the rectangle with the current pen and fill color.
           * @param x The x-coordinate at which the left edge of the rectangle will be drawn on the screen.
           * @param y The y-coordinate at which the top edge of the rectangle will be drawn on the screen.
           * @param width The width of the rectangle.
           * @param height The height of the rectangle.
          */
          void     drawRectangle( int x, int y, int width, int height );

          /** 
           * @prog_lang{cpp|pro}
           * @drawer_cat{action}
           * @block_sig{drawRectangle(1,1,50,20,vex::color::red);}
           * @brief Draws a rectangle using the specified points and attributes set in the parameters. Fills the rectangle with the color specified.
           * @param x The x-coordinate at which the left edge of the rectangle will be drawn on the screen.
           * @param y The y-coordinate at which the top edge of the rectangle will be drawn on the screen.
           * @param width The width of the rectangle.
           * @param height The height of the rectangle.
           * @param color A color unit where colors can be defined as names.
          */
          void     drawRectangle( int x, int y, int width, int height, const color& color );

          /** 
           * @prog_lang{pro}
           * @drawer_cat{action}
           * @block_sig{drawRectangle(1,1,50,20,"#FF0000");}
           * @brief Draws a rectangle using the specified points and attributes set in the parameters. Fills the rectangle with the color specified.
           * @param x The x-coordinate at which the left edge of the rectangle will be drawn on the screen.
           * @param y The y-coordinate at which the top edge of the rectangle will be drawn on the screen.
           * @param width The width of the rectangle.
           * @param height The height of the rectangle.
           * @param color A hexadecimal value that represents color.
          */
          void     drawRectangle( int x, int y, int width, int height, const char *color );

          /** 
           * @prog_lang{pro}
           * @drawer_cat{action}
           * @block_sig{drawRectangle(1,1,50,20,50);}
           * @brief Draws a rectangle using the specified points and attributes set in the parameters. Fills the rectangle with the color specified.
           * @param x The x-coordinate at which the left edge of the rectangle will be drawn on the screen.
           * @param y The y-coordinate at which the top edge of the rectangle will be drawn on the screen.
           * @param width The width of the rectangle.
           * @param height The height of the rectangle. 
           * @param hue The color of the rectangle.
          */
          void     drawRectangle( int x, int y, int width, int height, int hue );




          // Circles
          template <class T1, class T2, class T3, class C>
          void     drawCircle( T1 x, T2 y, T3 radius, C color ) {
            if( std::is_same< C, vex::color >::value ) 
              drawCircle( (int)x, (int)y, (int)radius, color );
            else
            if( std::is_same< C, const char * >::value )
              drawCircle( (int)x, (int)y, (int)radius, color );
            else
            if( std::is_same< C, int >::value )
              drawCircle( (int)x, (int)y, (int)radius, color );
            else
              _drawCircle( (int)x, (int)y, (int)radius, (uint32_t)color );
          }
          
          /** 
           * @prog_lang{block|cpp|pro}
           * @drawer_cat{action}
           * @block_sig{drawCircle(50,50,20);}
           * @brief Draws a circle using the specified points and attributes set in the parameters. Fills the circle with the current pen and fill color.
           * @param x The central x location of the circle.
           * @param y The central y location of the circle.
           * @param radius Sets the radius of the circle to be drawn on the Screen.
          */
          void     drawCircle( int x, int y, int radius );

          /** 
           * @prog_lang{cpp|pro}
           * @drawer_cat{action}
           * @block_sig{drawCircle(50,50,20,vex::color::red);}
           * @brief Draws a circle using the specified points and attributes set in the parameters. Fills the circle with the color specified.
           * @param x The central x location of the circle.
           * @param y The central y location of the circle.
           * @param radius Sets the radius of the circle to be drawn on the Screen.
           * @param color A color unit where colors can be defined as names.
          */
          void     drawCircle( int x, int y, int radius, const color& color );

          /** 
           * @prog_lang{pro}
           * @drawer_cat{action}
           * @block_sig{drawCircle(50,50,20,"#FF0000");}
           * @brief Draws a circle using the specified points and attributes set in the parameters. Fills the circle with the color specified.
           * @param x The central x location of the circle.
           * @param y The central y location of the circle.
           * @param radius Sets the radius of the circle to be drawn on the Screen.
           * @param color A hexadecimal value that represents color.
          */
          void     drawCircle( int x, int y, int radius, const char *color );

          /** 
           * @prog_lang{pro}
           * @drawer_cat{action}
           * @block_sig{drawCircle(50,50,20,50);}
           * @brief Draws a circle using the specified points and attributes set in the parameters. Fills the circle with the color specified.
           * @param x The central x location of the circle.
           * @param y The central y location of the circle.
           * @param radius Sets the radius of the circle to be drawn on the Screen.
           * @param hue An integer that represents the hue of the color.
          */
          void     drawCircle( int x, int y, int radius, int hue );



          /** 
           * @prog_lang{cpp|pro}
           * @drawer_cat{setting}
           * @block_sig{pressed(pressedFunction);}
           * @brief Sets the function to be called when the Screen is pressed.
           * @param callback A reference to a function.
          */          
          void     pressed( void (* callback)(void) );
          /** 
           * @prog_lang{pro}
           * @drawer_cat{setting|none}
           * @block_sig{pressed(pressedFunction, arg);}
           * @brief Sets the function to be called when the Screen is pressed.  A void pointer may be passed to the callback.
           * @param callback A reference to a function.
           * @param arg A void pointer that will be passed to the callback.
          */          
          void     pressed( void (* callback)(void *), void *arg );

          /** 
           * @prog_lang{cpp|pro}
           * @drawer_cat{setting}
           * @block_sig{released(releasedFunction);}
           * @brief Sets the function to be called when the screen is released after being pressed.
           * @param callback A reference to a function.
          */
          void     released( void (* callback)(void) );
          /** 
           * @prog_lang{pro}
           * @drawer_cat{setting|none}
           * @block_sig{released(releasedFunction, arg);}
           * @brief Sets the function to be called when the screen is released after being pressed.  A void pointer may be passed to the callback.
           * @param callback A reference to a function.
           * @param arg A void pointer that will be passed to the callback.
          */          
          void     released( void (* callback)(void *), void *arg );

          /** 
           * @prog_lang{block|cpp|pro}
           * @drawer_cat{sensing}
           * @block_sig{xPosition()}
           * @brief Gets the last x location pressed on the screen.
           * @return Returns an integer that represents the last x location pressed on the screen.
          */
          int32_t  xPosition();

          /** 
           * @prog_lang{block|cpp|pro}
           * @drawer_cat{sensing}
           * @block_sig{yPosition()}
           * @brief Gets the last y location pressed on the screen.
           * @return Returns an integer that represents the last y location pressed on the screen.
          */
          int32_t  yPosition();

          /** 
           * @prog_lang{block|cpp|pro}
           * @drawer_cat{sensing}
           * @block_sig{pressing()}
           * @brief Gets the pressed status of the Screen.
           * @return Returns a Boolean based on the state of a press on the screen. If the screen is pressed, the Boolean will be true, if the button is released, the Boolean will be false.
          */
          bool     pressing();
          
          /**
           * @prog_lang{pro}
           * @drawer_cat{action}
           * @block_sig{render();}
           * @brief Switches to double buffering or renders back buffer to screen.
           * @return Returns true if the back buffer was successfully copied to the screen.
          */
          bool     render();

          /**
           * @prog_lang{pro}
           * @drawer_cat{action}
           * @block_sig{render(true, true);}
           * @brief Switches to double buffering or renders back buffer to screen.
           * @param bVsyncWait If true, wait for the Vsync signal to render.
           * @param bRunScheduler (Optional) If true, run background tasks while waiting to render. By default, this parameter is true.
           * @return Returns true if the back buffer was successfully copied to the screen.
          */
          bool     render( bool bVsyncWait, bool bRunScheduler=true );

          /** 
           * @prog_lang{pro}
           * @drawer_cat{setting}
           * @block_sig{setClipRegion( 0, 0, 480, 240 );}
           * @brief Sets the clip region for screen output.  Only effects the current thread.
           * @param x The x-coordinate at the left edge of the clip region.
           * @param y The y-coordinate at the top edge of the clip region.
           * @param width The width of the clip region.
           * @param height The height of the clip region. 
          */
          void     setClipRegion( int x, int y, int width, int height );

          /**
           * @prog_lang{pro}
           * @drawer_cat{action}
           * @block_sig{drawImageFromBuffer( buffer, 0, 0, length );}
           * @brief Draws an image on the screen using the contents of the memory buffer.
           * @param buffer A pointer to a buffer containing image data in either bmp or png format.
           * @param x The x-coordinate at which the left edge of the image will be drawn.
           * @param y The y-coordinate at which the top edge of the image will be drawn.
           * @param bufferLen The size of the source image buffer in bytes.
           * @return Returns true if the image was successfully drawn on the screen.
           * @details
           *  This function draws an image on the screen using the contents of a buffer into which
           *  either BMP or PNG raw data has already been read.  The contents may have come from a
           *  file on the SD card or have been statically declared in the code.  The image should be
           *  no larger than the V5 Screen, that is, a maximum of 480 pixels wide by 272 pixels high.
           *  The top/left corner of the image is placed at the coordinates given by x and y, these can
           *  be negative if desired.
          */
          bool     drawImageFromBuffer( uint8_t  *buffer, int x, int y, int bufferLen );

          /**
           * @prog_lang{pro}
           * @drawer_cat{action}
           * @block_sig{drawImageFromBuffer( buffer, 0, 0, 480, 240 );}
           * @brief Draws an image on the screen using the contents of the memory buffer.
           * @param buffer A pointer to a buffer containing raw 32 bit per pixel image data.
           * @param x The x-coordinate at which the left edge of the image will be drawn.
           * @param y The y-coordinate at which the top edge of the image will be drawn.
           * @param width The width of the image.
           * @param height The height of the image. 
           * @return Returns true if the image was successfully drawn on the screen.
           * @details
           *  This funtion draws an image on the screen using the contents of a buffer into which
           *  raw RGB pixels have been placed.  Each pixel is represented by a 32 bit value, however,
           *  only the lower 24 bits are used as transparency is not yet supported.  The buffer contains
           *  pixels for the first row of the image immediately followed by pixels for the second row and so on.
           *  The image should be no larger than the V5 Screen, that is, a maximum of 480 pixels wide by 272 pixels high.
           *  The top/left corner of the image is placed at the coordinates given by x and y, these can
           *  be negative if desired.
          */
          bool     drawImageFromBuffer( uint32_t *buffer, int x, int y, int width, int height );

          /**
           * @prog_lang{pro}
           * @drawer_cat{action}
           * @block_sig{drawImageFromFile( "image.png", 0, 0 );}
           * @brief Draws an image on the screen using a file on the SD Card as the source.
           * @param name The name of the image, it must have either a ".bmp" or ".png" extension.
           * @param x The x-coordinate at which the left edge of the image will be drawn.
           * @param y The y-coordinate at which the top edge of the image will be drawn.
           * @return Returns true if the image was successfully drawn on the screen.
           * @details
           *  This funtion draws an image on the screen using the contents of a file on an SD Card.
           *  The file should be no larger than 512K bytes and must have either a ".bmp" or ".png" extension.
           *  The image should be no larger than the V5 Screen, that is, a maximum of 480 pixels wide by 272 pixels high.
           *  The top/left corner of the image is placed at the coordinates given by x and y, these can
           *  be negative if desired.
          */
          bool     drawImageFromFile( const char *name, int x, int y );
          
          // not for public use yet
          void     waitForRefresh();
          void     renderDisable();

           
          // touchscreen simple events
          mevent  PRESSED  = {(uint32_t)brain::_getIndex(), (int)tEventType::EVENT_LCD_PRESSED   };
          mevent  RELEASED = {(uint32_t)brain::_getIndex(), (int)tEventType::EVENT_LCD_RELEASED  };

        private:
          void     _setPenColor( uint32_t rgb ); 
          void     _setFillColor( uint32_t rgb ); 
          void     _clearScreen( uint32_t rgb );
          void     _clearLine( int number, uint32_t rgb );
          void     _drawRectangle( int x, int y, int width, int height, uint32_t rgb );
          void     _drawCircle( int x, int y, int radius, uint32_t rgb );
          
          enum class tImageBufferType {
            kImageBufferTypeUnknown = 0,
            kImageBufferTypeBmp,
            kImageBufferTypePng
          };
            
          tImageBufferType _validateImageBuffer( uint8_t *buffer );

          uint32_t  webColorToRgb( const char *color );      
          uint32_t  hueToRgb( uint32_t color );          
      };

      // timer
      /** 
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{sensing}
       * @block_sig{Brain.timer(seconds);}
       * @cpp_sig{Brain.timer(vex::timeUnits::sec);}
       * @brief Gets the value of the timer in the units specified.
       * @param units The unit of time that will be returned.
       * @return Returns a double that represents the value of the timer.
      */
      double      timer( timeUnits units );

      /** 
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{setting}
       * @block_sig{Brain.resetTimer();}
       * @brief Resets the timer to zero.
      */
      void        resetTimer();

      /** 
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{setting}
       * @block_sig{Brain.setTimer(10, seconds);}
       * @cpp_sig{Brain.setTimer(10, vex::timeUnits::sec);}
       * @brief Sets the timer to a value and time unit.
       * @param value The value that the timer is set to.
       * @param units The unit of time that will be returned.
      */
      void        setTimer( double value, timeUnits units );

      /** 
       * @prog_lang{cpp|pro}
       * @drawer_cat{instance}
       * @block_sig{Brain.Timer}
       * @brief Use the Timer class to obtain the system time.
       */
      vex::timer  Timer;
      
      /** 
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{instance}
       * @block_sig{Brain.Screen}
       * @brief Use the Screen class to write or draw to the screen.
       */
      lcd         Screen;

      /** 
       * @prog_lang{pro}
       * @drawer_cat{instance|none}
       * @brief The Brain's instance of Three Wire Ports A through H.
       */
      triport     ThreeWirePort = triport( PORT22 );

      /** 
        * @prog_lang{block|cpp|pro}
        * @brief Use the battery class to see information about the battery.
      */      
      class battery {
        public:
          battery() {};
          ~battery() {};

          /** 
           * @prog_lang{block|cpp|pro}
           * @drawer_cat{sensing}
           * @block_sig{capacity()}
           * @brief Gets the battery capacity.
           * @return Returns an integer that represents the batteries capacity in the units specified by the parameter.
           * @param units (Optional) The type of unit that will be returned. By default, this parameter is a percentage. 
          */
          uint32_t  capacity( percentUnits units = percentUnits::pct );

          /** 
           * @prog_lang{block|cpp|pro}
           * @drawer_cat{sensing}
           * @block_sig{temperature()}
           * @brief Gets the battery temperature.
           * @return Returns a double that represents the batteries temperature in the units specified by the parameter.
           * @param units (Optional) The type of unit that will be returned. By default, this parameter is a percentage.
          */
          double    temperature( percentUnits units = percentUnits::pct );
          
          /** 
           * @prog_lang{cpp|pro}
           * @drawer_cat{sensing}
           * @block_sig{temperature(vex::temperatureUnits::celsius)}
           * @brief Gets the battery temperature.
           * @return Returns a double that represents the batteries temperature in the units specified by the parameter.
           * @param units The unit of temperature that will be returned.
          */
          double    temperature( temperatureUnits units );
          
          /** 
           * @prog_lang{cpp|pro}
           * @drawer_cat{sensing}
           * @block_sig{voltage( vex::voltageUnits::volt )}
           * @brief Gets the battery voltage.
           * @return Returns a double that represents the batteries voltage in the units specified by the parameter.
           * @param units The unit of voltage to be returned.
          */
          double    voltage( voltageUnits units = voltageUnits::volt );
          
          /** 
           * @prog_lang{cpp|pro}
           * @drawer_cat{sensing}
           * @block_sig{current( vex::currentUnits::amp )}
           * @brief Gets the battery current.
           * @return Returns a double that represents the batteries current in the units specified by the parameter.
           * @param units The type of current to be returned.
          */
          double    current( currentUnits units = currentUnits::amp );
          
      };
      /** 
       * @prog_lang{block|cpp|pro}
       * @drawer_cat{instance}
       * @block_sig{Brain.Battery}
       * @brief This is the Brain's instance of the battery.
       */
      battery     Battery;

      /** 
        * @prog_lang{pro}
        * @brief Use the SD Card class to load or save files on your SD card.
      */      
      class sdcard {
        public:
          sdcard();
          ~sdcard();
          
          /** 
           * @prog_lang{pro}
           * @drawer_cat{sensing}
           * @block_sig{isInserted()}
           * @brief Gets the state of the SD card
           * @return Returns true if the SD card is inserted. Returns false if there is not an SD card inserted.
          */
          bool    isInserted();
          
          /** 
           * @prog_lang{pro}
           * @drawer_cat{action}
           * @block_sig{loadFile("filename.txt", buffer, 100);}
           * @return Returns the number of bytes read from the file.
           * @brief Loads a file from the SD card.
           * @param name The name of the file.
           * @param buffer Pointer to a buffer for file data.
           * @param len The length of the buffer in bytes. Usually set to the max length of the buffer.
          */
          int32_t loadfile(const char *name, uint8_t *buffer, int32_t len );

          /** 
           * @prog_lang{pro}
           * @drawer_cat{action}
           * @block_sig{saveFile("filename.txt", buffer, 100);}
           * @brief Saves a file to the SD card.
           * @return Returns the number of bytes saved to the file.
           * @param name The name of the file.
           * @param buffer Pointer to a buffer with file data.
           * @param len The length of the buffer in bytes. Usually set to the max length of the buffer.
          */
          int32_t savefile(const char *name, uint8_t *buffer, int32_t len );

          /** 
           * @prog_lang{pro}
           * @drawer_cat{action}
           * @block_sig{appendFile("filename.txt", buffer, 100);}
           * @brief Appends data to an existing file.
           * @return Returns the number of bytes saved to the file.
           * @param name The name of the file.
           * @param buffer Pointer to a buffer with file data.
           * @param len The length of the buffer in bytes. Usually set to the max length of the buffer.
          */
          int32_t appendfile(const char *name, uint8_t *buffer, int32_t len );
      };
      /** 
       * @prog_lang{pro}
       * @drawer_cat{instance}
       * @block_sig{Brain.SDcard}
       * @brief This is the instance of the SD card class.
       */
      sdcard      SDcard;
  };
};

#endif  // VEX_BRAIN_CLASS_H
