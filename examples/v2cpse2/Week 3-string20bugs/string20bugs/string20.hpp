#ifndef H_STRING20_
#define H_STRING20_

extern int string20bug;

class string20 {
public:

   const char * begin() const;
   const char * end() const;
   
   // begin of the interface that you have to test

   string20(); //written
   string20( const string20 & rhs ); //written
   explicit string20( char rhs ); //written
   explicit string20( const char * rhs ); //written
   
   int length() const; //written
   
   string20 & operator= ( const string20 & rhs ); //written
   string20 & operator= ( char rhs ); //written
   string20 & operator= ( const char * rhs ); //written

   string20 & operator+= ( const string20 & rhs ); //written
   string20 & operator+= ( char rhs ); //written
   string20 & operator+= ( const char * rhs ); //written

   string20 operator+ ( const string20 & rhs ) const; //written
   string20 operator+ ( char rhs ) const; //written
   string20 operator+ ( const char * rhs ) const; //written
   
   friend string20 operator+ ( char lhs, const string20 & rhs ); //written
   friend string20 operator+ ( const char * lhs, const string20 & rhs );  //written
   
   string20 operator* ( int n ) const; //written
   friend string20 operator* ( int n, const string20 & rhs ); //written
   
   char & operator[]( int n ); //written
   char operator[]( int n ) const; //written
   
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