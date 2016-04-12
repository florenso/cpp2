#include "bmptk.h"
#include "gtest/gtest.h"
#include "string20.hpp"

int len( const char * s ){
   return ( *s == '\0' ) ? 0 : 1 + len( s + 1 );
}

bool equal( const string20 & lhs, const char *rhs ){
   EXPECT_EQ( lhs.length(), len( rhs ) ) << "length";
   if( lhs.length() != len( rhs )) return false;
   for( int i = 0; i < lhs.length(); ++i ){
      EXPECT_EQ( lhs[ i ], rhs[ i ] ) << "content @ " << i ;
      if( lhs[ i ] != rhs[ i ] ) return false;
   }
   return true;
}

TEST( Constructors, Default ){
   string20 e;
   ASSERT_EQ( e.length(), 0 ) << "length";   
}

TEST( Constructors, Char ){      
   string20 c{ 'x' };
   ASSERT_EQ( c.length(), 1 ) << "length";   
   ASSERT_EQ( c[ 0 ], 'x' ) << "[0]";   
}

TEST( Assign, string ){      
   string20 s{};
   s = "";  
   ASSERT_TRUE( equal( s, "" )) << "empty";   
   s = "x";  
   ASSERT_TRUE( equal( s, "x" )) << "1char";   
   
   s = "01234567890123456789";
   ASSERT_TRUE( equal( s, "01234567890123456789" )) << "20char";  

   s = "012345678901234567890";
   ASSERT_TRUE( equal( s, "01234567890123456789" )) << "21char";  
   
   ASSERT_TRUE( equal( s = "abc", "abc" )) << "retval";     
   ASSERT_TRUE( equal( ( s = "abc" ) = "fgh", "fgh" )) << "retval assign";     
}

int main( int argc, char **argv ){	      

   string20bug = 1;  
   
   std::cout << "testing string20bug = " << string20bug << "\n";

   testing::InitGoogleTest( &argc, argv );
   int result = RUN_ALL_TESTS();
   (void) result;
   
   for(;;){
      bmptk::wait( 1 * bmptk::s );
   }
}

