/* Includes */
#include <stdio.h>
#include <string.h>

/* Defines */
#define MAX_LINE    256 /* Maximum length of a line */

/* Prototypes */
void usage( char * );

/* Main */
void main( int argc, char **argv ) {
  char line[MAX_LINE]; /* Read line */
  char *find, *tmp;    /* Pointers for moving in the string */
  int length;          /* Length of the replace string */

  /* Check for correct number of arguements */
  if ( argc != 3 ) usage( argv[0]); 

  length = strlen( argv[1] ); /* Get the length of replace string */

  while( !feof( stdin ) ) {
    if ( gets( line ) != NULL ) {

      /* Loop through string and find all occurences of replace string*/
      for (tmp = line; (find = strstr( tmp, argv[1] ))!=NULL; tmp += length) {
	/* Print up to found string */
        for ( ; tmp != find; tmp++ ) putchar( *tmp );

	/* Print replacement */
        printf( "%s", argv[2] );
      } 
      /* Put the rest of the line */
      puts( tmp );
    }
  }
}


/* Usage to help out inexperienced users of the program
 * Says what the arguements are                          */
void usage( char *pn ) {
  printf("USAGE\n");
  printf("%s <string to replace> <string to replace it with>\n\n", pn);
  exit( 1 );
}






