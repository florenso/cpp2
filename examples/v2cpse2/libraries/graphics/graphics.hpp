// ==========================================================================
//
// file: examples/v2cpse2/graphics-lib/graphics.h
//
// ==========================================================================

#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <limits>
#include "hwcpp.hpp"

//! graphic elements
namespace graphics {

// ==========================================================================
//
// class vector
//
//! a relative or absolute (= relative to (0,0)) location on a grid
//
//! A vector is a pair of 16-bit integer values that are the x and y 
//! coordinates of an absolute or relative location on an integer grid. 
//! A vector can be constructed from its x and y values. 
//! When no values are supplied a vector defaults to (0,0).
//!
//! Vectors are intended to represent a location, displacement, or
//! size on a graphics screen. 
//! 16 bits should be more than enough for this purpose.
//!
//! When a vector is used to identify a pixel on a screen (0,0)
//! is the top-left pixel.
//!
//! \image html lcd_pixel_coordinates.bmp
//!
//! Two vectors can be added or subtracted to yield a new vector. 
//! A vector can be multiplied or divided by an integer to yield a new vector. 
//! Vectors can be compared for equality and inequality. 
//! The x_projection() and y_projection() functions return the 
//! projection of the vector on the two axises. 
//! The function is_within() tests whether a vector is within the 
//! box bounded by the origin and the argument. 
//! 
//! For debugging, a << operator is provided to print a vector.
//!
//! A vector fits in a single (32 bits) word.
//! It has no references to other objects.
//

class vector {
private:   
     
   //! returns the sign (-1, 0, 1) of the argument  
   static constexpr int sign( short int x ){ 
      return ( x > 0 ) - (x < 0); }  
      
   //! returns whether the x is within <m,0] or [0,m>    
   static constexpr bool is_within( short int x, short int m ){
      return (( x >= 0 ) && ( x < m )) || (( x <= 0 ) && ( x > m )); }
      
   static constexpr unsigned int max( unsigned int a, unsigned int b ){
      return a > b ? a : b; }
   
   static constexpr unsigned int max( 
      unsigned int a, unsigned int b,
      unsigned int c, unsigned int d 
   ){
      return max( a, max ( b, max( c, d )));
   }      

public:   

   typedef short int coordinate_type;   

   //! the x coordinate
   coordinate_type x;
  
   //! the y coordinate
   coordinate_type y;

   //! construct a vector, the value defaults to (0,0)
   constexpr vector(): x{ 0 }, y{ 0 } {}   
     
   //! construct a vector from its x and y coordinates
   constexpr vector( int x, int y ): 
      x{ static_cast< coordinate_type >( x ) }, 
      y{ static_cast< coordinate_type >( y ) } 
   {}    
      
   //! add two vectors by adding the x and y coordinates
   constexpr vector operator + ( const vector p ) const {
      return vector( x + p.x, y + p.y ); }          
      
   //! add a vector to an existing vector   
   vector operator += ( const vector p ){
      return vector{ x += p.x, y += p.y }; }          
      
   //! return the vector unmodified   
   constexpr vector operator + ( void ) const {
      return vector{ x, y }; }
   
   //! subtract two vectors by subtracting the coordinates
   constexpr vector operator - ( const vector p ) const {
      return vector( x - p.x, y - p.y ); }          
      
   //! subtract a vector from an existing vector   
   vector operator -= ( const vector p ){
      return vector{ x -= p.x, y -= p.y }; }          
      
   //! returns the negative of the vector (point-mirrored in the origin)
   constexpr vector operator - ( void ) const {
      return vector( - x, - y ); }
   
   //! divides a vector by an integer by dividing the coordinates
   constexpr vector operator / ( int n ) const {
      return vector( x / n, y / n ); }          
      
   //! divides an existing vector by an integer   
   vector & operator /= ( int n ){
      x /= n; 
	  y /= n;
	  return *this;
   }	  
      
   //! multiplies a vector by an integer by multiplying the coordinates
   constexpr vector operator * ( int n ) const {
      return vector( x * n, y * n );}         
      
   //! multiplies an existing vector by an integer
   vector & operator *= ( int n ){
      x *= n;
	   y *= n;
      return *this;
   }         
   
   //! multiplies a vector by an integer by multiplying the coordinates
   friend constexpr vector operator * ( int n, const vector v ){
      return vector( v * n ); }     

   //! prints a vector
   //
   //! This operator prints a vector in the (\%d,\%d) format.
   friend hwcpp::io::ostream & operator<< ( hwcpp::io::ostream &s, const vector p ){
      s << hwcpp::io::dec << "(" << p.x << "," << p.y << ")";
      return s;
   }
      
   //! multiplying two vectors multiplies their X and Y components
   constexpr vector operator * ( const vector rhs ) const {
      return vector(x * rhs.x, y * rhs.y ); }         
      
   //! reports whether two vectors are equal  
   constexpr bool operator == ( const vector p ) const {
      return ( x == p.x ) && ( y == p.y );  }          

   //! reports whether two vectors are unequal
   constexpr bool operator != ( const vector p ) const {
      return ! ( *this == p );  }     
      
   //! returns the direction of a vector      
   //
   //! The direction of a vector is a vector that, 
   //! for both its x and y component, has the 
   //! value 1 or -1, and the same sign
   //! as the original vector.
   constexpr vector direction( void ) const {
      return vector( sign( x ), sign( y )); }           
           
   //! returns the absolute of a vector
   // 
   //! The absolute of a vector is the original vector,
   //! mirrored into the first quadrant by the x and y axises.
   //! In other words, the x and y of the absolute 
   //! are the absolutes of the original x and y.
   constexpr vector abs( void ) const {
      // abs is not present in DevKitPro??
      return vector( 
         ( x >= 0 ) ? x : -x,
         ( y >= 0 ) ? y : -y  ); 
   }  
      
   //! returns the projection of the vector on the x axis
   //
   //! In other words, the vector with y set to 0.   
   constexpr vector x_projection( void ) const {
      return vector( x, 0 ); }        
      
   //! returns the projection of the vector on the y axis
   //
   //! In other words, the vector with x set to 0.
   constexpr vector y_projection( void ) const {
      return vector( 0, y ); }        
      
   //! returns with x and y swapped
   //
   //! In other words, the return vector as mirrored in the y=x line.
   constexpr vector mirrored( void ) const {
      return vector( y, x ); }        
      
   //! reports whether te vector is within the box [0,p>
   //   
   //! The call a.is_within(b) returns true iff a is within 
   //! the rectangle [(0,0),b], where the boundary lines that go through (0,0) 
   //! are included, but the boundaries that go through b 
   //! are excluded.
   constexpr bool is_within( const vector p ) const {
      return is_within( x, p.x ) && is_within( y, p.y ); }
      
   //! the vector (0,0)   
   static vector origin(){ return vector( 0, 0 ); }
   
   //! the vector (0,0)   
   static vector zero(){ return vector( 0, 0 ); }
   
   //! the vector (1,1)   
   static vector one(){ return vector( 1, 1 ); }
   
   //! returns the vector that is the maximum of the arguments on each axis
   //
   //! For two vectors the returned vector is
   //! \code
   //!    return vector( 
   //!      max( a.x(), b.x() ),
   //!      max( a.y(), b.y() )
   //!   );
   //! \endcode
   static constexpr vector max( 
      vector a, 
      vector b, 
      vector c = vector::origin(), 
      vector d = vector::origin() 
   ){
      return vector( 
         max( a.x, b.x, c.x, d.x ),
         max( a.y, b.y, c.y, d.y )
      );   
   }
  
};


// ==========================================================================
//
// class color
//
//! a color (in the 3 * 8 bit RGB format + transparency)
//
//! A color is represented by three 8-bit values (0..255) for the 
//! red, green and blue components, 
//! and an additional boolean flag to indicate transparency 
//! (in which case the rgb values are irrelevant). 
//! Transparency is recessive: when a transparent color is combined with 
//! a non-transparent color the result is a non-transparent color. 
//!
//! A color can be constructed from is three components, 
//! or from a 3-byte value (as is commonly used in for instance HTML). 
//! Two colors can be added or subtracted, or be compared for equality. 
//! A color can be multiplied or divided by an integer.
//!
//! For debugging, a << operator is provided to print a color.
//!
//! Static methods are provided that return some basic colors,
//! including tranparent. (These static methods instead of constants
//! to avoid global initialization order problems.)
//!
//! This color format is emissive: when colors are added (or multiplied
//! by an integer >1), they add up towards white. Likewise subtracting 
//! works towards black.
//!
//! A color fits in a single (32 bits) word.
//! It has no references to other objects.
//

class color {  
private:    
              
   static constexpr unsigned char clip( int x, bool t = false ){
      return ( t || ( x < 0 )) ? 0 : ( x > 0xFF ? 0xFF : x ); }        

   bool transp;
   unsigned char r; 
   unsigned char g;
   unsigned char b; 
   
public:      
   
   //! constructs a color object from its three components
   //
   //! You can also supply the transparency flag, but better use
   //! the color::transparent constant.
   //! 
   //! Note that the arguments are integers, but they are clipped
   //! to the 0..255 range by the constructor.
   constexpr color( int r, int g, int b, bool t = 0 ):
      transp( t ), r( clip( r, t )), g( clip( g, t )), b( clip( b, t )) {}
      
   //! constructs a color from a three-byte value
   //
   //! For instance, color( 0xFF00FF ) is magenta.   
   constexpr color( unsigned int rgb = 0 ):
      transp{ 0 },  
      r{ clip( ( rgb & 0xFF0000 ) >> 16 ) }, 
      g{ clip( ( rgb & 0x00FF00 ) >>  8 ) }, 
      b{ clip( ( rgb & 0x0000FF ) >>  0 ) }{}
      
   //! the color in RGB15 (NintendoDS) format
   constexpr unsigned int rgb15_get( void ) const {
      return (
           ((unsigned int)( r & 0xF8 ) >>  3 )
         | ((unsigned int)( g & 0xF8 ) <<  2 )
         | ((unsigned int)( b & 0xF8 ) <<  7 ) 
      );
   }      
   
   //! transparency indicator
   //
   //! When a color is transparent its colors are irrelevant.
   constexpr bool is_transparent() const { return transp; }
   
   //! return the red component
   //
   //! The returned component is relevant only when the
   //! color is not transparent.
   constexpr unsigned char red_get() const { return r; } 
   
   //! return the green component
   //
   //! The returned component is relevant only when the
   //! color is not transparent.
   constexpr unsigned char green_get() const { return g; }
   
   //! return the blue component
   //
   //! The returned component is relevant only when the
   //! color is not transparent.
   constexpr unsigned char blue_get() const { return b; }    

   //! adds two colors; addition works towards white
   color operator + ( const color c ) const {
      return color {
         r + (int)c.r, 
         g + (int)c.g, 
         b + (int)c.b, 
         transp && c.transp }; }
      
   //! adds a color to an existing color   
   const color & operator += ( const color c ){
      r = clip( r + (int)c.r ); 
      g = clip( g + (int)c.g ); 
      b = clip( b + (int)c.b ); 
      transp = transp && c.transp; 
      return *this;
   }
      
   //! returns a color unmodified   
   constexpr color operator + ( void ) const {
      return color{ r, g, b, transp }; }          
      
   //! subtracts two colors; subtraction works towards black      
   constexpr color operator - ( const color c ) const {    
      return color {  
         r - (short int)c.r, 
         g - (short int)c.g, 
         b - (short int)c.b, 
         transp && c.transp }; }
      
   //! subtracts a color from an existing color   
   color & operator -= ( const color c ){
      r = clip( r - (int)c.r ); 
      g = clip( g - (int)c.g );
      b = clip( b - (int)c.b );
      transp = transp && c.transp; 
      return *this;
   }          
      
   //! returns the negative of a color   
   constexpr color operator - ( void ) const {
      return color{   
         0xFF - (int)r, 
         0xFF - (int)g, 
         0xFF - (int)b, 
         transp }; }
      
   //! divides a color by an integer; division works towards black   
   constexpr color operator / ( short int n ) const {
      return color{ r / n, g / n, b / n, transp }; }
      
   //! divides an exiting color by an integer   
   color & operator /= ( unsigned int n ){
      r = clip( r / n ); 
      g = clip( g / n ); 
      b = clip( b / n ); 
      return *this;
   }
      
   //! muliplies a color by an integer; multiplication works towards white   
   constexpr color operator * ( short int n ) const {
      return color{ r * n, g * n, b * n, transp }; }
   
   //! multiplies an existing color by an integer 
   color & operator *= ( unsigned int n ){
      r = clip( r * n ); 
      g = clip( g * n ); 
      b = clip( b * n ); 
      return *this;
   }
      
   //! reports whether two colors are equal   
   constexpr bool operator == ( const color c ) const {
      return transp ? c.transp : 
         ( ! c.transp ) && ( r == c.r ) && ( g == c.g ) && ( b == c.b ); }

   //! reports whether two colors are unequal
   constexpr bool operator != ( const color c ) const {
      return ! ( *this == c );  }   
   
   //! returns the mix of the current color and the argument   
   constexpr color mixed_with( const color c ) const {
      return color{   
         ( r + c.r ) / 2, 
         ( g + c.g ) / 2, 
         ( b + c.b ) / 2,
         transp && c.transp }; }          
         
   //! print a color
   //
   //! \relates color
   //! This operator prints a color, either as "(transparent )",
   //! or in the (\%02X,\%02X,\%02X) format.
   friend hwcpp::io::ostream & operator << ( 
      hwcpp::io::ostream &s, 
      const color c 
   ){
      if( c.is_transparent() ){
         s << "( transparent  )";
      } else {
         s << hwcpp::io::hex << hwcpp::io::setfill( '0' ) << "(" 
           << hwcpp::io::setw( 2 ) << c.red_get() << "," 
           << hwcpp::io::setw( 2 ) << c.green_get() << "," 
           << hwcpp::io::setw( 2 ) << c.blue_get() 
           << hwcpp::io::setfill( ' ' ) << ")";
      }        
      return s;
   }

};

//! some basic colors
//
// these 'constants' are deliberately NOT Doxygen-documented     
static constexpr color black        { 0,       0,    0 };   //!< ...
static constexpr color white        { 0xFF, 0xFF, 0xFF };   //!< ...
static constexpr color red          { 0xFF,    0,    0 };   //!< ...
static constexpr color green        { 0,    0xFF,    0 };   //!< ...
static constexpr color blue         { 0,       0, 0xFF };   //!< ...
static constexpr color gray         { 0x80, 0x80, 0x80 };   //!< ...
static constexpr color yellow       { 0xFF, 0xFF,    0 };   //!< ...
static constexpr color cyan         {    0, 0xFF, 0xFF };   //!< ...
static constexpr color magenta      { 0xFF,    0, 0xFF };   //!< ...
static constexpr color transparent  { 0, 0, 0, 1 };         //!< ...
static constexpr color violet       { 0xEE82EE };           //!< ...
static constexpr color sienna       { 0xA0522D };           //!< ...
static constexpr color purple       { 0x800080 };           //!< ... 
static constexpr color pink         { 0xFFC8CB };           //!< ...
static constexpr color silver       { 0xC0C0C0 };           //!< ...
static constexpr color brown        { 0xA52A2A };           //!< ...
static constexpr color salmon       { 0xFA8072 };           //!< ...


// ==========================================================================
//
// class event
//

//! types of events
//
//! \relates event
//!
//! This type represents an action the user performs on the screen, 
//! using a mouse or stylus (on a touch screen).
//
enum class event_type { 

   //! nothing happened
   //
   //! This event type is used when an event object is required,
   //! but nothing happened. 
   //! The location has no meaning.
   none, 
   
   //! user requests application exit
   //
   //! This event type is used when the user requests the
   //! (sub)application to terminate. 
   //! The location has no meaning. 
   exit, 
   
   //! user lands on the screen
   //
   //! This event type is used when the user lands on the screen:
   //! the mouse button is pressed down, or the stylus first
   //! contacts the screen. 
   //! The location indicates where this happened.   
   down, 
  
   //! user moves while touching the screen
   //
   //! This event type is used when the user touches a new pixel,
   //! either because the cursor or stylus first touched down on 
   //! the screen, or because the the mouse cursor or stylus 
   //! was down and moved to a different pixel.
   //! The location indicates the (new) pixel.
   //!
   //! This event type would typically be used by a freehand paint
   //! application.
   touch, 
  
   //! user takes off from the screen
   //
   //! This event type is used when the user has landed on the screen
   //! but now takes off (releases the mouse button, or moves the
   //! stylus from the screen).
   //! The location is the last location where the user was on
   //! the screen.
   up, 
  
   //! user clicks on the screen
   //
   //! This event type is used when the user clicks on the screen,
   //! which is the same as down and up in rapid succession.
   //! The down and up events will also be generated.
   //! The location is the location of the up event.
   click 
};

//! return the name of an event_type
//!
//! \relates event
//
const char * event_type_name( const event_type e );

//! prints the name of an event_type
//!
//! \relates event
//
hwcpp::io::ostream & operator<<( hwcpp::io::ostream &s, const event_type &e );

//! something that the users caused to happen on the screen
//
//! An event is a something that happens at a specific position on 
//! a screen. A typical event would be the user touching the screen
//! with a stylus, or clicking on a certain position with a mouse.
//!
//! When a user 
//! - touches the screen at (10,10);
//! - moves the stylus to (11,11) and to (12,12);
//! - and then removes the stylus from the screen,
//!
//! the following events will be generated in this order:
//!
//! - down:(10,10)
//! - touch:(10,10)
//! - touch:(11,11) 
//! - touch(12,12)
//! - up:(12,12)
//! - click:(12,12)
//! 
//! The last event (click) will only be generated if the down and 
//! the touch ocurred within rapid succession.
//
class event {

   static constexpr const char * const event_name[ 6 ] = {
      "none", "exit", "down", "touch", "up", "click" };


   friend const char * event_type_name( const event_type e ){
      return ( e <= event_type::click )
         ? event_name[ static_cast<int>( e ) ]
         : "invalid";
   }         
   
   friend hwcpp::io::ostream & operator<<( hwcpp::io::ostream &s, const event_type &e ){ 
      s << event_type_name( e );
      return s;
   }
   
public:

   //! the location where the event ocurred
   //!
   //! For some event types the location is irrelevant.
   const vector location;
   
   //! the type of the event that ocurred
   const event_type action;
   
   //! creates an event from its location and type
   constexpr event( const vector p, const event_type e ):
      location{ p }, action{ e } {}    

   //! prints an event
   //
   //! \relates event
   //! Example: 
   //!
   //! (47,120):touch:   
   friend hwcpp::io::ostream & operator<<( hwcpp::io::ostream &s, const event &e ){
      s << e.location << ":" << e.action;
      return s;
   }      
};


// ==========================================================================
//
// class frame
//
//! a rectangular block of writable pixels
//
//! A frame is an abstract class, representing a rectangle block of pixels.
//! Pixels are addressed by vectors.
//! By convention, (0,0) is the upper left pixel (origin).
//! Each pixel has a color, which can be written.
//!
//! The pixel operation checked_write is pure virtual. 
//! This operations must be implemented by a concrete frame.
//

class frame {
protected:
   
   frame( const frame &rhs ) = delete;
   frame & operator=( const frame &rhs ) = delete;
   
   //! default clear
   void clear_default(){
      vector step = size.direction() ;
      for( int x = 0; x != size.x; x += step.x  ){
         for( int y = 0; y != size.y; y += step.y ){
            write( vector( x, y ), bg ); } }
   } 
   
   //! most recently applied background color (as used in clear())
   color bg;
   
   //! write one pixel (implementation)
   //
   //! A concrete frame class must implement this function.
   //! It can safely assume that the address is within the frame.
   virtual void checked_write( const vector p, const color c ) = 0;  
   
   //! clear the frame (implementation)
   //
   //! A concrete frame class must implement this function.
   //! It can safely assume that the address is within the frame.
   virtual void checked_clear(){ clear_default(); }
   
public:   
       
   //! the size of the frame
   const vector size;
   
   //! create a frame of specified size
   frame( const vector size ): bg{ white }, size{ size } {}
   
           
   //! translate a subframe coordinate to a master frame coordinate
   virtual vector translate_outfrom( const vector p ) const {
      return p; }   
   
   //! translate a master frame coordinate to a subframe coordinate
   virtual vector translate_into( const vector p ) const {
      return p; }   
   
   //! whether p is within the frame   
   bool is_valid( vector p ){
      return p.is_within( size ); }   
      
   //! get the backround color
   //
   //! This method retruns the argument used in the most recently
   //! clear method call.
   color bg_get(){ return bg; }      
   
   //! write one pixel, address specified by vector
   //
   //! This function checks whether the p is valid
   //! (writing to a pixel outside the frame is ignored).
   void write( const vector p, const color c ){
      if( is_valid( p ) ){ checked_write( p, c ); }}        
   
   //! fill the full frame with the indicated color
   //
   //! This method fills the screen with the indicated color
   //! and save this color for \ref bg_get().
   void clear( const color c = white ){
      bg = c;
      if( ! c.is_transparent() ){  
         checked_clear();
      }    
   }
   
   //! for buffered frames: write the changes to the underlying frame
   //
   //! For buffered frames this method must be called to write
   //! the changes 'through' to the underlying frame. Most frames
   //! are not buffered, for such frames an empty default is provided.
   virtual void flush(){}
};


// ==========================================================================
//
// class frame_dummy
//
//! writing to this frame does nothing
//

class frame_dummy : public frame {
public:

   //! construct a dummy frame
   //
   //! This constror creates a dummy frame. 
   //! All writes to this frame are ignored.
   //! Hence the specified size is not important
   //! (out-of-bounds writes are equally ignored), except
   //! that it is the size reported by size_get().
   frame_dummy( const vector size = vector::origin() ): frame( size ){}
   
protected:

   //! checked_write implementation as required by frame
   //
   //! This method does nothing.
   //! 
   void checked_write( const vector p, const color c ) override {}
};


// ==========================================================================
//
// class frame_buffer
//
//! in-memory frame buffer that can be written in one go
//
//! A frame_buffer catches and buffers the writes to the underlying frame
//! in an in-memory buffer. The flush() call writes the buffer to the
//! underlying frame.
//!
//! A frame_buffer can be used to prevent flickering while a frame
//! is updated. The downside is the memory use and the extra CPU time
//! for writing the changed pixels to the underlying frame.
//! To do this all buffered pixels must be checked.
//!
//! Note that buffering the writing to a screen that itself does
//! fancy things (for instance shadowing) can change what appears on a 
//! screen because the order in which pixels are written is changed.
//! The safest is to buffer directly above the target screen.
//!
//! The buffer is allocated on the heap. 

class frame_buffer : public frame {
private:
   //! the underlying frame
   frame &f;
   
   //! the in-memory pixel buffer
   color *pixels;
   
   //! return the specified pixel in the buffer
   //
   //! This function does no range checking. 
   //! Calling it with an invalid p will give unpredicatble results.
   color & pixel( vector p ){
      return pixels[ p.x + f.size.x * p.y ];
   }
   
   color pixel( vector p ) const {
      return pixels[ p.x + f.size.x * p.y ]; 
   }
      
   //! private copy constructor: prevent copying
   frame_buffer( const frame_buffer &rhs );
   
     //! private assignment: prevent assignment
   void operator=( const frame_buffer &rhs );
   
public:   

   //! construct a frame_buffer from an underlying frame
   //
   //! This constructor allocates the pixel buffer on the heap.
   //! The size is the number of pixels in the underlying frame *
   //! 4 bytes for each pixel.
   frame_buffer( frame &fr ):
      frame( fr.size ),
	  f( fr )
   {
      pixels = new color[ f.size.x * f.size.y ];
      for( int x = 0; x < f.size.x; x++ ){
         for( int y = 0; y < f.size.y; y++ ){
			   pixel( vector( x, y )) = transparent;
         }
      }	  
   }
   
   //! destruct a frame_buffer, freeing the allocated pixel buffer
   virtual ~frame_buffer(){
      delete[] pixels;
   }
   
   //! write to the pixel buffer
   void checked_write( const vector p, const color c ) override {
      pixel( p ) = c;
   }
  
   //! write the pixel buffer to the underlying frame
   //
   //! This method writes all changed pixels in the buffer to the
   //! underlying frame, and flushes that frame.
   void flush(){
      for( int x = 0; x < f.size.x; x++ ){
         for( int y = 0; y < f.size.y; y++ ){
            vector p( x, y );
		      if( ! pixel( p ).is_transparent() ){
               f.write( p, pixel( p ));
			      pixel( p ) = transparent;
			   }   
         }
      }		              
	  f.flush();
   }
   
   //! clear the buffer, and rember the color used
   void checked_clear() override {
      frame::clear( bg );
   }   
   
};


// ==========================================================================
//
// class frame_snapshot
//
//! in-memory write-through frame buffer that can be written to a .bmp file
//
//! A frame_bsnapshot remembers the writes to the underlying frame
//! in an in-memmory buffer. The write_to_bsmp_file method writes
//! the content of the buffer to a .bmp file.
//!
//! The buffer is allocated on the heap. 

class frame_snapshot : public frame {
private:
   //! the underlying frame
   frame &f;
   
   //! the in-memory pixel buffer
   color *pixels;
   
   //! return the specified pixel in the buffer
   //
   //! This function does no range checking. 
   //! Calling it with an invalid p will give unpredicatble results.
   color & pixel( vector p ){
      return pixels[ p.x + f.size.x * p.y ];
   }
   
   color pixel( vector p ) const {
      return pixels[ p.x + f.size.x * p.y ]; 
   }
      
   //! private copy constructor: prevent copying
   frame_snapshot( const frame_snapshot &rhs );
   
     //! private assignment: prevent assignment
   void operator=( const frame_snapshot &rhs );
   
public:   

   //! construct a frame_snapshot from an underlying frame
   //
   //! This constructor allocates the pixel buffer on the heap.
   //! The size is the number of pixels in the underlying frame *
   //! 4 bytes for each pixel.
   frame_snapshot( frame &fr ):
      frame( fr.size ),
	  f( fr )
   {
      pixels = new color[ f.size.x * f.size.y ];
      for( int x = 0; x < f.size.x; x++ ){
         for( int y = 0; y < f.size.y; y++ ){
			   pixel( vector( x, y )) = transparent;
         }
      }	  
   }
   
   //! destruct a frame_snapshot, freeing the allocated pixel buffer
   virtual ~frame_snapshot(){
      delete[] pixels;
   }
   
   //! write to the pixel buffer and the underlying frame
   void checked_write( const vector p, const color c ) override {
      if( ! c.is_transparent() ){
         pixel( p ) = c;
      }		 
	  f.write( p, c );
   }
  
   //! flush the underlying frame
   void flush(){              
	  f.flush();
   }
   
   //! clear the buffer, and rember the color used
   void checked_clear() override {
      frame::clear( bg );
   }   
   
   //! write to a .bmp file
   //
   //! This method writes the buffer content to the indicated
   //! filename in .bmp format (uncompressed, 24 bits/pixel).
   //! This works on the win target, it won't be usefull
   //! on targets that don't have a filesystem.
   void write_to_bmp_file( const char *file_name );

};


// ==========================================================================
//
// class frame_tee
//
//! writes to the (2..4) underlying frames
//
//! A frame_tee is a frame that forwards writes to the underlying frames. 
//! The constructor supports 2..4 underlying frames.

class frame_tee : public frame {
private:
   frame &f1, &f2, &f3, &f4;
   
   static frame & frame_dummy_ref(){
      static frame_dummy dummy;
      return dummy;
   }
   
public:
  	  
    //! construct a frame_tee from underlying frames
   frame_tee( 
      frame &f1, 
	  frame &f2,
      frame &f3 = frame_dummy_ref(), 
	  frame &f4 = frame_dummy_ref() 
   ): 
      frame( vector::max( f1.size, f2.size, f3.size, f4.size )),
	  f1( f1 ), 
	  f2( f2 ),
	  f3( f3 ),
	  f4( f4 ){}
   	  
   //! write to both underlying frames
   void checked_write( const vector p, const color c ) override {
      f1.write( p, c );
	   f2.write( p, c );
      f3.write( p, c );
	   f4.write( p, c );
   }
   
   //! flush both underlying frames
   void flush(){
      f1.flush();
	   f2.flush();
      f3.flush();
	   f4.flush();
   }   
   
   //! clear both underlying frames, and remember the color used
   void checked_clear() override {
      f1.clear( bg ); 
      f2.clear( bg ); 
      f3.clear( bg ); 
      f4.clear( bg ); 
   }   
};


// ==========================================================================
//
// class frame_filter
//
//! apply a function to the color before writing 
//
//! When a frame_filter is consructed a filter function is specified that
//! will be applied to the color of each pixel before it is written.
//!
//! Alternatively, a writer function can be specified that is called
//! to write a pixel. Besides changing the color, it can for instance
//! write to one or more (different) points.

class frame_filter : public frame {
private:
   frame &f;
   color (&filter)(color);
   void (&writer)(frame &f, vector p, color c, color bg );
   
   static color default_filter( color c ){ return c; }
   static void default_writer( frame &f, vector p, color c, color bg ){ 
      f.write( p, c ); }
   
public:

   //! construct a frame_filter from the underlying frame and a filter function
   frame_filter( frame &f, color (&filter)(color) ): 
      frame( f.size ),
      f( f ),
	  filter( filter ),
	  writer( frame_filter::default_writer ){}
   	  
   //! construct a frame_filter from the underlying frame and a writer function
   frame_filter( 
      frame &f, 
	  void (&writer)(frame &f, vector p, color c, color bg ) 
   ): 
      frame( f.size ),
      f( f ),
	  filter( frame_filter::default_filter ),
	  writer( writer ){}
   	  
   //! apply the filter function, write the result to the underlying frame
   void checked_write( const vector p, const color c ) override {
      writer( f, p, filter( c ), bg );
   }
   
   //! flush the underlying frame
   void flush(){
      f.flush();
   }   
   
   //! clear the underlying frame with the filtered color, and remember it
   void checked_clear() override {
      bg = filter( bg );
      f.clear( bg ); 
   }   
};


// ==========================================================================
//
// class subframe
//
//! frame that represents a rectangular part of another frame
//
//! A subframe is created by specifying the master frame, the top-left pixel
//! of the subfram within the master frame, and the direction
//! in which the subframe extends within the master frame.
//! ( top_left + direction - direction.direction() ) == 
//! bottom-right pixel of the subframe.
//! The direction can point towards all four quadrants, hence
//! the subframe can appear mirrored within the master frame.
//!
#ifdef notyet
//! The default scale is 1, which causes the subframe to appear
//! 1:1 in the master frame. When the scale is 0 it does not appear,
//! and reading a pixel from the subframe will always 
//! return color::transparent.
//!
//! When the scale factor is larger than 1, the subframe will expand its 
//! use of the area in the master by the scale factor, starting from
//! the upperleft (as supplied to the subframe constructor). 
//! In other words, the size inside the subframe remains the same,
//! but the area it occupies in the master frame is larger.
//!
//! When the scale is large than 1, the topleft pixel of the subframe
//! still occupies the pixel at the original place in the master frame,
//! but also its neigbouring pixels in the direction towards the bottomright
//! pixel.
#endif
//

class subframe : public frame {
public:

   //! the master of this subframe
   frame & master;              
   
   //! location within the master of this subframes topleft pixel
   const vector top_left;
   
   //! location within the master of this subframes bottomright pixel
   const vector bottom_right;
   
#ifdef notyet   
   //! the scale at which this subframe appears in its master
   const unsigned int scale;
#endif
   
   //! whether the subframe coordinates are swapped
   const bool swapped;
   
   //! translate a subframe coordinate to a master frame coordinate
   vector translate_outfrom( const vector p ) const {
      vector x( 
         top_left.x < bottom_right.x
            ? top_left.x + p.x 
            : top_left.x - p.x,
         top_left.y < bottom_right.y  
            ? top_left.y + p.y
            : top_left.y - p.y
       );
	   if( swapped ){
          x = x.mirrored();
	   }       
	   return x;
	}   
      
   //! translate a master frame coordinate to a subframe coordinate
   vector translate_into( const vector p ) const {
      vector x( 
         top_left.x < bottom_right.x
            ? p.x - top_left.x
            :  ( - p.x) - top_left.x,
         top_left.y < bottom_right.y  
            ? + p.y- top_left.y 
            : ( - p.y) - top_left.y
       );
	   if( swapped ){
          x = x.mirrored();
	   }       
	   return x;
	}   
      
   //! create a subframe, endpoints specified as vectors
   subframe( 
      frame &f, 
      vector top_left, 
      vector direction,
#ifdef notyet  
      unsigned int scale = 1,
#endif	  
	  bool swapped = false
   ):
      frame( direction.abs() ),
      master( f ), 
      top_left( top_left ), 
      bottom_right( top_left + direction - direction.direction() ),
#ifdef notyet  	  
      scale( scale ),
#endif	  
	  swapped( swapped ){}
  
protected:

   //! checked_write implementation as requiredby frame
   //
   //! When scale == 0 checked_write will do nothing, hence the
   //! subframe will not appear in the master frame.
   //! 
   void checked_write( const vector p, const color c ) override {
      if( is_valid( p )){
         vector q = swapped ?  p.mirrored() : p;
#ifdef notyet  		 
         for( unsigned int x = 0; x < scale; x++ ){
            for( unsigned int y = 0; y < scale; y++ ){       
               master.write( translate( q * scale + vector( x, y )), c ); 
            }}}}
#else
         master.write( translate_outfrom( q ), c ); 
      }		 
   }		  
#endif			
                   
};


// ==========================================================================
//
// class drawable
//
//! an object that can be drawn in a frame
//
//! A drawable is an abstract object that can be drawn in a frame.
//! A drawable knows the frame the location (anchor point) within this
//1 frame where it can draw itself, and
//! it has has has a forgeground and background color
//! and a (line) width.
//! What these properties exactly mean depends on the specific drawable.
//!
//! A drawable contains two colors and one integer. 
//! It has a reference to a frame.
//! This frame must still exist when the drwabale is asked to draw itself.
//
class drawable {
private:

   //! private copy constructor: prevent copying
   drawable( const drawable &rhs );
   
   //! private assignment: prevent assignment
   drawable & operator=( const drawable &rhs );

protected:
  
   //! the position
   vector position;

   //! foreground color
   color fg;
   
   //! background color
   color bg;
   
   //! width of (for instance) lines
   unsigned int width;
   
   //! draw one pixel on f, at position
   //
   //! This is the function that the draw function in a concrete drawable
   //! should use to draw each pixel of itself.
   //! Address is the location of the pixel that is to be drawn, c its color.
   void drawable_draw_pixel( 
      frame & fr,
      const vector address, 
      const color c 
   ) const {
      fr.write( position + address, c );	   
   }
         
   //! constructor, specify position, fg, bg colors, (line) width
   //
   //! The default is to draw in black forgeground, with transparent 
   //! (meaning: do not draw) background, line width (when applicable)
   //! 1 pixel.
   drawable( 
      const vector position = vector::origin(),
      const color fg = black, 
      const color bg = transparent,
      unsigned int width = 1
   ): position{ position }, fg{ fg }, bg{ bg }, width{ width } {}
   
public:    
   
   //! get the position
   const vector position_get() const { return position; }
     
   //! get the forgeround color
   color fg_get() const { return fg; }
      
   //! get the background color
   color bg_get() const { return bg; }
      
   //! get the width
   unsigned int width_get() const { return width; }
   
   //! set the position
   // void position_set( const vector pos ){ position = pos; }
      
   //! set the forgeround color
   void fg_set( const color c ){ fg = c; }
      
   //! set the background color
   void bg_set( const color c ){ bg = c; }
      
   //! set the width
   void width_set( unsigned int w ){ width = w; }
   
   //! draw yourself
   virtual void draw( frame & fr ) = 0;
      
};


// ==========================================================================
//
// class line
//
//! a drawable line object
//
//! A line object is a drawable that represents a line.
//! When it draws itself it will use the fg of its drawable part
//! for the line, the bg of its drawable part will not be used.
//! The line will be drawn using the specified width, by drawing
//! adjacent pixels.
//! The size of a line is its lenghth in the x and y directions,
//! \b not its endpoint (it is one pixel beyond the end).
//

class line : public drawable {
public:    

   //! the length of the line; can be read or written
   //
   //! The position of a drawable is specified when it is drawn, 
   //! it is not part of the drawable. You can think of the line
   //! starting at the origin. The size is the length in the
   //! x and y directions (not the endpoint!).
   vector size;
   
   //! constructs a line from its frame, position, size, color, and width
   line( 
      const vector position,
      const vector size, 
      const color fg = black, 
      int width = 1 
   ):
      drawable( 
		   position, 
		   fg, 
		   transparent, 
		   width 
	    ), size( size ){}
      
        
   //! draw the line on f, at position, and to scale   
   void draw( frame & fr ) override;
};    


// ==========================================================================
//
// class rectangle

//! appearance of the border of a rectangle
//!   
//! \relates rectangle
enum relief {  

   //! the border is drawn flat, using the fg color
   relief_flat,
 
   //! the border is drawn raised, using the bright and shadow colors
   relief_raised, 
   
   //! the border is drawn raised, using the shadow and bright colors
   relief_sunken
}; 
   
//! returns the inverse of the supplied relief 
//!   
//! \relates rectangle
relief flip( const relief r );   

//! prints a relief value
//!   
//! \relates rectangle
hwcpp::io::ostream & operator<<( hwcpp::io::ostream &s, const relief &r );

//
//! a drawable rectangle object
//
//! A rectangle object is a drawable that represents a rectangle.
//! By default, when it draws itself it will use the fg of its 
//! drawable part for its boundary lines, which will be filled 
//! to the width by drawing extra lines within the outer boundary.
//! The remaining area within will be filled using the bg.
//!
//! When the relief is raised, the top and left boundary will be draw
//! using the bright color, and the bottom and right boundary will be
//! drawn using the dark color. When the relief is sunken, this
//! is reversed. The initial relief is flat.
//

class rectangle : public drawable {
private:
   //! private copy constructor: prevent copying
   rectangle( const rectangle & );
   
   //! private assignment: prevent assignment
   void operator=( const rectangle & rhs );
   
public:

   //! bright border color; can be read or written; intitally fg
   //
   //! This is the color used for the bright parts of teh border
   //! when its relief is raised or sunken.
   color bright;
   
   //! dark border color; can be read or written; intially fg
   //
   //! This is the color used for the dark parts of the border
   //! when its relief is raised or sunken.
   color dark;
   
   //! the relief; can be read or written; initially flat
   //
   //! The relief used to draw the border.
   relief border;
   
   //! the position of the far corner; can be read or written
   //
   //! The position of a drawable is specified when it is drawn, 
   //! it is not part of the drawable. You can think of the origin
   //! being the near corner.
   vector size;
   
   //! constructs a rectangle from its far corner, bg, fg, width and relief
   rectangle(
      const vector position,
      const vector size, 
      const color fg     = black,
      const color bg     = transparent,
      int width          = 1,
      relief rel         = relief_flat
   ):
      drawable( position, fg, bg, width ), 
      bright( fg ), 
      dark( fg / 4 ), 
      border( rel ),
      size( size ){}       

   //! draw the rectangle on f, at position
   void draw( frame & fr ) override;
};  
    
    
// ==========================================================================
//
// class circle
//
//! a drawable circle object
//
//! A circle object is a drawable that represents a circle.
//! When it draws itself it will use the fg of its drawable part
//! for its boundary line, which will be filled to the width
//! by drawing extra circles within the outer boundary.
//! The remaining area within will be filled using the bg.
//

class circle : public drawable {
private:

   void circle_draw(
      frame &fr,
      const color c,
      bool fill
   ) const;
   
   void circle_draw_pixel(  
      frame &fr,
      const vector v,
      const color c
   ) const;

public:    

   //! the radius of the circle
   //!
   //! The position of a drawable is specified when it is drawn, 
   //! it is not part of the drawable. You can think of the origin
   //! being the centre.
   unsigned int radius; 
   
   //! create a circle from a radius, fg and bg colcors, and line width
   circle( 
      const vector position,
      unsigned int radius,
      const color fg = black,
      const color bg = transparent,
      unsigned int width = 1
   ):
      drawable( position, fg, bg, width ), radius( radius ){}        
      
   //! draw the circle on fr
   void draw( frame & fr ) override;
};    


// ==========================================================================
//
// class image
//
//! a recangular block that can be drawn at a position in a frame
//
//! An image can draw itself in a frame.
//
class image {
private:

   //! private copy constructor: prevent copying
   image( const image &rhs );
   
   //! private assignment: prevent assignment
   image & operator=( const image &rhs );
   
public:

   //! default constructor
   image(){}
	   
   //! draw the picture in the frame at the position
   virtual void draw( 
      frame &frame, 
      const vector position = vector::origin() ) const = 0;      
};


// ==========================================================================
//
// class image_pixels
//
//! an image that can be read pixel by pixel
//
//! An image_pixels is an image, hence it can draw itself in a frame.
//!
//! Additionally, each pixel of the image_pixels can be read.
//! A concrete child class must implement a \ref checked_read() 
//! function that returns the color of the requested pixel. 
//! The image_pixels class itself provides a read() function that first 
//! checks whether the requested pixel is within the area (otherwise 
//! it returns color::transparent) and if so, calls \ref checked_read() 
//! to do the real work. 
//
class image_pixels : public image {
protected:	

   //! the size of the (rectangular) block occupied by the objecy	
   vector size;
	
   //! get the color of the specified pixel    
   //
   //! This function must be provided by a concrete photo class
   //! that depends on the 
   //! It can assume that the requested pixel is valid (within
   //! the photo).
   virtual color checked_read( const vector p ) const = 0;

public:

   //! constructor, specify the size
   image_pixels( vector size ): size( size ){}	
	      
   //! get the size of the picture	   
   vector size_get() const { return size; }	
   
     //! report whether p is within the image   
   bool is_valid( const vector p ) const {
      return p.is_within( size ); }  
   
   //! draw the picture in the frame at the position
   //!
   //! The default draw method reads each pixel and writes it in the frame.
   //! A concrete image class might provide a more efficient draw method,
   //! that draws only the pixels that are not transparent.
   virtual void draw( 
      frame &frame, 
      const vector position = vector::origin() ) const;
      
   //! read one pixel, address specified by vector
   //
   //! This function will return color::transparent
   //! when the requested pixel is outside the image.
   //! Otherwise it will call \ref checked_read.
   color read( const vector p ) const {
      if( is_valid( p )){
         return checked_read( p );
      } else {
         return transparent;
      }               
   }       
};


// ==========================================================================
//
// class inline_rgb_photo
//
//! a color photo stored as inline constant data (in ROM)
//
//! The class inline_rgb_photo is a concrete child of the photo class.
//! It stores the colors of the pixels in an array of constant data. 
//! Inline_rgb_photo uses 3 bytes of red, green, and blue per pixel
//! (\ref inline_bw_photo uses 1 bit per pixel). 
//! The inline.py tool can be used to convert a .jpg or .bmp file into the 
//! .h and .cpp file for an inline_rgb_photo.
//! This is likely to be the only way you will instantiate this class.
//

class inline_rgb_photo : public image_pixels {
private:

   //! the pixel data     
   const unsigned char *data;  
   
   //! read one pixel
   color checked_read( const vector p ) const;
     
public:     
   
   //! create an inline_rgb_photo object   
   inline_rgb_photo( vector size, const unsigned char *data ):
      image_pixels( size ), data( data ){}        

};

// ==========================================================================
//
// class inline_bw_photo
//
//! a black-and-wite photo stored as inline constant data (in ROM)
//
//! The class inline_bw_photo is a concrete child of the photo class.
//! It stores the colors of the pixels in an array of constant data. 
//! Inline_wb_photo uses 1 bit per pixel
//! (\ref inline_rgb_photo uses 3 bytes per pixel). 
//! The inline.py tool can be used to convert a .jpg or .bmp file into the 
//! .h and .cpp file for an inline_bw_photo.
//! This is likely to be the only way you will instantiate this class.
//!
//! Each pixel can either be on or off. An 'on' pixel returns the
//! fg colcor (default: color::black), an off pixel returns the 
//! bg colcor (deafult: color::white).
//!
//! The inline_bw_photo class can be used instead of \ref inline_rgb_photo
//! to store a picture in a more compact form. It is also used by the
//! library to store fonts.
//

class inline_bw_photo : public image_pixels {
private:

   //! the pixel data     
   const unsigned char *data;  

   color fg, bg;

public:        
    
   //! read one pixel, return bool
   bool bool_read( const vector p ) const; 
   
   //! create an inline_bw_photo object   
   inline_bw_photo( 
   
   //! the size of the photo
   const vector size,   
      
   //! the pixel data
   //
   //! The data contains one bit per pixel, x address varies fastest.
   //! No filling except (when needed) the last byte.
   //! The bits within a byte are stored LSB first.
   const unsigned char *data 
   ):
      image_pixels{ size }, 
	   data( data ), 
      fg{ black }, bg{ white } {}    
      
private:
        
   //! read one pixel, return color
   color checked_read( const vector p ) const {
      return bool_read( p ) ? fg : bg; }                    
};


// ==========================================================================
//
// class font
//
//! the photo's (bitmaps) of characters
//
//! A font is an abstract class that holds the pixel-level black and white 
//! representation of a set of characters, according to some font rules.
//! You can read the pixels for a specific character.
//!
//! The common way to use a font is to use it to construct
//! a \ref text object, which can subsequently be drawn.
//!
//! A concrete font class must provide the has() and read() functions.
//

class font {
public:    
    
   //! true iff the font is fixed-width (all characters are the same width)
   bool const fixed;
   
   //! true iif the font is proportional (width of the characters varies)
   bool const proportional;
   
   //! the size of one character, x is valid for fixed fonts only 
   const vector font_char_size;
   
   //! create a font, specify its fixedness and character size
   font( bool fixed, const vector char_size ):
      fixed( fixed ), proportional( ! fixed ), font_char_size( char_size ){}     
    
   //! reports whether the font has the char
   //
   //! To reduce ROM size, a font can contain a subset of the ASCII
   //! characters.
   virtual bool has( char c ) const = 0;
       
   //! read pixel p of characters c    
   virtual bool read( char c, const vector p ) const = 0;
   
   //! reports te size of character c
   //
   //! This function must report (0,0) for a character that is 
   //! not in the set (for which \ref has is false).
   virtual vector char_size( char c ) const = 0;
    
};


// ==========================================================================
//
// class char_photo
//
//! a photo of a single char from a font
//
//! A char photo is the photo of one character from a \ref font.
//! It is a photo, so it can be drawn.
//! Temporary char_photo objects are used by \ref text to draw a
//! text in a specified front. 
//!
//! Unless you want to drawn characters in a way that is not provided
//! by \ref text it is unlikely that you will ever use this class.
//! 
//! A char_photo contains a reference to its font object.
//! Using a char_photo object when the font object is no longer available
//! will cause unpredictable results. 
//! When used with an \ref inline_font, which is a global const 
//! (readonly) object, so it can not become unavailable
//

class char_photo : public image_pixels {   
public:    
       
   //! the font     
   const font &f;  
    
   //! the character 
   const char c;
   
   //! the foreground colcor (default: black)
   const color fg;
   
   //! the background colcor (default: transparent)
   const color bg;

   //! instantiate a char_photo, specfy font, char, forgeground and background
   char_photo( 
      const font &f,
      char c, 
      const color fg = black, 
      const color bg = transparent
   ):
      image_pixels( f.char_size( c )),
      f( f ),
      c( c ), 
      fg( fg ), 
      bg( bg )
   {}
   
   //! read one pixel, return color
   color checked_read( const vector p ) const {
      return f.read( c, p ) ? fg : bg; }      
         
};


// ==========================================================================
//
// class inline_font
//
//! a font stored as inline constant data (in ROM)
//
//! An inline_font is a photo of a line of characters, stored 
//! in in-line data (in ROM).
//! As it is a photo, you can draw it in a frame to see how the
//! characters look.
//!
//! The common way to use a font is to use it to construct
//! a \ref text object, which can subsequently be drawn.
//!
//! The inline.py tool can be used to convert a .jpg or .bmp file into the 
//! .h and .cpp file for an inline_font.
//! This is likely to be the only way you will instantiate this class.
//

         // font type
         // picture is a picture of the characters in the font, 
         //    stored as one long line
         // when list is NULL the characters 0x20 .. 0x7F are supported,
         //    otherwise it is a (0-terminated) list of characters
         // for a fixed-width font x_size is the width of a char,
         //    and start is NULL
         // for a proportional font x_size is 0, and
         //    start points to an array with the x-offsets of each
         //    character. The first offset is of course 0, but
         //    still stored, and there are 0x61 offsets (not 0x60!)

class inline_font : public font, public inline_bw_photo {
public: 
    
   //! x offset within the photo of all ASCII characters
   const int *start; 
   
   //! instantiate an inline font
   inline_font( 
   
      //! true iif the font has the same size for each character
      bool fixed,
      
      //! the size of a character, x is valid for fixed fonts only
      const vector char_size,
      
      //! the x offset in the photo of each char, -1 for missing chars
      const int *start,
      
      //! the size of the photo
      const vector size,
            
      //! the photo pixels, see \ref inline_bw_photo
      const unsigned char *data
   ):         
      font( fixed, char_size ), 
      inline_bw_photo( size, data ),
      start( start )
   {}        
           
   //! report whether the font has a photo for char c        
   bool has( char c ) const { 
      if( ( c < ' ' ) || ( c >= 127 ) ) return false;
      return start[ (int) c - 32 ] >= 0; 
   }
      
   //! report the size of the photo for char c   
   vector char_size( char c ) const;
   
   //! read one pixel, return true iff it is foreground
   bool read( char c, const vector p ) const;
};


// ==========================================================================
//
// class format

//! the alignment of a text
//!   
//! \relates format
enum font_alignment { 
	
	 //! the text is put nearest to the near edge
   align_near, 
   
	 //! the text is put nearest to the far edge
   align_far, 
   
	 //! the text is centered between the edges   
   align_centre, 
   
   //! the text is space-filled to occupy the space between the edges
   align_fill 
};

//! prints an alignment
//!   
//! \relates format
hwcpp::io::ostream & operator<<( hwcpp::io::ostream &s, const font_alignment &a );

//! returns the default font
const inline_font & font_default();

//
//! specifies how a text is rendered on a screen 
//
//! A format specifies how an ASCII text is shown on a screen.
//! A format specifies the following aspects:
//!
//! - the font to be used
//! - the horizontal alignment
//! - the vertical alignment
//! - whether a line is chopped at the right edge or wrapped to the next line
//! - the foreground colcor to be used
//! - the background color to be used
//! - the margins between the text and the edges
//! - the scale factor
//!
//! These aspects are all stored in public attributes and can
//! be read and written.
//

class format {
public:
   //! the font, default is the default font
   const font &f;
   
   //! the horizontal alignment, default is near
   font_alignment h;
   
   //! the vertical alignment, default is near
   font_alignment v;
   
   //! wrapping: true for wraparound, false for cutoff (default).
   bool wrap;
   
   //! scale: 1 is default, 2 is doubole size, etc.
   unsigned int scale;
   
   //! extra spacing between the characters. default is 0.
   vector spacing;
   
   //! top-left margin, default is (2,2)
   vector top_left_margin;
   
   //! bottom-right margin, default is (0,0)
   vector bottom_right_margin;
   
   //! foreground, default is black
   color fg;
   
   //! background, default is transparent
   color bg;
   
   //! create a format specification
   //!
   //! All parameters have suitable default values:
   //! - default font
   //! - black-on-transparent
   //! - top-left aligned 
   //! - no wrapping
   //! - no extra spacing between the characters
   //! - 2 pixels all-around margin
   format( 
      const font &f = font_default(),
      font_alignment h = align_near, 
      font_alignment v = align_near, 
      bool wrap = 0,
      unsigned int scale = 1,
      vector spacing = vector::origin(),
      vector top_left_margin = vector( 2,2 ),
      vector bottom_right_margin = vector( 2,2 ),
      color fg = black,
      color bg = transparent
   ): 
      f( f ),         
      h( h ), 
      v( v ), 
      wrap( wrap ),
      scale( scale ),
      spacing( spacing ),
      top_left_margin( top_left_margin ),
      bottom_right_margin( bottom_right_margin ),
      fg( fg ),
      bg( bg )
   {}

   //! create a format from an existing format and a font
   format( const format &fmt, const font &fr ):
      f( fr ),
      h( fmt.h ), 
      v( fmt.v ), 
      wrap( fmt.wrap ),
      scale( fmt.scale ),
      spacing( fmt.spacing ),
      top_left_margin( fmt.top_left_margin ),
      bottom_right_margin( fmt.bottom_right_margin ),
      fg( fmt.fg ),
      bg( fmt.bg )
   {}	  
};    

//! print a format
hwcpp::io::ostream & operator<<( hwcpp::io::ostream &s, const format &f );


// ==========================================================================
//
// class text
//
//! a formatted text
//
//! This class is used to draw a formatted text in a frame.
//! A format object contains a \b copy of its \ref format, and a
//! \b pointer to its text string. Hence the character string is not copied, 
//! so it must still be available when the text object is drawn.
//!
//
class text : public image {
public:    
	
	 //! the ASCII text string; can be changed
   const char *s;
     
   //! the format used to draw the text; can be changed
   format f;    
   
   //! instantiate a text object
   text( 
      //! pointer to the 0-terminated character string
      //
      //! This string is not copied, only the address is stored.
      //! You can change the content of the string, or even the
      //! pointer (the \ref s attribute), as you see fit.
      //! Note: the string must still be availabe when the text is drawn
      const char *s,
           
      //! the format used to draw the text
      //
      //! This format is copied. You can change the 
      //! copy (the \ref f attribute) as you see fit.
      const format f = format()
   ): s( s ), f( f ){}        
      
   //! draw the text on f, at position
   //
   //! The text is drawn according to the current format 
   //! (the \ref f attribute), and the text that is drawn is the 
   //! current string (whatever the \ref s attribute points to).
   void draw( frame &f, const vector position = vector::origin() ) const; 
};   

// LCD5510 interface
template< 
   typename arg_sce,
   typename arg_res,
   typename arg_dc,
   typename arg_sdin,
   typename arg_sclk
> class lcd_5510 : public frame {

   typedef hwcpp::pin_out_from< arg_sce  > sce;
   typedef hwcpp::pin_out_from< arg_res  > res;
   typedef hwcpp::pin_out_from< arg_dc   > dc;
   typedef hwcpp::pin_out_from< arg_sdin > sdin;
   typedef hwcpp::pin_out_from< arg_sclk > sclk;
   
   void send_byte( unsigned char d ){
      int i;
      for( i = 0; i < 8; i++ ){
         sdin::set( d & 0x80 );
         sclk::set( 1 );
         d = d << 1;
         sclk::set( 0 );
      }
   }    
      
   void command( unsigned char d ){
      dc::set( 0 );
      sce::set( 0 );
      send_byte( d );
      sce::set( 1 );
   } 	
   
   void data( unsigned char d ){
      dc::set( 1 );
      sce::set( 0 );
      send_byte( d );
      sce::set( 1 );
   } 	
      
   void pixels( unsigned char x, unsigned char y, unsigned char d ){
      command( 0x80 | x );   
      command( 0x40 | y );  
      data( d );
   }
   
   unsigned char pixel_buffer[ 504 ];
   
public:   
        
   lcd_5510() : frame( vector( 84, 48 )){
   
      sce::init();
      res::init();
      dc::init();
      sdin::init();
      sclk::init();   
        
      sclk::set( 0 );
      bmptk::wait( 1 * bmptk::us );
      sce::set( 1 );
      bmptk::wait( 1 * bmptk::us );
      res::set( 0 );
      bmptk::wait( 1 * bmptk::us );
      res::set( 1 ); 
      bmptk::wait( 1 * bmptk::us );
   	  
   	   // initialization according to
   	   // https://www.sparkfun.com/products/10168 - nee, andere
      command( 0x21 );  // select exteded instructions
      command( 0xC8 );  // Vop = 110000b
      command( 0x06 );  // TCx = 00b
      command( 0x13 );  // BSx = 100b
      command( 0x20 );  // select basic instructions, horizontal addressing
      command( 0x0C );	// normal mode   
   }	
       
   void checked_write( const vector v, const color c ){
      unsigned int a = v.x + ( v.y / 8 ) * 84;
      unsigned int m = 1 << ( v.y % 8 );
      
      if( c == black ){
         pixel_buffer[ a ] |= m;
      } else {     
         pixel_buffer[ a ] &= ~m;
      }
      
      pixels( v.x, v.y / 8, pixel_buffer[ a ] );      
   }
   
}; 

#ifdef BMPTK_TARGET_win

class target_screen : public frame {
public:
   target_screen( int xsize = 640, int ysize  = 480 );
   void checked_write( const vector v, const color c );
};

#endif

} // namespace graphics

#endif // #ifdef _GRAPHICS_H_
