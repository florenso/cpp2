#include "bmptk.h"
#include "graphics.hpp"
typedef graphics::vector vector;

void f( graphics::frame &f ){
   f.clear( graphics::blue ); 
   graphics::circle( 
      vector( 10, 10 ), 5, graphics::red, graphics::red ).draw( f );
}

int main( void ){
   #ifdef BMPTK_TARGET_db103
      #error "this examples uses color, hence it is not for the LCD5510"
   #endif
   #ifdef BMPTK_TARGET_win
      graphics::target_screen lcd; 
   #endif 
   
   lcd.clear();
   graphics::subframe a{ lcd, vector{ 10, 10 }, vector{ 20, 20 }};
   graphics::subframe b{ lcd, vector{ 100, 100 }, vector{ 20, 20 }};
   f( a );
   f( b );
   for(;;){
      bmptk::wait( 10 * bmptk::ms );
   }      
}

