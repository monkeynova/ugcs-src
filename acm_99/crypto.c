#include <stdio.h>

void main( void ) {
  char g[80], x[80], p[80], running[80];

  fgets( g, 80, stdin );
  fgets( x, 80, stdin );
  fgets( p, 80, stdin );

  for( ; x > 0; x-- ) {
    running *= g;
    running %= p;
  }

  printf( "%d\n", running );
}
