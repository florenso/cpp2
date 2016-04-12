#include "bmptk.h"
#include "threads.h"
#include "hwcpp.hpp"

#ifndef BMPTK_TARGET_db103
   #error "this is a DB103 project"      
#endif

typedef hwcpp::lpc1114fn28< 48 * hwcpp::MHz > target;
typedef target::uart<> uart;

static int currentPWM = 1;

thread * t1;
thread * t2;
thread * t3;
thread * t4;

/*
void test(){
	hwcpp::io::cout << " Bla doet een schaap\n" <<"\n";  
}  

void vis(){

      volatile int blah[30];
      blah[2] = 10; 
      hwcpp::io::cout << "blah: " << blah[2] <<"\n";   
      test();
}
*/


void dimLED(){
	if((currentPWM+3) <= 25){
		currentPWM += 3;	
	}
}

void brigthLED(){
	if((currentPWM-3) >= 1){
		currentPWM -= 3;
	}
}


//3Hz
void f1(){
   typedef hwcpp::pin_out_from< target::gpio_1_0 > led;
   led::init();
   for(;;){
      // hwcpp::io::cout << "====== thread1 ======\n";
      led::set( 1 );
      rtos::wait( 332 * bmptk::ms );
      led::set( 0 );
      rtos::wait( 332 * bmptk::ms );
   }      
}

//7Hz		
void f2(){
   typedef hwcpp::pin_out_from< target::gpio_1_1 > led;
   led::init();
   for(;;){
      // hwcpp::io::cout << "   ====== thread2 ======\n";
      led::set( 1 );
      rtos::wait( currentPWM * bmptk::ms );
      led::set( 0 );
      rtos::wait( currentPWM * bmptk::ms );
   }      
}

//max 15, min: 
void f3(){
   // hwcpp::io::cout << "   ====== thread3 start ======\n";
   for(;;){
      rtos::wait( 1 * bmptk::ms );
      if( ! uart::get_will_block() ){
         char c = uart::get();
		 if(c == 'u'){
			 brigthLED();
			 hwcpp::io::cout << "Brighten Leds\n"; 
		 } 
		 if(c == 'd'){
			 dimLED();
			 hwcpp::io::cout << "Dimming Leds\n"; 
		 }
		 if(c == 's'){
			 hwcpp::io::cout << "Unused StackSize T4: " << t4->stackOverWritten() <<"\n";
			 hwcpp::io::cout << "Unused StackSize T3: " << t3->stackOverWritten()<<"\n";
			 hwcpp::io::cout << "Unused StackSize T2: " << t2->stackOverWritten()<<"\n";
			 hwcpp::io::cout << "Unused StackSize T1: " << t1->stackOverWritten()<<"\n";
		 }
        // hwcpp::io::cout << c;   
      }
   }      
}



//11hz
void f4(){
   typedef hwcpp::pin_out_from< target::gpio_1_2 > led;
   led::init();
   
   for(;;){
      // hwcpp::io::cout << "   ====== thread2 ======\n";
      led::set( 1 );
      rtos::wait( currentPWM * bmptk::ms );
      led::set( 0 );
      rtos::wait( currentPWM * bmptk::ms );
   }      
}







int main( void ){	
	hwcpp::io::cout.connect< uart >();
	hwcpp::io::cout << "thread demo\n\n";      
	
	thread x1{ f1 };
	thread x2{ f2 };
	thread x3{f3};
	thread x4{f4};
	
	t4 = &x4;
	t3 = &x3;
	t2 = &x2;
	t1 = &x1;
	
	//In switch to asm staan aantal registers dat gepusht worden, daar worden er dus 10 gepusht vandaar 11 
	// getallen is hoe vaak deadbeaf uit de stack is gehaald, stack loopt van boven naar beneden. Getal is eerste plek waar deadbeaf niet meer voorkomt
	
	hwcpp::io::cout << "Unused StackSize X4: " << x4.stackOverWritten() <<"\n";
	hwcpp::io::cout << "Unused StackSize X3: " << x3.stackOverWritten()<<"\n";
	hwcpp::io::cout << "Unused StackSize X2: " << x2.stackOverWritten()<<"\n";
	hwcpp::io::cout << "Unused StackSize X1: " << x1.stackOverWritten()<<"\n";
	hwcpp::io::cout << "Unused StackSize T4: " << t4->stackOverWritten() <<"\n";
	hwcpp::io::cout << "Unused StackSize T3: " << t3->stackOverWritten()<<"\n";
	hwcpp::io::cout << "Unused StackSize T2: " << t2->stackOverWritten()<<"\n";
	hwcpp::io::cout << "Unused StackSize T1: " << t1->stackOverWritten()<<"\n";
	
	//	thread t2{ f2 };
	rtos::run();


	hwcpp::io::cout << "back in main - should not happen :(";   
   
	return 0;
}