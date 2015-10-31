#include <stdio.h>
#include <local/cs1.h>

#define TOTAL_MOVES 18
#define ERASE       0
#define DRAW        1
#define COLOR       "black"

void Next_Move(int *,int,int,int);
int Pegs(int *);
void Move(int,int,int *);
void unMove(int,int,int *);
void Disp_Board(int *,int,int);
void Draw_Row(CS1_Window,int,int,int,int *);

int moves[TOTAL_MOVES][3]={
  {0,1,3},
  {0,2,5},
  {1,3,6},
  {1,4,8},
  {2,4,7},
  {2,5,9},
  {3,4,5},
  {3,6,10},
  {3,7,12},
  {4,7,11},
  {4,8,13},
  {5,8,12},
  {5,9,14},
  {6,7,8},
  {7,8,9},
  {10,11,12},
  {11,12,13},
  {12,13,14} };

CS1_Window mw;

void main() {
  int board_start[15];
  int t;
  int free;
  
  mw=cs1_make_window("blue",0,100,700,200);

  for (free=0;free<15;free++) {
    /* printf("Start with %d open.\n",free);*/
    for (t=0;t<15;t++) board_start[t]=(t!=free);
    Next_Move(board_start,-1,0,1);
    /*Disp_Board(board_start,ERASE);*/
  }
}

void Next_Move(int board[15],int move,int sign,int depth) {
  int possible[TOTAL_MOVES*2];
  int t,key;
  /*int board[15];
  for (t=0;t<15;t++) board[t]=board_in[t];*/

  if (depth ==3 ) return;
  if (move != -1) {
    Move(move,sign,board);
    Disp_Board(board,DRAW,depth);
    cs1_set_color(COLOR);
    cs1_printf(mw,10,150,"Legal Move,%d,%d to %d",moves[move+(sign==1)*TOTAL_MOVES][0],moves[move+(sign==1)*TOTAL_MOVES][1],moves[move+(sign==1)*TOTAL_MOVES][2]);
    while (!(key=cs1_inkey()));
    if (key=='q') exit();
    cs1_set_color("blue");
    cs1_printf(mw,10,150,"Legal Move,%d,%d to %d",moves[move+(sign==1)*TOTAL_MOVES][0],moves[move+(sign==1)*TOTAL_MOVES][1],moves[move+(sign==1)*TOTAL_MOVES][2]);
  } else Disp_Board(board,DRAW,depth);

  if (depth != 2) {
  for (t=0;t<TOTAL_MOVES;t++) {
    if (board[moves[t][1]] && (board[moves[t][0]] || board[moves[t][2]]) && !(board[moves[t][0]] && board[moves[t][2]]) ) {
      if (board[moves[t][0]]) {
        possible[t]=1;
        possible[t+TOTAL_MOVES]=0;
      } else {
        possible[t]=0;
        possible[t+TOTAL_MOVES]=1;
      }
    } else {
      possible[t]=0;
      possible[t+TOTAL_MOVES]=0;
    }
  }
  
  for (t=0;t<TOTAL_MOVES;t++) {
    if (possible[t]) {
      Next_Move(board,t,1,depth+1);
    } else {
      cs1_set_color(COLOR);
      cs1_printf(mw,10,150,"Illegal Move,%d,%d to %d",moves[t][0],moves[t][1],moves[t][2]);
      while (!(key=cs1_inkey()));
      if (key=='q') exit();
       cs1_set_color("blue");
      cs1_printf(mw,10,150,"Illegal Move,%d,%d to %d",moves[t][0],moves[t][1],moves[t][2]);
      if (possible[t+TOTAL_MOVES]) {
        Next_Move(board,t,-1,depth+1);
      } else {
        cs1_set_color(COLOR);
        cs1_printf(mw,10,150,"Illegal Move,%d,%d to %d",moves[t][2],moves[t][1],moves[t][0]);
        while (!(key=cs1_inkey()));
        if (key=='q') exit();
	 cs1_set_color("blue");
        cs1_printf(mw,10,150,"Illegal Move,%d,%d to %d",moves[t][2],moves[t][1],moves[t][0]);
      }
    }
  }

  }
 
  while(!(key=cs1_inkey()));
  /*printf("About to Unmove...\n");*/
  if (depth != 1) unMove(move,sign,board);
  /*printf("UnMoved...\n");*/
  if (key=='q') exit();
  Disp_Board(board,ERASE,depth);
  /*printf("Erased board...\n");*/
}

int Pegs(int b[15]) {
  int t,sum=0;
  for (t=0;t<15;t++) {
    if (b[t]) sum++;
  }
  return(sum);
}

void Move(int move_num, int dir,int b[15]) {
  b[moves[move_num][1]]=0;
  if (dir == 1) {
    b[moves[move_num][0]]=0;
    b[moves[move_num][2]]=1;
  } else {
    b[moves[move_num][0]]=1;
    b[moves[move_num][2]]=0;
  }
}

void unMove(int move_num, int dir,int b[15]) {
  b[moves[move_num][1]]=1;
  if (dir == 1) {
    b[moves[move_num][0]]=1;
    b[moves[move_num][2]]=0;
  } else {
    b[moves[move_num][0]]=0;
    b[moves[move_num][2]]=1;
  }
}


#define RADIUS 5
#define PERROW 8

void Disp_Board(int board[15], int status, int depth) {
  int position;
  int y=10;
  depth--;
  position=(depth%PERROW+1)*75-25;
  y+=75*(int)(depth/PERROW);
  if (status!=ERASE) {
    Draw_Row(mw,4,y,position,board);
  } else {
    cs1_set_color("blue");
    cs1_fill_box(mw,position-7*RADIUS,y-RADIUS*2,position+12*RADIUS,y+250+RADIUS*2);
  }
}

void Draw_Row(CS1_Window mw, int t, int y,int position,int *board) {
  int s;
  int n=0;

  for (s=1;s<=t;s++) n+=s;
  if (t==-1) return;
  for (s=0;s<=t;s++) {
    if (board[n]==0) {
      cs1_set_color("white");
      cs1_fill_circle(mw,2*RADIUS*s-RADIUS*t+position,10*t+y,RADIUS);
    } else {
      cs1_set_color("red");
      cs1_fill_circle(mw,2*RADIUS*s-RADIUS*t+position,10*t+y,RADIUS);
    }
    cs1_set_color("black");
    cs1_draw_circle(mw,2*RADIUS*s-RADIUS*t+position,2*RADIUS*t+y,RADIUS);
    n++;
  }
  Draw_Row(mw,t-1,y,position,board);
}
