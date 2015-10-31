#include <stdio.h>

void main( void ) {
  char s[80];
  int n;
  int total;

  while( ! feof( stdin ) ) {
    total = 0;

    if ( fgets( s, 80, stdin ) == NULL )
      break;
    sscanf( s, "%d", &n );
    
    if ( n < 2 ) {
      printf( "1\n" );
      continue;
    }

    for( ; n > 1; n-- ) {
      total += getPrimeFactors( n );
    }

    printf( "%d\n", total );
  }
}

int getPrimeFactors( int x ) {
  int i;

  if ( x <= 3 )
    return 1;

  for( i = 2; i * i <= x; i++ ) {
    if ( x % i == 0 )
      return( 1 + getPrimeFactors( x / i ) ); 
  }
  
  return 1;
}

