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

//randen controleren, dus max 20 min 1 etc.

TEST( Constructors, Default ){
   string20 e;
   ASSERT_EQ( e.length(), 0 ) << "length";   
}

TEST( Constructors, string20){
   const string20 c{"TEST"};
   string20 s{ c };
   ASSERT_EQ( s.length(), c.length()) << "length";
   ASSERT_EQ( s[0], c[0]) << "[0]";

   //Check if max == 20
   const string20 x{"012345678901234567890"};
   string20 z{ x };
   ASSERT_TRUE( equal( z, "01234567890123456789" )) << "21char"; 
}

TEST( Constructors, Char ){      
   string20 s{ 'x' };
   ASSERT_EQ( s.length(), 1 ) << "length";   
   ASSERT_EQ( s[ 0 ], 'x' ) << "[0]";   
}

TEST( Constructors, string){
   string20 s{ "test" };
   ASSERT_EQ( s.length(), 4) << "length";
   ASSERT_EQ( s[0], 't') << "[0]";
   ASSERT_EQ( s[3], 't') << "[3]";

   string20 z{ "012345678901234567890" };
   ASSERT_TRUE( equal( z, "01234567890123456789" )) << "21char"; 
}

TEST( Function, length){
   string20 s{ "t" };
   ASSERT_EQ( s.length(), 1) << "4length";
   s = "";
   ASSERT_EQ( s.length(), 0) << "0length";
   s = "0123456789012345678901234567890";
   ASSERT_EQ( s.length(), 20) << "20length";
   
}

TEST( Assign, string20 ){
   const string20 c{"test"};
   string20 s{"tester"};
   s = c;
   ASSERT_EQ( s.length(), 4) << " not right length";
   ASSERT_EQ( s[0], c[0]) << "[0]";
   ASSERT_EQ( s[3], c[3]) << "[3]";

   const string20 x {"012345678901234567890"};
   string20 z {};
   z = x;
   ASSERT_TRUE( equal( z, "01234567890123456789" )) << "21char"; 
}

TEST( Assign, Char ){
   string20 s{};
   s = 'x';
   ASSERT_EQ( s, "x") << "1char";
   ASSERT_EQ( s.length(), 1 ) << "length";
   ASSERT_EQ( s[0], 'x' ) << "[0]";
} 

TEST( Assign, String ){      
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

TEST(AddAssign, String20){
   const string20 s{"efgh"};
   string20 c{"abcd"};
   
   c += s;
   
   ASSERT_EQ( c.length() , 8) << "8char";
   ASSERT_EQ(  c, "abcdefgh") << "content";
   
   const string20 z{"012345678901234567890"};
   c += z;
   ASSERT_TRUE( equal( c, "abcdefgh012345678901" )) << "21char"; 

}

TEST(AddAssign, Char){
   string20 s{ "ab" };
   s += 'c';

   ASSERT_EQ( s.length() , 3) << "3char";
   ASSERT_EQ( s, "abc") << "content";
   ASSERT_EQ( s += 'd', "abcd") << "retval";


   //Check if max 20
   for( int i = 0; i < 20; ++i ){
      s += 'c';
   }
   ASSERT_TRUE( equal( s, "abcdcccccccccccccccc" )) << "21char"; 
}

TEST(AddAssign, String){
   string20 s{ "abc" };
   s += "defgh";

   ASSERT_EQ( s.length() , 8) << "6char";
   ASSERT_EQ( s, "abcdefgh") << "content";

   s += "012345678901234567890";
   ASSERT_TRUE( equal( s, "abcdefgh012345678901" )) << "21char"; 
}


TEST(Add, String20){
   const string20 s{"efgh"};
   string20 c{"abcd"};
   
   c = c + s;
     ASSERT_EQ( c.length() , 8) << "8char";
   ASSERT_EQ( c, "abcdefgh") << "content";

   c = c + c;
   ASSERT_EQ( c.length(), 16) << "16char";
   ASSERT_EQ( c, "abcdefghabcdefgh") << "content";
   
   const string20 z{"012345678901234567890"};
   c = c + z;
   ASSERT_TRUE( equal( c, "abcdefghabcdefgh0123" )) << "21char"; 
}

TEST(Add, Char){
   string20 s{ "ab" };
   s = s + 'c';

   ASSERT_EQ( s.length() , 3) << "3char";
   ASSERT_EQ( s, "abc") << "content";

   //Check if max 20
   for( int i = 0; i < 20; ++i ){
      s += 'c';
   }
   ASSERT_TRUE( equal( s, "abcccccccccccccccccc" )) << "21char"; 
}

TEST(Add, String){
   string20 s{ "abc" };
   s = s + "defgh";

   ASSERT_EQ( s.length() , 8) << "6char";
   ASSERT_EQ( s, "abcdefgh") << "content";

   s = s + "012345678901234567890";
   ASSERT_TRUE( equal( s, "abcdefgh012345678901" )) << "21char"; 
}

TEST(AddLHS, Char){
   string20 s{ "" };
   const string20 c { "ab" };
   s = 'c' + c;
   ASSERT_EQ( s.length() , 3) << "3char";
   ASSERT_EQ( s, "cab") << "content";

   //Check if max 20
   for( int i = 0; i < 20; ++i ){
      s = 'c' + s;
   }
   ASSERT_TRUE( equal( s, "cccccccccccccccccccc" )) << "21char"; 
}

TEST(AddLHS, String){
   string20 s{ "" };
   const string20 c { "abc" };
   s = "defgh" + c;
  
   ASSERT_EQ( s.length() , 8) << "6char";
   ASSERT_EQ( s, "defghabc") << "content";

   s = "012345678901234567890" + s;
   ASSERT_TRUE( equal( s, "01234567890123456789" )) << "21char"; 
}

TEST(Multiply, self){
   string20 s{ "123" };
   s = s * 3;

   ASSERT_EQ( s.length() , 9) << "6char";
   ASSERT_EQ( s, "123123123") << "content";
   ASSERT_EQ( s * 2, "123123123123123123") << "retval";

   s = s * 200;
   ASSERT_TRUE( equal( s, "12312312312312312312" )) << "21char";
   ASSERT_TRUE( equal( s * 2, "12312312312312312312" )) << "retval21char";
}

TEST(Multiply, other){
   string20 s{ "123" };
   s = 3 * s;

   ASSERT_EQ( s.length() , 9) << "6char";
   ASSERT_EQ( s, "123123123") << "content";

   s = 200 * s;
   ASSERT_TRUE( equal( s, "12312312312312312312" )) << "21char";
}

TEST(Array, default){
   string20 s {"00"};

   ASSERT_EQ( s[3], '\0');  
   ASSERT_EQ( s.length() , 2) << "2char";
   ASSERT_EQ( s , "00") << "content";

   s[1] = '1';

   ASSERT_EQ( s , "01") << "content";
}

TEST( Array, const){
   const string20 s {"test"};
   std::string testvalue = "test";

   for(int i = 0; i < s.length(); i++) {
      ASSERT_EQ( s[i], testvalue[i] ) << "array check"; 
   }

   std::cout << s[0] << "\n";
   std::cout << s[1] << "\n";
   std::cout << s[2] << "\n";
   std::cout << s[3] << "\n";
   std::cout << s[4] << "\n";
   std::cout << s[5] << "\n";
  
   ASSERT_EQ(  s[10], '\0' ) << "const [4]"; 
}

/* ============================ TEST */

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

