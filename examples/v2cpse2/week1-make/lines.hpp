
#include "bmptk.h"
#include "graphics.hpp"
class picture {
public:
   static void draw( graphics::frame & f ){

      graphics::line{ graphics::vector{ 100,20 }, graphics::vector{ 3,2 } }.draw( f );
      graphics::line{ graphics::vector{ 103,22 }, graphics::vector{ 3,2 } }.draw( f );
      graphics::line{ graphics::vector{ 106,24 }, graphics::vector{ 0,5 } }.draw( f );
      graphics::line{ graphics::vector{ 106,29 }, graphics::vector{ 16,23 } }.draw( f );
      graphics::line{ graphics::vector{ 122,52 }, graphics::vector{ -13,42 } }.draw( f );
      graphics::line{ graphics::vector{ 109,94 }, graphics::vector{ 10,6 } }.draw( f );
      graphics::line{ graphics::vector{ 119,100 }, graphics::vector{ -21,21 } }.draw( f );
      graphics::line{ graphics::vector{ 98,121 }, graphics::vector{ 1,7 } }.draw( f );
      graphics::line{ graphics::vector{ 99,128 }, graphics::vector{ 13,10 } }.draw( f );
      graphics::line{ graphics::vector{ 112,138 }, graphics::vector{ -7,12 } }.draw( f );
      graphics::line{ graphics::vector{ 105,150 }, graphics::vector{ 0,8 } }.draw( f );
      graphics::line{ graphics::vector{ 105,158 }, graphics::vector{ -22,1 } }.draw( f );
      graphics::line{ graphics::vector{ 83,159 }, graphics::vector{ -8,-5 } }.draw( f );
      graphics::line{ graphics::vector{ 75,154 }, graphics::vector{ 4,-30 } }.draw( f );
      graphics::line{ graphics::vector{ 79,124 }, graphics::vector{ 3,-19 } }.draw( f );
      graphics::line{ graphics::vector{ 82,105 }, graphics::vector{ 1,-3 } }.draw( f );
      graphics::line{ graphics::vector{ 83,102 }, graphics::vector{ -1,-2 } }.draw( f );
      graphics::line{ graphics::vector{ 82,100 }, graphics::vector{ -3,-1 } }.draw( f );
      graphics::line{ graphics::vector{ 79,99 }, graphics::vector{ -5,-1 } }.draw( f );
      graphics::line{ graphics::vector{ 74,98 }, graphics::vector{ -5,-1 } }.draw( f );
      graphics::line{ graphics::vector{ 69,97 }, graphics::vector{ -5,-2 } }.draw( f );
      graphics::line{ graphics::vector{ 64,95 }, graphics::vector{ -3,-3 } }.draw( f );
      graphics::line{ graphics::vector{ 61,92 }, graphics::vector{ 4,-2 } }.draw( f );
      graphics::line{ graphics::vector{ 65,90 }, graphics::vector{ 2,-9 } }.draw( f );
      graphics::line{ graphics::vector{ 67,81 }, graphics::vector{ 8,-4 } }.draw( f );
      graphics::line{ graphics::vector{ 75,77 }, graphics::vector{ 10,-3 } }.draw( f );
      graphics::line{ graphics::vector{ 85,74 }, graphics::vector{ 7,-5 } }.draw( f );
      graphics::line{ graphics::vector{ 92,69 }, graphics::vector{ -4,-6 } }.draw( f );
      graphics::line{ graphics::vector{ 88,63 }, graphics::vector{ -3,-10 } }.draw( f );
      graphics::line{ graphics::vector{ 85,53 }, graphics::vector{ -2,-10 } }.draw( f );
      graphics::line{ graphics::vector{ 83,43 }, graphics::vector{ 4,-1 } }.draw( f );
      graphics::line{ graphics::vector{ 87,42 }, graphics::vector{ 8,-1 } }.draw( f );
      graphics::line{ graphics::vector{ 95,41 }, graphics::vector{ 6,0 } }.draw( f );
      graphics::line{ graphics::vector{ 101,41 }, graphics::vector{ -7,-13 } }.draw( f );
      graphics::line{ graphics::vector{ 94,28 }, graphics::vector{ -2,-9 } }.draw( f );
      graphics::line{ graphics::vector{ 92,19 }, graphics::vector{ -7,-7 } }.draw( f );
      graphics::line{ graphics::vector{ 85,12 }, graphics::vector{ -1,-1 } }.draw( f );
      graphics::line{ graphics::vector{ 84,11 }, graphics::vector{ 2,0 } }.draw( f );
      graphics::line{ graphics::vector{ 86,11 }, graphics::vector{ 7,2 } }.draw( f );

   }
};
