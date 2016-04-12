#include "bmptk.h"
#include "threads.h"
#include "switch_to.h"

thread * rtos::first_thread = nullptr;
thread * rtos::current_thread;

thread::thread( void f( void ) ){
	this->stack[ STACK_SIZE - 1 ] = (int) f;
	this->sp = (int) & this->stack[ STACK_SIZE - 10 ];
	
	for(int i = 0; i <= (STACK_SIZE - 2); i++){ //fill up stack size with deadbeef :P
		this->stack[i] = 0xDEADBEEF;
	}
	
	rtos::add( this );
}

int thread::stackOverWritten(){

	int *d = &this->stack[0];
	int *e = &this->stack[STACK_SIZE - 1];
   
	int not_used = 0;
    int compare = 0xDEADBEEF; 
	while (d != e) {
		if (*d++ != compare) { //check if deadbeaf equals non deadbeef       
		break;
	}
	not_used++;
	}
	return (STACK_SIZE-not_used);
}

void rtos::add( thread * t ){
   t->wakeup_time = 0;
   t->next = rtos::first_thread;
   rtos::first_thread = t;
}

thread * rtos::find_thread(){
   for(;;){
      for( thread * t = first_thread; t != nullptr; t = t->next ){
         if( bmptk::now() >= t->wakeup_time ){
            return t;
         }
      }
   }
}

void rtos::wait( int d ){
   
   current_thread->wakeup_time = bmptk::now() + d;
   // hwcpp::io::cout << "Stack Size: \n" << current_thread->stackOverWritten();
   switch_from_to( &current_thread, rtos::find_thread() );
}

void rtos::run(){
   static int main_sp;
   rtos::current_thread = ( thread *) & main_sp;
   
   if( first_thread ){
	   
      switch_from_to( &current_thread, first_thread );
   }   
}
