#include <stdio.h>

struct item {
  int u;
  float p;
  char name[ 80 ];
  char lineOrig[ 80 ];
};

int findBestBudget( float budget, struct item out[], int *numitems, 
		    struct item list[], int maxItems ) {
  struct item tmplist[ 200 ];
  struct item tmp;
  int util, holder = -1;
  int i, numStore, j;
  int maxUtil = 0;

  if ( maxItems == 1 ) {
    if ( list[ 0 ].p <= budget ) {
      *numitems = 1;
      out[ 0 ] = list[ 0 ];
      return list[ 0 ].u;
    } else {
      *numitems = 0;
      return 0;
    }
  }

  memcpy( tmplist, list, 200 * sizeof( struct item ) );
  for( i = 0; i < maxItems; i++ ) {
    if ( list[i].p > budget )
      continue;

    tmp = tmplist[ i ];
    tmplist[ i ] = tmplist[maxItems - 1 ];
    tmplist[ maxItems - 1 ] = tmp;
    
    util = findBestBudget( budget - list[ i ].p, out, &numStore, tmplist, maxItems - 1 );

    if ( list[i].u + util > maxUtil ) {
      maxUtil = list[i].u + util;
      holder = i;
    }

    tmp = tmplist[ i ];
    tmplist[ i ] = tmplist[maxItems - 1 ];
    tmplist[ maxItems - 1 ] = tmp;
  }

  if ( holder == -1 ) {
    *numitems = 0;
    return -1;
  }

  tmp = tmplist[ holder ];
  tmplist[ holder ] = tmplist[maxItems - 1 ];
  tmplist[ maxItems - 1 ] = tmp;
  util = findBestBudget( budget - list[ holder ].p, out, &numStore, tmplist, maxItems - 1 );
  out[ numStore ] = tmp;
  numStore++;
  *numitems = numStore;

  return util + list[ holder ].u;
}

void main( void ) {
  float budget;
  char line[ 80 ];
  struct item list[200];
  struct item goodItems[ 200 ];
  int i, maxItems, numGood;
  float expense;

  fgets( line, 80, stdin );
  sscanf( line, "%f", &budget );

  for( i = 0; ! feof( stdin ); i++ ) {
    if ( fgets( line, 80, stdin ) == NULL )
      break;
    
    strcpy( list[i].lineOrig, line );
    sscanf( line, "%d %f %[^\n]", &list[i].u, &list[i].p, list[i].name );
    if ( list[i].u == 0 )
      i--;
  }
  maxItems = i;

  findBestBudget( budget, goodItems, &numGood, list, maxItems );
  
  expense = 0;
  for( i = 0; i < numGood; i++ ) {
    printf( goodItems[ i ].lineOrig );
    expense += goodItems[ i ].p;
  }
  printf( "Projected Expense: %.2f\n", expense );
  printf( "Budget Remaining: %.2f\n", budget - expense );
}
