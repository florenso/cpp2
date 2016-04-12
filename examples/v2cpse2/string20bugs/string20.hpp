#ifndef H_STRING20_
#define H_STRING20_

extern int string20bug;

class string20 {
public:

   const char * begin() const;
   const char * end() const;
   
   // begin of the interface that you have to test

   string20();
   string20( const string20 & rhs );
   explicit string20( char rhs );
   explicit string20( const char * rhs );
   
   int length() const;
   
   string20 & operator= ( const string20 & rhs );
   string20 & operator= ( char rhs );
   string20 & operator= ( const char * rhs );

   string20 & operator+= ( const string20 & rhs );
   string20 & operator+= ( char rhs );
   string20 & operator+= ( const char * rhs );

   string20 operator+ ( const string20 & rhs ) const;
   string20 operator+ ( char rhs ) const;
   string20 operator+ ( const char * rhs ) const;
   
   friend string20 operator+ ( char lhs, const string20 & rhs );
   friend string20 operator+ ( const char * lhs, const string20 & rhs );
   
   string20 operator* ( int n ) const;
   friend string20 operator* ( int n, const string20 & rhs );
   
   char & operator[]( int n );
   char operator[]( int n ) const;
   
   // end of the interface that you have to test

   bool operator==( char rhs ) const;
   bool operator==( const char * rhs ) const;
   bool operator==( const string20 & rhs ) const;
   
   bool operator!=( const string20 & rhs ) const;
   bool operator>( const string20 & rhs ) const;
   bool operator>=( const string20 & rhs ) const;
   bool operator<( const string20 & rhs ) const;
   bool operator<=( const string20 & rhs ) const;
   
private:
   char chars[ 20 ];
   int valid;   
   
   void append( char c ){
      if( valid < 20 ){
         chars[ valid++ ] = c;
      }   
   }
   
};

#endif