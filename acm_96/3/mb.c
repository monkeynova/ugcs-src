#include <stdio.h>

void main (void) {
  int t,s,i,j,b[5];
  int balls;
  int data[32];
  int gen[32];
  int board[8][8];  

  fscanf(stdin,"%d\n",&balls);
  for (s=0;s<4;s++) {
    for (t=0;t<8;t++) {
      fscanf(stdin,"%d ",&data[t*s]);
    } fscanf(stdin,"\n");
  }

  
  
}

