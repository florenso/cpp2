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

TEST( Constructors, string){   
   const char * b = new char { 'b' };   
   string20 c{ b  };
   ASSERT_EQ( c.length(), 1 ) << "length";   
   ASSERT_EQ( c[ 0 ], 'b' ) << "[0]";   
   
   const char * b = "012345678901234567890";   
   string20 c{ b  };
   ASSERT_EQ( c.length(), 20 ) << "length";   
}

TEST( Constructors, String20 ){   
	const string20 c{"TEST"};
    string20 s{ c };
    ASSERT_EQ( s.length(), c.length()) << "length";
    ASSERT_EQ( s[0], c[0]) << "[0]";

   const string20 x{"012345678901234567890"};
   string20 z{ x };
   ASSERT_TRUE( equal( z, "01234567890123456789" )) << " 21 chars ";   
}

TEST( Function, length){
   string20 s{ "t" };
   ASSERT_EQ( s.length(), 1) << "4 length";
   s = "";
   ASSERT_EQ( s.length(), 0) << "0 length";
   s = "0123456789012345678901234567890";
   ASSERT_EQ( s.length(), 20) << "20 length";
   
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

TEST( Assign, string20 ){      
	const string20 c{"testje"};
   string20 s{"testestetest"};
   s = c;
   ASSERT_EQ( s.length(), 12) << " not right length";
   ASSERT_EQ( s[0], c[0]) << "[0]";
   ASSERT_EQ( s[3], c[3]) << "[3]";

   const string20 x {"012345678901234567890"};
   string20 z {};
   z = x;
   ASSERT_TRUE( equal( z, "01234567890123456789" )) << "21char"; 
}

TEST( Assign, Char ){      
   char thechar = 'b';
   string20 beassigned{ };
   beassigned = thechar;
   ASSERT_TRUE( equal( beassigned, "b" )) << "b equals b.";
   ASSERT_EQ( beassigned.length(), 1 ) << "length";
   ASSERT_EQ( beassigned[0], 'b' ) << "[0]";
}

TEST( Append, string20 ){     
   string20 f{ "firstpart_"}; 
   string20 s{ "appended"};

   f += s;
   ASSERT_TRUE( equal( f, "firstpart_appended" )) << "appended string20";  
}

TEST( Append, Char ){     
   char test = 'a';
   string20 s{ "appended_" };

   s += test;
   ASSERT_TRUE( equal( s, "appended_a" )) << "appended char";  
}

TEST( Append, string ){     
   const char * test = "string_appending";
   string20 s{ "appended_" };

   s += test;
   ASSERT_TRUE( equal( s, "appended_string_appending" )) << "appended string";  
}

TEST( Add, string20 ){     
   string20 first {"asdf"};
   string20 second{ "asdf" };
   ASSERT_TRUE( equal( first + second, "asdfasdf" )) << "added string20";  
}

TEST( Add, Char ){     
   string20 first {"asdf"};
   char second = 'g';
   ASSERT_TRUE( equal( first + second, "asdfg" )) << "added char";  
}

TEST( Add, string ){     
   string20 first {"asdf"};
   const char * second = "_fdsa";
   ASSERT_TRUE( equal( first + second, "asdf_fdsa" )) << "added string";  
}

TEST( Add, Char_String20_reverse ){     
   string20 first {"asdf"};
   char s = 'f';
   ASSERT_TRUE( equal( s + first, "fasdf" )) << "added string reverse";  
}

TEST( Add, string_String20_reverse ){     
   string20 first {"asdf"};
   const char * second = "vissenkop_";
   ASSERT_TRUE( equal( second + first, "vissenkop_asdf" )) << "added string20 reverse";  
}

TEST( Multiply, string20_int ){     
   string20 first {"asdf"};
   ASSERT_TRUE( equal( first*4, "asdfasdfasdfasdf" )) << "multiplied string";  
}

TEST( Multiply, string20_int_reverse ){     
   string20 first {"kip_"};
   ASSERT_TRUE( equal( 4*first, "kip_kip_kip_kip_" )) << "multiplied string reverse";  
}

TEST( Get, String20Length ){   
   const char * b =  "asdf" ;
   string20 long_string{ b };
   ASSERT_EQ( long_string.length(), 4 ) << "length";   
   ASSERT_EQ( long_string[ 0 ], 'a' ) << "[0]";   
   ASSERT_EQ( long_string[ 1 ], 's' ) << "[1]";   
   ASSERT_EQ( long_string[ 2 ], 'd' ) << "[2]";   
   ASSERT_EQ( long_string[ 3 ], 'f' ) << "[3]";   
}

TEST( Get, String20valueChange ){   
   string20 long_string{ "visjes" };
   long_string[ 0 ] = 'p';
   ASSERT_TRUE( equal(long_string, "pisjes") ) << "get and change char";   
}

TEST( Get, String20valueConst ){   
   const string20 long_string{ "visjes" };
   ASSERT_EQ( long_string[ 3 ], 'j' ) << "[3]"   << "get and const char";   
}


int main( int argc, char **argv ){	      

   string20bug = 10;  
   
   std::cout << "testing string20bug = " << string20bug << "\n";

   testing::InitGoogleTest( &argc, argv );
   int result = RUN_ALL_TESTS();
   (void) result;
   
   for(;;){
      bmptk::wait( 1 * bmptk::s );
   }
}

