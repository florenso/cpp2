#include "bmptk.h"
#include "graphics.hpp"
class picture {
public:
   static void draw( graphics::frame & f ){
      graphics::rectangle( 
         graphics::vector{ 0, 0 }, 
         f.size - graphics::vector{ 1, 1 }
      ).draw( f );   
      graphics::line{ graphics::vector{ 10,10 }, graphics::vector{ 5,5 } }.draw( f );
      graphics::line{ graphics::vector{ 20,20 }, graphics::vector{ 5,5 } }.draw( f );
      graphics::line{ graphics::vector{ 30,30 }, graphics::vector{ 5,5 } }.draw( f );
   }
};
