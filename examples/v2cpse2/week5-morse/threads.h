#ifndef _threads_
#define _threads_

#define STACK_SIZE 100

class thread  {
public:
   thread( void f( void ) );
private:
   int sp; // switch_from_to assumes this to be the first attribute!
   int stack[ STACK_SIZE ];
   struct thread * next;
   int wakeup_time;
   friend class rtos;
};

class rtos {
public:
   static void wait( int d );
   static void run();
   static void add( thread * t );
private:
   static thread * find_thread();
   static thread * current_thread;
   static thread * first_thread;
};

#endif
