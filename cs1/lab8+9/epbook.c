#include <stdio.h>
#include <local/cs1.h>
#include <malloc.h>
#include <strings.h>
#include <ctype.h>

typedef struct pn {
  struct pn *next;
  char name[30];
  int number;
  int in_search;
} ENTRY;

typedef struct button_typ {
  char name[30];
  int x1,x2,y1,y2;
  CS1_Window *w;
  int status;
} BUTTON;

typedef struct scroll_typ {
  int y;
  int *scroll_var;
  int x1,y1,x2,y2;
  CS1_Window *w;
  int length;
  int *ww;
  int *wh;
} SCROLL_BAR;

ENTRY *new_entry(char *,int);
ENTRY *add_entry(void);
ENTRY *delete_entry(ENTRY *,int,ENTRY **);
void Search(ENTRY *start);
int matches(char *,char *);
int Start_String(char *, char *);
int Get_Length(ENTRY *);
void Draw_Entries(CS1_Window,ENTRY *,int,int);
void Sort_Entries(ENTRY *first);
int In_List(int,int,int,int);
SCROLL_BAR *Init_Scroll(CS1_Window *,int,int,int,int,int,int *,int *,int *);
void Draw_Scroll(SCROLL_BAR *,ENTRY *);
int On_Scroll(SCROLL_BAR *,int,int);
void Set_Scroll_Length(SCROLL_BAR *,ENTRY *);
void Set_Scroll_Position(SCROLL_BAR *s, int y,ENTRY *);
BUTTON *Init_Button(CS1_Window *,int,int,int,int,char *);
void Draw_Button(BUTTON *);
int On_Button(BUTTON *,int,int);
int cs1_scanf(char *prompt,char *fmt,...);


#define EDGE   10
#define HEIGHT 15
#define YES    1
#define NO     0
#define DOWN   1
#define UP     0

int yscroll=0;
int selected=-1;

void main(void) {
  ENTRY *start=NULL, *last;
  BUTTON *add,*search,*delete,*quit, *sort;
  SCROLL_BAR *sb;
  int done=0,sorted=0;
  CS1_Window mw;
  int x,y;
  int ww=300,wh=150;

  mw=cs1_make_window("gray80",100,100,ww+20,wh+27);
  cs1_window_title(mw,"Electronic Phonebook");

  /* cs1_set_color("black");
  for (t=0;t<filenum;t++) {
    cs1_printf(mw,10,10+(t+1)*HEIGHT-2,"%s",files[t]);
  }*/

  sb=Init_Scroll(&mw,ww+4,1,ww+19,wh+26,0,&yscroll,&ww,&wh);
  Set_Scroll_Length(sb,start);
  /*Draw_Scroll(sb);*/

  add=Init_Button(&mw,ww/2-122,wh+4,ww/2-87,wh+17,"Add");
  search=Init_Button(&mw,ww/2-77,wh+4,ww/2-32,wh+17,"Search");
  delete=Init_Button(&mw,ww/2-22,wh+4,ww/2+23,wh+17,"Delete");
  sort=Init_Button(&mw,ww/2+33,wh+4,ww/2+73,wh+17,"Sort");
  quit=Init_Button(&mw,ww/2+83,wh+4,ww/2+123,wh+17,"Quit");

  Draw_Button(add);
  Draw_Button(search);
  Draw_Button(delete);
  Draw_Button(quit);
  Draw_Button(sort);

  Draw_Entries(mw,NULL,ww,wh);

  while (!done) {
    if (cs1_mouse_button(mw,cs1_left_button)) {
      x=cs1_mouse_x(mw); y=cs1_mouse_y(mw);
      if (On_Button(quit,x,y)) done=1;
      if (On_Button(sort,x,y)) {
        sort->status=!sort->status;
        Draw_Button(sort);
        while (cs1_mouse_button(mw,cs1_left_button));
        if (!sorted) {
          Sort_Entries(start);
          Draw_Entries(mw,start,ww,wh);
        }
        sort->status=!sort->status;
        Draw_Button(sort);
        sorted=1;
      }

      if (On_Button(add,x,y)) {
        add->status=!add->status;
        Draw_Button(add);
        if (start==NULL) {
          start=add_entry();
          last=start;
        } else {
          last->next=add_entry();
          last=last->next;
        }
        Set_Scroll_Length(sb,start);
        add->status=!add->status;
        Draw_Button(add);
        Draw_Entries(mw,start,ww,wh);
        sorted=0;
      }
      if (On_Button(search,x,y)) {
        search->status=!search->status;
        Draw_Button(search);
        Search(start);
        Draw_Entries(mw,start,ww,wh);
        search->status=!search->status;
        Draw_Button(search);
      }
      if (On_Button(delete,x,y)) {
        delete->status=!delete->status;
        Draw_Button(delete);
        start=delete_entry(start,selected,&last);
        delete->status=!delete->status;
        while (cs1_mouse_button(mw,cs1_left_button));
        Set_Scroll_Length(sb,start);
        selected=-1;
        Draw_Button(delete);
        Draw_Entries(mw,start,ww,wh);
      }
      if (In_List(x,y,ww,wh)) {
        if (selected!=(y-(EDGE+5))/HEIGHT+yscroll) {
          selected=(y-(EDGE+5))/HEIGHT+yscroll;
          Draw_Entries(mw,start,ww,wh);
        }
      }
      if (On_Scroll(sb,x,y)) {
        Set_Scroll_Position(sb,y,start);
        Draw_Entries(mw,start,ww,wh);
      }
    }

    if (cs1_inkey()==27) done=1;
  }

}

int On_Button(BUTTON *b,int x,int y) {
  int c,d;
  if ((b->x1)<(b->x2)) c=(x<b->x2 && x>b->x1);
  else c=(x>b->x2 && x<b->x1);
  if ((b->y1)<(b->y2)) d=(y<b->y2 && y>b->y1);
  else d=(y>b->y2 && y<b->y1);
  return (c && d);
}

void Draw_Button(BUTTON *b) {

  b->status==UP?cs1_set_color("white"):cs1_set_color("black");
  cs1_draw_line(*(b->w),b->x1,b->y1,b->x1,b->y2);
  cs1_draw_line(*(b->w),b->x1,b->y1,b->x2,b->y1);
  b->status==UP?cs1_set_color("black"):cs1_set_color("white");
  cs1_draw_line(*(b->w),b->x2,b->y1,b->x2,b->y2);
  cs1_draw_line(*(b->w),b->x1,b->y2,b->x2,b->y2);
  cs1_set_color("black");
  cs1_printf(*(b->w),b->x1+5,b->y2-2,"%s",b->name);

}

BUTTON *Init_Button(CS1_Window *w,int x1,int y1,int x2,int y2,char *s) {
  BUTTON *b;

  if ((b=(BUTTON *)malloc(sizeof(BUTTON)))==NULL) exit();

  b->w=w;
  b->x1=x1;
  b->y1=y1;
  b->x2=x2;
  b->y2=y2;
  strcpy(b->name,s);
  b->status=UP;

  return (b);
}

SCROLL_BAR *Init_Scroll(CS1_Window *w,int x1,int y1,int x2,int y2, int y,int *yvar,int *ww,int *wh) {
  SCROLL_BAR *s;

  if ((s=(SCROLL_BAR *)malloc(sizeof(SCROLL_BAR)))==NULL) exit();
  s->w=w;
  s->x1=x1;
  s->x2=x2;
  s->y1=y1;
  s->y2=y2;
  s->y=y;
  s->scroll_var=yvar;
  s->wh=wh;
  s->ww=ww;
  

  return(s);
}

void Draw_Scroll(SCROLL_BAR *b,ENTRY *first) {
  int y,length;
  
  y=b->y;
  length=b->length;
  cs1_set_color("gray40");
  cs1_fill_box(*(b->w),b->x1,b->y1,b->x2,b->y2);

  cs1_set_color("black");
  cs1_draw_line(*(b->w),b->x1,b->y1,b->x1,b->y2);
  cs1_draw_line(*(b->w),b->x1,b->y1,b->x2,b->y1);
  cs1_set_color("white");
  cs1_draw_line(*(b->w),b->x2,b->y1,b->x2,b->y2);
  cs1_draw_line(*(b->w),b->x1,b->y2,b->x2,b->y2);

  cs1_set_color("gray80");
  cs1_fill_box(*(b->w),b->x1+2,b->y1+y+1,b->x2-2,b->y1+length+y);

  cs1_set_color("white");
  cs1_draw_line(*(b->w),b->x1+2,b->y1+y+1,b->x1+2,b->y1+length+y);
  cs1_draw_line(*(b->w),b->x1+2,b->y1+y+1,b->x2-2,b->y1+y+1);
  cs1_set_color("black");
  cs1_draw_line(*(b->w),b->x2-2,b->y1+y+1,b->x2-2,b->y1+length+y);
  cs1_draw_line(*(b->w),b->x1+2,b->y1+length+y,b->x2-2,b->y1+length+y);
  Draw_Entries(*(b->w),first,*(b->ww),*(b->wh));  

}

void Set_Scroll_Length(SCROLL_BAR *s, ENTRY *first) {
  int list_length;
  
  list_length=Get_Length(first);
  if (list_length<8) s->length=(s->y2-s->y1-2);
  else {
    s->length=((s->y2-s->y1-2)*8)/list_length;
    if ((s->length) > (s->y2-s->y1-2)) s->length=(s->y2-s->y1-2);
  }

  /* s->length; */

  Draw_Scroll(s,first);
}

void Set_Scroll_Position(SCROLL_BAR *s, int y, ENTRY *first) {
  int y_tmp;

  if (y<=(s->y1+(s->length)+(s->y)) && y >= (s->y1+(s->y))) {
    while (cs1_mouse_button(*(s->w),cs1_left_button)) {
      if ((y_tmp=cs1_mouse_y(*(s->w))) != y) {
        s->y+=y_tmp-y;
        if (s->y < s->y1) s->y = s->y1;
        if ((s->y1)+(s->length)+(s->y)+2 > s->y2) s->y=(s->y2)-(s->y1)-(s->length)-2;
	/*        if (s->y > s->y2-(s->length)-1) s->y=s->y2-(s->length)-1;*/
        y=y_tmp;
        if (Get_Length(first) < 8) *(s->scroll_var)=0;
        else *(s->scroll_var)=((s->y)-(s->y1)) / Get_Length(first);
        Draw_Scroll(s,first);
      }
    }
  } else {
    while (cs1_mouse_button(*(s->w),cs1_left_button)) {
      if ((y_tmp=cs1_mouse_y(*(s->w))) > y) {
        s->y += 5;
	/*        if (s->y > s->y2-(s->length)-1) s->y=s->y2-(s->length)-1;*/
        if ((s->y1)+(s->length)+(s->y)+2 > s->y2) s->y=(s->y2)-(s->y1)-(s->length)-2;
        y=y_tmp;
        if (Get_Length(first) < 8) *(s->scroll_var)=0;
        else *(s->scroll_var)=((s->y)-(s->y1)) / Get_Length(first);
        Draw_Scroll(s,first);
      } else if (y_tmp != y) {
        s->y -= 5;
        if (s->y < s->y1) s->y = s->y1;
        y=y_tmp;
        if (Get_Length(first) < 8) *(s->scroll_var)=0;
        else *(s->scroll_var)=((s->y)-(s->y1)) / Get_Length(first);
        Draw_Scroll(s,first);
      }        
    }
  }
  

  /* Draw_Entries(*(s->w),first,ww,wh);*/
}

int On_Scroll(SCROLL_BAR *b,int x,int y) {
  int c,d;
  if ((b->x1)<(b->x2)) c=(x<b->x2 && x>b->x1);
  else c=(x>b->x2 && x<b->x1);
  if ((b->y1)<(b->y2)) d=(y<b->y2 && y>b->y1);
  else d=(y>b->y2 && y<b->y1);
  return (c && d);
}
 

int In_List(int x, int y,int ww,int wh) {
  int c,d;
  
  c=(x>=EDGE+3 && x<=ww-EDGE-3);
  d=(y>EDGE+3 && y<=ww-EDGE-3);

  return (c && d);
}

void Draw_Entries(CS1_Window w,ENTRY *first,int ww,int wh) {
  int n;
  ENTRY *work=first;

  for (n=0;n<3;n++) {
    cs1_set_color("black");
    cs1_draw_line(w,EDGE+n,EDGE+n,ww-EDGE-n,EDGE+n);
    cs1_draw_line(w,EDGE+n,EDGE+n,EDGE+n,wh-EDGE-n);
    cs1_set_color("white");
    cs1_draw_line(w,ww-EDGE-n,EDGE+n,ww-EDGE-n,wh-EDGE-n);
    cs1_draw_line(w,EDGE+n,wh-EDGE-n,ww-EDGE-n,wh-EDGE-n);
  }  
  cs1_set_color("gray80");
  cs1_fill_box(w,EDGE+3,EDGE+3,ww-EDGE-3,wh-EDGE-3);
  cs1_set_color("black");
  cs1_draw_line(w,ww/2,EDGE+6,ww/2,wh-EDGE-6);

  for (n=0;n<yscroll && work!=NULL;n++,work=work->next);

  for (n=0;n<8 && work!=NULL;work=work->next) {
    if (work->in_search==YES) {
      if (n+yscroll==selected) {
        cs1_set_color("black");
        cs1_fill_box(w,EDGE+3,EDGE+5+n*HEIGHT,ww-EDGE-3,EDGE+5+(n+1)*HEIGHT);
        cs1_set_color("white");
        cs1_draw_line(w,ww/2,EDGE+5+n*HEIGHT,ww/2,EDGE+5+(n+1)*HEIGHT);
        cs1_printf(w,EDGE+5,EDGE+5+(n+1)*HEIGHT-2,"%s",work->name);
        cs1_printf(w,ww/2+4,EDGE+5+(n+1)*HEIGHT-2,"%04d",work->number);
       } else {
        cs1_set_color("black");
        cs1_printf(w,EDGE+5,EDGE+5+(n+1)*HEIGHT-2,"%s",work->name);
        cs1_printf(w,ww/2+4,EDGE+5+(n+1)*HEIGHT-2,"%04d",work->number);
      }
      n++;
    }
  }
}

ENTRY *new_entry(char *s,int i) {
  ENTRY *e;
  
  if ((e=(ENTRY *)malloc(sizeof(ENTRY)))==NULL) exit();
  e->next=NULL;
  e->number=i;
  e->in_search=YES;
  strcpy(e->name,s);

  return(e);
}

ENTRY *add_entry(void) {
  ENTRY *e;
  char s[256];
  int i;
  
  cs1_scanf("Person's Name:","%[^\n]",s);
  cs1_scanf("Phone Number:","%d",&i);
  i %= 10000;

  e=new_entry(s,i);

  return e;
}

ENTRY *delete_entry(ENTRY *first,int selected,ENTRY **end) {
  ENTRY *last,*work;
  int n;

  if (selected != 0) {
    for (n=0,work=first;n<selected && work!= NULL;n++){
      last=work;
      work=work->next;
    }

    if (n==selected) {
      /*    if (last->next != work) printf("The ponter's aren't right...\n");*/
      if (work->next==NULL) *end=last;
      last->next=work->next;
      free(work);
    }
  } else {
    last=first;
    first=first->next;
    free(last);
  }   

  return (first);
}

int Get_Length(ENTRY *e) {
  int n;
  ENTRY *work;

  for (n=0,work=e;work!=NULL;work=work->next,n++);

  return (n);
}

void Search (ENTRY *first) {
  ENTRY *work;
  char s[256];

  s[0]=-1;
  cs1_scanf("Search for?","%s",s);

  for (work=first;work != NULL;work=work->next) {
    /* if (!strcasecmp(work->name,s) || s[0]==-1) {*/
    if (matches(work->name,s) || s[0]==-1) {
      work->in_search=YES;
    } else {
      work->in_search=NO;
    }
  }
}


/* strstr(s1,s2) - Returns first pointer to s2 in s1 or NULL */

void Sort_Entries(ENTRY *first) {
  char tname[30];
  int  tnum, tis;
  ENTRY *work1, *work2;

  for(work1=first;work1 != NULL; work1=work1->next) {
    for (work2=work1->next; work2 != NULL; work2=work2->next) {
      if (strcasecmp(work1->name,work2->name) > 0) {
        strcpy(tname,work2->name);
        tnum=work2->number;
        tis=work2->in_search;
        strcpy(work2->name,work1->name);
        work2->number=work1->number;
        work2->in_search=work1->in_search;
        strcpy(work1->name,tname);
        work1->number=tnum;
        work1->in_search=tis;
      }
    }
  }
}

int matches(char *s1,char *s2) {
  char *p;
  
  if (strstr(s1,s2) != NULL) return (1);

  for (p=s1;p<s1+strlen(s1);p++) {
    if (Start_String(p,s2)) return (1);
  }

  return (0);
}

int Start_String(char *string1, char *string2) {
  char *p1,*p2;

  for (p1=string1,p2=string2;p2<string2+strlen(string2);p1++,p2++) {
    if (*p2 == '*') {
      return(matches(p1,p2+1));
    } else if (*p2 != '?') {
      if (tolower(*p2) != tolower(*p1)) return(0);
    }
  }
  return (1);
}


