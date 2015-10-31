/*Keith Peters*/

#include <stdio.h>

#define MASK 128

char key_note[8];
char key_fs[8];
char *notes[]={"C","C#","D","D#","E","F","F#","G","G#","A","A#","B"};
char *notes2[]={"C","Db","D","Eb","E","F","Gb","G","Ab","A","Bb","B"};
char sf[]={'=','#','b'};
 
void getnote(int,char *);
void get_key(char *);
void print_key(void);
void usage(void);

void main(int argc, char *argv[]) {
  char midi[50*1024];
  int after,t;
  int num,notenum=1,last_num;
  int first=1;
  char key[256];
  char note[4];
  int pos=0;

  t=0;
  while ((key[t++]=getchar())!='\n');
  key[t]=0;
  get_key(key);
  
  t=0;
  while ((midi[t++]=getchar())!=EOF);
  midi[t]=0;
  /* printf ("%s\n",midi);*/
  last_num=0;
  while (midi[pos]!=0) {
    for(num=0;midi[pos]<='9' && midi[pos]>='0';pos++) num = num*10+(midi[pos]-'0');
    pos++;
    if (num>127) {
      if (!first) {
        if (note[0]!= 0 && last_num >= 144) printf("%s ",note);
        notenum++;
        if (notenum==21) {
          printf("\n");
          notenum=1;
        }
      }
      note[0]=0;
      after=0;
      first=0;
      last_num=num;
    } else {
      if (after==1) {
        getnote(num,note);
      } else if (after==2 && num ==0) {
        note[0]=0;
        notenum--;
      }
    }
    /* printf("%s\n",note);*/
    after++;
  }
  if (num >= 144) printf("%s",note);
  printf("\n");
}

void getnote(int num,char *note) {
  int t;
  char temp_note1[4];
  char temp_note2[4];
  strcpy(temp_note2,notes2[num%12]);
  strcpy(temp_note1,notes[num%12]);

  for (t=0;key_fs[t] != 0;t++) {
    if (key_note[t]==temp_note1[0]) {
      if (temp_note1[1]==0) {
        temp_note1[1]='=';
        temp_note1[2]=0;
      } else {
        if (temp_note1[1]==sf[(int)key_fs[t]]) {
          temp_note1[1]=0;
        } else {
          temp_note1[1]=sf[3-(int)key_fs[t]];
          temp_note1[2]=0;
        }
      }
    }
  }

  for (t=0;key_fs[t] != 0;t++) {
    if (key_note[t]==temp_note2[0]) {
      if (temp_note2[1]==0) {
        temp_note2[1]='=';
        temp_note2[2]=0;
      } else {
        if (temp_note2[1]==sf[(int)key_fs[t]]) {
          temp_note2[1]=0;
        } else {
          temp_note2[1]=sf[3-(int)key_fs[t]];
          temp_note2[2]=0;
        }
      }
    }
  }

  /* printf("%s %s\n",temp_note1,temp_note2);*/
  if (strlen(temp_note2) < strlen(temp_note1)) strcpy(note,temp_note2);
  else strcpy(note,temp_note1);

}

void print_key(void) {
  int t;
  for (t=0;key_fs[t] != 0;t++) {
    printf("%c%c ",key_note[t],sf[(int)key_fs[t]]);
  } printf ("\n");
}

void get_key(char *k) {
  int len;
  int t,n=0;
  len=strlen(k);
  if (k[0]=='=') return;
  for (t=0;t<len;t++) {
    /*while (k[t]==' ') t++;*/
    if (k[t]=='#') {
      while (k[t+1] != ' ') {
        key_fs[n]=1;
        key_note[n]=k[++t];
        n++;
      } t++;
    } else if(k[t]=='b') {
      while (k[t+1] != ' ') {
        key_fs[n]=2;
        key_note[n]=k[++t];
        n++;
      } t++;
    } /*else {
      printf("Error on Key Signature.(%c)\n",k[t]);
      exit();
    }*/
  }
}

void usage (void) {
  printf("USAGE:\nmidi <midi_file>\n");
  exit();
}
