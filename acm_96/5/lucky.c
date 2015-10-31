#include <stdio.h>

int primes[1000];
int prime_num;

void init_primes(void);

void main(void) {
  int t;
  double prod=1;
  init_primes();
  for (t=0;t<prime_num;t++) {
    prod*=primes[t];
    printf("%d %g\n",primes[t],prod);
  }
}

void init_primes(void) {
  int s,t,n;
  int prime;
  n=0;
  for (t=2;t<=2100;t++) {
    prime=1;
    for (s=2;s*s<=t;s++) {
     if ((float)t/s==(float)((int)t/s)) {
        prime=0;
      }
    }
    if (prime) {
      primes[n]=t;
      n++;
    }
  }
  prime_num=n;
}

