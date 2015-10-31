#include <stdio.h>
#include <math.h>

void Optimize(int,int,int *,int *);

void main(void) {
  int cass_time[100], CD_tracks[100];
  int minutes[100][17],seconds[100][17];
  int t,s,n;

  s=0;
  while (!feof(stdin)) {
    fscanf(stdin,"%d %d\n",&cass_time[s],&CD_tracks[s]);
    for (t=0;t<CD_tracks[s];t++) {
      fscanf(stdin,"%d:%d\n",&minutes[s][t],&seconds[s][t]);
    }
    s++;
  }
  for (n=0;n<s;n++) {
    Optimize(cass_time[n],CD_tracks[n],minutes[n],seconds[n]);
  }
}

void Optimize(int ct, int tracks,int *m,int *s) {
  long int t;
  int u;
  int bests=0,bestm=0,best_t[tracks];
  int mint,sect;
  int summ,sums;

  mint=ct/2;
  sect=(ct%2)*30;
  for (t=0;t<pow(2,tracks);t++) {
    summ=0;sums=0;
    for (u=0;u<tracks;u++){
      if (((int)pow(2,u))&t) {
	/* printf("%x\n",t);*/
        summ+=m[u];
        sums+=s[u];
        if (sums>59) {
         summ++;
         sums%=60;
        }
      }
    }
    if ((summ>bestm && summ<=mint) || (summ==mint && sums>bests && sums<=sect)) {
      for (u=0;u<tracks;u++) {
        best_t[u]=((int)pow(2,u))&t;
      }
      bestm=summ;
      bests=sums;
      /*printf("%d:%d\n",bestm,bests);*/
    }
  }
  
  printf("%d tracks on a C-%d cassette\n",tracks,ct);
  printf("Side 1: ");
  for (t=0;t<tracks;t++) if (best_t[t]) {
    printf("%d ",t+1);
    /*  bestm+=m[t];
    bests+=s[t];
    if (bests>59) {
     bestm++;
     bests%=60;
    }*/
  }
  printf("\nSide 1: Elapsed Time %02d:%02d\n",bestm,bests);
  printf("Side 2: ");
  sums=0;summ=0;
  for (t=0;t<tracks;t++) if (!best_t[t]) {
    printf("%d ",t+1);
    summ+=m[t];
    sums+=s[t];
    if (sums>59) {
     summ++;
     sums%=60;
    }
  }
  printf("\nSide 2: Elapsed Time %02d:%02d\n",summ,sums);

}



