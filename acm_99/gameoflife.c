#include <stdio.h>

void main( void ) {
  char board[85][85];
  char newboard[85][85];
  int i, j;
  int neighbors;

  for( i = 1; ! feof( stdin ) && i < 81; i++ ) {
    fgets( board[i] + 1, 81, stdin );
  }

  for( i = 0; i < 82; i++ )
    for( j = 0; j < 82; j++ ) {
      if ( board[i][j] != 'X' && board[i][j] != '.' )
	board[i][j] = 0;
      
      if ( i < 80 && j < 80 )
	newboard[i][j] = 0;
    }

  for( i = 1; i < 82; i++ ) {
    if ( board[ i ][ 1 ] == 0 )
      break;

    for( j = 1; j < 82; j++ ) {
      if ( board[ i ][ j ] == 0 )
	break;
      
      neighbors = (board[ i - 1 ][ j - 1 ] == 'X') + 
	(board[ i ][ j - 1 ] == 'X') +
	(board[ i + 1 ][ j - 1 ] == 'X') + (board[ i - 1 ][ j ] == 'X') + 
	(board[ i + 1 ][ j ] == 'X') + (board[ i - 1 ][ j + 1 ] == 'X') +
	(board[ i ][ j + 1 ] == 'X') + (board[ i + 1 ][ j + 1 ] == 'X');

      if ( board[ i ][ j ] == '.' ) {
	if ( neighbors == 3 )
	  newboard[ i - 1 ][ j - 1 ] = 'X';
	else
	  newboard[ i - 1 ][ j - 1 ] = '.';

      } else {
	if ( neighbors == 2 || neighbors == 3 )
	  newboard[ i - 1 ][ j - 1 ] = 'X';
	else
	  newboard[ i - 1 ][ j - 1 ] = '.';
      }

    }
  }

  for( i = 0; i < 80; i++ ) {
    if ( newboard[ i ][ 0 ] == 0 )
	  break;

    printf( "%s\n", newboard[ i ] );
  }
}
