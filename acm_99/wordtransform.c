#include <stdio.h>
#include <string.h>

char dictionary[1000][16];
int maxwords;
char wd[1000][16];
int wmw;

int oneStep( char *word1, char *word2 ) {
  int diffs = 0;
  int i;

  if ( strlen( word1 ) != strlen( word2 ) )
    return 0;

  for( i = 0; i < strlen( word1 ); i++ )
    if ( word1[i] != word2[i] )
      diffs++;

  return (diffs == 1);
}

int minTransform( char *word1, char *word2 ) {
  int i;
  char checks[1000][16];
  int c, holder;
  int tmp, min = 2000;
  
  if ( strlen( word1 ) != strlen( word2 ) )
    return min;

  if ( strcmp( word1, word2 ) == 0 )
    return 0;

  if ( oneStep( word1, word2 ) )
    return 1;

  for( i = 0; i < wmw; i++ ) {
    if ( oneStep( word1, wd[ i ] ) ) {
      strcpy( checks[ c++ ], wd[ i ] );
      strcpy( wd[ i ], wd[ wmw - 1 ] );
      wmw--;
      i--;
    } else if ( strcmp( word1, wd[ i ] ) == 0 ) {
      strcpy( wd[ i ], wd[ wmw - 1 ] );
      wmw--;
      i--;
    }
  }

  for( i = 0; i < c; i++ ) {
    tmp = minTransform( checks[ i ], word2 );
    if( tmp < min ) { 
      min = tmp;
      holder = i;
    }
  }

  for( i = 0; i < c; i++ ) {
    strcpy( wd[ wmw++ ], checks[ i ] );
  }

  return min + 1;
}

void main( void ) {
  char line[40], *wordbreak;
  int i, n;

  fgets( line, 16, stdin );
  for( i = 0; line[0] != '*'; i++ ) {
    line[ strlen( line ) - 1 ] = 0;

    wordbreak = strstr( line, " " );
    if ( wordbreak != NULL )
      *wordbreak = 0;

    strcpy( dictionary[i], line );
    fgets( line, 16, stdin );
  }
  maxwords = i;

  while( ! feof( stdin ) ) {
    fgets( line, 35, stdin );

    wordbreak = strstr( line, "\n" );
    if ( wordbreak == NULL )
      break;
    *wordbreak = 0;
    
    wordbreak = strstr( line, " " );
    if ( wordbreak == NULL )
      break;
    *wordbreak = 0;
    
    memcpy( wd, dictionary, sizeof( char ) * 1000 * 16 );
    wmw = maxwords;
    n = minTransform( line, wordbreak + 1 );

    *wordbreak = ' ';
    if ( n == 2001 ) 
      printf( "Impossible tranformation\n" );
    else
      printf( "%s %d\n", line, n );
  }
}

