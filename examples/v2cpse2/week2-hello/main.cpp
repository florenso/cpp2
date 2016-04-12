#include "bmptk.h"


extern "C" {

   // don't chance this function: it is the bridge 
   // between the C and assembler 'world' and C++.
   void put_char( char c ){
      hwcpp::io::cout << c;
   }

   void print_asciz( const char * p );
//      while( *p != '\0' ){
//         put_char( *p );
//         p++;
//      }
//   }

   void application();//{
//      print_asciz( "Hello world\n" );
//   }       

char magic_tolower(char);
char magic_toupper(char);

char do_magic(char p){
  if(isupper(p)){
  p=magic_tolower(p);
  }
  else if (islower(p)){
  p=magic_toupper(p);
  }
   return p;
}

};
 
// Do not change the code below. Execution starts in C++, 
// then continues in application(). Make your modifications 
// there in the extern "C" { . . . }; part, and in the separate .asm file.
int main(){	        
   #ifdef BMPTK_TARGET_db103
      hwcpp::io::cout.connect< bmptk::target::uart<> >();
   #endif   
   application();   
   hwcpp::io::cout << "\n** application ended **\n";
   for(;;){
      bmptk::wait( 10 * bmptk::ms );
   }  
}

