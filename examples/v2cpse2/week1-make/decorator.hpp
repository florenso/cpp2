#include <stdlib.h>
#include "bmptk.h"
#include "graphics.hpp"

class decorator : public graphics::frame {
private:
   graphics::frame &f;
   
   void checked_write( 
      const graphics::vector p, 
      const graphics::color c 
   ) override { 
	  //f.write( graphics::vector{ ( size.x - 1 ) - p.x, p.y }, c );
     f.write( graphics::vector{ ( size.x - 1 ) -p.y, p.x }, c );
   }
   
public:
   decorator( graphics::frame &fr ):frame( fr.size ),f( fr ){}
};
