#include <stdio.h>
#include <ctype.h>
#include <string.h>

/*

filter.c

Description:
Reads from stander input and write to standard output replacing words
as dictated by the table filterList.

problems:
Well if the case of the output word is independant of the case of the input.

*/

char *get_word( FILE * );
char *filter( char * );

char *filterList[] = 
{
  "yes", "no",
  "black", "white",
  "SCUD", "Patriot",
  "war", "peace",
  "Caltech", "MIT",
  ""
};

void main( void ) {
  char *s;
  
  /* Grab a word then filter it */
  while ( (s = get_word( stdin )) != NULL ) {
    /*    printf( "%s", s );*/
    printf( "%s", filter( s ) );
  }
}

static char word[1024]; /* This is the return word - I've never heard of a word this long */

char *get_word( FILE * f ) {
  int i = 0;
  int c;

  while ( (c = fgetc( f )) != EOF ) {
    if ( tolower( c  ) >= 'a' && tolower( c ) <= 'z' ) { /* Letters so part of word */
      word[ i++ ] = c;
    } else if ( i == 0 ) { /* Symbol by itself */
      word[ i++ ] = c;
      break;
    } else {               /* End of word */
      ungetc( c, f );
      break;
    }
  }

  if ( i == 0 ) return NULL; /* EOF */
  
  /* Null Terminate the string */
  word[ i ] = '\0';

  return word;
}

char *filter( char *str ) {
  int i = 0;

  while( strcmp( filterList[ i ], "" ) != 0 ) {       /* Loop over the list */
    if ( strcasecmp( filterList[ i ], str ) == 0 )    /* is it a first word? */
      return filterList[ i + 1 ];

    if ( strcasecmp( filterList[ i + 1], str ) == 0 ) /* is it a second word? */
      return filterList[ i ];

    i += 2;
  }

  /* If we didn't find it, return the original */
  return str;
}
