#include "bmptk.h"
#include "pRTOS.h"
#include "hwcpp.hpp"

#ifndef BMPTK_TARGET_db103
   #error "this is a DB103 project"      
#endif

typedef bmptk::target::uart<> uart;
typedef hwcpp::pin_out_from< bmptk::target::gpio_1_3 > lsp;

typedef hwcpp::pin_out_from< bmptk::target::gpio_1_4 > bar1;
typedef hwcpp::pin_out_from< bmptk::target::gpio_1_5 > bar2;
typedef hwcpp::pin_out_from< bmptk::target::gpio_1_8 > bar3;
typedef hwcpp::pin_out_from< bmptk::target::gpio_1_9 > bar4;

struct beep_task : public RTOS::task {
   beep_task(): 
      task{ 0, "beep" },
      interval_clock{ this, 500 * bmptk::us, "interval" }, 
      morse_mb{"morse_mailbox"}
   {}
   
    void mail_morse(const char * c) {
        morse_mb.write(c);
    }
   
private:
   RTOS::clock interval_clock;
   RTOS::mailbox<const char *> morse_mb;
   static constexpr auto dot = 200 * bmptk::ms;
   
   void beep(bmptk::time on) {
		int current_time = bmptk::now();
		while(on+current_time > bmptk::now()) {
			lsp::set(1);
			wait(interval_clock);
			lsp::set(0);
			wait(interval_clock);
		}
		sleep(dot);
	}
   
   
   void main(){
      lsp::init();
      for( ;; ){
         const char * s = morse_mb.read();
		for( int i = 0; s[ i ] != '\0'; ++i ){
		   if( s[ i ] == '.' ){
			  beep( dot );
		   } else {
			  beep( 3 * dot );
		   }
		}
      }
	  sleep(2 * dot);      
   }
};

struct bar_task : public RTOS::task {
   bar_task() : 
      task{ 3, "bar" }, 
	  bar_indicator( this, "bar_indicator" )
   {}
      
   void change( int n ){
      bar_indicator.write(n);
   }
   
private:
   RTOS::channel<int, 10> bar_indicator;
   int value;
   
   void update() {
		int u = bar_indicator.read();
		value += u;
	}
   
   
   void main(){
	  value = 0;
	  bar_indicator.write(0);
      bar1::init();
      bar2::init();
      bar3::init();
      bar4::init();
	  
      for(;;){
		 
     		update();
			hwcpp::io::cout << "value is: " << value << "\n\n" ;   
			bar1::set( value >= 1 );
			bar2::set( value >= 2 );
			bar3::set( value >= 3 );
			bar4::set( value >= 4 );
		 
			wait(bar_indicator);
      }
	  
   }      
};

const char * morse( char c ){
   switch( c ){
      case 'a' : return ".-";
	   case 'b' : return "-...";
	   case 'c' : return "-.-.";
	   case 'd' : return "-..";
      case 'e' : return ".";
	   case 'f' : return "..-.";
	   case 'g' : return "--.";
	   case 'h' : return "....";
	   case 'i' : return "..";
	   case 'j' : return ".---";
	   case 'k' : return "-.-";
	   case 'l' : return ".-..";
	   case 'm' : return "--";
	   case 'n' : return "-.";
	   case 'o' : return "---";
	   case 'p' : return ".--.";
	   case 'q' : return "--.-";
	   case 'r' : return ".-.";
	   case 's' : return "...";
	   case 't' : return "-";
	   case 'u' : return "..-";
	   case 'v' : return "...-";
	   case 'w' : return ".--";
	   case 'x' : return "-..-";
	   case 'y' : return "-.--";
	   case 'z' : return "--..";
	   default : return "";
   }
}

struct morse_task : public RTOS::task {
   morse_task( beep_task & beeper, bar_task & bar ): 
      task{ 1, "morse" }, 
      beeper( beeper ), 
      bar( bar ),
      store( this, "store" )
   {}
   
   void enqueue( char c ){
      bar.change( +1 );
      store.write( c );
   }
      
private:
   beep_task & beeper;
   bar_task & bar;
   RTOS::channel< char, 100 > store;
   static constexpr auto dot = 200 * bmptk::ms;
   
   
   void main(){
      for(;;){
         char c = store.read();
		bar.change( -1 );
		if( c == ' ' ){
			sleep(7 * dot);
		} else {
			const char * s = morse(c);
			beeper.mail_morse(s);
		}
      }   
   }
};

struct poll_task : public RTOS::task {
   poll_task( morse_task & morse ): 
      task{ 1, "poll" }, 
      morse( morse )
   {}
      
private:
   morse_task & morse;
   
   void main(){
      for(;;){
         sleep( 500 * bmptk::us );
         if( ! uart::get_will_block() ){
            char c = uart::get();
            if( c == '@' ){
               RTOS::display_statistics();
            }
            morse.enqueue( c );
         }
      }
   }
};

		
int main( void ){	
   hwcpp::io::cout.connect< uart >();
   hwcpp::io::cout << "RTOS demo\n\n";   
   
   beep_task beep;
   bar_task bar;
   morse_task morse( beep, bar );
   poll_task poll( morse );
   RTOS::run();
   
   hwcpp::io::cout << "back in main";   
   
   return 0;
}