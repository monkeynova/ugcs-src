#include <stdio.h>
#include <local/cs1.h>
#include <math.h>
#include <stdlib.h>

#define MAX 65535
#define MAXSPRAY 3
#define MAXMODE 5

void KP_Set_Color(int);
void KP_Draw_Circle(CS1_Window,int,int);
void KP_Draw_Square(CS1_Window,int,int);
void KP_Draw_Text(CS1_Window,int,int);
void Draw_Line(CS1_Window, int, int);
void Draw_Spray(CS1_Window, int, int);
void Draw_Can(CS1_Window,int,int);
void Draw_Palette(CS1_Window p);
void Draw_Sizer(CS1_Window s);
void Draw_Mode(CS1_Window m);
void DM_Color(int);
void Set_Mode(CS1_Window,int);
void Set_Size(CS1_Window,int);
void KP_Set_Palette(CS1_Window p,int y);

unsigned int colors[8][3]={
     {MAX,MAX,MAX},
     {0,0,MAX},
     {0,MAX,0},
     {MAX,0,0},
     {0,0,0},
     {MAX,MAX,0},
     {MAX,0,MAX},
     {0,MAX,MAX}
};

int color;
int radius=3;
int mode=1;

void main() {
  CS1_Window mw, palette,size,modew;

  size=cs1_make_window("white",100,370,170,50);
  modew=cs1_make_window("white",50,100,50,170);
  mw=cs1_make_window("white",100,100,270,270);
  palette=cs1_make_window("gray40",370,100,50,270);

  color=0;
  mode=1;
  radius=3; 

  Draw_Palette(palette);
  Draw_Sizer(size);
  Draw_Mode(modew);

  KP_Set_Color(color);
  cs1_fill_box(palette,0,1,50,29);
  while(cs1_inkey() != 13) {
    if (cs1_mouse_button(mw,cs1_left_button)) {
      switch (mode) {
        case 1:
         {
         KP_Draw_Circle(mw,cs1_mouse_x(mw),cs1_mouse_y(mw));
         } break;
        case 2:
         { 
         KP_Draw_Square(mw,cs1_mouse_x(mw),cs1_mouse_y(mw));
         } break;
        case 3:
         {
         KP_Draw_Text(mw,cs1_mouse_x(mw),cs1_mouse_y(mw));
         } break;
        case 4:
         {
         Draw_Line(mw,cs1_mouse_x(mw),cs1_mouse_y(mw));
         } break;
        case 5:
         {
         Draw_Spray(mw,cs1_mouse_x(mw),cs1_mouse_y(mw));
         } break;
      }  
  }
  if (cs1_mouse_button(modew,cs1_left_button)) Set_Mode(modew,cs1_mouse_y(modew));
  if (cs1_mouse_button(palette,cs1_left_button)) KP_Set_Palette(palette,cs1_mouse_y(palette));
    if (cs1_mouse_button(size,cs1_left_button)) Set_Size(size,cs1_mouse_x(size));
  }

}

void KP_Set_Palette(CS1_Window p,int y) {
  int t;
  for (t=0;t<8;t++) {
    if ((t+1)*30+1<=y && (t+2)*30-1>=y) {
      color=t;
    }
  }
  Draw_Palette(p);
}

void Draw_Palette(CS1_Window p) {
  int t;
  for (t=0;t<8;t++) {
    KP_Set_Color(t);
    cs1_fill_box(p,0,(t+1)*30+1,50,(t+2)*30-1);
  }
  KP_Set_Color(color);
  cs1_fill_box(p,5,5,45,25);
  
}

void Set_Size(CS1_Window s, int x) {
  int t;
  for (t=1;t<=8;t++) {
    if ((t-1)*20<=x && t*20>x) radius=t; 
    /*printf("%d\n",radius);*/
  }
  Draw_Sizer(s);
}

void Draw_Sizer(CS1_Window s) {
  int t;

  for(t=1;t<=8;t++) {
    if (t==radius) cs1_set_color("red");
    else cs1_set_color("black");
    cs1_fill_circle(s,(t-1)*20+10,25,t);
  }
  KP_Set_Color(color);
}

void DM_Color(int t) {
  if (t==mode) cs1_set_color("red");
  else cs1_set_color("black");
}

void Set_Mode(CS1_Window m, int y) {
  int t;
  
  for (t=1;t<=MAXMODE;t++) {
    if ((t-1)*20<y && y<t*20) mode=t;
  }
 
  Draw_Mode(m);
}

void Draw_Mode(CS1_Window m) {
  int temp;
  temp=radius;
 
  radius=5;
 
  DM_Color(1); 
  KP_Draw_Circle(m,25,10);
  DM_Color(2);
  KP_Draw_Square(m,25,30);
  DM_Color(3);
  cs1_text_size(10);
  cs1_printf(m,20,50,"A");
  DM_Color(4);
  cs1_draw_line(m,35,65,20,75);
  DM_Color(5);
  Draw_Can(m,25,90);

  radius=temp;
  KP_Set_Color(color);
}

void KP_Set_Color(int c){
  cs1_set_rgb(colors[c][0],colors[c][1],colors[c][2]);
}

void KP_Draw_Circle(CS1_Window w,int x,int y) {
  cs1_fill_circle(w,x,y,radius);
}

void KP_Draw_Square(CS1_Window w,int x, int y) {
  cs1_draw_line(w,x-radius,y-radius,x+radius,y-radius);
  cs1_draw_line(w,x-radius,y-radius,x-radius,y+radius);
  cs1_draw_line(w,x-radius,y+radius,x+radius,y+radius);
  cs1_draw_line(w,x+radius,y+radius,x+radius,y-radius);

}

void KP_Draw_Text(CS1_Window w,int x,int y) {
  char string[256];
  printf("Enter Text: ");
  scanf("%s",string);
  
  /* cs1_scanf("Enter text","%s",string); */
  cs1_text_size(radius*2);
  cs1_printf(w,x,y,"%s",string);
}

void Draw_Line(CS1_Window w, int sx, int sy) {
  int x1,y1,x2,y2;
  float m,dx,dy;
  int x[4],y[4];
  int done=0;
 
  x1=sx;
  y1=sy;
  while(cs1_mouse_button(w,cs1_left_button));
  cs1_fill_circle(w,x1,y1,radius);
  while (!done) {
    if (cs1_mouse_button(w,cs1_left_button)) {
      x2=cs1_mouse_x(w);
      y2=cs1_mouse_y(w);
      m=(y2!=y1)?-(x1-x2)/(y1-y2):0;
      dx=1/sqrt(1+m*m);
      dy=m*dx;
      x[0]=x1+radius*dx;y[0]=y1+radius*dy;x[1]=x2+radius*dx;y[1]=y2+radius*dy;
      x[2]=x2-radius*dx;y[2]=y2-radius*dy;x[3]=x1-radius*dx;y[3]=y1-radius*dy;
      cs1_fill_array(w,4,x,y);
      x1=x2;
      y1=y2;
      cs1_fill_circle(w,x1,y1,radius);
      while(cs1_mouse_button(w,cs1_left_button));
    }
    if (cs1_mouse_button(w,cs1_right_button)) done=1; 
  }
  
}

void Draw_Can(CS1_Window w, int x, int y) {
  cs1_draw_line(w,x,y+radius,x,y-radius);
  cs1_draw_line(w,x,y+radius,x-radius,y+radius);
  cs1_draw_line(w,x-radius,y+radius,x-radius,y-radius);
  cs1_draw_line(w,x-radius,y-radius,x,y-radius);
  cs1_draw_line(w,x,y-radius/2,x-radius/2,y-radius/2);
  cs1_draw_line(w,x,y+radius/2,x-radius/2,y+radius/2);
  cs1_draw_line(w,x-radius/2,y-radius/2,x-radius/2,y+radius/2);
  cs1_draw_line(w,x,y-radius,x+radius/4,y-radius);
}

void Draw_Spray(CS1_Window w, int x, int y) {
  int t;
  int xp,yp;
  int theta,r; 
  
  for (t=0;t<MAXSPRAY;t++) {
    theta=rand()%360;
    r=rand()%radius;
    xp=r*cos(theta*M_PI/180);
    yp=r*sin(theta*M_PI/180);
    cs1_fill_circle(w,x+xp,y+yp,1);
  }

}


