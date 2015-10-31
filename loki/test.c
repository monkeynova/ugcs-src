#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>

void main( int argc, char *argv[] ) {
  clock_t start, end;
  int i, numtests= 100000;
  long pos;
  struct stat info;
  long size;
  FILE *fp;

  start = clock();
  for( i = 0; i < numtests; i++ ) {
    stat( argv[1], &info );
    size = info.st_size;
  }
  end = clock();

  printf( "Stat: %0.2f seconds\n", (end - start) / ((float)(CLOCKS_PER_SEC)) );

  fp = fopen( argv[1], "r" );
  start = clock();
  for( i = 0; i < numtests; i++ ) {
    pos = ftell(fp);
    
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, pos, SEEK_SET);
  }
  end = clock();
  fclose( fp );

  printf( "Fseek: %0.2f seconds\n", (end - start) / ((float)(CLOCKS_PER_SEC)) );
}
