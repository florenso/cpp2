#include "bmptk.h"
  
int main(){	        
   #ifdef BMPTK_TARGET_db103
      hwcpp::io::cout.connect< bmptk::target::uart<> >();
   #endif

   hwcpp::io::cout << "Hello world\n";
   
   for( int n = 1; ; n++ ){
      bmptk::wait( 1 * bmptk::s );
      hwcpp::io::cout << n << "\n";
   }
}

