#include "bmptk.h"
#include "threads.h"
#include "switch_to.h"

thread * rtos::first_thread = nullptr;
thread * rtos::current_thread;

thread::thread( void f( void ) ){
   this->stack[ STACK_SIZE - 1 ] = (int) f;
   this->sp = (int) & this->stack[ STACK_SIZE - 10 ];
   rtos::add( this );
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
   switch_from_to( &current_thread, rtos::find_thread() );
}

void rtos::run(){
   static int main_sp;
   rtos::current_thread = ( thread *) & main_sp;
   if( first_thread ){
      switch_from_to( &current_thread, first_thread );
   }   
}
