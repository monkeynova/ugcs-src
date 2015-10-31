#include <stdio.h>
#include <iostream.h>

class Bigint {
public:
  char digits[ 1000 ];

  Bigint();
  Bigint( int i );
  Bigint( char *s );

  Bigint &operator +=( const Bigint &other );
  Bigint &operator -=( const Bigint &other );
  Bigint &operator *=( const Bigint &other );
  //  Bigint &operator /( const Bigint &other );
  //  Bigint &operator %=( const Bigint &other );
};

Bigint::Bigint() {
  for( int i = 0; i < 1000; i++ )
    digits[ i ] = 0;
}

Bigint::Bigint( int n ) {
  int pos = 999;

  for( int i = 0; i < 1000; i++ )
    digits[ i ] = 0;

  while( n > 0 ) {
    digits[ pos ] = n % 10 + '0';
    pos--;
    n /= 10;
  }
}

Bigint::Bigint( char *s ) {
  int pos = 999;
  char *p;

  for( int i = 0; i < 1000; i++ )
    digits[ i ] = 0;

  p = s + strlen( s ) - 1;
  while( p >= s ) {
    digits[ pos ] = *p;;
    pos--;
    p--;
  }
}

Bigint &Bigint::operator +=( const Bigint &other ) {
  int carry = 0;
  int pos = 999;

  for( pos = 999; 
       other.digits[ pos ] != 0 && digits[ pos ] != 0 && carry != 0; 
       pos-- ) {
    digits[pos] += other.digits[ pos ] + carry;
    if ( digits[ pos ] > '9' ) {
      digits[ pos ] -= 10;
      carry = 1;
    }
  }

  return *this;
}

Bigint &Bigint::operator -=( const Bigint &other ) {
  int pos = 999;
  int pos2;

  for( pos = 999; 
       other.digits[ pos ] != 0 && digits[ pos ] != 0; 
       pos-- ) {
       
    if ( digits[ pos ] < other.digits[ pos ] ) {
      for( pos2 = pos - 1; digits[ pos2 ] != '0'; pos2-- )
        digits[ pos2 ] = '9';

      digits[ pos2 ]--;

    }
    
    digits[pos] -= other.digits[ pos ];
  }

  return *this;
}

Bigint &Bigint::operator *=( const Bigint &other ) {
  Bigint tmp;
  int carry;

  for( int pos = 999; other.digits[pos] != 0; pos-- ) {
    carry = 0;
    for( int pos2 = 999; digits[pos] != 0 && carry != 0; pos2-- ) {
      tmp.digits[ pos2 - (999 - pos) ] += digits[ pos2 ] * other.digits[ pos ] + carry;
      carry = tmp.digits[ pos2 - (999 - pos) ] / 10;
      tmp.digits[ pos2 - (999 - pos) ] %= 10;
    }
  }

  *this = tmp;

  return *this;
}

ostream &operator <<( ostream &o, Bigint &b ) {
  int pos;

  for( pos = 999; b.digits[ pos ] != 0; pos -- ) 
    ;

  o << b.digits + pos + 1;

  return o;
}

void main( void ) {
  Bigint b1( 34 ), b2( 56 );

  cout << b1 << endl;
  cout << b2 << endl;
  b1 *= b2;
  cout << b1 << endl;
  /*
  char g[80], x[80], p[80], running[80];

  fgets( g, 80, stdin );
  fgets( x, 80, stdin );
  fgets( p, 80, stdin );

  for( ; x > 0; x-- ) {
    
    running *= g;
    running %= p;
  }

  printf( "%d\n", running );
  */
}
