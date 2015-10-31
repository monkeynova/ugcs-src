#include <stdio.h>

void usage(void);
void FileErr(void);
void soundex(char *,char *);

void main(int argc, char *argv[]) {
  char c1[4]; 
  FILE *dir;
  char directory[100][71];
  char name[30];
  char req_name[30];
  char c2[4];
  int t,s,total_dir,found,done;
 
  /* if (argc != 2)  usage();
  if ((dir=fopen(argv[1],"r")) == NULL) FileErr();
  */
 
  done=0;
  for (t=0,s=0;!done;) {
    directory[t][s]=getchar();
    if (directory[t][s]=='\n') {
      if (s==0) done=1;
      directory[t][s]=0;
      t++; s=0;
    } else s++;
  }
  total_dir=t-2;

  done=0;
  while ((req_name[0]=getchar())!=EOF) {
    for (t=1;(req_name[t]=getchar()) != '\n';t++);
    req_name[t]=0;
    /* fscanf(dir,"%s\n",req_name);*/
    found=0;
    soundex(req_name,c1);
    printf("%s\t\t\t%s\n",req_name,c1);
    for (t=0;t<=total_dir;t++) {
      for (s=0;(name[s]=directory[t][s])!=' ';s++);
      name[s]=0;
      soundex(name,c2);
      /* printf("%s %s\n",directory[t],c2);*/
      if (!strcmp(c1,c2)) {
        printf("%s\n",directory[t]);
        found=1;
      }
    }
    if (!found) printf("NO ENTRIES FOUND\n");
    printf("\n");
  }
  /* fclose(dir);*/
}

void soundex(char *name_in,char *code) {
  int t,s,u;
  char name[70];
  int remove_num=7;
  char remove[]={'A','E','I','O','U','Y','H','W'};
  char others[]={'B','F','P','V','C','G','J','K','Q','S','X','Z','D','T','L','M','N','R'};
  char others_c[]={'1','1','1','1','2','2','2','2','2','2','2','2','3','3','4','5','5','6'};
  int others_num=18;

  strcpy(name,name_in);
  code[0]=name[0];
  for (t=1;name[t] != 0;t++) {
    for (s=0;s<remove_num;s++) {
      if (name[t]==remove[s]) {
        for (u=t;name[u]!=0;u++) name[u]=name[u+1];
      }
    }
    for (s=0;s<others_num;s++) {
      if (name[t]==others[s]) name[t]=others_c[s];
    }
  }

  for (t=1;name[t] != 0;t++) {
    if (name[t]==name[t+1]) {
      for (u=t+1;name[u]!=0;u++) name[u]=name[u+1];
      t--;
    }
  }
  for (t=1;t<=3;t++) {
    if (name[t] > '9' || name[t]<'0') name[t]='0';
    code[t]=name[t];
  }
}

void usage(void) {
  printf("USAGE:\nsoundex <file>\n");
  exit();
}

void FileErr(void) {
  printf("The file does not exist.\n");
  exit();
}
