#include <stdlib.h>
#include "bmptk.h"
#include "graphics.hpp"
//#include "lines.hpp"
#include "output.hpp"
#include "decorator.hpp"

int main(){

   #ifdef BMPTK_TARGET_db103
      #error "the LCD5510 LCD is too small for this project"
   #endif
   #ifdef BMPTK_TARGET_win
      graphics::target_screen lcd( 400, 200 ); 
   #endif      
   
   graphics::subframe left{ lcd, graphics::vector{   0, 0 }, graphics::vector{ 200, 200 } };
   graphics::subframe right{ lcd, graphics::vector{ 200, 0 }, graphics::vector{ 200, 200 } };
   decorator dec{right};
   graphics::frame_tee both{ left, dec };
   
   both.clear();  
   picture::draw( both );
      
   for(;;){    
      bmptk::wait( 1000 * bmptk::ms );      
   }
}
