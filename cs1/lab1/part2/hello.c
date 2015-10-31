#include<stdio.h>

void main() {
  int i,t;
  printf("Enter a number: ");
  scanf("%d",&i);
  if (i<0) {
    printf("Invalid Number.\n");
  } else {
    for (t=1;t<=i;t++) {
      printf("Hello World #%d\n",t);
    }
  }
}
