#include <stdio.h>
#include <local/cs1.h>
#include <math.h>

#define ROWS    10
#define COLUMNS 5
#define WIDTH   110
#define HEIGHT  15

void Show_Board(CS1_Window);
void Input(int,int);
void Error(char *);
int is_op(char);
float eval(char *);
void Parse(int,int);
int cs1_scanf(char *prompt,char *fmt,...);

double data[COLUMNS][ROWS];
int error=0;

void main() {
  CS1_Window mw;

  mw=cs1_make_window("white",100,100,(COLUMNS+1)*WIDTH,(ROWS+1)*HEIGHT);
  cs1_window_title(mw,"Peters Spreadsheet");  

  cs1_text_style(cs1_normal_style);
  cs1_set_rgb(0,0,0);
  Show_Board(mw);
  while (cs1_inkey() != 'q') {
    if (cs1_mouse_x(mw)>=WIDTH||cs1_mouse_y(mw)>=HEIGHT) {
      if (cs1_mouse_button(mw,cs1_left_button)) {
        Input(cs1_mouse_x(mw)/WIDTH-1,cs1_mouse_y(mw)/HEIGHT-1);
        Show_Board(mw);
      }
      if (cs1_mouse_button(mw,cs1_right_button)) {
        Parse(cs1_mouse_x(mw)/WIDTH-1,cs1_mouse_y(mw)/HEIGHT-1);
        Show_Board(mw);
      }
    }
  }
}

void Show_Board(CS1_Window w) {
  int t,s;
  
  cs1_set_color("white");
  cs1_fill_box(w,0,0,(COLUMNS+1)*WIDTH,(ROWS+1)*HEIGHT);
  cs1_set_color("black");

  for (t=0;t<COLUMNS;t++) {
    cs1_printf(w,(t+1)*WIDTH+2,HEIGHT-2,"     R%d",t);
  }
  for (t=0;t<ROWS;t++) {
    cs1_printf(w,2,(t+2)*HEIGHT-2,"      C%d",t);
  }
  for (t=1;t<COLUMNS+1;t++) {
    for (s=1;s<ROWS+1;s++) {
      cs1_draw_box(w,t*WIDTH,s*HEIGHT,(t+1)*WIDTH,(s+1)*HEIGHT);
      cs1_set_color("gray60");
      cs1_draw_box(w,t*WIDTH+1,s*HEIGHT+1,(t+1)*WIDTH-1,(s+1)*HEIGHT-1);
      cs1_set_color("gray80");
      cs1_draw_box(w,t*WIDTH+2,s*HEIGHT+2,(t+1)*WIDTH-2,(s+1)*HEIGHT-2);
      cs1_set_color("black");
      cs1_printf(w,t*WIDTH+2,(s+1)*HEIGHT-2,"%7g",data[t-1][s-1]);
    }
  }
}

#define OPS  11

void Input (int cellx,int celly) {
  int t,done,op;
  CS1_Window ow;
  char *ops[]={" + "," - "," * "," / ","New","SIN","COS","TAN","EXP","LN ","SQR"};
  float newn;

  ow=cs1_make_window("blue",120,120,50,300);
  cs1_window_title(ow,"Pick");

  for (t=0;t<OPS;t++) {
    cs1_set_color("gray70");
    cs1_fill_box(ow,10,t*(HEIGHT+10)+10,40,t*(HEIGHT+10)+HEIGHT+10);
    cs1_set_color("white");
    cs1_draw_line(ow,10,t*(HEIGHT+10)+10,10,t*(HEIGHT+10)+HEIGHT+10);
    cs1_draw_line(ow,10,t*(HEIGHT+10)+10,40,t*(HEIGHT+10)+10);
    cs1_set_color("black");
    cs1_draw_line(ow,40,t*(HEIGHT+10)+10,40,t*(HEIGHT+10)+HEIGHT+10);
    cs1_draw_line(ow,10,t*(HEIGHT+10)+HEIGHT+10,40,t*(HEIGHT+10)+HEIGHT+10);
    cs1_printf(ow,12,t*(HEIGHT+10)+HEIGHT+8,"%s",ops[t]);
  }

  done=0;
  while (!done) {
    if (cs1_mouse_button(ow,cs1_left_button)) {
      if (10<=cs1_mouse_x(ow) && 40>=cs1_mouse_x(ow)) {
        for (t=0;t<OPS;t++) {
          if (t*(HEIGHT+10)+10<cs1_mouse_y(ow) && t*(HEIGHT+10)+HEIGHT+10 >= cs1_mouse_y(ow)) {
            op=t;
            done=1;
          }
        }
      }
    }
  }

  t=op;
  cs1_set_color("black");
  cs1_draw_line(ow,10,t*(HEIGHT+10)+10,10,t*(HEIGHT+10)+HEIGHT+10);
  cs1_draw_line(ow,10,t*(HEIGHT+10)+10,40,t*(HEIGHT+10)+10);
  cs1_set_color("white");
  cs1_draw_line(ow,40,t*(HEIGHT+10)+10,40,t*(HEIGHT+10)+HEIGHT+10);
  cs1_draw_line(ow,10,t*(HEIGHT+10)+HEIGHT+10,40,t*(HEIGHT+10)+HEIGHT+10);

  if (op<5) {
    cs1_scanf("Enter the number","%f",&newn);
  }
  
  switch (op) {
    case 0: {
      data[cellx][celly]+=newn;
    } break;
    case 1: {
      data[cellx][celly]-=newn;
    } break;
    case 2: {
      data[cellx][celly]*=newn;
    } break;
    case 3: {
      if (newn==0) {
        Error("You should know better. Don't divide by 0.");
      } else data[cellx][celly]/=newn;
    } break;
    case 4: {
      data[cellx][celly]=newn;
    } break;
    case 5: {
      data[cellx][celly]=sin(data[cellx][celly]);
    } break;
    case 6: {
      data[cellx][celly]=cos(data[cellx][celly]);
    } break;
    case 7: {
      data[cellx][celly]=tan(data[cellx][celly]);
    } break;
    case 8: {
      data[cellx][celly]=exp(data[cellx][celly]);
    } break;
    case 9: {
      if (data[cellx][celly]>0) data[cellx][celly]=log(data[cellx][celly]);
      else Error("You REAL-ly can't take the natural log of non-positive numbers.");
    } break;
    case 10: {
      if (data[cellx][celly]>=0) data[cellx][celly]=sqrt(data[cellx][celly]);
      else Error("You REAL-ly can't take the square root of negative numbers.");
    } break;
  }
  
  cs1_remove_window(ow); 
}



void Error(char *message) {
  CS1_Window error;
  int ew,t;

  ew=(strlen(message)*WIDTH/12+20);

  error=cs1_make_window("red",200,200,ew,80);
  cs1_set_color("black");
  cs1_text_style(cs1_bold_style);
  cs1_printf(error,10,30,"%s",message);
  cs1_text_style(cs1_normal_style);
  cs1_printf(error,10,45,"No changes made.");

  cs1_set_color("gray70");
  cs1_fill_box(error,ew/2-15,58,ew/2+15,75);
  cs1_set_color("white");
  cs1_draw_line(error,ew/2-15,58,ew/2-15,75);
  cs1_draw_line(error,ew/2-15,58,ew/2+15,58);
  cs1_set_color("black");
  cs1_draw_line(error,ew/2+15,58,ew/2+15,75);
  cs1_draw_line(error,ew/2-15,75,ew/2+15,75);
  cs1_printf(error,ew/2-8,73,"OK");

  while(!cs1_mouse_button(error,cs1_left_button) || cs1_mouse_y(error)>75 || cs1_mouse_y(error)<58 || cs1_mouse_x(error)>ew/2+15 || cs1_mouse_x(error)<ew/2-15);
  cs1_set_color("black");
  cs1_draw_line(error,ew/2-15,58,ew/2-15,75);
  cs1_draw_line(error,ew/2-15,58,ew/2+15,58);
  cs1_set_color("white");
  cs1_draw_line(error,ew/2+15,58,ew/2+15,75);
  cs1_draw_line(error,ew/2-15,75,ew/2+15,75);
  
  for (t=0;t<1500000;t++);
  cs1_remove_window(error);
  cs1_inkey();
}

void Parse(int boxx,int boxy) {
  int t,s;
  int len,numlen;
  int rnum=0,cnum=0;
  float result;
  char temp_s1[256];
  char temp_s2[256];
  char str[256];
  cs1_scanf("Enter string to parse","%s",str);
  len=strlen(str);
  for (t=0;t<len;t++) {
    if (str[t] == 'R' || str[t] == 'r') {
      numlen=sscanf(str+t+1,"%d",&rnum);
      if (str[t+numlen+1] != 'C' && str[t+numlen+1] != 'c') {
        Error("Parse error on string.");
        return;
      }
      numlen+=sscanf(str+(t+numlen+2),"%d",&cnum)+1;
      for (s=0;s<t;s++) temp_s1[s]=str[s];
      temp_s1[s]=0;
      for (s=t+numlen+1;s<len;s++) temp_s2[s-t-numlen]=str[s];
      temp_s2[s-t-numlen]=0;
      sprintf(str,"%s%f%s",temp_s1,data[rnum][cnum],temp_s2+1);
      len=strlen(str);
    }
  }
  result=eval(str);

  if (error == 1) {
    error=0;
  } else {
    data[boxx][boxy]=result;
  }
}

float eval(char *expr){
  float nums[80];
  char ops[80];
  char c;
  char temp_string[80];
  int t,s;
  int line=0,neg=0,done=0;
  int sparens;
  float temp_result;

  /* Parse String */
  nums[0]=0;
  for (t=0;(c=expr[t]);t++) {
    if (nums[line]==0 && c=='-') {
      neg=1;
    } else if (('0' <= c && c <= '9') || c=='.') {
      sscanf(expr+t,"%f",&nums[line]);
      while (('0' <= expr[t] && expr[t] <= '9') || expr[t]=='.') t++;
      t--;
      if (neg) nums[line] = -nums[line];
    } else if (is_op(c)) {
      ops[line]=c;
      line++;
      nums[line]=0;
      neg=0;
    } else if (c != ' ') {
      Error("Parse Error on string");
      error=1;
      return 0;
    }
  }
  ops[line]=0;

  /* Handle Parenthases */
  sparens=0;
  for (t=0;t<line;t++) {
    if (ops[t]=='(') sparens++;
    if (ops[t]==')') sparens--;
  }
  if (sparens != 0) {
    Error("Error with parenthases.");
    error=1;
    return 0;
  }
  
  while(!done) {
    sparens=-1;
    for (t=0;t<line;t++) {
      if (ops[t]=='(') {
        sparens=t;
      } else if (ops[t]==')') {
        if (sparens==-1) {
	 Error("Error with parenthases.");
         error=1;
	 return 0;
        }
        *temp_string='\0';
        for (s=sparens+1;s<=t;s++) sprintf(temp_string,"%s%f%c",temp_string,nums[s],ops[s]);
        temp_string[strlen(temp_string)-1]='\0';
        temp_result=eval(temp_string);
        ops[sparens]=ops[t+1];
        for (s=sparens+1;s<line-t+1;s++) {
	  ops[s]=ops[(t-sparens)+s+1];
	  nums[s]=nums[(t-sparens)+s+1];
        }
        nums[sparens]=temp_result;
        line-=(t-sparens)+1;
        t=line;
      }
    }
    if (sparens==-1) done=1;
    if (t==line-1 && sparens != -1) {
      Error("Error with parenthases.");
      error=1;
      return 0;
      done=1;
    }
  }

  /* Handle Exponent */
  for (t=0;t<line;t++) {
    if (ops[t]=='^') {
      nums[t]=pow(nums[t],nums[t+1]);
      ops[t]=ops[t+1];
      for (s=t+1;s<line;s++) {
        nums[s]=nums[s+1];
        ops[s]=ops[s+1];
      }
      line--;
      t--;
    }
  }


  /* Handle Mult and Div */
  for (t=0;t<line;t++) {
    if (ops[t]=='*') nums[t]*=nums[t+1];
    else if (ops[t]== '/') nums[t] /= nums[t+1];
    if (ops[t]=='*' || ops[t]=='/') {
      ops[t]=ops[t+1];
      for (s=t+1;s<line;s++) {
        nums[s]=nums[s+1];
        ops[s]=ops[s+1];
      }
      line--;
      t--;
    }
  }

  /* Handle Add and Sub */
  for (t=0;t<line;t++) {
    if (ops[t]=='+') nums[t]+=nums[t+1];
    else if (ops[t]== '-') nums[t] -= nums[t+1];
    if (ops[t]=='+' || ops[t]=='-') {
      ops[t]=ops[t+1];
      for (s=t+1;s<line;s++) {
        nums[s]=nums[s+1];
        ops[s]=ops[s+1];
      }
      line--;
      t--;
    }
  }

  if (line != 0) {
    printf("Error processing string %s\n",expr);
    exit();
  }

  return (nums[0]);

}

int is_op(char c) {
  char legal_ops[10];
  int legal_num;
  int t;
  strcpy(legal_ops,"+-*/^()");
  legal_num=strlen(legal_ops);
  for (t=0;t<legal_num;t++) if (c==legal_ops[t]) return(1);
  return(0);
}
