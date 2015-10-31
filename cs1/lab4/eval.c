#include <stdio.h>
#include <math.h>

main(int argc, char *argv[]) {
  char string[80];
  int result;
  /* strcpy(string,"3*(5+7)+2");*/
  if (argc <2) {
   printf("Enter an expression. ");
   scanf("%s",string);
  } else {
   strcpy(string,argv[1]);
  }
  result=eval(string);
  printf("%s=%d\n",string,result);
}

eval(char *expr){
  int nums[80];
  char ops[80];
  char c;
  char temp_string[80];
  char numstr[80];
  int t,s;
  int line=0,neg=0,done=0;
  int sparens,smult,splus,temp_result;

  /* printf("%s\n",expr);*/

  /* Parse String */
  nums[0]=0;
  for (t=0;c=expr[t];t++) {
    if (nums[line]==0 && c=='-') {
      neg=1;
    } else if ('0' <= c && c <= '9') {
      if (neg) nums[line]=nums[line]*10-(c-'0');
      else nums[line]=nums[line]*10+(c-'0');
    } else if (is_op(c)) {
      ops[line]=c;
      line++;
      nums[line]=0;
      neg=0;
    } else if (c != ' ') {
      printf("Error in expression %s. Unknown character %c (%d)\n",expr,t+1,c);
      exit();
    }
  }
  ops[line]=0;

  /* Disp_Stack(nums,ops,line);*/

  /* Handle Parenthases */
  while(!done) {
    sparens=-1;
    for (t=0;t<line;t++) {
      if (ops[t]=='(') {
        sparens=t;
      } else if (ops[t]==')') {
        if (sparens==-1) {
	printf("Error with parenthases.\n");
	exit();
        }
        *temp_string='\0';
        for (s=sparens+1;s<=t;s++) sprintf(temp_string,"%s%d%c",temp_string,nums[s],ops[s]);
        temp_string[strlen(temp_string)-1]='\0';
        temp_result=eval(temp_string);
        ops[sparens]=ops[t+1];
        for (s=sparens+1;s<line-t+1;s++) {
	ops[s]=ops[(t-sparens)+s+1];
	nums[s]=nums[(t-sparens)+s+1];
        }
        nums[sparens]=temp_result;
        line-=(t-sparens)+1;
        /*Disp_Stack(nums,ops,line);*/
        t=line;
      }
    }
    if (sparens==-1) done=1;

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

  /* printf("%d\n",nums[0]);*/
  return (nums[0]);

}

is_op(char c) {
  char legal_ops[10];
  int legal_num;
  int t;
  strcpy(legal_ops,"+-*/^()");
  legal_num=strlen(legal_ops);
  for (t=0;t<legal_num;t++) if (c==legal_ops[t]) return(1);
  return(0);
}

Disp_Stack(int *nums,char *ops,int line) {
  int t;
  for (t=0;t<=line;t++) printf("%d | %c\n",nums[t],ops[t]);
  printf("\n");
}
