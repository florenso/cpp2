// ==========================================================================
//
// refer to graphics.h for all information
//
// ==========================================================================

#include "bmptk.h"
#include "graphics.hpp"

#include <cstdlib>

// avoid these because <algorithm> imports iostream stuff
template <class T> void swap( T& a, T& b ){
  T c(a); a=b; b=c;
}
template <class T> T max( T a, T b ){
  return a > b ? a : b;
}
template <class T> T abs( T a ){
  return a > 0 ? a : -a;
}
 
int abs( int a ){
  return a > 0 ? a : -a;
}
 
namespace graphics {  

			
// ==========================================================================
//
// frame_snapshot
//

#ifdef BMPTK_HAS_FILESYSTEM_X

typedef unsigned short int WORD;
typedef unsigned int DWORD;
typedef int LONG;

// note: For GCC 4.7.0 and higher __packed__ requires 
// -mno-ms-bitfields on the command line.

typedef struct __attribute__ ((__packed__)) {
   WORD    bfType;        // must be 'BM' 
   DWORD   bfSize;        // size of the whole .bmp file
   WORD    bfReserved1;   // must be 0
   WORD    bfReserved2;   // must be 0
   DWORD   bfOffBits;     
} BITMAPFILEHEADER; 
 
typedef struct __attribute__ ((__packed__)) {
   DWORD  biSize;            // size of the structure
   LONG   biWidth;           // image width
   LONG   biHeight;          // image height
   WORD   biPlanes;          // bitplanes
   WORD   biBitCount;        // resolution 
   DWORD  biCompression;     // compression
   DWORD  biSizeImage;       // size of the image
   LONG   biXPelsPerMeter;   // pixels per meter X
   LONG   biYPelsPerMeter;   // pixels per meter Y
   DWORD  biClrUsed;         // colors used
   DWORD  biClrImportant;    // important colors
} BITMAPINFOHEADER;

void frame_snapshot::write_to_bmp_file( const char *file_name ){
    int row_byte_size = 4 * (( 3 * size_get().x + 3 ) / 4);
    int padded_size = row_byte_size * size_get().y;

    hwcpp::io::ofstream bmp( file_name );

	BITMAPFILEHEADER bmfh;	
	bmfh.bfType = 0x4d42;       // 0x4d42 = 'BM'
	bmfh.bfSize = 
	   sizeof(BITMAPFILEHEADER) 
	   + sizeof(BITMAPINFOHEADER) 
	   + padded_size;
	bmfh.bfReserved1 = 0;
	bmfh.bfReserved2 = 0;
	bmfh.bfOffBits = 0x36;	
    bmp.write( (char*)& bmfh, sizeof(BITMAPFILEHEADER) );
	
	BITMAPINFOHEADER info;
	info.biSize = sizeof(BITMAPINFOHEADER);
	info.biWidth = size_get().x;
	info.biHeight = size_get().y;
	info.biPlanes = 1;	
	info.biBitCount = 24;
	info.biCompression = 0; // BI_RGB
	info.biSizeImage = 0;
	info.biXPelsPerMeter = 0x0ec4;  
	info.biYPelsPerMeter = 0x0ec4;     
	info.biClrUsed = 0;	
	info.biClrImportant = 0; 	
    bmp.write( (char*)& info, sizeof(BITMAPINFOHEADER) );
	
    for( int y = size_get().y - 1; y >= 0; y-- ){
	   for( int x = 0; x < size_get().x; x++ ){
	       color c = pixel( vector( x, y ));
		   unsigned char r = c.red_get();
		   unsigned char g = c.green_get();
		   unsigned char b = c.blue_get();
		   bmp.write( (char*)& b, 1 );
		   bmp.write( (char*)& g, 1 );
		   bmp.write( (char*)& r, 1 );
	   }
	   int pad = ( 4 - size_get().x % 4 ) % 4;
	   bmp.write( (char*)& pad, pad );
    }	   
	
	bmp.close();
}

#endif


// ==========================================================================
//
// line
//

void line::draw( frame & fr ){
    
   // don't bother to draw anything 
   // when the size would be 0 or the color transparent
   if( width < 1 || fg.is_transparent() ){
      return;       
   }
              
   // http://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
   // http://homepages.enterprise.net/murphy/thickline/index.html
   
   // int i0 = 0; int i1 = 1;
   int i0 = - ( width / 2 ); 
   // int i1 = 1;
   int i1 = width + i0;
   // i1 = width;
   
   int x0 = 0;
   int y0 = 0;
   int x1 = size.x;
   int y1 = size.y;
   int Dx = x1 - x0; 
   int Dy = y1 - y0;
   int steep = (abs(Dy) >= abs(Dx));
   vector offset( 0, 1);
   if( steep ){
      swap(x0, y0);
      swap(x1, y1);
      // recompute Dx, Dy after swap
      Dx = x1 - x0;
      Dy = y1 - y0;
      offset = vector( 1, 0 );
   }
   int xstep = 1;
   if( Dx < 0 ){
      xstep = -1;
      Dx = -Dx;
   }
   int ystep = 1;
   if( Dy < 0 ){
      ystep = -1;    
      Dy = -Dy; 
   }
   int TwoDy = 2*Dy; 
   int TwoDyTwoDx = TwoDy - 2*Dx; // 2*Dy - 2*Dx
   int E = TwoDy - Dx; //2*Dy - Dx
   int y = y0;
   int xDraw, yDraw;  
   for( int x = x0; x != x1; x += xstep ){    
      if (steep) {     
         xDraw = y;
         yDraw = x;
      } else {     
         xDraw = x;
         yDraw = y;
      }
      for( int i = i0; i < i1; i++ ){
         drawable_draw_pixel(
           fr,
           vector( xDraw, yDraw ) + offset * i, 
           fg );
      }   
      // trace << xDraw << " " << yDraw;
      if( E > 0 ){
         E += TwoDyTwoDx; //E += 2*Dy - 2*Dx;
         y = y + ystep;
      } else {
         E += TwoDy; //E += 2*Dy;
      }
   }
}


// ==========================================================================
//
// rectangle
//

const char * const shape_relief_name[] = {
   "flat", "raised", "sunken" };
   
relief flip( const relief r ){
   if( r == relief_flat ) return relief_flat;	
   if( r == relief_raised ) return relief_sunken;	
   return relief_raised;	
}   

hwcpp::io::ostream & operator<<( hwcpp::io::ostream &s, const relief &r ){ 
   if( r <= relief_raised ){
      s << shape_relief_name[ r ];
   } else {
      s << "invalid";
   }         
   return s;
}
   
void rectangle::draw( frame & fr ){
    
   // don't draw anything that should be invisible
   if( size.x == 0 || size.y == 0 ){
      return;       
   }

   // determine the border color(s)
   color c1 = fg, c2 = fg;
   if( border == relief_raised ){ 
      c1 = bright; 
      c2 = dark;
   }
   if( border == relief_sunken ){ 
      c2 = bright; 
      c1 = dark;
   }

   // draw the borders
   for( unsigned int i = 0; i < width; i++ ){
      vector s = size.direction() * i;  
      vector d = size - ( s * 2 );   
      line( 
	     position + s,                    d.x_projection(),   c1 ).draw( fr );
      line(  
	     position + s + d.x_projection(), d.y_projection(),   c2 ).draw( fr );
      line( 
	     position + s + d,                - d.x_projection(), c2 ).draw( fr );
      line( 
	     position + s + d.y_projection(), - d.y_projection(), c1 ).draw( fr );
   }   
   
   // draw the inner region
   vector margin = size.direction() * width;
   subframe( 
      fr, 
      position + margin, 
      ( size + size.direction() ) - margin * 2 ).clear( bg ); 
}   


// ==========================================================================
//
// circle
//

void circle::draw( frame & fr ){
   circle_draw( fr, bg, 1 );
   circle_draw( fr, fg, 0 );
}

void circle::circle_draw_pixel( 
   frame &fr,
   const vector v,
   const color c
) const {
   
   int start = width / 2;
   int end = (int) width - start;
   for( int x = - start; x < end; x++ ){
      for( int y = - start; y < end; y ++ ){
         if( abs( x ) + abs( y ) < (int) width ){
            drawable_draw_pixel( fr, v + vector( x, y ), c );   
         }   
      }
   }      
}   

void circle::circle_draw (
   frame &fr,
   const color c,
   bool fill
) const {

   // don't draw anything when the size would be 0 
   if( radius < 1 ){
      return;       
   }
   
   // http://en.wikipedia.org/wiki/Midpoint_circle_algorithm
   
   int f = 1 - radius;
   int ddFx = 1;
   int ddFy = -2 * radius;
   int x = 0;
   int y = radius;
    
   if( fill ){
   
      // top and bottom
      drawable_draw_pixel( fr, vector( 0, + radius ), c );
      drawable_draw_pixel( fr, vector( 0, - radius ), c );

      // left and right
      line( 
		   position - vector( radius, 0 ), 
		   vector( 2 * radius, 0 ), 
		   c 
	    ).draw( fr );
      
   } else {
   
      // top and bottom
      circle_draw_pixel( fr, vector( 0, + radius ), c );
      circle_draw_pixel( fr, vector( 0, - radius ), c );

      // left and right 
      circle_draw_pixel( fr, vector( + radius, 0 ), c );
      circle_draw_pixel( fr, vector( - radius, 0 ), c );
   }   
    
   while( x < y ){
      
      // calculate next outer circle point
      if( f >= 0 ){
        y--;
        ddFy += 2;
        f += ddFy;
      }
      x++;
      ddFx += 2;
      f += ddFx;   
                    
      if( fill ){
         line( position + vector( -x,  y ), vector( 2 * x, 0 ), c ).draw( fr );
         line( position + vector( -x, -y ), vector( 2 * x, 0 ), c ).draw( fr );
         line( position + vector( -y,  x ), vector( 2 * y, 0 ), c ).draw( fr );
         line( position + vector( -y, -x ), vector( 2 * y, 0 ), c ).draw( fr );
      } else {
         circle_draw_pixel( fr, vector( + x, + y ), c );
         circle_draw_pixel( fr, vector( - x, + y ), c );
         circle_draw_pixel( fr, vector( + x, - y ), c );
         circle_draw_pixel( fr, vector( - x, - y ), c );
         circle_draw_pixel( fr, vector( + y, + x ), c );
         circle_draw_pixel( fr, vector( - y, + x ), c );
         circle_draw_pixel( fr, vector( + y, - x ), c );
         circle_draw_pixel( fr, vector( - y, - x ), c );
      }
   }
}


// ==========================================================================
//
// image
//

void image_pixels::draw( frame &f, const vector position ) const {
   for( int x = 0; x < size.x; x++  ){
      for( int y = 0; y < size.y; y++ ){
         vector a( x, y );            
         f.write( position + a, read( a )); } } } 

         
// ==========================================================================
//
// inline_photo
//

color inline_rgb_photo :: checked_read( const vector p ) const {
   unsigned int base = 3 * ( p.x + p.y * size.x );    
   return color( data[ base ], data[ base + 1 ], data[ base + 2 ] );    
}

bool inline_bw_photo :: bool_read( const vector p ) const {
   unsigned int a = p.x + p.y * size.x;
   return ( data[ a / 8 ] ) & ( 1 << ( a % 8 ));   
}


// ==========================================================================
//
// inline_font
//

vector inline_font :: char_size( char c ) const {
   if( ! has( c )){
      return vector( 0, font_char_size.y ); 
             
   } else if( fixed ){
      return font_char_size;      
      
   } else {           
      return vector( 
         start[ 1 + (int)c - 32 ] - start[ (int)c - 32 ],
         font_char_size.y );
   }
}   

bool inline_font :: read( char c, const vector p ) const {
   return bool_read( p + vector( start[ (int) c - 32 ], 0 ));
}


// ==========================================================================
//
// format
//

const char * const font_alignment_name[] = {
   "near", "far", "centre", "filled" }; 
hwcpp::io::ostream & operator<<( hwcpp::io::ostream &s, const font_alignment &a ){ 
   if( a <= align_fill ){
      s << font_alignment_name[ a ];
   } else {
      s << "invalid";
   }         
   return s;
}
hwcpp::io::ostream & operator<<( hwcpp::io::ostream &s, const format &f ){
//   s << "{ f@" << hwcpp::io::hex << (unsigned long) &f.f;
//   s << " h=" << f.h << " v=" << f.v;
//   s << " w=" << f.wrap << " sc=" << f.scale;
//   s << " sp=" << f.spacing;
   s << " tlm=" << f.top_left_margin;
   s << " brm=" << f.top_left_margin;
   s << " fg=" << f.fg << " bg=" << f.bg;
   s << "}";
   return s;
}


// ==========================================================================
//
// text
//

//! returns number of lines needed to draw the text 
//
//! This function returns the number of (vertical) lines rquired to draw 
//! the text s using the format fm and size. 
//! Wrapping is taken into account.
//!
//! This width is used to determine where to start drawing the 
//! text when the vertical alignment is not align_near.
int line_count( 
   const char *s, 
   const vector size, 
   const format &fm 
){
   int count = 1; 
   int x = 0;
   for( ; *s != '\0' ; s++ ){  
      if( *s == '\n' ){
         count++;
         x = 0;
      } else {
         int char_size = fm.f.char_size( *s ).x + fm.spacing.x;
         if(( x + char_size > size.x ) && fm.wrap ){
            count++;    
            x = 0;                
         }
         x += char_size;                
      }                  
   }        
   return count;
}

//! returns the length (width) in pixels of the first formatted line from s 
//
//! This function returns the width, in pixels, of the first
//! line of characters from s, taking the size and format into account.
//!
//! This width is used to determine where to start drawing the 
//! text when the horizontal alignment is not align_near.
int line_width( 
   const char *s, 
   const vector size, 
   const format &fm 
){
   int length = 0;
   int space = 0;
   for( ; ( *s != '\0' ) && ( *s != '\n' ); s++ ){
      int char_size = fm.f.char_size( *s ).x + space; 
      // trace << "len=" << length << "[" << *s << "] cs=" << char_size;
      if( length + char_size > size.x ){
         return length;                 
      }
      length += char_size;
      space = fm.spacing.x;               
   }     
   return length;
}

//! returns the number of characters in the first formatted line from s 
int line_chars( 
   const char *s, 
   const vector size, 
   const format &fm 
){
   int length = 0;
   int space = 0;
   int chars = 0;
   for( ; ( *s != '\0' ) && ( *s != '\n' ); s++ ){
      int char_size = fm.f.char_size( *s ).x + space;
      if( length + char_size > size.x ){
         return chars;                 
      }
      length += char_size; 
      space = fm.spacing.x; 	            
      chars++;
   }     
   return chars;
}

//! draws a single line of text, and advances the text pointer-pointer
void draw_text_line( 
   frame &fr, 
   vector &p, 
   const format &fm, 
   const char **s 
){   
   // trace << "[" << *s << "]@" << p << " in " << fr.size_get();
   int width = line_width( *s, fr.size, fm );
   int extra = fr.size.x - width;
   int spaces = line_chars(  *s, fr.size, fm ) - 1;
   int missing = 0;
   // trace << "w=" << width << " extra=" << extra << " spaces=" << spaces;
   if( fm.h == align_far ){
      p += vector( extra, 0 );
   } 
   if( fm.h == align_centre ){
      p += vector( extra / 2, 0 );
   } 
   int n = 0;
   for( ; (**s != '\n') && (**s != '\0') ; (*s)++ ){           
      if( ( fm.h == align_fill ) && ( n++ > 0 ) ){    
         missing += extra; 
         int adjust = missing / max( spaces, 1 );
         p += vector( adjust, 0 );
         missing -= adjust * spaces;
      }
      char_photo fc( fm.f, **s, fm.fg, fm.bg );
      fc.draw( fr, p );
      p += vector( fc.size_get().x + fm.spacing.x, 0 );
   }          
}

//! draw a text
void text::draw( 
   frame &fx, 
   const vector fx_position
) const {

   // trace << f << "[" << s << "]";
   subframe fr( 
     fx, 
	 fx_position + f.top_left_margin, 
	 fx.size - ( fx_position + f.top_left_margin + f.bottom_right_margin ), 
	 false ); // f.scale );
   // fr.clear( color::red() ); 

   vector p( 0, 0 );
   int lines = line_count( s, fr.size, f ); 
   int extra = max( 
      0, 
      fr.size.y - lines * f.f.font_char_size.y );
   int missing = 0;
   if( f.v == align_far ){
      p += vector( 0, extra);
   } 
   if( f.v == align_centre ){
      p += vector( 0, extra / 2 );
   } 
   const char *ss = s;
   for( ; *ss != '\0'; ){
      if( f.v == align_fill ){  
         missing += extra;   
         int adjust = missing / ( lines + 1 ); 
         // trace << extra << " " << missing << " " << adjust;
         p += vector( 0, adjust );
         missing -= adjust * ( lines + 1 );
      }
      // trace << p << f.f->font_char_size << f.spacing;
      draw_text_line( fr, p, f, &ss );   
      if( *ss == '\n' ){ 
         ss++;
         p = ( p + f.f.font_char_size + f.spacing ).y_projection();          
      }   
   }               
}

} // namespace graphics

// win window interface
#ifdef BMPTK_TARGET_win

#include "windows.h"

namespace graphics {

// derived by trial-and-error :(
#define X_MARGIN 20
#define Y_MARGIN 42

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		/* trap the WM_CLOSE (clicking X) message, and actually tell the window to close */
		case WM_CLOSE: {
			DestroyWindow(hwnd);
			break;
		}
		
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

HINSTANCE hInstance;
WNDCLASSEX wc; /* A properties struct of our window */
HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
MSG Msg; /* A temporary location for all messages */
HDC hdc;
	
/* The 'main' function of Win32 GUI programs: this is where execution starts */
/*
int WINAPI WinMain(HINSTANCE xhInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
   hInstance = xhInstance;
   extern "C" int main();
   main();
   return 0;
}
*/

target_screen::target_screen( int xsize, int ysize ):
   frame( vector( xsize, ysize ))
{

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION);

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		for(;;);
	}

	hwnd = CreateWindowEx(
	    WS_EX_CLIENTEDGE,
		"WindowClass",
		"Caption",
		WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		xsize + X_MARGIN, /* width */
		ysize + Y_MARGIN, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		for(;;);
	}
	
   hdc = GetDC(hwnd);
   for( int x = 0; x < 200; x++ ){
      SetPixel( hdc, 10 + x , 10 + x, RGB( 10+x, 100, 0 ) );
   }

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produre unreasonably CPU usage
	*/
	if(0)while(GetMessage(&Msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&Msg); /* Translate keycodes to chars if present */
		DispatchMessage(&Msg); /* Send it to WndProc */
	}
	// return Msg.wParam;
}

#define SCALE 1

void target_screen::checked_write( 
   const vector v,
   const color c 
){
   if( ! c.is_transparent() ){ 
      for( int x = 0; x < SCALE; x++ ){
         for( int y = 0; y < SCALE; y++ ){
            SetPixel( 
		        hdc, 
   			  SCALE * v.x + x , 
	   		  SCALE * v.y + y,
		   	  RGB( c.red_get(), c.green_get(), c.blue_get() )
            );
         }            
      }
   }      
}

} // namespace graphics

#endif


