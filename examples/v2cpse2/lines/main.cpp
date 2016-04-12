#include <stdlib.h>
#include "bmptk.h"
#include "graphics.hpp"

short int random_in_range( unsigned int min, unsigned int max ){
   auto x = rand();
   x = x % ( max - min + 1 ); 
   return min + x;
}

graphics::vector random_vector_within( const graphics::vector size ){ 
   return graphics::vector{ 
      random_in_range( 0, size.x ), 
      random_in_range( 0, size.y )
   };
}

int main(){

   #ifdef BMPTK_TARGET_db103
      graphics::lcd_5510<
         bmptk::target::gpio_1_0,  // sce
         bmptk::target::gpio_1_1,  // res
         bmptk::target::gpio_1_2,  // dc
         bmptk::target::gpio_1_3,  // sdin
         bmptk::target::gpio_1_4   // sclk
      > lcd;
   #endif
   #ifdef BMPTK_TARGET_win
      graphics::target_screen lcd; 
   #endif      
   
   for(;;){ 
      lcd.clear();  
      graphics::rectangle( 
         graphics::vector{ 0, 0 }, 
         lcd.size - graphics::vector{ 1, 1 }
      ).draw( lcd );
      for( auto n = 0; n < 20; n++ ){
         auto start = random_vector_within( lcd.size );
         auto end = random_vector_within( lcd.size );
         graphics::line{ start, end - start }.draw( lcd );
         bmptk::wait( 100 * bmptk::ms );        
      }
      bmptk::wait( 1000 * bmptk::ms );      
   }
}
