#include <stdio.h>

struct listing {
  char name[53];
  char number[7];
  char sortname[ 200 ];
};

char *ones[] = { "", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten" };
char *tens[] = { "", "ten", "twenty", "thirty", "fourty", "fifty", "sixty", "seventy", "eighty", "ninty" };
char *teens[] = { "", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen" };

void createSubhundred( char **dst, int n ) {
  printf( "%d\n", n );

  if ( n > 100 ) {
    strcpy( *dst, ones[ n / 100 ] );
    *dst += strlen( ones[ n / 100 ] );
    strcpy( *dst, " hundred " );
    *dst += strlen( " hundred " );
    n /= 100;
  }

  if ( n > 20 ) {
    strcpy( *dst, tens[ n / 10 ] );
    *dst += strlen( tens[ n / 10 ] );
    **dst = ' ';
    (*dst)++;
    strcpy( *dst, ones[ n % 10 ] );
    *dst += strlen( ones[ n % 10 ] );
    **dst = ' ';
    (*dst)++;
  } else if ( n < 10 ) {
    strcpy( *dst, teens[ n - 10 ] );
    *dst += strlen( teens[ n - 10 ] );
    **dst = ' ';
    (*dst)++;        
  } else {
    strcpy( *dst, ones[ n ] );
    *dst += strlen( ones[ n ] );
    **dst = ' ';
    (*dst)++;    
  }
}

void createName( char **dst, int n ) {
  printf( "%d\n", n );

  if ( n > 1000000 ) {
    createSubhundred( dst, n / 1000000 );
    n /= 1000000;
    strcpy( *dst, "million " );
    *dst += strlen( "million " );
  } 

  if ( n > 1000 ) {
    createSubhundred( dst, n / 1000 );
    n /= 1000;
    strcpy( *dst, "thousand " );
    *dst += strlen( "thousand " );
  } 

  createSubhundred( dst, n );
}


void createSortname( char *sname, char *name ) {
  char *p, *dst;
  int wbreak;
  int num;
  int capword[80], cappos = 0;
  int j;

  dst = sname;
  num = 0;
  for( p = name; *p != 0; p++ ) {
    if ( wbreak && *p <= 'Z' && *p >= 'A' ) {
      capword[ cappos++ ] = *p;

    } else if ( *p <= '9' && *p >= '0' ) {
      num = num * 10 + *p - '0';
    } else if ( (*p <= 'z' && *p >= 'a') || (*p <= 'Z' && *p >= 'A') ) {
      wbreak = 0;
      if ( cappos != 0 ) {
        for( j = 0; j < cappos; j++ ) {
	  *dst = capword[ j ];
	  dst++;
	}
        cappos = 0;
      }
      *dst = *p;
      dst++;
    } else {
      if ( cappos != 0 ) {
        for( j = 0; j < cappos; j++ ) {
	  *dst = capword[ j ];
	  dst++;
	  *dst = ' ';
	  dst++;
	}
        cappos = 0;
      }
      *dst = ' ';
      dst++;
      wbreak = 1;
      cappos = 0;

      if ( num != 0 ) {
	createName( &sname, num );
	num = 0;
      }
    }     
  }

  if ( cappos != 0 ) {
    for( j = 0; j < cappos; j++ ) {
      *dst = capword[ j ];
      dst++;
      *dst = ' ';
      dst++;
    }
    cappos = 0;
  }

  if ( num != 0 ) {
    createName( &sname, num );
  }
}

void main( void ) {
  struct listing everyone[ 1000 ];
  char c;
  int i, j;

  for( i = 0; ! feof( stdin ); i++ ) {
    for( j = 0; j < 7; j++ )
      everyone[ i ].number[ j ] = getchar();

    for( j = 0; j < 52 && (c = getchar()) != '\n'; j++ )
      everyone[ i ].name[ j ] = c;

    while( c != '\n' )
      c = getchar();

    createSortname( everyone[ i ].sortname, everyone[ i ].name );
    printf( "%s\n", everyone[ i ].sortname );
  }
}
